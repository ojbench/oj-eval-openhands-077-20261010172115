#include <bits/stdc++.h>
using namespace std;

namespace sjtu {
class CrossArray {
private:
    int maxLines;          // capacity of lines
    int **arr;            // pointers to each line array
    int *sizes;           // size of each line (0 if nullptr)
    int totalElements;    // total number of elements across all lines
public:
    explicit CrossArray(int lines) : maxLines(lines), totalElements(0) {
        arr = new int*[maxLines];
        sizes = new int[maxLines];
        for (int i = 0; i < maxLines; ++i) {
            arr[i] = nullptr;
            sizes[i] = 0;
        }
    }

    // Deep copy constructor
    CrossArray(const CrossArray &o) : maxLines(o.maxLines), totalElements(o.totalElements) {
        arr = new int*[maxLines];
        sizes = new int[maxLines];
        for (int i = 0; i < maxLines; ++i) {
            if (o.arr[i]) {
                sizes[i] = o.sizes[i];
                arr[i] = new int[sizes[i]];
                std::copy(o.arr[i], o.arr[i] + sizes[i], arr[i]);
            } else {
                arr[i] = nullptr;
                sizes[i] = 0;
            }
        }
    }

    // Destructor
    ~CrossArray() {
        for (int i = 0; i < maxLines; ++i) {
            delete[] arr[i];
        }
        delete[] arr;
        delete[] sizes;
    }

    // Insert a new array; returns false if capacity exceeded
    bool InsertArrays(const int *Input, int size) {
        // find first empty slot
        int idx = -1;
        for (int i = 0; i < maxLines; ++i) {
            if (arr[i] == nullptr) { idx = i; break; }
        }
        if (idx == -1) return false; // no space
        arr[idx] = new int[size];
        std::copy(Input, Input + size, arr[idx]);
        sizes[idx] = size;
        totalElements += size;
        return true;
    }

    // Append to existing line
    void AppendArrays(const int *Input, int Line, int size) {
        // assume arr[Line] exists
        int oldSize = sizes[Line];
        int newSize = oldSize + size;
        int *newArr = new int[newSize];
        if (oldSize > 0) {
            std::copy(arr[Line], arr[Line] + oldSize, newArr);
        }
        std::copy(Input, Input + size, newArr + oldSize);
        delete[] arr[Line];
        arr[Line] = newArr;
        sizes[Line] = newSize;
        totalElements += size;
    }

    // Return reference to the larger (by element count) CrossArray
    CrossArray &WhichGreater(CrossArray &o) {
        if (o.totalElements > this->totalElements) return o;
        return *this; // if equal, return this
    }

    // Check if two objects share the same underlying storage
    bool IsSame(const CrossArray &o) {
        return this->arr == o.arr;
    }

    // Double the capacity of lines
    void DoubleCrossLength() {
        int newMax = maxLines * 2;
        int **newArr = new int*[newMax];
        int *newSizes = new int[newMax];
        for (int i = 0; i < maxLines; ++i) {
            newArr[i] = arr[i];
            newSizes[i] = sizes[i];
        }
        for (int i = maxLines; i < newMax; ++i) {
            newArr[i] = nullptr;
            newSizes[i] = 0;
        }
        delete[] arr;
        delete[] sizes;
        arr = newArr;
        sizes = newSizes;
        maxLines = newMax;
    }

    const int *AtArray(int i) {
        return arr[i];
    }

    int &At(int i, int j) {
        return arr[i][j];
    }
};
} // namespace sjtu

int main(){
    // No specific I/O required for this problem.
    return 0;
}
