#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

int n;
long long node_count = 0;
long long solution_count = 0;
uint32_t full_mask;
vector<int> x;
vector<int> first_solution;

void backtrack(int row, uint32_t cols, uint32_t d1, uint32_t d2) {
    ++node_count;
    if (row == n) {
        ++solution_count;
        if (solution_count == 1) first_solution = x;
        return;
    }
    uint32_t avail = full_mask & ~(cols | d1 | d2);
    while (avail) {
        uint32_t bit = avail & -avail;        // bit thấp nhất
        avail ^= bit;
        x[row] = __builtin_ctz(bit);           // vị trí bit = số bit 0 ở cuối
        backtrack(row + 1,
                  cols | bit,
                  ((d1 | bit) << 1) & full_mask,
                  (d2 | bit) >> 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n) || n <= 0 || n > 31) return 0;

    x.assign(n, 0);
    first_solution.assign(n, 0);
    full_mask = (uint32_t(1) << n) - 1;

    backtrack(0, 0, 0, 0);

    cout << "So nut da duyet: " << node_count << "\n"
         << "So loi giai: " << solution_count << "\n";
    if (solution_count > 0) {
        cout << "Ban co loi giai dau tien:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                cout << (first_solution[i] == j ? "Q " : ". ");
            cout << "\n";
        }
    } else {
        cout << "Khong co loi giai nao.\n";
    }
    return 0;
}