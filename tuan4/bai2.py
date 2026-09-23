import sys

def main():
    try:
        line = sys.stdin.readline().strip()
        if not line:
            return
        n = int(line)
        if n <= 0:
            return
    except Exception:
        return

    full_mask = (1 << n) - 1
    x = [0] * n
    first_solution = [0] * n

    # Stack trạng thái cho mỗi hàng (lặp thay vì đệ quy để tránh overhead)
    cols_arr = [0] * (n + 1)
    d1_arr   = [0] * (n + 1)
    d2_arr   = [0] * (n + 1)
    avail_arr = [0] * (n + 1)
    avail_arr[0] = full_mask

    row = 0
    node_count = 1            # tương đương lời gọi backtrack(0)
    solution_count = 0

    while row >= 0:
        avail = avail_arr[row]
        if avail:
            bit = avail & -avail                 # lấy bit thấp nhất
            avail_arr[row] = avail ^ bit          # xoá bit vừa lấy
            x[row] = bit.bit_length() - 1        # vị trí cột (0-indexed)

            new_cols = cols_arr[row] | bit
            new_d1   = ((d1_arr[row] | bit) << 1) & full_mask
            new_d2   = (d2_arr[row] | bit) >> 1

            if row == n - 1:                      # đặt xong hậu cuối -> lá
                solution_count += 1
                node_count += 1                  # nút lá backtrack(n)
                if solution_count == 1:
                    first_solution[:] = x
            else:                                 # đi sâu hơn
                row += 1
                cols_arr[row] = new_cols
                d1_arr[row]   = new_d1
                d2_arr[row]   = new_d2
                avail_arr[row] = full_mask & ~(new_cols | new_d1 | new_d2)
                node_count += 1
        else:
            row -= 1                              # backtrack

    out = [f"So nut da duyet: {node_count}",
           f"So loi giai: {solution_count}"]
    if solution_count > 0:
        out.append("Ban co loi giai dau tien:")
        for i in range(n):
            out.append(" ".join("Q" if first_solution[i] == j else "."
                                for j in range(n)))
    else:
        out.append("Khong co loi giai nao.")
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    main()