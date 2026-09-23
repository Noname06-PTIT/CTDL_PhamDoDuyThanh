#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

struct InputData {
    int id, x, y;
    string label;
};

struct Record {
    long long d2;
    int id;
    string label;
};

vector<Record> temp_buffer;

// Hàm sắp xếp trộn tự cài đặt
void merge_sort(vector<Record>& arr, int lo, int hi) {
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    merge_sort(arr, lo, mid);
    merge_sort(arr, mid + 1, hi);
    
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        // So sánh d2, nếu bằng nhau thì so sánh id
        if (arr[i].d2 < arr[j].d2 || (arr[i].d2 == arr[j].d2 && arr[i].id <= arr[j].id)) {
            temp_buffer[k++] = arr[i++];
        } else {
            temp_buffer[k++] = arr[j++];
        }
    }
    while (i <= mid) temp_buffer[k++] = arr[i++];
    while (j <= hi) temp_buffer[k++] = arr[j++];
    
    for (int idx = lo; idx <= hi; ++idx) {
        arr[idx] = temp_buffer[idx];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) {
        cout << "ERROR: invalid data\n";
        return 1;
    }
    
    if (n < 1 || n > 2000 || k < 1 || k > n) {
        cout << "ERROR: invalid data\n";
        return 1;
    }
    
    vector<InputData> inputs(n);
    set<int> seen_ids;
    
    for (int i = 0; i < n; ++i) {
        if (!(cin >> inputs[i].id >> inputs[i].x >> inputs[i].y >> inputs[i].label)) {
            cout << "ERROR: invalid data\n";
            return 1;
        }
        int id = inputs[i].id;
        int x = inputs[i].x;
        int y = inputs[i].y;
        string label = inputs[i].label;
        
        if (id < 1 || id > 1000000 || seen_ids.count(id) || 
            x < 0 || x > 10 || y < 0 || y > 10 || 
            (label != "A" && label != "B")) {
            cout << "ERROR: invalid data\n";
            return 1;
        }
        seen_ids.insert(id);
    }
    
    long long qx, qy;
    if (!(cin >> qx >> qy)) {
        cout << "ERROR: invalid data\n";
        return 1;
    }
    
    vector<Record> records(n);
    for (int i = 0; i < n; ++i) {
        long long dx = inputs[i].x - qx;
        long long dy = inputs[i].y - qy;
        records[i].d2 = dx * dx + dy * dy;
        records[i].id = inputs[i].id;
        records[i].label = inputs[i].label;
    }
    
    // Cấp phát bộ đệm và gọi Merge Sort
    temp_buffer.resize(n);
    merge_sort(records, 0, n - 1);
    
    // Bỏ phiếu
    int votesA = 0, votesB = 0;
    for (int i = 0; i < k; ++i) {
        if (records[i].label == "A") votesA++;
        else votesB++;
    }
    
    string prediction = (votesA >= votesB) ? "A" : "B";
    
    // Xuất kết quả
    cout << "NEIGHBORS " << k << "\n";
    for (int i = 0; i < k; ++i) {
        cout << records[i].id << " " << records[i].label << " " << records[i].d2 << "\n";
    }
    cout << "VOTES A " << votesA << " B " << votesB << "\n";
    cout << "PREDICT " << prediction << "\n";
    
    return 0;
}