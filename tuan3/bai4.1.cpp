// [DÁN MÃ NGUỒN C++ BÀI TOÁN TWO POINTERS TẠI ĐÂY]
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

vector<pair<int, int>> findPairsTwoPointers(vector<int> arr, int S) {
    vector<pair<int, int>> results;
    
    // Bước 1: Sắp xếp mảng
    sort(arr.begin(), arr.end());
    
    int left = 0;
    int right = arr.size() - 1;
    
    // Bước 2: Dùng 2 con trỏ để tìm cặp
    while (left < right) {
        int current_sum = arr[left] + arr[right];
        if (current_sum == S) {
            results.push_back({arr[left], arr[right]});
            left++;
            right--;
        } else if (current_sum < S) {
            left++; // Tổng nhỏ quá, cần tăng con trỏ trái
        } else {
            right--; // Tổng lớn quá, cần giảm con trỏ phải
        }
    }
    return results;
}

int main() {
    vector<int> testArr = {1, 4, 3, 2, 5, 7, 6};
    int S = 9;
    cout << "Mảng ban đầu: 1 4 3 2 5 7 6" << endl;
    vector<pair<int, int>> pairs = findPairsTwoPointers(testArr, S);
    
    cout << "Tìm các cặp có tổng bằng " << S << ": ";
    for(auto p : pairs) {
        cout << "(" << p.first << ", " << p.second << ") ";
    }
    cout << endl;
    return 0;
}