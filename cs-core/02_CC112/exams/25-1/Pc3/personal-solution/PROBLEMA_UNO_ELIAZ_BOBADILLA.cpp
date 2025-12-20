#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

struct WebPage{
	int id;
	string url;
	string title;
	string date;
	string time;
};

void printMenu(){
	cout << "-- HISTORIAL DE NAVEGACION WEB --" << endl;
	cout << "1. Agregar entrada al historial" << endl;
	cout << "2. Mostrar historial completo" << endl;
	cout << "3. Eliminar una entrada por ID" << endl;
	cout << "4. Buscar visitas por ULR" << endl;
	cout << "5. Limpiar historial completo" << endl;
	cout << "0. Salir" << endl;
}

int getOption(){
	printMenu();
	int option;
	cin >> option;
	return option;
}

WebPage createPage(int id){
	WebPage page;

	page.id = id;

	cout << "Ingrese la URL: " ;
	cin >> page.url;

	cout << "Titulo de la pagina: " ;
	cin >> page.title;


	cout << "Ingrese la Fecha: " ;
	cin >> page.date;

	cout << "Ingrese la hora: " ;
	cin >> page.time;

	return page;
}

void printHistorialRow(WebPage currentPage){
	cout << "ID: " << currentPage.id << " / " << "URL: " << currentPage.url << " Titulo: " << currentPage.title << " / " << "Fecha: " << currentPage.date << " / " << "Hora: " << currentPage.time << endl;

}

void printHistorial(WebPage* pages, int size){
	if (size == 0){
		cout << "Aun no hay elementos!" << endl;
		return;
	}

	cout << "--- Historial de navegacion --" << endl;

	for (int j = 0; j < size; j ++){
		WebPage currentPage = pages[j];
		printHistorialRow(currentPage);
	}

	cout << "---------------" << endl;
}



int main(){
	WebPage *pages = nullptr;
	int size = 0;
	int id = 0;
	int firstRun = true;


	while(true){
		if (!firstRun){
			cout << endl;
		} else{
			firstRun = false;
		}

		int userOption = getOption();
		cout << endl;

		cout << "Opcion: " << userOption << endl;

		if (userOption == 0){

			cout << "Saliendo..." << endl;
			break;
		}

		WebPage page;

		if  (userOption == 1){
			id++;
			page = createPage(id);

			if (size  == 0){
				pages = new WebPage[1];
				pages[0] = page;
				size = 1;
			}else{
				WebPage *newPages = new WebPage[size +1];

				for (int j = 0; j < size; j++){
					newPages[j] = pages[j];
				}

				newPages[size] = page;
				delete[] pages;
				pages = newPages;
				size++;
			}

		} else if (userOption == 2){
			printHistorial(pages, size);
		}else if (userOption==4){

			if (size == 0){
				cout << "Cree un registro antes de buscar!" << endl;
			}else{
				string needleURL;
				cout << "Ingrese la URL a buscar: ";
				cin >> needleURL;
				cout << endl;
	
				for (int j = 0; j < size ; j++){
					auto currentPage = pages[j];
	
					if (currentPage.url == needleURL){
						printHistorialRow(currentPage);
						break;
					}
				}	
			}
		}
		 else if (userOption == 3){
			if (size == 0){
				cout << "Crea algun registro antes de intentar borrar!";
			}else{
				int idToDelete;
				cout << "Ingresa el ID de la entrada a eliminar: ";
				cin >> idToDelete;
				cout << endl;


				bool itIsInside = false;

				for (int i = 0; i < size; i++){
					auto currentPage = pages[i];

					if (currentPage.id == idToDelete){
						itIsInside = true;
					}
				}

				if (!itIsInside){
					cout << "El ID no se encuentra dentro del historial!!!" << endl;
				}else{

				auto *newPages = new WebPage[size - 1];

				int newCounter = 0;

				for(int j =0; j < size ; j++){
					auto currentPage = pages[j];

					if (currentPage.id == idToDelete){
						continue;
					}

					newPages[newCounter] = currentPage;
					newCounter++;
				}

				delete[] pages;
				pages = newPages;
				size = size - 1;

				cout << "Entrada eliminada exitosamente";
				}
			}
		} else if (userOption == 5){
			if (size == 0){
				cout << "No hay nada que eliminar!!" << endl;
			} else{
				delete[] pages;
				size = 0;
				pages = nullptr;
			}
		}else{
			cout << "Esa opcion no es valida!" << endl;
		}
	}

	if (size > 0){
		delete[] pages;
	}

	cout << "Hasta luego!" << endl;
	return 0;
}
