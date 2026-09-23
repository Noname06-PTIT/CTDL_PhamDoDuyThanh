import math

# Ma trận chi phí chuẩn mục D của đề bài
matrix = [
    [0, 10, 9, 22, 23],
    [10, 0, 16, 19, 14],
    [9, 16, 0, 7, 28],
    [22, 19, 7, 0, 8],
    [23, 14, 28, 8, 0]
]
N = len(matrix)

# Tìm c_min (cạnh rẻ nhất toàn ma trận, bỏ qua đường chéo chính)
c_min = math.inf
for i in range(N):
    for j in range(N):
        if i != j and matrix[i][j] < c_min:
            c_min = matrix[i][j]

best_cost = math.inf
best_path = []
nodes_visited = 0

def dfs(city, visited, cost, path, prune):
    global best_cost, best_path, nodes_visited
    nodes_visited += 1
    
    # Số cạnh còn phải đi để hoàn thành chu trình quay về 0
    edges_left = N - (len(path) - 1)
    lower_bound = cost + edges_left * c_min
    
    # Cắt nhánh nếu cận dưới >= kỷ lục hiện tại
    if prune and lower_bound >= best_cost:
        return
    
    # Nếu đã đi qua đủ N thành phố, đóng chu trình quay về 0
    if len(path) == N:
        final_cost = cost + matrix[city][0]
        if final_cost < best_cost:
            best_cost = final_cost
            best_path = path[:] + [0]
        return

    # Thử các thành phố tiếp theo
    for next_city in range(N):
        if not (visited & (1 << next_city)):
            dfs(next_city, visited | (1 << next_city), 
                cost + matrix[city][next_city], path + [next_city], prune)

def solve(prune):
    global best_cost, best_path, nodes_visited
    best_cost = math.inf
    best_path = []
    nodes_visited = 0
    dfs(0, 1 << 0, 0, [0], prune)
    
    print(f"Chi phí tối ưu: {best_cost}")
    print(f"Hành trình: {' -> '.join(map(str, best_path))}")
    print(f"Số nút đã duyệt: {nodes_visited}")

print(f"Canh re nhat toan ma tran c_min: {c_min}\n")

print("--- KHÔNG CẮT NHÁNH ---")
solve(False)

print("\n--- CÓ CẮT NHÁNH ---")
solve(True)