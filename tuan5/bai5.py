import sys

def solve_knapsack():
    # Đọc toàn bộ đầu vào
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    W = int(input_data[1])
    
    w = [0] * (n + 1)
    v = [0] * (n + 1)
    
    for i in range(1, n + 1):
        w[i] = int(input_data[1 + i])
    for i in range(1, n + 1):
        v[i] = int(input_data[1 + n + i])

    # Khởi tạo bảng f (n+1) x (W+1) toàn 0
    f = [[0] * (W + 1) for _ in range(n + 1)]

    # Quy hoạch động cái túi 0/1
    for i in range(1, n + 1):
        for j in range(W + 1):
            f[i][j] = f[i-1][j] # Mặc định không lấy đồ vật i
            if j >= w[i]:
                f[i][j] = max(f[i][j], f[i-1][j-w[i]] + v[i])

    # In toàn bộ bảng f
    print("BANG F:")
    header = "i/j\t0" + "".join(f"\t{j}" for j in range(1, W + 1))
    print(header)
    for i in range(n + 1):
        row_str = f"i={i}\t" + "\t".join(str(f[i][j]) for j in range(W + 1))
        print(row_str)

    print(f"\nGIA TRI LON NHAT: {f[n][W]}")

    # Truy vết tìm tập đồ vật được chọn
    chosen = []
    j = W
    for i in range(n, 0, -1):
        if f[i][j] != f[i-1][j]: # Nếu giá trị khác hàng trên, tức là đã lấy đồ vật i
            chosen.append(i)
            j -= w[i]
    
    chosen.reverse() # Đảo ngược để in ra theo thứ tự đồ vật tăng dần
    print("TAP DO VAT DUOC CHON (chi so 1-based):", " ".join(map(str, chosen)))

if __name__ == '__main__':
    solve_knapsack()