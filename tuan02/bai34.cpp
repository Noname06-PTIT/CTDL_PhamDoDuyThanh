#include <iostream>
using namespace std;

int main() {
    long long n;
    // Vòng lặp while kết hợp cin sẽ tự động dừng khi gặp EOF
    while (cin >> n) {
        long long sign = (n < 0) ? -1 : 1;
        long long abs_n = (n < 0) ? -n : n;
        
        long long rev = 0;
        while (abs_n > 0) {
            rev = rev * 10 + abs_n % 10;
            abs_n /= 10;
        }
        
        cout << sign * rev << "\n";
    }
    return 0;
}