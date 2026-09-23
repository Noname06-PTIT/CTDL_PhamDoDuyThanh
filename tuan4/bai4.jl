# Ma trận chuẩn mục D của đề bài (Julia đánh chỉ số từ 1)
matrix = [
    0 10  9 22 23;
   10  0 16 19 14;
    9 16  0  7 28;
   22 19  7  0  8;
   23 14 28  8  0
]
N = size(matrix, 1)

# Tìm c_min (bỏ qua đường chéo chính)
c_min = minimum(matrix[i, j] for i in 1:N for j in 1:N if i != j)

best_cost = typemax(Int)
best_path = Int[]
nodes_visited = 0

function dfs(city::Int, visited::Int, cost::Int, path::Vector{Int}, prune::Bool)
    global best_cost, best_path, nodes_visited
    nodes_visited += 1
    
    # Số cạnh còn lại cần đi: N - (độ dài path - 1)
    edges_left = N - (length(path) - 1)
    lower_bound = cost + edges_left * c_min
    
    # Điều kiện cắt nhánh
    if prune && lower_bound >= best_cost
        return
    end
    
    # Nếu đã đi qua đủ N thành phố, quay về thành phố 1 (tương ứng đỉnh 0)
    if length(path) == N
        final_cost = cost + matrix[city, 1]
        if final_cost < best_cost
            best_cost = final_cost
            best_path = push!(copy(path), 1)
        end
        return
    end
    
    # Thử các thành phố tiếp theo
    for next_city in 1:N
        if (visited & (1 << (next_city - 1))) == 0
            dfs(next_city, visited | (1 << (next_city - 1)), 
                cost + matrix[city, next_city], push!(copy(path), next_city), prune)
        end
    end
end

function solve(prune::Bool)
    global best_cost = typemax(Int)
    global best_path = Int[]
    global nodes_visited = 0
    dfs(1, 1 << 0, 0, [1], prune)
    
    println("Chi phí tối ưu: ", best_cost)
    print("Hành trình: ")
    # Trừ đi 1 để in ra dạng 0-based khớp với ma trận đề bài
    println(join([string(c - 1) for c in best_path], " -> "))
    println("Số nút đã duyệt: ", nodes_visited)
end

println("Cạnh rẻ nhất c_min: ", c_min)
println("\n--- KHÔNG CẮT NHÁNH ---")
solve(false)

println("\n--- CÓ CẮT NHÁNH ---")
solve(true)