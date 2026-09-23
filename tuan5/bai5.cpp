#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, W;
    // Nếu không đọc được n và W thì kết thúc
    if (!(cin >> n >> W)) return 0;
    
    vector<int> w(n + 1), v(n + 1);
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1; i <= n; ++i) cin >> v[i];
    
    // Khởi tạo bảng f (n+1) x (W+1) toàn 0
    vector<vector<int>> f(n + 1, vector<int>(W + 1, 0));
    
    // Quy hoạch động cái túi 0/1
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= W; ++j) {
            f[i][j] = f[i - 1][j]; // Mặc định không lấy đồ vật i
            if (j >= w[i]) {
                f[i][j] = max(f[i][j], f[i - 1][j - w[i]] + v[i]);
            }
        }
    }
    
    // In toàn bộ bảng f
    cout << "BANG F:\n";
    cout << "i/j\t0";
    for(int j = 1; j <= W; ++j) cout << "\t" << j;
    cout << "\n";
    for(int i = 0; i <= n; ++i) {
        cout << "i=" << i << "\t";
        for(int j = 0; j <= W; ++j) {
            cout << f[i][j] << (j == W ? "" : "\t");
        }
        cout << "\n";
    }
    
    cout << "\nGIA TRI LON NHAT: " << f[n][W] << "\n";
    
    // Truy vết tìm tập đồ vật được chọn
    vector<int> chosen;
    int j = W;
    for (int i = n; i >= 1; --i) {
        if (f[i][j] != f[i - 1][j]) { // Nếu giá trị khác hàng trên, tức là đã lấy đồ vật i
            chosen.push_back(i);
            j -= w[i];
        }
    }
    
    cout << "TAP DO VAT DUOC CHON (chi so 1-based): ";
    // In mảng theo thứ tự đồ vật tăng dần
    for (int i = chosen.size() - 1; i >= 0; --i) {
        cout << chosen[i] << (i == 0 ? "" : " ");
    }
    cout << "\n";
    
    return 0;
}