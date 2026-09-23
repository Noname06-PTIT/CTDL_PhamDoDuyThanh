# x luu hoan vi; da_dung[v] gan voi GIA TRI v.
function thu(i::Int, n::Int, x, da_dung)
    # --- KHOI DIEU KIEN DA SUA ---
    if i > n
        p = 1  # Thay 2 bang p trong R0 (với s = 6, n = 3 thì p = 1)
        if x[1] != p
            return 0
        end
        println(join(x, " "))
        return 1
    end
    # -----------------------------
    dem = 0
    for v in 1:n
        if !da_dung[v]
            x[i] = v
            da_dung[v] = true
            dem += thu(i + 1, n, x, da_dung)
            da_dung[v] = false  # Hoan tac sau khi quay ve (giu nguyen).
        end
    end
    return dem
end

function liet_ke(n::Int)
    x = zeros(Int, n)
    da_dung = falses(n)
    return thu(1, n, x, da_dung)
end

function main()
    println("MSSV: N24DCDT086 | Ma ca: 6")
    println("Nhap n (1..7):")
    n = tryparse(Int, strip(readline()))
    if n === nothing || !(1 <= n <= 7)
        println("Du lieu khong hop le.")
        return
    end
    dem = liet_ke(n)
    println("So hoan vi dat: ", dem)
end

main()
