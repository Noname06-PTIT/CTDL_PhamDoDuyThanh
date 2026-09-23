# [DÁN MÃ NGUỒN JULIA BÀI TOÁN TWO POINTERS TẠI ĐÂY]
function find_pairs_two_pointers(arr, S)
    # Bước 1: Sắp xếp mảng (Julia dùng sort! để sắp xếp in-place)
    sort!(arr)
    
    left = 1
    right = length(arr)
    results = Tuple{Int, Int}[]
    
    # Bước 2: Dùng 2 con trỏ để tìm cặp
    while left < right
        current_sum = arr[left] + arr[right]
        if current_sum == S
            push!(results, (arr[left], arr[right]))
            left += 1
            right -= 1
        elseif current_sum < S
            left += 1 # Tổng nhỏ quá, cần tăng con trỏ trái
        else
            right -= 1 # Tổng lớn quá, cần giảm con trỏ phải
        end
    end
    return results
end

# --- THỰC NGHIỆM ---
test_arr = [1, 4, 3, 2, 5, 7, 6]
S = 9
println("Mảng ban đầu: $test_arr")
pairs_found = find_pairs_two_pointers(copy(test_arr), S)
println("Tìm các cặp có tổng bằng $S: $pairs_found")