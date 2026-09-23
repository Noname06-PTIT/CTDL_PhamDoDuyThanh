#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

struct Cau { 
    vector<string> tu; 
    double diem; 
};

// 1. Liệt kê toàn bộ câu độ dài 3 và tính điểm
pair<vector<string>, double> liet_ke(map<string, map<string, double>>& P, vector<string> current, double score, int L) {
    if (current.size() == L) {
        cout << "  Câu: ";
        for (string w : current) cout << w << " ";
        cout << "- Điểm: " << score << "\n";
        return {current, score};
    }
    vector<string> best_sent;
    double best_score = -1.0;
    string last = current.back();
    if (P.count(last)) {
        for (auto& pair : P[last]) {
            vector<string> next = current;
            next.push_back(pair.first);
            auto res = liet_ke(P, next, score * pair.second, L);
            if (res.second > best_score) {
                best_score = res.second;
                best_sent = res.first;
            }
        }
    }
    return {best_sent, best_score};
}

// 2 & 3. Beam Search
Cau beam_search(map<string, map<string, double>>& P, string start, int L, int k) {
    vector<Cau> beam = {{{start}, 1.0}};
    for (int i = 0; i < L - 1; i++) {
        vector<Cau> new_beam;
        for (auto& cau : beam) {
            string tt = cau.tu.back();
            if (P.count(tt)) {
                for (auto& wp : P[tt]) {
                    Cau moi = cau;
                    moi.tu.push_back(wp.first);
                    moi.diem *= wp.second;
                    new_beam.push_back(moi);
                }
            }
        }
        sort(new_beam.begin(), new_beam.end(), [](const Cau& a, const Cau& b) {
            return a.diem > b.diem;
        });
        if (new_beam.size() > k) new_beam.resize(k);
        beam = new_beam;
    }
    return beam[0];
}

// 4. Viterbi
pair<vector<string>, double> viterbi(vector<string> cau, vector<string> nhan, 
                                     map<string, double>& pi, 
                                     map<string, map<string, double>>& A, 
                                     map<string, map<string, double>>& B) {
    int T = cau.size();
    vector<map<string, double>> f(T);
    vector<map<string, string>> tu(T);
    
    for (auto t : nhan) f[0][t] = pi[t] * B[t][cau[0]];
    
    for (int i = 1; i < T; i++) {
        for (auto t : nhan) {
            string tot; double gt = -1.0;
            for (auto s : nhan) {
                double x = f[i-1][s] * A[s][t];
                if (x > gt) { gt = x; tot = s; }
            }
            f[i][t] = gt * B[t][cau[i]];
            tu[i][t] = tot;
        }
    }
    
    string cuoi; double cao = -1.0;
    for (auto t : nhan) {
        if (f[T-1][t] > cao) { cao = f[T-1][t]; cuoi = t; }
    }
    
    vector<string> day = {cuoi};
    for (int i = T - 1; i > 0; i--) day.push_back(tu[i][day.back()]);
    reverse(day.begin(), day.end());
    return {day, cao};
}

// Chương trình kiểm chứng vét cạn
pair<vector<string>, double> vet_can_viterbi(vector<string> cau, vector<string> nhan, 
                                             map<string, double>& pi, 
                                             map<string, map<string, double>>& A, 
                                             map<string, map<string, double>>& B) {
    vector<string> best_seq;
    double best_prob = -1.0;
    int n = cau.size();
    
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<string> seq;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << (n - 1 - i))) seq.push_back(nhan[1]);
            else seq.push_back(nhan[0]);
        }
        
        double prob = pi[seq[0]] * B[seq[0]][cau[0]];
        for (int i = 1; i < n; i++) {
            prob *= A[seq[i-1]][seq[i]] * B[seq[i]][cau[i]];
        }
        
        if (prob > best_prob) {
            best_prob = prob;
            best_seq = seq;
        }
    }
    return {best_seq, best_prob};
}

int main() {
    map<string, map<string, double>> P = {
        {"em", {{"học", 0.52}, {"đi", 0.48}}},
        {"học", {{"bài", 0.40}, {"toán", 0.35}, {"vẽ", 0.25}}},
        {"đi", {{"chợ", 0.58}, {"bơi", 0.22}, {"ngủ", 0.20}}}
    };
    
    cout << "--- Liệt kê toàn bộ câu độ dài 3 ---\n";
    auto kq_lk = liet_ke(P, {"em"}, 1.0, 3);
    cout << "Liệt kê: câu tốt nhất ";
    for (string w : kq_lk.first) cout << w << " ";
    cout << kq_lk.second << "\n\n";
    
    cout << "--- Beam Search ---\n";
    for (int k = 1; k <= 3; k++) {
        Cau kq = beam_search(P, "em", 3, k);
        cout << "Beam k=" << k << " : [ ";
        for (string w : kq.tu) cout << w << " ";
        cout << "] - Điểm: " << kq.diem << "\n";
    }
    
    vector<string> nhan = {"N", "V"};
    map<string, double> pi = {{"N", 0.6}, {"V", 0.4}};
    map<string, map<string, double>> A = {
        {"N", {{"N", 0.35}, {"V", 0.65}}}, 
        {"V", {{"N", 0.70}, {"V", 0.30}}}
    };
    map<string, map<string, double>> B = {
        {"N", {{"em", 0.35}, {"học", 0.10}, {"bài", 0.40}, {"toán", 0.30}}},
        {"V", {{"em", 0.05}, {"học", 0.45}, {"bài", 0.05}, {"toán", 0.02}}}
    };
    vector<string> cau = {"em", "học", "bài", "toán"};
    
    pair<vector<string>, double> kq_v = viterbi(cau, nhan, pi, A, B);
    cout << "\n--- Viterbi ---\nDay nhan : [ ";
    for (string t : kq_v.first) cout << t << " ";
    cout << "]\nXac suat : " << fixed << setprecision(9) << kq_v.second << "\n";
    
    pair<vector<string>, double> kq_vc = vet_can_viterbi(cau, nhan, pi, A, B);
    cout << "\n--- Vét cạn đối chiếu ---\nDay nhan : [ ";
    for (string t : kq_vc.first) cout << t << " ";
    cout << "]\nXac suat : " << fixed << setprecision(9) << kq_vc.second << "\n";
    
    // Đối chiếu chương trình chính và kiểm chứng độc lập
    if (kq_v.first != kq_vc.first) {
        cerr << "LOI KIEM CHUNG: Viterbi khong khop voi vet can!" << endl;
        return 1;
    }
    
    return 0;
}