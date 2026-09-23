# x luu hoan vi; da_dung[v] gan voi GIA TRI v.
def thu(i: int, n: int, x: list, da_dung: list) -> int:
    # --- KHỐI ĐIỀU KIỆN ĐÃ SỬA ---
    if i == n:
        p = 1  # Thay 2 bằng p trong R0 (với s = 6, n = 3 thì p = 1)
        if x[0] != p:
            return 0
        print(" ".join(map(str, x)))
        return 1
    # -----------------------------
    dem = 0
    for v in range(1, n + 1):
        if not da_dung[v]:
            x[i] = v
            da_dung[v] = True
            dem += thu(i + 1, n, x, da_dung)
            da_dung[v] = False  # Hoan tac sau khi quay ve (giữ nguyên).
    return dem

def liet_ke(n: int) -> int:
    x = [0] * n
    da_dung = [False] * (n + 1)  # Bo trong chi so 0.
    return thu(0, n, x, da_dung)

def main():
    print("MSSV: N24DCDT086 | Ma ca: 6")
    print("Nhap n (1..7):")
    try:
        n = int(input().strip())
    except (ValueError, EOFError):
        print("Du lieu khong hop le.")
        return
    if not 1 <= n <= 7:
        print("Du lieu khong hop le.")
        return
    dem = liet_ke(n)
    print("So hoan vi dat:", dem)

if __name__ == "__main__":
    main()

