function solve_knapsack()
    # QUY ƯỚC CHỈ SỐ:
    # Trong bài toán, bảng f có hàng 0 và cột 0 (f[0][0], f[1][0], ...).
    # Julia không hỗ trợ chỉ số 0 mặc định, nên ta dùng mảng kích thước (n+1) x (W+1).
    # Tương ứng: f[i+1, j+1] trong code là f[i][j] trong toán học.
    
    # Đọc toàn bộ đầu vào và chia thành các token
    input_str = read(stdin, String)
    tokens = split(input_str)
    if isempty(tokens)
        return
    end
    
    n = parse(Int, tokens[1])
    W = parse(Int, tokens[2])
    
    # Khởi tạo mảng w và v kích thước n+1
    w = zeros(Int, n + 1)
    v = zeros(Int, n + 1)
    
    # Điền dữ liệu (bỏ qua phần tử 0 ở đầu)
    for i in 1:n
        w[i+1] = parse(Int, tokens[2 + i])
    end
    for i in 1:n
        v[i+1] = parse(Int, tokens[2 + n + i])
    end
    
    # Khởi tạo bảng f (n+1) x (W+1) toàn 0
    f = zeros(Int, n + 1, W + 1)
    
    # Quy hoạch động cái túi 0/1
    for i in 1:n
        for j in 0:W
            f[i+1, j+1] = f[i, j+1]  # Tương ứng: f[i][j] = f[i-1][j]
            if j >= w[i+1]            # Tương ứng: if j >= w[i]
                # Tương ứng: f[i][j] = max(f[i][j], f[i-1][j-w[i]] + v[i])
                f[i+1, j+1] = max(f[i+1, j+1], f[i, j - w[i+1] + 1] + v[i+1])
            end
        end
    end
    
    # In toàn bộ bảng f
    println("BANG F:")
    print("i/j\t0")
    for j in 1:W
        print("\t$j")
    end
    println()
    for i in 0:n
        print("i=$i\t")
        for j in 0:W
            print(f[i+1, j+1])
            if j < W
                print("\t")
            end
        end
        println()
    end
    
    println("\nGIA TRI LON NHAT: ", f[n+1, W+1])
    
    # Truy vết tìm tập đồ vật được chọn
    chosen = Int[]
    j = W
    for i in n:-1:1
        if f[i+1, j+1] != f[i, j+1]
            push!(chosen, i)
            j -= w[i+1]
        end
    end
    reverse!(chosen) # Đảo ngược để in ra theo thứ tự đồ vật tăng dần
    println("TAP DO VAT DUOC CHON (chi so 1-based): ", join(chosen, " "))
end

solve_knapsack()