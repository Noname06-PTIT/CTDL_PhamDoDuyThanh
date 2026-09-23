function isPerfectSquare(n)
    if n < 0 return false end
    lo, hi = 0, 1_000_000_000
    while lo <= hi
        mid = (lo + hi) ÷ 2
        sq = mid * mid
        if sq == n
            return true
        elseif sq < n
            lo = mid + 1
        else
            hi = mid - 1
        end
    end
    return false
end

# --- ĐỔI HÀM NÀY ---
function main()
    for line in eachline(stdin)
        # Nếu gõ Enter mà không có gì thì bỏ qua
        if isempty(strip(line))
            continue
        end
        # Xử lý từng số trên cùng 1 dòng (cách nhau bởi dấu cách)
        for tok in split(line)
            n = parse(Int, tok)
            println(isPerfectSquare(n) ? "YES" : "NO")
        end
    end
end

main()