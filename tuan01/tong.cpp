#include <iostream>              
using namespace std;
int main() 
{

    int n;
    cin >> n;

    // Dùng long long vì tổng có thể rất lớn:
    // n <= 10^5 và |ai| <= 10^9
    // Tổng có thể lên tới 10^14, vượt giới hạn của int
    long long sum = 0;           // Biến lưu tổng các phần tử, ban đầu bằng 0

    long long x;                 // Biến x dùng để lưu từng phần tử ai

    cin >> x;                    // Đọc phần tử đầu tiên của dãy

    // Khởi tạo giá trị lớn nhất bằng phần tử đầu tiên
    // Không được khởi tạo maxv = 0 vì các phần tử có thể đều là số âm
    long long maxv = x;

    sum += x;                    // Cộng phần tử đầu tiên vào tổng

    // Duyệt từ phần tử thứ 2 đến phần tử thứ n
    for (int i = 1; i < n; i++) {

        cin >> x;                // Đọc phần tử tiếp theo

        sum += x;                // Cộng phần tử hiện tại vào tổng

        // Kiểm tra xem phần tử hiện tại có lớn hơn giá trị lớn nhất
        // đang lưu trong maxv hay không
        if (x > maxv) {

            maxv = x;            // Nếu x lớn hơn, cập nhật giá trị lớn nhất
        }
    }

    // In ra tổng và giá trị lớn nhất
    // Hai giá trị được ngăn cách bởi một dấu cách
    // "\n" tạo ký tự xuống dòng ở cuối kết quả
    cout << sum << " " << maxv << "\n";

    return 0;
}