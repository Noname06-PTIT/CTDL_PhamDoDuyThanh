#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

pair<int, vector<int>> doi_tien_tham_lam(vector<int> coins, int S) {
    sort(coins.rbegin(), coins.rend());
    int count = 0;
    vector<int> ans;
    for (int c : coins) {
        if (S >= c) {
            int q = S / c;
            count += q;
            for (int i = 0; i < q; ++i) ans.push_back(c);
            S %= c;
        }
    }
    return {count, ans};
}

pair<int, vector<int>> doi_tien_qhd(const vector<int>& coins, int S) {
    vector<int> dp(S + 1, 1e9);
    vector<int> trace(S + 1, 0);
    dp[0] = 0;

    for (int i = 1; i <= S; ++i) {
        for (int c : coins) {
            if (i >= c && dp[i - c] + 1 < dp[i]) {
                dp[i] = dp[i - c] + 1;
                trace[i] = c;
            }
        }
    }

    vector<int> ans;
    int curr = S;
    while (curr > 0) {
        ans.push_back(trace[curr]);
        curr -= trace[curr];
    }
    return {dp[S], ans};
}

// Chương trình kiểm chứng độc lập bằng BFS
int kiem_chung_bfs(const vector<int>& coins, int S) {
    if (S == 0) return 0;
    vector<bool> visited(S + 1, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;
    int steps = 0;
    
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            int u = q.front(); q.pop();
            if (u == S) return steps;
            for (int c : coins) {
                int v = u + c;
                if (v <= S && !visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        steps++;
    }
    return -1;
}

int main() {
    vector<pair<vector<int>, int>> bo_du_lieu = {
        {{1, 4, 6, 9}, 12},
        {{1, 5, 10, 20, 50}, 85},
        {{1, 3, 7, 12}, 20},
        {{1, 2, 5, 10}, 38},
        {{1, 6, 10}, 12},
        {{1, 4, 5, 15, 20}, 23}
    };

    for (size_t i = 0; i < bo_du_lieu.size(); ++i) {
        auto coins = bo_du_lieu[i].first;
        int S = bo_du_lieu[i].second;

        auto tl = doi_tien_tham_lam(coins, S);
        auto qhd = doi_tien_qhd(coins, S);
        int bfs_count = kiem_chung_bfs(coins, S);

        // Kiểm tra sự khớp nhau giữa QHD và BFS
        if (qhd.first != bfs_count) {
            cerr << "LOI KIEM CHUNG BO " << i + 1 << endl;
            return 1;
        }

        cout << "Bo " << i + 1 << ":\n";
        cout << "  - Tham lam : " << tl.first << " to, chi tiet [ ";
        for (int c : tl.second) cout << c << " ";
        cout << "]\n";

        cout << "  - Toi uu   : " << qhd.first << " to, chi tiet [ ";
        for (int c : qhd.second) cout << c << " ";
        cout << "]\n";

        cout << "  - Kiem chung BFS khop: " << bfs_count << " to\n";
        cout << "  => Tham lam dung? " << (tl.first == qhd.first ? "Co" : "Khong") << "\n\n";
    }

    return 0;
}