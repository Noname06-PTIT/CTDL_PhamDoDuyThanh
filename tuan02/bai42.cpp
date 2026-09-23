#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    if (!(cin >> n >> k)) return 0;
    
    if (k > n) {
        cout << "Loi: k > n\n";
        return 0;
    }
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // Tính tổng cửa sổ đầu tiên
    long long window_sum = 0;
    for (int i = 0; i < k; i++) {
        window_sum += a[i];
    }
    
    long long max_sum = window_sum;
    int best_start = 1;
    
    // Trượt cửa sổ
    for (int i = k; i < n; i++) {
        window_sum += a[i] - a[i - k];
        if (window_sum > max_sum) {
            max_sum = window_sum;
            best_start = i - k + 2; // Đánh số từ 1
        }
    }
    
    cout << "tổng " << max_sum << ", bắt đầu tại vị trí " << best_start << "\n";
    return 0;
}