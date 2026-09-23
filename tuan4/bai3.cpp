#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    char name;
    double w, v;
    double ratio;
};

double W = 14;
vector<Item> items;
int n;

double max_val;
int best_mask;
int nodes_visited;

double bound(int level, double cw, double cv) {
    if (cw > W) return 0;
    double b = cv;
    double w = cw;
    for (int i = level; i < n; i++) {
        if (w + items[i].w <= W) {
            w += items[i].w;
            b += items[i].v;
        } else {
            b += (W - w) * items[i].ratio;
            break;
        }
    }
    return b;
}

void dfs(int level, double cw, double cv, int mask, bool prune) {
    nodes_visited++;
    if (cv > max_val) {
        max_val = cv;
        best_mask = mask;
    }
    if (level == n) return;

    if (prune && bound(level, cw, cv) <= max_val) {
        return;
    }

    if (cw + items[level].w <= W) {
        dfs(level + 1, cw + items[level].w, cv + items[level].v, mask | (1 << level), prune);
    }
    dfs(level + 1, cw, cv, mask, prune);
}

void solve(bool prune) {
    max_val = 0;
    best_mask = 0;
    nodes_visited = 0;
    dfs(0, 0, 0, 0, prune);
    
    cout << "Gia tri lon nhat: " << max_val << endl;
    cout << "Tap do vat chon: ";
    for (int i = 0; i < n; i++) {
        if (best_mask & (1 << i)) {
            cout << items[i].name << " ";
        }
    }
    cout << endl;
    cout << "So nut da duyet: " << nodes_visited << endl;
}

int main() {
    // Dữ liệu chuẩn mục C của đề bài
    items = {
        {'A', 4, 19, 19.0 / 4},
        {'B', 7, 25, 25.0 / 7},
        {'C', 3, 7,  7.0 / 3},
        {'D', 3, 8,  8.0 / 3},
        {'E', 3, 9,  9.0 / 3},
        {'F', 10, 21, 21.0 / 10}
    };
    n = items.size();
    
    // Sắp xếp giảm dần theo tỉ số v/w
    sort(items.begin(), items.end(), [](const Item& a, const Item& b){
        return a.ratio > b.ratio;
    });
    
    cout << "--- KHONG CAT NHANH ---" << endl;
    solve(false);
    
    cout << "\n--- CO CAT NHANH ---" << endl;
    solve(true);

    return 0;
}