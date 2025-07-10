//List enlazada para modelar un historial de navegacion
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class Node{
    public:

    string url;
    int time;
    Node* next;

    Node(string url, int time){
        this->url = url;
        this->time= time;
        this->next = nullptr;
    }

    void visitarPagina(string url, int time){
        cout << "Visitando pagina: " << url << "(" << time << " segundos)" << endl;
        Node* head = this->next;

        while (head->next != nullptr){
            head  = head->next;
        }

        Node newNode(url, time);
        head->next = &newNode;
        cout << "Visita registrada: " << url << "(" << time << " segundos)";
    }

    void mostrarHistorial(){
        cout << "Historial de navegacion: ";
        Node* head = this->next;

        while (head->next != nullptr){
            cout << "URL: " << this->url << "| Tiempo de visita? " << this->time << " s";
            head  = head->next;
        }
    }

    void liberarHistorial(){
        cout << "Limpiar historial de  navegacion: ";
        this->next = nullptr;
        cout << "Historial de navegacion eliminado." << endl;
    }
};

int main(){
    Node page("https://openai.com", 120);

    page.mostrarHistorial();

    page.visitarPagina("https://wikipedia.org", 300);

    page.mostrarHistorial();

    return 0;
}