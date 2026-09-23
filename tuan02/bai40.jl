function solve()
    data = split(read(stdin, String))
    if isempty(data) return end
    
    n = parse(Int, data[1])
    a = [parse(Int, data[i+1]) for i in 1:n]
    
    if n == 0 return end

    # Khởi tạo (Julia đánh số mảng từ 1 nên rất thuận lợi)
    best_sum = a[1]
    cur_sum = a[1]
    best_start = 1
    best_end = 1
    cur_start = 1

    for i in 2:n
        if cur_sum > 0
            cur_sum += a[i]
        else
            cur_sum = a[i]
            cur_start = i
        end

        # Dùng > để ưu tiên đoạn xuất hiện sớm nhất
        if cur_sum > best_sum
            best_sum = cur_sum
            best_start = cur_start
            best_end = i
        end
    end

    # --- PHÉM KIỂM TRA CHÉO (CROSS-CHECK) ---
    check_sum = sum(a[best_start:best_end])
    @assert check_sum == best_sum "Lỗi kiểm tra chéo: $check_sum != $best_sum"
    # -----------------------------------------

    println("tổng $best_sum, đoạn [$best_start..$best_end]")
end

solve()