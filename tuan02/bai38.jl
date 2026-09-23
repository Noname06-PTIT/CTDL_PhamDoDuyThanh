function solve()
    data = split(read(stdin, String))
    if isempty(data)
        println("nghiêm ngặt: YES — không giảm: YES")
        return
    end
    
    n = parse(Int, data[1])
    
    if n <= 1
        println("nghiêm ngặt: YES — không giảm: YES")
        return
    end
    
    # Lấy mảng, lưu ý Julia bắt đầu index từ 1
    arr = [parse(Int, data[i]) for i in 2:n+1]
    
    is_strict = true
    is_non_decr = true
    
    # Chỉ số i chạy từ 1 đến n-1 (khác hẳn C++ và Python)
    for i in 1:(n-1)
        if arr[i] > arr[i+1]
            is_strict = false
            is_non_decr = false
        elseif arr[i] == arr[i+1]
            is_strict = false
        end
        
        if !is_strict && !is_non_decr
            break
        end
    end
    
    s1 = is_strict ? "YES" : "NO"
    s2 = is_non_decr ? "YES" : "NO"
    
    println("nghiêm ngặt: $s1 — không giảm: $s2")
end

solve()