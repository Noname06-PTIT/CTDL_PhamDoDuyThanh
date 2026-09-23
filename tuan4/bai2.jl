function main()
    line = readline()
    if isempty(strip(line))
        return
    end
    n = parse(Int, strip(line))
    if n <= 0 || n > 31
        return
    end

    full_mask = (UInt32(1) << n) - UInt32(1)
    x = zeros(Int, n)
    first_solution = zeros(Int, n)
    node_count     = Ref{Int}(0)
    solution_count = Ref{Int}(0)

    function backtrack(row::Int, cols::UInt32, d1::UInt32, d2::UInt32)
        node_count[] += 1
        if row > n
            solution_count[] += 1
            if solution_count[] == 1
                first_solution .= x
            end
            return
        end
        avail = full_mask & ~(cols | d1 | d2)
        while avail != 0
            bit = avail & -avail
            avail ⊻= bit
            x[row] = trailing_zeros(bit) + 1        # 1-indexed
            backtrack(row + 1,
                      cols | bit,
                      ((d1 | bit) << 1) & full_mask,
                      (d2 | bit) >> 1)
        end
    end

    backtrack(1, UInt32(0), UInt32(0), UInt32(0))

    println("So nut da duyet: ", node_count[])
    println("So loi giai: ", solution_count[])
    if solution_count[] > 0
        println("Ban co loi giai dau tien:")
        for i in 1:n
            row = [first_solution[i] == j ? "Q" : "." for j in 1:n]
            println(join(row, " "))
        end
    else
        println("Khong co loi giai nao.")
    end
end

main()