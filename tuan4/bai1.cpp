#include <iostream>
#include <vector>
#include <string>

bool xau_ke_tiep(std::vector<int>& x) {
    int i = static_cast<int>(x.size()) - 1;

    while (i >= 0 && x[i] == 1) {
        x[i] = 0;
        i--;
    }

    if (i < 0) {
        return false;
    }

    // Đổi chữ số 0 đầu tiên thành 1
    x[i] = 1;
    return true;
}

std::vector<std::string> liet_ke_xau(int n) {
    std::vector<int> x(n, 0);

    std::vector<std::string> ds;
    ds.push_back("");

    for (int i : x) {
        ds.back() += std::to_string(i);
    }

    while (xau_ke_tiep(x)) {
        std::string s = "";

        for (int i : x) {
            s += std::to_string(i);
        }

        ds.push_back(s);
    }

    return ds;
}

// Chạy thử với n = 3
int main() {
    std::vector<std::string> ds = liet_ke_xau(3);

    for (const std::string& s : ds) {
        std::cout << s << " ";
    }

    return 0;
}