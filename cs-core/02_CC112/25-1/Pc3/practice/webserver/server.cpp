#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace std;

const std::string RESPONSE =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: application/json\r\n"
    "Connection: close\r\n\r\n"
    "{\"message\":\"Hello from C++ server!\",\"status\":\"success\"}\n";

int main() {
  try {
    io_context context;
    tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(), 8080));

    std::cout << "Server running on port 8080..." << std::endl;

    while (true) {
      tcp::socket socket(context);
      acceptor.accept(socket);

      write(socket, buffer(RESPONSE));
      socket.shutdown(tcp::socket::shutdown_send);
    }
  } catch (std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
