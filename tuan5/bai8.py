import itertools

# 1. Liệt kê toàn bộ câu độ dài 3 và tính điểm
def liet_ke_va_tinh_diem(P, start, L):
    def dfs(cau, diem):
        if len(cau) == L:
            print(f"  Câu: {' '.join(cau)} - Điểm: {diem:.4f}")
            return cau, diem
        best_c, best_d = None, -1.0
        tt = cau[-1]
        if tt in P:
            for w, p in P[tt].items():
                c, d = dfs(cau + [w], diem * p)
                if d > best_d:
                    best_d = d
                    best_c = c
        return best_c, best_d
    return dfs([start], 1.0)

# 2 & 3. Giải mã tham lam và giải mã theo chùm
def beam_search(P, start, L, k):
    beam = [([start], 1.0)]
    for _ in range(L - 1):
        new_beam = []
        for cau, d in beam:
            tt = cau[-1]
            if tt in P:
                for w, p in P[tt].items():
                    new_beam.append((cau + [w], d * p))
        new_beam.sort(key=lambda x: x[1], reverse=True)
        beam = new_beam[:k]
    return beam[0]

# 4. Viterbi gán nhãn
def viterbi(cau, nhan, pi, A, B):
    T = len(cau)
    f = [{} for _ in range(T)]
    tu = [{} for _ in range(T)]
    
    for t in nhan:
        f[0][t] = pi.get(t, 0) * B.get(t, {}).get(cau[0], 0)
        tu[0][t] = None
        
    for i in range(1, T):
        for t in nhan:
            tot, gt = None, -1.0
            for s in nhan:
                x = f[i-1][s] * A.get(s, {}).get(t, 0)
                if x > gt:
                    gt, tot = x, s
            f[i][t] = gt * B.get(t, {}).get(cau[i], 0)
            tu[i][t] = tot
            
    cuoi = max(nhan, key=lambda t: f[T-1][t])
    day = [cuoi]
    for i in range(T-1, 0, -1):
        day.append(tu[i][day[-1]])
    day.reverse()
    return day, f[T-1][cuoi]

# Chương trình kiểm chứng vét cạn
def vet_can_viterbi(cau, nhan, pi, A, B):
    best_seq = None
    best_prob = -1.0
    for seq in itertools.product(nhan, repeat=len(cau)):
        prob = pi.get(seq[0], 0) * B.get(seq[0], {}).get(cau[0], 0)
        for i in range(1, len(cau)):
            prob *= A.get(seq[i-1], {}).get(seq[i], 0) * B.get(seq[i], {}).get(cau[i], 0)
        if prob > best_prob:
            best_prob = prob
            best_seq = seq
    return list(best_seq), best_prob

if __name__ == "__main__":
    P = {
        "em": {"học": 0.52, "đi": 0.48},
        "học": {"bài": 0.40, "toán": 0.35, "vẽ": 0.25},
        "đi": {"chợ": 0.58, "bơi": 0.22, "ngủ": 0.20}
    }
    
    print("--- Liệt kê toàn bộ câu độ dài 3 ---")
    best_cau, best_diem = liet_ke_va_tinh_diem(P, "em", 3)
    print(f"Liệt kê: câu tốt nhất {' '.join(best_cau)} {best_diem:.4f}\n")
    
    print("--- Beam Search ---")
    b1 = beam_search(P, "em", 3, 1)
    print(f"Tham lam (Beam k=1): {' '.join(b1[0])} - Điểm: {b1[1]:.4f}")
    b2 = beam_search(P, "em", 3, 2)
    print(f"Beam k=2          : {' '.join(b2[0])} - Điểm: {b2[1]:.4f}")
    b3 = beam_search(P, "em", 3, 3)
    print(f"Beam k=3          : {' '.join(b3[0])} - Điểm: {b3[1]:.4f}")
    print("-" * 40)
    
    nhan = ["N", "V"]
    pi = {"N": 0.6, "V": 0.4}
    A = {"N": {"N": 0.35, "V": 0.65}, "V": {"N": 0.70, "V": 0.30}}
    B = {
        "N": {"em": 0.35, "học": 0.10, "bài": 0.40, "toán": 0.30},
        "V": {"em": 0.05, "học": 0.45, "bài": 0.05, "toán": 0.02}
    }
    cau = ["em", "học", "bài", "toán"]
    
    nhan_kq, xac_suat = viterbi(cau, nhan, pi, A, B)
    print("Viterbi dãy nhãn   :", nhan_kq)
    print("Xác suất lớn nhất  :", f"{xac_suat:.9f}")
    
    vc_nhan, vc_xs = vet_can_viterbi(cau, nhan, pi, A, B)
    print("\n--- Vét cạn đối chiếu ---")
    print("Vét cạn dãy nhãn   :", vc_nhan)
    print("Xác suất lớn nhất  :", f"{vc_xs:.9f}")
    
    # Đối chiếu chương trình chính và kiểm chứng độc lập
    assert nhan_kq == vc_nhan, "LỖI KIỂM CHỨNG: Viterbi không khớp với Vét cạn!"