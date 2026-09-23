// [DÁN MÃ NGUỒN C++ BÀI TOÁN KNN TẠI ĐÂY]
#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

string knnClassify(vector<tuple<int, int, string>> train_data, pair<int,int> test_point, int k) {
    int n = train_data.size();
    vector<double> dists(n);
    
    // Bước 1: Tính khoảng cách
    for(int i = 0; i < n; ++i) {
        double dx = get<0>(train_data[i]) - test_point.first;
        double dy = get<1>(train_data[i]) - test_point.second;
        dists[i] = sqrt(dx*dx + dy*dy);
    }
    
    // Bước 2: Tạo mảng chỉ số và sắp xếp
    vector<int> indices(n);
    for(int i = 0; i < n; ++i) indices[i] = i;
    
    // Dùng lambda function để sắp xếp mảng chỉ số dựa vào mảng dists
    sort(indices.begin(), indices.end(), [&](int a, int b) {
        return dists[a] < dists[b];
    });
    
    // Bước 3: Đếm nhãn K phần tử đầu
    map<string, int> classCount;
    for(int i = 0; i < k; ++i) {
        string label = get<2>(train_data[indices[i]]);
        classCount[label]++;
    }
    
    // Bước 4: Tìm nhãn có số phiếu cao nhất
    string bestLabel = "";
    int maxCount = -1;
    for(auto const& pair : classCount) {
        if(pair.second > maxCount) {
            maxCount = pair.second;
            bestLabel = pair.first;
        }
    }
    return bestLabel;
}

int main() {
    vector<tuple<int, int, string>> trainSet = {{1,1,"A"}, {2,3,"A"}, {4,2,"B"}, {5,6,"B"}, {9,9,"B"}};
    pair<int,int> testSample = {3,2};
    int K = 3;
    cout << "Mẫu kiểm thử: (" << testSample.first << ", " << testSample.second << ") -> Phân loại vào nhóm: " 
         << knnClassify(trainSet, testSample, K) << endl;
    return 0;
}