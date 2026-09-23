#include <iostream>
using namespace std;

bool isPerfectSquare(long long n) {
    long long lo = 0, hi = 1000000000LL;   // sqrt(10^18) = 10^9
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        long long sq = mid * mid;          // mid ≤ 10^9 → sq ≤ 10^18, không tràn
        if (sq == n) return true;
        if (sq < n) lo = mid + 1;
        else        hi = mid - 1;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    while (cin >> n) {                     // ← đọc liên tục đến EOF
        cout << (isPerfectSquare(n) ? "YES" : "NO") << '\n';
    }
    return 0;
}