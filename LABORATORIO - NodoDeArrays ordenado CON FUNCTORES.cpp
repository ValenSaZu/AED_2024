#include <iostream>

using namespace std;

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
struct nodoArray {
    T Array[5] = { 0 };
    T* puntero = Array;
    nodoArray<T, U>* next = nullptr;
    U comp;

    nodoArray(nodoArray<T, U>* p = NULL) : next(p) {}

    bool find(T valor, T*& pos) {
        pos = Array;
        while (pos < puntero && comp(*pos, valor)) {
            pos++;
        }
        return pos < puntero && *pos == valor;
    }

    T add(T valor) {
        T* pos = nullptr;
        if (!find(valor, pos)) {
            T val = 0;
            if (puntero == Array + 5) {
                val = Array[4];
                for (T* ult_num = Array + 4; ult_num > pos; ult_num--) {
                    *ult_num = *(ult_num - 1);
                }
                *pos = valor;
                return val;
            } else {
                for (T* ult_num = puntero; ult_num > pos; ult_num--) {
                    *ult_num = *(ult_num - 1);
                }
                *pos = valor;
                puntero++;
                return 0;
            }
        } else {
            cout << "El valor " << valor << " ya existe" << endl;
            return 0;
        }
    }

    bool remove(T valor) {
        T* pos = nullptr;
        if (find(valor, pos)) {
            for (T* ult_num = pos; ult_num < puntero - 1; ult_num++) {
                *ult_num = *(ult_num + 1);
            }
            puntero--;
            return true;
        } else {
            cout << "El valor " << valor << " no existe" << endl;
            return false;
        }
    }

    bool isEmpty() const {
        return puntero == Array;
    }

    void print() {
        cout << "[";
        for (T* i = Array; i < puntero; i++) {
            if (i != puntero - 1)
                cout << *i << "->";
            else
                cout << *i;
        }
        cout << "]";
    }
};

template <class T, class U>
struct ListaEnlazadaArray {
    nodoArray<T, U>* head = nullptr;

    bool find(T valor, T*& pos, nodoArray<T, U>*& nodoEncontrado) {
        nodoArray<T, U>* current = head;
        while (current != nullptr) {
            if (current->find(valor, pos)) {
                nodoEncontrado = current;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void add(T valor) {
        T* pos = nullptr;
        nodoArray<T, U>* nodoEncontrado = nullptr;

        if (find(valor, pos, nodoEncontrado)) {
            cout << "El valor " << valor << " ya existe en la lista." << endl;
            return;
        }
        if (head == nullptr) {
            head = new nodoArray<T, U>();
            head->add(valor);
            return;
        }

        nodoArray<T, U>* current = head;

        while (current != nullptr) {
            T valorDesbordado = current->add(valor);

            if (valorDesbordado == 0) {
                return;
            }

            if (current->next == nullptr) {
                nodoArray<T, U>* new_nodo = new nodoArray<T, U>();
                current->next = new_nodo;
                new_nodo->add(valor);
                return;
            }
            current = current->next;
            valor = valorDesbordado;
        }
    }

    void remove(T valor) {
        T* pos = nullptr;
        nodoArray<T, U>* nodoEncontrado = nullptr;

        if (!find(valor, pos, nodoEncontrado)) {
            cout << "El valor " << valor << " no existe en la lista." << endl;
            return;
        }

        if (nodoEncontrado->remove(valor)) {
            nodoArray<T, U>* current = nodoEncontrado;
            nodoArray<T, U>* nextNodo = current->next;

            while (nextNodo != nullptr) {

                T* posNext = nextNodo->Array;
                T primerValorSiguienteNodo = *posNext;

                nextNodo->remove(primerValorSiguienteNodo);

                current->add(primerValorSiguienteNodo);

                current = nextNodo;
                nextNodo = nextNodo->next;
            }

            if (current->isEmpty()) {
                if (current == head) {
                    head = head->next;
                    delete current;
                }
                else {
                    nodoArray<T, U>* prev = head;
                    while (prev->next != current) {
                        prev = prev->next;
                    }
                    prev->next = current->next;
                    delete current;
                }
            }
        }
    }

    void print() {
        nodoArray<T, U>* current = head;
        while (current != nullptr) {
            current->print();
            cout << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    ListaEnlazadaArray<int, Desc<int>> lista;

    lista.add(50);
    lista.add(40);
    lista.add(30);
    lista.add(20);
    lista.add(10);
    lista.add(5);

    cout << "Lista después de agregar valores:" << endl;
    lista.print();

    lista.add(45);
    cout << "Lista después de agregar 45:" << endl;
    lista.print();

    cout << "Eliminando el valor 30:" << endl;
    lista.remove(30);
    lista.print();

    cout << "Intentando eliminar el valor 60 (no existe):" << endl;
    lista.remove(60);
    lista.print();

    cout << "Eliminando el valor 10:" << endl;
    lista.remove(10);
    lista.print();

    return 0;
}
