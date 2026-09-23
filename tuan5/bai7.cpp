#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct HoatDong { 
    int s, f;
    string id; 
};

vector<string> chon_hoat_dong(vector<HoatDong> hd, string tieu_chi) {
    if (tieu_chi == "ket_thuc") {
        sort(hd.begin(), hd.end(), [](HoatDong a, HoatDong b) { return a.f < b.f; });
    } else if (tieu_chi == "bat_dau") {
        sort(hd.begin(), hd.end(), [](HoatDong a, HoatDong b) { return a.s < b.s; });
    } else if (tieu_chi == "ngan_nhat") {
        sort(hd.begin(), hd.end(), [](HoatDong a, HoatDong b) { return (a.f - a.s) < (b.f - b.s); });
    } else if (tieu_chi == "it_chong_lan") {
        vector<pair<int, HoatDong>> chong_lan;
        for (size_t i = 0; i < hd.size(); i++) {
            int count = 0;
            for (size_t j = 0; j < hd.size(); j++) {
                if (i != j && !(hd[i].f <= hd[j].s || hd[j].f <= hd[i].s)) {
                    count++;
                }
            }
            chong_lan.push_back({count, hd[i]});
        }
        sort(chong_lan.begin(), chong_lan.end(), [](pair<int, HoatDong> a, pair<int, HoatDong> b) {
            return a.first < b.first;
        });
        
        hd.clear();
        for (auto p : chong_lan) hd.push_back(p.second);
    }
    
    vector<string> ans;
    int het = -1;
    for (auto x : hd) {
        if (x.s >= het) {
            ans.push_back(x.id);
            het = x.f;
        }
    }
    return ans;
}

// Chương trình kiểm chứng độc lập bằng Vét cạn (Brute-force)
int kiem_chung_vet_can(vector<HoatDong> hd) {
    int n = hd.size();
    for (int r = n; r >= 1; --r) {
        for (int mask = 1; mask < (1 << n); ++mask) {
            if (__builtin_popcount(mask) != r) continue;
            vector<HoatDong> subset;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    subset.push_back(hd[i]);
                }
            }
            sort(subset.begin(), subset.end(), [](HoatDong a, HoatDong b) { return a.f < b.f; });
            bool valid = true;
            for (size_t i = 0; i < subset.size() - 1; ++i) {
                if (subset[i].f > subset[i+1].s) {
                    valid = false;
                    break;
                }
            }
            if (valid) return r;
        }
    }
    return 0;
}

int main() {
    vector<int> s = {1, 2, 2, 3, 4, 6, 8, 9, 11, 12};
    vector<int> f = {5, 5, 6, 4, 8, 9, 11, 14, 13, 15};
    vector<HoatDong> hd;
    for (int i = 0; i < 10; i++) {
        hd.push_back({s[i], f[i], "H" + to_string(i + 1)});
    }

    vector<string> tieu_chi_list = {"ket_thuc", "bat_dau", "ngan_nhat", "it_chong_lan"};
    vector<string> ten_tieu_chi = {"Ket thuc som nhat ", "Bat dau som nhat  ", "Ngan nhat         ", "It chong lan nhat "};

    for (int i = 0; i < 4; i++) {
        vector<string> kq = chon_hoat_dong(hd, tieu_chi_list[i]);
        cout << ten_tieu_chi[i] << " : [ ";
        for (string id : kq) cout << id << " ";
        cout << "] (So hoat dong: " << kq.size() << ")\n";
    }
    
    vector<string> kq_ket_thuc = chon_hoat_dong(hd, "ket_thuc");
    int kq_vet_can = kiem_chung_vet_can(hd);
    
    // Đối chiếu chương trình chính và kiểm chứng độc lập
    if ((int)kq_ket_thuc.size() != kq_vet_can) {
        cerr << "LOI KIEM CHUNG: Tham lam khong khop voi vet can!" << endl;
        return 1;
    }

    cout << "------------------------------\n";
    cout << "So nhieu nhat that su (Vet can kiem chung): " << kq_vet_can << "\n";

    return 0;
}