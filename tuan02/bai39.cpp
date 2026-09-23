#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
typedef long long ll;

// --- CÁCH 1: O(n^3) ---
ll maxSubarray_C1(const vector<int>& a) {
    int n = a.size();
    ll best = a[0];
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            ll cur_sum = 0;
            for (int k = i; k <= j; k++) cur_sum += a[k];
            if (cur_sum > best) best = cur_sum;
        }
    }
    return best;
}

// --- CÁCH 2: O(n^2) ---
ll maxSubarray_C2(const vector<int>& a) {
    int n = a.size();
    ll best = a[0];
    vector<ll> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + a[i];
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            ll cur_sum = prefix[j + 1] - prefix[i];
            if (cur_sum > best) best = cur_sum;
        }
    }
    return best;
}

// --- CÁCH 3: Kadane O(n) ---
ll maxSubarray_C3(const vector<int>& a) {
    ll best = a[0];
    ll cur = a[0];
    for (size_t i = 1; i < a.size(); i++) {
        cur = max((ll)a[i], cur + a[i]);
        best = max(best, cur);
    }
    return best;
}

void runManualTests() {
    vector<pair<vector<int>, int>> tests = {
        {{4, -3, 5, -2, -1, 2, 6, -9}, 11},
        {{-5, -2, -9}, -2},
        {{1, 2, 3, 4}, 10},
        {{-2, 1, -3, 4, -1, 2, 1, -5, 4}, 6},
        {{0, -1, 0}, 0}
    };
    cout << "=== KET QUA TEST BAT BUOC ===\n";
    for (int t = 0; t < tests.size(); t++) {
        ll r1 = maxSubarray_C1(tests[t].first);
        ll r2 = maxSubarray_C2(tests[t].first);
        ll r3 = maxSubarray_C3(tests[t].first);
        string status = (r1 == r2 && r2 == r3 && r3 == tests[t].second) ? "PASS" : "FAIL";
        cout << "Test " << t+1 << ": " << status 
             << " (C1=" << r1 << ", C2=" << r2 << ", C3=" << r3 << ")\n";
    }
}

void runAutoTest() {
    cout << "\n=== KIEM THU TU DONG (1000 TESTS) ===\n";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist_n(1, 50);
    uniform_int_distribution<> dist_val(-50, 50);

    for (int i = 0; i < 1000; i++) {
        int n = dist_n(gen);
        vector<int> a(n);
        for (int& x : a) x = dist_val(gen);
        
        ll r1 = maxSubarray_C1(a);
        ll r2 = maxSubarray_C2(a);
        ll r3 = maxSubarray_C3(a);
        
        if (r1 != r2 || r2 != r3) {
            cout << "FAIL! Phan vi du: ";
            for (int x : a) cout << x << " ";
            cout << "\nC1=" << r1 << ", C2=" << r2 << ", C3=" << r3 << "\n";
            return;
        }
    }
    cout << "OK\n";
}

void runBenchmark() {
    cout << "\n=== BANG THOI GIAN VA DOI CHIEU ===\n";
    int sizes[] = {200, 400, 800};
    random_device rd;
    mt19937 gen(42); // Fix seed để 3 hàm chạy trên cùng 1 data
    uniform_int_distribution<> dist_val(-1000, 1000);

    vector<vector<int>> arrays;
    for (int n : sizes) {
        vector<int> a(n);
        for (int& x : a) x = dist_val(gen);
        arrays.push_back(a);
    }

    auto bench = [](const vector<int>& a, ll (*func)(const vector<int>&)) -> double {
        auto start = chrono::high_resolution_clock::now();
        func(a);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        return diff.count();
    };

    cout << left << setw(15) << "Thoi gian (s)" 
         << " | " << setw(10) << "n=200" 
         << " | " << setw(10) << "n=400" 
         << " | " << setw(10) << "n=800"
         << " | " << setw(15) << "T(400)/T(200)"
         << " | " << setw(15) << "T(800)/T(400)" << "\n";
    cout << string(90, '-') << "\n";

    vector<string> names = {"C1 (O(n^3))", "C2 (O(n^2))", "C3 (O(n))"};
    vector<ll (*)(const vector<int>&)> funcs = {maxSubarray_C1, maxSubarray_C2, maxSubarray_C3};

    for (int i = 0; i < 3; i++) {
        double t1 = bench(arrays[0], funcs[i]);
        double t2 = bench(arrays[1], funcs[i]);
        double t3 = bench(arrays[2], funcs[i]);
        
        double r1 = (t1 > 0) ? t2 / t1 : 0;
        double r2 = (t2 > 0) ? t3 / t2 : 0;

        cout << left << setw(15) << names[i] 
             << " | " << setw(10) << fixed << setprecision(4) << t1 
             << " | " << setw(10) << t2 
             << " | " << setw(10) << t3
             << " | " << setw(15) << setprecision(2) << r1 
             << " | " << setw(15) << r2 << "\n";
    }
}

int main() {
    runManualTests();
    runAutoTest();
    runBenchmark();
    return 0;
}