# Ma trận đề bài Sudoku mục E (0 là ô trống)
board = [
    5 3 0 0 7 0 0 0 0;
    6 0 0 1 9 5 0 0 0;
    0 9 8 0 0 0 0 6 0;
    8 0 0 0 6 0 0 0 3;
    4 0 0 8 0 3 0 0 1;
    7 0 0 0 2 0 0 0 6;
    0 6 0 0 0 0 2 8 0;
    0 0 0 4 1 9 0 0 5;
    0 0 0 0 8 0 0 7 9
]

calls_count = 0

function is_valid(b::Matrix{Int}, r::Int, c::Int, num::Int)
    for i in 1:9
        if b[r, i] == num || b[i, c] == num
            return false
        end
    end
    br = 3 * div(r - 1, 3) + 1
    bc = 3 * div(c - 1, 3) + 1
    for i in 0:2
        for j in 0:2
            if b[br + i, bc + j] == num
                return false
            end
        end
    end
    return true
end

function solve_sequential!(b::Matrix{Int})
    global calls_count
    calls_count += 1
    for r in 1:9, c in 1:9
        if b[r, c] == 0
            for num in 1:9
                if is_valid(b, r, c, num)
                    b[r, c] = num
                    if solve_sequential!(b) return true end
                    b[r, c] = 0
                end
            end
            return false
        end
    end
    return true
end

function solve_mrv!(b::Matrix{Int})
    global calls_count
    calls_count += 1
    
    best_r, best_c = 0, 0
    min_opts = 10
    best_nums = Int[]
    
    for r in 1:9, c in 1:9
        if b[r, c] == 0
            opts = [n for n in 1:9 if is_valid(b, r, c, n)]
            if length(opts) < min_opts
                min_opts = length(opts)
                best_r, best_c = r, c
                best_nums = opts
                if min_opts == 0 return false end
                if min_opts == 1 break end
            end
        end
    end
    
    if best_r == 0 return true end
    
    for num in best_nums
        b[best_r, best_c] = num
        if solve_mrv!(b) return true end
        b[best_r, best_c] = 0
    end
    return false
end

function run_solver(name::String, solver::Function)
    global calls_count
    b = copy(board)
    calls_count = 0
    
    start = time()
    success = solver(b)
    finish = time()
    
    println("--- ", name, " ---")
    if success
        println("Thoi gian chay: ", finish - start, " giay")
        println("So loi goi de quy: ", calls_count)
    end
end

run_solver("QUET TUAN TU", solve_sequential!)
println()
run_solver("MRV", solve_mrv!)