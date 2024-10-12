#include <iostream>
using namespace std;

template <class T>
class Pila {
private:
    struct Nodo {
        T valor;
        Nodo* next;
    };
    Nodo* top;

public:
    Pila() : top(nullptr) {}

    void push(T valor) {
        Nodo* nuevoNodo = new Nodo;
        nuevoNodo->valor = valor;
        nuevoNodo->next = top;
        top = nuevoNodo;
    }

    bool pop() {
        if (top == nullptr) {
            cout << "Pila vacía\n";
            return false;
        }
        Nodo* temp = top;
        top = top->next;
        delete temp;
        return true;
    }

    void print() const {
        Nodo* temp = top;
        while (temp != nullptr) {
            cout << temp->valor << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~Pila() {
        while (top != nullptr) {
            pop();
        }
    }
};

int main() {
    Pila<int> pilaEnteros;
    pilaEnteros.push(1);
    pilaEnteros.push(2);
    pilaEnteros.push(3);
    pilaEnteros.push(4);
    pilaEnteros.push(5);
    pilaEnteros.print();
    pilaEnteros.pop();
    pilaEnteros.print();

    return 0;
}
