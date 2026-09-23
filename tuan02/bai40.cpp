#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Khởi tạo (chỉ số tính từ 1)
    int best_sum = a[0], cur_sum = a[0];
    int best_start = 1, best_end = 1, cur_start = 1;

    for (int i = 1; i < n; i++) {
        if (cur_sum > 0) {
            cur_sum += a[i];
        } else {
            cur_sum = a[i];
            cur_start = i + 1; // Chuyển về 1-based
        }

        // Dùng > để ưu tiên đoạn xuất hiện sớm nhất
        if (cur_sum > best_sum) {
            best_sum = cur_sum;
            best_start = cur_start;
            best_end = i + 1;   // Chuyển về 1-based
        }
    }

    // --- PHÉP KIỂM TRA CHÉO (CROSS-CHECK) ---
    int check_sum = 0;
    for (int i = best_start - 1; i < best_end; i++) {
        check_sum += a[i];
    }
    assert(check_sum == best_sum); // Sẽ ném lỗi nếu tính sai
    // -----------------------------------------

    cout << "tổng " << best_sum << ", đoạn [" << best_start << ".." << best_end << "]\n";

    return 0;
}