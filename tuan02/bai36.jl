# Khai báo hằng số ở phạm vi TOÀN CỤC
const LLONG_MAX = 9223372036854775807

function format_number(s::String)::String
    """Hàm chèn dấu cách cách nhau 3 chữ số từ phải sang trái"""
    res = IOBuffer()
    len = length(s)
    for (i, c) in enumerate(s)
        if (len - i) % 3 == 0 && i != 1
            write(res, " ")
        end
        write(res, c)
    end
    return String(take!(res))
end

function solve(n::Int)
    """Xử lý một test case duy nhất"""
    # Biến f dùng Int128 để tránh lỗi OverflowError của Julia
    f::Int128 = 1
    overflow = false
    overflow_at_i = 0
    
    for i in 1:n
        if f > div(LLONG_MAX, i)
            overflow = true
            overflow_at_i = i
            break
        end
        f *= i
    end
    
    if !overflow
        println(format_number(string(f)))
    else
        # Tính đúng giá trị thực tế bằng Int128 để in ra thông báo
        for i in overflow_at_i:n
            f *= i
        end
        
        exact_str = string(f)
        max_str = string(LLONG_MAX)
        println("TRAN SO ($(n)! = $(format_number(exact_str)) > $(format_number(max_str)))")
    end
end

function main()
    # Đọc tất cả các dòng từ đầu vào
    for line in readlines(stdin)
        line = strip(line)
        if !isempty(line)
            n = parse(Int, line)
            solve(n)
        end
    end
end

main()