#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    int x;
    cin >> x;

    // 1. Thống kê (Sum, Min, Max, Scan visits)
    long long total = 0;
    bool has_low = false, has_high = false;
    int min_val = 0, max_val = 0;
    int scan_visits = 0;

    for (int i = 0; i < n; ++i) {
        scan_visits++;
        total += A[i];
        if (!has_low || A[i] < min_val) {
            min_val = A[i];
            has_low = true;
        }
        if (!has_high || A[i] > max_val) {
            max_val = A[i];
            has_high = true;
        }
    }

    // 2. Tìm kiếm tuần tự (First, Search comparisons)
    int first_idx = -1;
    int search_cmps = 0;
    for (int i = 0; i < n; ++i) {
        search_cmps++;
        if (A[i] == x) {
            first_idx = i;
            break;
        }
    }

    // 3. Đếm số cặp (Pairs) - Chạy vòng lặp thật
    long long pairs = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            pairs++;
        }
    }

    // 4. Đếm vòng nhân đôi (Doublings) - Chạy vòng lặp thật
    long long doubles = 0;
    long long size = 1;
    while (size <= n) {
        doubles++;
        size *= 2;
    }

    // In kết quả
    cout << "SUM " << total << "\n";
    cout << "MIN " << (has_low ? to_string(min_val) : "NA") << "\n";
    cout << "MAX " << (has_high ? to_string(max_val) : "NA") << "\n";
    cout << "FIRST " << first_idx << "\n";
    cout << "SEARCH_CMPS " << search_cmps << "\n";
    cout << "PAIRS " << pairs << "\n";
    cout << "DOUBLINGS " << doubles << "\n";
    cout << "SCAN_VISITS " << scan_visits << "\n";

    return 0;
}