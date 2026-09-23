import sys

def solve():
    # Đọc toàn bộ đầu vào
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    a = [int(x) for x in input_data[1:n+1]]
    
    if n == 0:
        return

    # Khởi tạo các biến (chỉ số bắt đầu từ 1)
    best_sum = a[0]
    cur_sum = a[0]
    best_start = 1
    best_end = 1
    cur_start = 1

    # Duyệt từ phần tử thứ 2 (index 1 trong mảng 0-based)
    for i in range(1, n):
        if cur_sum > 0:
            cur_sum += a[i]
        else:
            # Bắt đầu đoạn mới
            cur_sum = a[i]
            cur_start = i + 1  # Chuyển về 1-based
        
        # Cập nhật kết quả tốt nhất (dùng > để giữ đoạn xuất hiện đầu tiên)
        if cur_sum > best_sum:
            best_sum = cur_sum
            best_start = cur_start
            best_end = i + 1    # Chuyển về 1-based

    # --- PHÉP KIỂM TRA CHÉO (CROSS-CHECK) ---
    check_sum = 0
    for i in range(best_start - 1, best_end):
        check_sum += a[i]
    assert check_sum == best_sum, f"Lỗi kiểm tra chéo: {check_sum} != {best_sum}"
    # -----------------------------------------

    print(f"tổng {best_sum}, đoạn [{best_start}..{best_end}]")

if __name__ == "__main__":
    solve()