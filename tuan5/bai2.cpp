#include <iostream>
#include <vector>
#include <string>

using namespace std;

void insertion_sort(vector<int>& A, long long& cmps, long long& shifts) {
    int n = A.size();
    cmps = 0;
    shifts = 0;
    for (int i = 1; i < n; ++i) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0) {
            cmps++; // Đếm mỗi lần so sánh A[j] với key
            if (A[j] <= key) {
                break;  // Phép so sánh này vẫn được tính
            }
            A[j + 1] = A[j];
            shifts++; // Đếm số lần dịch chuyển
            j--;
        }
        A[j + 1] = key;
    }
}

long long merge_sort(vector<int>& A, int lo, int hi, vector<int>& buffer) {
    if (lo >= hi) return 0;
    int mid = lo + (hi - lo) / 2;
    long long cmps = 0;
    
    cmps += merge_sort(A, lo, mid, buffer);
    cmps += merge_sort(A, mid + 1, hi, buffer);
    
    int i = lo, j = mid + 1, out = lo;
    while (i <= mid && j <= hi) {
        cmps++; // Chỉ đếm khi cả hai nửa còn phần tử
        if (A[i] <= A[j]) {
            buffer[out++] = A[i++];
        } else {
            buffer[out++] = A[j++];
        }
    }
    
    // Chép phần dư (không đếm)
    while (i <= mid) {
        buffer[out++] = A[i++];
    }
    while (j <= hi) {
        buffer[out++] = A[j++];
    }
    
    for (int k = lo; k <= hi; ++k) {
        A[k] = buffer[k];
    }
    
    return cmps;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> A_orig(n);
    for (int i = 0; i < n; ++i) {
        cin >> A_orig[i];
    }

    if (n == 0) {
        cout << "INSERT \n";
        cout << "INSERT_CMPS 0\n";
        cout << "INSERT_SHIFTS 0\n";
        cout << "MERGE \n";
        cout << "MERGE_CMPS 0\n";
        return 0;
    }

    // 1. Sắp xếp chèn
    vector<int> A_insert = A_orig;
    long long ins_cmps = 0, ins_shifts = 0;
    insertion_sort(A_insert, ins_cmps, ins_shifts);
    
    cout << "INSERT ";
    for (int i = 0; i < n; ++i) cout << A_insert[i] << (i == n - 1 ? "" : " ");
    cout << "\n";
    cout << "INSERT_CMPS " << ins_cmps << "\n";
    cout << "INSERT_SHIFTS " << ins_shifts << "\n";

    // 2. Sắp xếp trộn
    vector<int> A_merge = A_orig;
    vector<int> buffer(n);
    long long merge_cmps = merge_sort(A_merge, 0, n - 1, buffer);
    
    cout << "MERGE ";
    for (int i = 0; i < n; ++i) cout << A_merge[i] << (i == n - 1 ? "" : " ");
    cout << "\n";
    cout << "MERGE_CMPS " << merge_cmps << "\n";

    return 0;
}