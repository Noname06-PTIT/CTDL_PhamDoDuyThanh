function dao_nguoc_so(n::Int)
    # Quy ước: Tách dấu ra xử lý riêng, đảo phần trị tuyệt đối
    # Lý do: Trong Julia, phép modulo (%) giữ nguyên dấu của số bị chia (-123 % 10 = -3)
    # nên ta phải lấy trị tuyệt đối để không bị dính chữ số âm.
    sign = n < 0 ? -1 : 1
    abs_n = abs(n)
    
    rev = 0
    while abs_n > 0
        rev = rev * 10 + abs_n % 10
        abs_n = div(abs_n, 10) # Dùng div() hoặc phép ÷= để chia nguyên
    end
    
    return sign * rev
end

# Xử lý đọc đến hết file (EOF)
# eachline(stdin) sẽ tự động lặp qua từng dòng cho đến khi kết thúc tệp
for line in eachline(stdin)
    line = strip(line)
    if !isempty(line)
        n = parse(Int, line)
        println(dao_nguoc_so(n))
    end
end