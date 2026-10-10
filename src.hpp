
// placeholder
#ifndef SRC_HPP
#define SRC_HPP

#include <algorithm>
#include <cstring>

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

    ~CrossArray() {
        for (int i = 0; i < maxLines; ++i) {
            delete[] arr[i];
        }
        delete[] arr;
        delete[] sizes;
    }

    bool InsertArrays(const int *Input, int size) {
        int idx = -1;
        for (int i = 0; i < maxLines; ++i) {
            if (arr[i] == nullptr) { idx = i; break; }
        }
        if (idx == -1) return false;
        arr[idx] = new int[size];
        std::copy(Input, Input + size, arr[idx]);
        sizes[idx] = size;
        totalElements += size;
        return true;
    }

    void AppendArrays(const int *Input, int Line, int size) {
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

    CrossArray &WhichGreater(CrossArray &o) {
        if (o.totalElements > this->totalElements) return o;
        return *this;
    }

    bool IsSame(const CrossArray &o) {
        return this->arr == o.arr;
    }

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

    const int *AtArray(int i) const {
        return arr[i];
    }

    int &At(int i, int j) {
        return arr[i][j];
    }
};
}

#endif // SRC_HPP
