#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

// Ma trận đề bài Sudoku mục E (0 là ô trống)
vector<vector<int>> board = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

long long calls_count = 0;

bool is_valid(const vector<vector<int>>& b, int r, int c, int num) {
    for (int i = 0; i < 9; i++) {
        if (b[r][i] == num || b[i][c] == num) return false;
    }
    int br = 3 * (r / 3), bc = 3 * (c / 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[br + i][bc + j] == num) return false;
        }
    }
    return true;
}

bool solve_sequential(vector<vector<int>>& b) {
    calls_count++;
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (b[r][c] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (is_valid(b, r, c, num)) {
                        b[r][c] = num;
                        if (solve_sequential(b)) return true;
                        b[r][c] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool solve_mrv(vector<vector<int>>& b) {
    calls_count++;
    int best_r = -1, best_c = -1;
    int min_options = 10;
    vector<int> best_nums;

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (b[r][c] == 0) {
                vector<int> opts;
                for (int num = 1; num <= 9; num++) {
                    if (is_valid(b, r, c, num)) opts.push_back(num);
                }
                if ((int)opts.size() < min_options) {
                    min_options = opts.size();
                    best_r = r; 
                    best_c = c;
                    best_nums = opts;
                    if (min_options == 0) return false;
                    if (min_options == 1) break;
                }
            }
        }
        if (min_options == 1) break;
    }

    if (best_r == -1) return true;

    for (int num : best_nums) {
        b[best_r][best_c] = num;
        if (solve_mrv(b)) return true;
        b[best_r][best_c] = 0;
    }
    return false;
}

void run_solver(string name, bool(*solver)(vector<vector<int>>&)) {
    vector<vector<int>> b = board;
    calls_count = 0;
    auto start = chrono::high_resolution_clock::now();
    bool success = solver(b);
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000000.0;

    cout << "--- " << name << " ---" << endl;
    if (success) {
        cout << "Thoi gian chay: " << time_taken << " giay" << endl;
        cout << "So loi goi de quy: " << calls_count << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    run_solver("QUET TUAN TU", solve_sequential);
    cout << endl;
    run_solver("MRV", solve_mrv);
    return 0;
}