# [DÁN MÃ NGUỒN PYTHON BÀI TOÁN TWO POINTERS TẠI ĐÂY]
def find_pairs_two_pointers(arr, S):
    # Bước 1: Sắp xếp mảng
    arr.sort()
    left = 0
    right = len(arr) - 1
    results = []
    
    # Bước 2: Dùng 2 con trỏ để tìm cặp
    while left < right:
        current_sum = arr[left] + arr[right]
        if current_sum == S:
            results.append((arr[left], arr[right]))
            left += 1
            right -= 1
        elif current_sum < S:
            left += 1  # Tổng nhỏ quá, cần tăng con trỏ trái
        else:
            right -= 1 # Tổng lớn quá, cần giảm con trỏ phải
            
    return results

# --- THỰC NGHIỆM ---
test_arr = [1, 4, 3, 2, 5, 7, 6]
S = 9
print(f"Mảng ban đầu: {test_arr}")
print(f"Tìm các cặp có tổng bằng {S}: {find_pairs_two_pointers(test_arr, S)}")