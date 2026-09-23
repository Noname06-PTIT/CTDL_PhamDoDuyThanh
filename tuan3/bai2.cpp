// [DÁN MÃ NGUỒN C++ THUẬT TOÁN INSERTION SORT TẠI ĐÂY]
#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        // Di chuyển các phần tử lớn hơn key lên một vị trí
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void printArray(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << (i < arr.size() - 1 ? ", " : "");
    }
    cout << "]" << endl;
}

int main() {
    vector<int> A = {8, 3, 5, 1, 9, 2};
    cout << "Dãy ban đầu   : [";
    printArray(A);
    
    insertionSort(A);
    
    cout << "Dãy sau khi sx : [";
    printArray(A);
    return 0;
}