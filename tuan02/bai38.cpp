#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Tối ưu hóa tốc độ nhập xuất
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0; // Xử lý nếu không có dữ liệu

    // Mảng rỗng hoặc 1 phần tử luôn thỏa mãn
    if (n <= 1) {
        cout << "nghiêm ngặt: YES — không giảm: YES\n";
        return 0;
    }

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    bool is_strict = true;    // Tăng nghiêm ngặt
    bool is_non_decr = true;  // Không giảm

    // Chỉ số i chạy từ 0 đến n-2
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i+1]) {
            is_strict = false;
            is_non_decr = false;
        } else if (arr[i] == arr[i+1]) {
            is_strict = false;
        }

        // Thoát sớm khi cả hai đều sai
        if (!is_strict && !is_non_decr) break;
    }

    cout << "nghiêm ngặt: " << (is_strict ? "YES" : "NO") 
         << " — không giảm: " << (is_non_decr ? "YES" : "NO") << "\n";

    return 0;
}