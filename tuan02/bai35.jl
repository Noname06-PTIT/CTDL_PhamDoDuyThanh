# Cách 1: Kiểm tra từng số
function method1(n::Int)
    count = 0
    total = 0
    primes = Int[]
    for i in 2:n
        is_p = true
        if i % 2 == 0 || i % 3 == 0
            if i != 2 && i != 3
                is_p = false
            end
        end
        if is_p
            j = 5
            while j * j <= i
                if i % j == 0 || i % (j + 2) == 0
                    is_p = false
                    break
                end
                j += 6
            end
        end
        if is_p
            count += 1
            total += i
            if n <= 30
                push!(primes, i)
            end
        end
    end
    
    if n <= 30
        println(join(primes, " "), "  ($count số)")
    elseif n < 1000000
        println("số lượng = $count")
    else
        println("số lượng = $count, tổng = $total")
    end
end

# Cách 2: Sàng Eratosthenes
function method2(n::Int)
    n < 2 && return
    is_p = trues(n)
    is_p[1] = false
    i = 2
    while i * i <= n
        if is_p[i]
            for j in i*i:i:n
                is_p[j] = false
            end
        end
        i += 1
    end
    
    count = 0
    total = 0
    primes = Int[]
    for i in 2:n
        if is_p[i]
            count += 1
            total += i
            if n <= 30
                push!(primes, i)
            end
        end
    end
    
    if n <= 30
        println(join(primes, " "), "  ($count số)")
    elseif n < 1000000
        println("số lượng = $count")
    else
        println("số lượng = $count, tổng = $total")
    end
end

# CHẠY TRƯỚC 1 LẦN ĐỂ LOẠI BỎ THỜI GIAN BIÊN DỊCH JIT (BẮT BUỘC THEO GỢI Ý)
method1(10)
method2(10)

function main()
    for line in eachline(stdin)
        if isempty(line) continue end
        n = parse(Int, line)
        method2(n) # Gọi sàng để tối ưu
    end
end

main()