#include <iostream>
using namespace std;

template <class T>
struct nodo {
    T valor;
    nodo<T>* next;

    nodo(T v, nodo <T>* n = NULL) {
        valor = v;
        next = n;
    }
};

template <class T>
struct Asc {
    bool operator()(T a, T b) {
        return a < b;
    }
};

template <class T>
struct Desc {
    bool operator()(T a, T b) {
        return a > b;
    }
};

template <class T, class U>
struct LE {
    nodo <T>* head;
    U orden;

    LE() : head(nullptr) {}  // Inicializar head a nullptr

    void add(T v) {
        nodo<T>* new_nodo = new nodo<T>(v);
        if (!head || orden(v, head->valor)) {
            new_nodo->next = head;
            head = new_nodo;
            return;
        }

        nodo<T>* prev = nullptr;
        nodo<T>* current = head;
        while (current && !orden(v, current->valor)) {
            prev = current;
            current = current->next;
        }

        new_nodo->next = current;
        if (prev) {
            prev->next = new_nodo;
        }
    }

    void del(T v) {
        if (!head) {
            cout << "La lista está vacía" << endl;
            return;
        }

        // Caso en que el nodo a eliminar es el primero
        if (head->valor == v) {
            nodo<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        nodo<T>* prev = nullptr;
        nodo<T>* current = head;
        while (current && current->valor != v) {
            prev = current;
            current = current->next;
        }

        if (!current) {
            cout << "El valor " << v << " no existe en la lista" << endl;
            return;
        }

        prev->next = current->next;
        delete current;
    }

    void print() {
        nodo <T>* recorre = head;
        if (!head) {
            cout << "La lista está vacía" << endl;
        }
        else {
            while (recorre) {
                cout << recorre->valor << " -> ";
                recorre = recorre->next;
            }
            cout << "NULL" << endl;
        }
    }
};

int main() {
    LE<int, Asc<int>> listaAscInt;
    listaAscInt.add(10);
    listaAscInt.add(5);
    listaAscInt.add(15);
    listaAscInt.add(7);
    cout << "Lista Ascendente de Enteros:" << endl;
    listaAscInt.print();

    cout << "Eliminando el valor 10 de la lista de enteros:" << endl;
    listaAscInt.del(10);
    listaAscInt.print();
    cout << endl;


    LE<int, Desc<int>> listaDescInt;
    listaDescInt.add(10);
    listaDescInt.add(5);
    listaDescInt.add(15);
    listaDescInt.add(7);
    cout << "Lista Descendente de Enteros:" << endl;
    listaDescInt.print();
    cout << endl;


    LE<string, Asc<string>> listaAscString;
    listaAscString.add("banana");
    listaAscString.add("apple");
    listaAscString.add("cherry");
    listaAscString.add("date");
    cout << "Lista Ascendente de Strings:" << endl;
    listaAscString.print();

    cout << "Eliminando 'banana' de la lista de strings:" << endl;
    listaAscString.del("banana");
    listaAscString.print();
    cout << endl;


    LE<string, Desc<string>> listaDescString;
    listaDescString.add("banana");
    listaDescString.add("apple");
    listaDescString.add("cherry");
    listaDescString.add("date");
    cout << "Lista Descendente de Strings:" << endl;
    listaDescString.print();
    cout << endl;


    LE<char, Asc<char>> listaAscChar;
    listaAscChar.add('d');
    listaAscChar.add('a');
    listaAscChar.add('c');
    listaAscChar.add('b');
    cout << "Lista Ascendente de Chars:" << endl;
    listaAscChar.print();

    cout << "Eliminando 'c' de la lista de chars:" << endl;
    listaAscChar.del('c');
    listaAscChar.print();
    cout << endl;

    LE<char, Desc<char>> listaDescChar;
    listaDescChar.add('d');
    listaDescChar.add('a');
    listaDescChar.add('c');
    listaDescChar.add('b');
    cout << "Lista Descendente de Chars:" << endl;
    listaDescChar.print();

    return 0;
}