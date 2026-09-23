#include <iostream>
#include <vector>
#include <utility>

using namespace std;

pair<int, int> find_bound(const vector<int>& A, int n, int x, bool is_upper) {
    int lo = 0;
    int hi = n;
    int probes = 0;
    
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        probes++;
        
        bool move_right;
        if (is_upper) {
            move_right = (A[mid] <= x);
        } else {
            move_right = (A[mid] < x);
        }
        
        if (move_right) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    
    return {lo, probes};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);6
    
    int n;
    if (!(cin >> n)) return 0;
    
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    
    // Kiểm tra mảng có sắp xếp không giảm
    for (int i = 1; i < n; ++i) {
        if (A[i] < A[i-1]) {
            cout << "ERROR: array must be sorted" << endl;
            return 1;
        }
    }
    
    int x;
    cin >> x;
    
    auto [lower, p1] = find_bound(A, n, x, false);
    auto [upper, p2] = find_bound(A, n, x, true);
    
    int first = -1;
    if (lower < n && A[lower] == x) {
        first = lower;
    }
    
    int count = upper - lower;
    int probes = p1 + p2;
    
    cout << "FIRST " << first << "\n";
    cout << "COUNT " << count << "\n";
    cout << "LOWER " << lower << "\n";
    cout << "UPPER " << upper << "\n";
    cout << "PROBES " << probes << "\n";
    
    return 0;
}