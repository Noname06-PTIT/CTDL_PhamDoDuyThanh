#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long x;
    cin >> x;

    long long tong   = x;
    long long minVal = x;
    long long maxVal = x;

    for (int i = 1; i < n; ++i) {
        cin >> x;
        tong += x;
        if (x < minVal) minVal = x;
        if (x > maxVal) maxVal = x;
    }

    double trungBinh = static_cast<double>(tong) / n;

    cout << tong << " "
         << fixed << setprecision(4) << trungBinh << " "
         << minVal << " " << maxVal << '\n';

    return 0;
}