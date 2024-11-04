#include <iostream>
#include <thread>
#include <vector>
#include <random>

using namespace std;

template <class T>
struct ASC {
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

template <class T, class U>
struct MergeSort {
    U comp;

    vector<T> Sort(const vector<T>& A) {
        size_t lon = A.size();
        if (lon <= 1) return A;

        vector<T> izq(A.begin(), A.begin() + lon / 2);
        vector<T> der(A.begin() + lon / 2, A.end());

        return Ordenar(Sort(izq), Sort(der));
    }

private:
    vector<T> Ordenar(const vector<T>& A, const vector<T>& B) {
        vector<T> ret;
        size_t lonA = A.size();
        size_t lonB = B.size();
        size_t i = 0, j = 0;

        while (i < lonA && j < lonB) {
            if (comp(A[i], B[j])) {
                ret.push_back(A[i]);
                i++;
            }
            else {
                ret.push_back(B[j]);
                j++;
            }
        }

        while (i < lonA) {
            ret.push_back(A[i]);
            i++;
        }
        while (j < lonB) {
            ret.push_back(B[j]);
            j++;
        }

        return ret;
    }
};

int main() {
    int nThreads = thread::hardware_concurrency();
    vector<int> vecOrdenado;

    MergeSort<int, ASC<int>> Merge;

    for (int i = 0; i < 10000; i++) {
        vecOrdenado.push_back(rand() % 100000);
    }

    while (nThreads >= 1) {
        int partSize = vecOrdenado.size() / nThreads;
        if (partSize == 0) break;

        vector<vector<int>> subvecs(nThreads);

        vector<thread> vecThread;
        for (int i = 0; i < nThreads; ++i) {
            int startIdx = i * partSize;
            int endIdx = (i == nThreads - 1) ? vecOrdenado.size() : (i + 1) * partSize;

            subvecs[i] = vector<int>(vecOrdenado.begin() + startIdx, vecOrdenado.begin() + endIdx);
            vecThread.emplace_back([&Merge, &subvecs, i]() {
                subvecs[i] = Merge.Sort(subvecs[i]);
                });
        }

        for (int t = 0; t < nThreads; ++t) {
            vecThread[t].join();
        }

        vecOrdenado.clear();
        for (const auto& subvec : subvecs) {
            vecOrdenado.insert(vecOrdenado.end(), subvec.begin(), subvec.end());
        }

        nThreads /= 2;
        vecThread.clear();
    }

    for (int i = 0; i < vecOrdenado.size(); i++) {
        cout << vecOrdenado[i] << " ";
    }
    cout << endl;

    return 0;
}