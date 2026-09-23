#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Ma trận chi phí chuẩn mục D của đề bài
vector<vector<int>> matrix = {
    {0, 10, 9, 22, 23},
    {10, 0, 16, 19, 14},
    {9, 16, 0, 7, 28},
    {22, 19, 7, 0, 8},
    {23, 14, 28, 8, 0}
};
int N = matrix.size();
int c_min = INT_MAX;

int best_cost;
vector<int> best_path;
int nodes_visited;

void dfs(int city, int visited, int cost, vector<int>& path, bool prune) {
    nodes_visited++;
    
    int edges_left = N - (path.size() - 1);
    int lower_bound = cost + edges_left * c_min;
    
    if (prune && lower_bound >= best_cost) {
        return;
    }
    
    if (path.size() == N) {
        int final_cost = cost + matrix[city][0];
        if (final_cost < best_cost) {
            best_cost = final_cost;
            best_path = path;
            best_path.push_back(0);
        }
        return;
    }
    
    for (int next_city = 0; next_city < N; next_city++) {
        if (!(visited & (1 << next_city))) {
            path.push_back(next_city);
            dfs(next_city, visited | (1 << next_city), cost + matrix[city][next_city], path, prune);
            path.pop_back();
        }
    }
}

void solve(bool prune) {
    best_cost = INT_MAX;
    best_path.clear();
    nodes_visited = 0;
    vector<int> path = {0};
    dfs(0, 1 << 0, 0, path, prune);
    
    cout << "Chi phi toi uu: " << best_cost << endl;
    cout << "Hanh trinh: ";
    for (size_t i = 0; i < best_path.size(); i++) {
        cout << best_path[i] << (i == best_path.size() - 1 ? "" : " -> ");
    }
    cout << endl;
    cout << "So nut da duyet: " << nodes_visited << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j && matrix[i][j] < c_min) {
                c_min = matrix[i][j];
            }
        }
    }
    
    cout << "Canh re nhat toan ma tran c_min: " << c_min << "\n\n";

    cout << "--- KHONG CAT NHANH ---" << endl;
    solve(false);
    
    cout << "\n--- CO CAT NHANH ---" << endl;
    solve(true);

    return 0;
}