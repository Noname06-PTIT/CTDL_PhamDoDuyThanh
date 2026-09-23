#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void solve_method2(int n) {
    if (n < 2) return;
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    long long sum = 0;
    int count = 0;
    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            count++;
            sum += i;
            if (n <= 30) primes.push_back(i);
        }
    }
    
    if (n <= 30) {
        for (int p : primes) cout << p << " ";
        cout << "  (" << count << " so)\n";
    } else if (n < 1000000) {
        cout << "so luong = " << count << "\n";
    } else {
        cout << "so luong = " << count << ", tong = " << sum << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        solve_method2(n);
    }
    
    return 0;
}