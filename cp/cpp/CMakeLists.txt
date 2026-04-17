cmake_minimum_required(VERSION 3.21)
project(cp_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.6.0
)
FetchContent_MakeAvailable(Catch2)

function(enable_common_warnings target_name)
	if(MSVC)
		target_compile_options(${target_name} PRIVATE /W4 /permissive-)
	else()
		target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic)
	endif()
endfunction()

function(target_name_from_source out_var source_file suffix_to_strip)
	get_filename_component(file_stem ${source_file} NAME_WE)
	string(REGEX REPLACE "${suffix_to_strip}$" "" target_name ${file_stem})
	set(${out_var} ${target_name} PARENT_SCOPE)
endfunction()

function(create_algorithm_libraries out_var)
	file(GLOB ALL_CPP CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
	set(algo_targets)

	foreach(source_file IN LISTS ALL_CPP)
		get_filename_component(file_name ${source_file} NAME)
		if(file_name MATCHES "_test\\.cpp$" OR file_name MATCHES "_bench\\.cpp$")
			continue()
		endif()

		get_filename_component(target_name ${source_file} NAME_WE)
		add_library(${target_name} ${source_file})
		target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
		enable_common_warnings(${target_name})
		list(APPEND algo_targets ${target_name})
	endforeach()

	set(${out_var} ${algo_targets} PARENT_SCOPE)
endfunction()

include(CTest)
include(Catch)

create_algorithm_libraries(ALGORITHM_TARGETS)

# Auto-discover test files matching *_test.cpp.
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*_test.cpp")
foreach(test_source IN LISTS TEST_SOURCES)
	get_filename_component(test_target ${test_source} NAME_WE)
	target_name_from_source(algo_target ${test_source} "_test")
	if(NOT TARGET ${algo_target})
		message(FATAL_ERROR "No algorithm source found for ${test_target}. Expected ${algo_target}.cpp")
	endif()

	add_executable(${test_target} ${test_source})
	target_link_libraries(${test_target} PRIVATE ${algo_target} Catch2::Catch2WithMain)
	enable_common_warnings(${test_target})
	catch_discover_tests(${test_target})
endforeach()

# Auto-discover benchmark files matching *_bench.cpp.
file(GLOB BENCH_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*_bench.cpp")
foreach(bench_source IN LISTS BENCH_SOURCES)
	get_filename_component(bench_target ${bench_source} NAME_WE)
	target_name_from_source(algo_target ${bench_source} "_bench")
	if(NOT TARGET ${algo_target})
		message(FATAL_ERROR "No algorithm source found for ${bench_target}. Expected ${algo_target}.cpp")
	endif()

	add_executable(${bench_target} ${bench_source})
	target_link_libraries(${bench_target} PRIVATE ${algo_target})
	enable_common_warnings(${bench_target})
endforeach()
