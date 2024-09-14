#include <iostream>
#include <algorithm>

using namespace std;


template <class O, class T>
void Bubble(O begin, O end, T comp) {
    bool sigue = true;
    while ((begin < end) && sigue) {
        sigue = false;
        for (O it = begin; it < end - 1; ++it) {
            if (comp(*(it + 1), *it)) {
                swap(*it, *(it + 1));
                sigue = true;
            }
        }
    }
}

template <class T>
struct ASC {
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

template <class T>
struct DESC {
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

int main() {
    int A[6] = { 6, 5, 4, 3, 2, 1 };

    Bubble(A, A + 6, ASC<int>());

    cout << "Ascendente: ";
    for (int i : A) {
        cout << i << ' ';
    }
    cout << endl;

    Bubble(A, A + 6, DESC<int>());

    cout << "Descendente: ";
    for (int i : A) {
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}