#include <iostream>
#include <string>
#include <climits>

using namespace std;

// Hàm nhân một chuỗi số lớn với một số nguyên nhỏ
string multiplyString(string num, int x) {
    int carry = 0;
    for (int i = num.size() - 1; i >= 0; i--) {
        int product = (num[i] - '0') * x + carry;
        num[i] = (product % 10) + '0';
        carry = product / 10;
    }
    while (carry) {
        num.insert(num.begin(), (carry % 10) + '0');
        carry /= 10;
    }
    return num;
}

// Hàm định dạng chuỗi số thêm dấu cách cách nhau 3 chữ số
string formatNumber(string s) {
    string res = "";
    int count = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        res = s[i] + res;
        count++;
        if (count % 3 == 0 && i != 0) {
            res = " " + res;
        }
    }
    return res;
}

int main() {
    long long n;
    if (!(cin >> n)) return 0;

    long long f = 1;
    bool overflow = false;
    long long overflow_at_i = -1;

    // Tính giai thừa và KIỂM TRA TRÀN SỐ TỰ ĐỘNG
    for (long long i = 1; i <= n; i++) {
        // Nếu f * i vượt quá LLONG_MAX thì tức là f > LLONG_MAX / i
        if (f > LLONG_MAX / i) {
            overflow = true;
            overflow_at_i = i;
            break;
        }
        f *= i;
    }

    if (!overflow) {
        // Nếu không tràn, in ra kết quả đã định dạng
        cout << formatNumber(to_string(f)) << endl;
    } else {
        // Nếu bị tràn, dùng chuỗi (string) để tính tiếp phần giá trị còn lại
        // nhằm in ra đúng giá trị toán học của n! trong thông báo lỗi
        string exact_fact_str = to_string(f);
        for (long long i = overflow_at_i; i <= n; i++) {
            exact_fact_str = multiplyString(exact_fact_str, i);
        }
        
        cout << "TRAN SO (" << n << "! = " << formatNumber(exact_fact_str) 
             << " > " << formatNumber(to_string(LLONG_MAX)) << ")" << endl;
    }

    return 0;
}