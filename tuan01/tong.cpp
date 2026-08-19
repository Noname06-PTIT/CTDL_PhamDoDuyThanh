#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long sum = 0;

    long long x;
    cin >> x;

    long long maxv = x;
    sum += x;

    for (int i = 1; i < n; i++) {
        cin >> x;
        sum += x;

        if (x > maxv) {
            maxv = x;
        }
    }

    cout << sum << " " << maxv << "\n";

    return 0;
}