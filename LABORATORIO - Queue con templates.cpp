#include <iostream>
using namespace std;

template <class T>
class Queue {
private:
    struct Nodo {
        T valor;
        Nodo* next;
    };
    Nodo* head;
    Nodo* tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}

    void push(T valor) {
        Nodo* newNodo = new Nodo;
        newNodo->valor = valor;
        newNodo->next = nullptr;

        if (head == nullptr) {
            head = tail = newNodo;
        }
        else {
            tail->next = newNodo;
            tail = newNodo;
        }
    }

    bool pop() {
        if (head == nullptr) {
            cout << "Queue vacía\n";
            return false;
        }
        Nodo* temp = head;
        head = head->next;

        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
        return true;
    }

    void print() const {
        Nodo* temp = head;
        while (temp != nullptr) {
            cout << temp->valor << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~Queue() {
        while (head != nullptr) {
            pop();
        }
    }
};

int main() {
    Queue<int> Queue;
    Queue.push(1);
    Queue.push(2);
    Queue.push(3);
    Queue.print();
    Queue.pop();
    Queue.print();
    return 0;
}