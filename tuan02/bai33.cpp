#include <iostream>
using namespace std;

int main() {
    long long n;
    // Đọc cho đến khi hết file (hỗ trợ nạp nhiều test cùng lúc)
    while (cin >> n) {
        int count = 0;
        int sum = 0;
        
        // Vòng lặp O(log_10(n))
        while (n > 0) {
            int d = n % 10;       // Lấy chữ số cuối
            sum += d;             // Cộng vào tổng
            count++;              // Đếm số chữ số
            n = n / 10;           // C++ mặc định chia nguyên cho số nguyên
        }
        
        // In ra theo format yêu cầu (2 khoảng trắng)
        cout << count << "  " << sum << endl;
    }
    
    /* NHẬN XÉT VỀ n = 0:
       Nếu n = 0, vòng while không chạy, in ra "0  0". 
       Đó là lý do đề bài quy định n là nguyên dương (n >= 1). */
       
    return 0;
}