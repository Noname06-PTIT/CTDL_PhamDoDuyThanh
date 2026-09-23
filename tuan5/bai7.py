import itertools

def chon_hoat_dong(hd, tieu_chi):
    if tieu_chi == "ket_thuc":
        hd_sorted = sorted(hd, key=lambda x: x[1])
    elif tieu_chi == "bat_dau":
        hd_sorted = sorted(hd, key=lambda x: x[0])
    elif tieu_chi == "ngan_nhat":
        hd_sorted = sorted(hd, key=lambda x: x[1] - x[0])
    elif tieu_chi == "it_chong_lan":
        chong_lan = []
        for i in range(len(hd)):
            count = 0
            for j in range(len(hd)):
                if i != j and not (hd[i][1] <= hd[j][0] or hd[j][1] <= hd[i][0]):
                    count += 1
            chong_lan.append((count, hd[i]))
        hd_sorted = [x[1] for x in sorted(chong_lan, key=lambda x: x[0])]

    ans = []
    het = -1
    for s, f, idx in hd_sorted:
        if s >= het:
            ans.append(idx)
            het = f
    return ans

# Chương trình kiểm chứng độc lập bằng Vét cạn (Brute-force)
def kiem_chung_vet_can(hd):
    n = len(hd)
    if n == 0: return 0
    # Thử tất cả các kích thước tập con từ n xuống 1
    for r in range(n, 0, -1):
        for combo in itertools.combinations(hd, r):
            combo_sorted = sorted(combo, key=lambda x: x[1])
            valid = True
            for i in range(len(combo_sorted) - 1):
                if combo_sorted[i][1] > combo_sorted[i+1][0]:
                    valid = False
                    break
            if valid:
                return r # Trả về ngay kích thước lớn nhất tìm được
    return 0

if __name__ == "__main__":
    s = [1, 2, 2, 3, 4, 6, 8, 9, 11, 12]
    f = [5, 5, 6, 4, 8, 9, 11, 14, 13, 15]
    hd = [(s[i], f[i], f"H{i+1}") for i in range(10)]

    kq_ket_thuc = chon_hoat_dong(hd, "ket_thuc")
    kq_vet_can = kiem_chung_vet_can(hd)
    
    # Đối chiếu chương trình chính và kiểm chứng độc lập
    assert len(kq_ket_thuc) == kq_vet_can, "LỖI KIỂM CHỨNG: Tham lam không khớp với Vét cạn!"

    print("Kết thúc sớm nhất :", kq_ket_thuc)
    print("Bắt đầu sớm nhất  :", chon_hoat_dong(hd, "bat_dau"))
    print("Ngắn nhất         :", chon_hoat_dong(hd, "ngan_nhat"))
    print("Ít chồng lấn nhất :", chon_hoat_dong(hd, "it_chong_lan"))
    print("-" * 30)
    print(f"Số nhiều nhất thật sự (Vét cạn kiểm chứng): {kq_vet_can}")