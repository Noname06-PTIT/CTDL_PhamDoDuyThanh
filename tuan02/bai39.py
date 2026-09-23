import random
import time

# --- CÁCH 1: O(n^3) ---
def max_subarray_c1(a):
    n = len(a)
    best = a[0]
    for i in range(n):
        for j in range(i, n):
            cur_sum = 0
            for k in range(i, j + 1):
                cur_sum += a[k]
            if cur_sum > best:
                best = cur_sum
    return best

# --- CÁCH 2: O(n^2) ---
def max_subarray_c2(a):
    n = len(a)
    best = a[0]
    prefix = [0] * (n + 1)
    for i in range(n):
        prefix[i + 1] = prefix[i] + a[i]
    for i in range(n):
        for j in range(i, n):
            cur_sum = prefix[j + 1] - prefix[i]
            if cur_sum > best:
                best = cur_sum
    return best

# --- CÁCH 3: Kadane O(n) ---
def max_subarray_c3(a):
    best = a[0]
    cur = a[0]
    for i in range(1, len(a)):
        cur = max(a[i], cur + a[i])
        best = max(best, cur)
    return best

# --- 1. CHẠY TEST BẮT BUỘC ---
def run_manual_tests():
    tests = [
        ([4, -3, 5, -2, -1, 2, 6, -9], 11),
        ([-5, -2, -9], -2),
        ([1, 2, 3, 4], 10),
        ([-2, 1, -3, 4, -1, 2, 1, -5, 4], 6),
        ([0, -1, 0], 0)
    ]
    print("=== KET QUA TEST BAT BUOC ===")
    for i, (arr, expected) in enumerate(tests):
        r1, r2, r3 = max_subarray_c1(arr), max_subarray_c2(arr), max_subarray_c3(arr)
        status = "PASS" if (r1 == r2 == r3 == expected) else "FAIL"
        print(f"Test {i+1}: {status} (C1={r1}, C2={r2}, C3={r3}, Expected={expected})")

# --- 2. KIỂM THỬ TỰ ĐỘNG ---
def run_auto_test():
    print("\n=== KIEM THU TU DONG (1000 TESTS) ===")
    for _ in range(1000):
        n = random.randint(1, 50)
        a = [random.randint(-50, 50) for _ in range(n)]
        r1, r2, r3 = max_subarray_c1(a), max_subarray_c2(a), max_subarray_c3(a)
        if not (r1 == r2 == r3):
            print(f"FAIL! Phan vi du: {a}")
            print(f"C1={r1}, C2={r2}, C3={r3}")
            return
    print("OK")

# --- 3. ĐO THỜI GIAN ---
def benchmark(arr, func):
    start = time.perf_counter()
    func(arr)
    return time.perf_counter() - start

def run_benchmark():
    print("\n=== BANG THOI GIAN VA DOI CHIEU ===")
    sizes = [200, 400, 800]
    results = {"C1 (O(n^3))": [], "C2 (O(n^2))": [], "C3 (O(n))": []}
    
    # Dùng giá trị lớn hơn để dễ đo thời gian, tránh bị 0s
    for n in sizes:
        a = [random.randint(-1000, 1000) for _ in range(n)]
        results["C1 (O(n^3))"].append(benchmark(a, max_subarray_c1))
        results["C2 (O(n^2))"].append(benchmark(a, max_subarray_c2))
        results["C3 (O(n))"].append(benchmark(a, max_subarray_c3))

    print(f"{'Thoi gian (s)':<15} | {'n=200':<10} | {'n=400':<10} | {'n=800':<10} | {'T(400)/T(200)':<15} | {'T(800)/T(400)':<15}")
    print("-" * 90)
    
    for name, times in results.items():
        r1 = times[1] / times[0] if times[0] > 0 else 0
        r2 = times[2] / times[1] if times[1] > 0 else 0
        print(f"{name:<15} | {times[0]:<10.4f} | {times[1]:<10.4f} | {times[2]:<10.4f} | {r1:<15.2f} | {r2:<15.2f}")

if __name__ == "__main__":
    run_manual_tests()
    run_auto_test()
    # Lưu ý: Cách 1 với n=800 trong Python có thể mất khoảng 10-30 giây do Python chạy chậm
    run_benchmark() 