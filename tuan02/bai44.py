import time
import random
import matplotlib.pyplot as plt

def selection_sort(arr):
    n = len(arr)
    for i in range(n - 1):
        min_idx = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        if min_idx != i:
            arr[i], arr[min_idx] = arr[min_idx], arr[i]

# Bẫy 1: Bo qua dong do dau tien (lam sach cache va bo nho)
warmup_arr = random.sample(range(10000), 500)
selection_sort(warmup_arr)

sizes = [500, 1000, 2000, 4000]
times = []
NUM_RUNS = 3

print(f"Chay moi mốc {NUM_RUNS} lan va lay gia tri nho nhat:")
for n in sizes:
    min_t = float('inf')
    for _ in range(NUM_RUNS):
        # Tạo mảng ngẫu nhiên để tránh tối ưu hóa từ compiler/interpreter
        arr = random.sample(range(n * 10), n)
        
        start = time.perf_counter() # Bẫy 3: Dùng đồng hồ có độ phân giải cao
        selection_sort(arr)
        end = time.perf_counter()
        
        min_t = min(min_t, end - start)
    times.append(min_t)
    print(f"n = {n:4d}: {min_t:.6f} s")

print("\n--- Bang ty le T(2n)/T(n) ---")
for i in range(1, len(sizes)):
    ratio = times[i] / times[i-1]
    print(f"T({sizes[i]})/T({sizes[i-1]}) = {ratio:.2f}")

# === VE DO THI ===
plt.figure(figsize=(8, 5))
# Đồ thị thời gian thực tế
plt.plot(sizes, times, marker='o', linestyle='-', color='b', label='Thời gian thực tế (s)')

# Đồ thị lý thuyết O(n²) (cân chỉnh hệ số c để đi qua điểm thực tế đầu tiên)
c = times[0] / (sizes[0]**2)
theoretical_times = [c * (n**2) for n in sizes]
plt.plot(sizes, theoretical_times, marker='x', linestyle='--', color='r', label='Đường lý thuyết c·n²')

# Vẽ trên thang log-log (đường thẳng có hệ số góc 2)
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Kích thước mảng n (thang log)')
plt.ylabel('Thời gian (giây, thang log)')
plt.title('Đồ thị thời gian thuật toán O(n²) - Thang Log-Log')
plt.legend()
plt.grid(True, which="both", ls="--")

# Lưu ảnh
plt.savefig('plot_o_n2_python.png')
print("\nDa luu do thi vao file 'plot_o_n2_python.png'")
# plt.show() # Uncomment de hien thi cua so