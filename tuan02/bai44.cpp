#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <numeric>

using namespace std;
using namespace std::chrono;

void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;

        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            swap(arr[i], arr[min_idx]);
        }
    }
}

int main() {
    vector<int> sizes = {500, 1000, 2000, 4000};
    int num_runs = 3;
    vector<double> times;

    // Bộ sinh số ngẫu nhiên
    random_device rd;
    mt19937 g(rd());

    // Warm-up
    vector<int> warmup_arr(500);
    iota(warmup_arr.begin(), warmup_arr.end(), 1);
    shuffle(warmup_arr.begin(), warmup_arr.end(), g);
    selectionSort(warmup_arr);

    cout << "Chay moi moc " << num_runs
         << " lan va lay gia tri nho nhat:\n";

    for (int n : sizes) {
        double min_t = 1e9;

        for (int r = 0; r < num_runs; ++r) {
            vector<int> arr(n);

            iota(arr.begin(), arr.end(), 1);
            shuffle(arr.begin(), arr.end(), g);

            auto start = steady_clock::now();

            selectionSort(arr);

            auto end = steady_clock::now();

            duration<double> diff = end - start;
            min_t = min(min_t, diff.count());
        }

        times.push_back(min_t);

        cout << "n = " << n << ": "
             << fixed << setprecision(6)
             << min_t << " s\n";
    }

    // Tính tỉ lệ
    cout << "\n--- Bang ty le T(2n)/T(n) ---\n";

    for (size_t i = 1; i < sizes.size(); ++i) {
        double ratio = times[i] / times[i - 1];

        cout << "T(" << sizes[i] << ")/T("
             << sizes[i - 1] << ") = "
             << fixed << setprecision(2)
             << ratio << "\n";
    }

    // Dữ liệu để vẽ đồ thị
    cout << "\n--- Du lieu de ve do thi ---\n";
    cout << "n\tTime(s)\n";

    for (size_t i = 0; i < sizes.size(); ++i) {
        cout << sizes[i] << "\t"
             << fixed << setprecision(6)
             << times[i] << "\n";
    }

    return 0;
}