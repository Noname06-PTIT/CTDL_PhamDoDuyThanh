class Item:
    def __init__(self, name, w, v):
        self.name = name
        self.w = w
        self.v = v
        self.ratio = v / w

# Bộ dữ liệu chuẩn mục C của đề bài
W = 14
raw_data = [
    ('A', 4, 19),
    ('B', 7, 25),
    ('C', 3, 7),
    ('D', 3, 8),
    ('E', 3, 9),
    ('F', 10, 21)
]

items = [Item(name, w, v) for name, w, v in raw_data]
items.sort(key=lambda x: x.ratio, reverse=True)
n = len(items)

max_val = 0
best_mask = 0
nodes_visited = 0

def bound(level, cw, cv):
    if cw > W:
        return 0
    b = cv
    w = cw
    for i in range(level, n):
        if w + items[i].w <= W:
            w += items[i].w
            b += items[i].v
        else:
            b += (W - w) * items[i].ratio
            break
    return b

def dfs(level, cw, cv, mask, prune):
    global max_val, best_mask, nodes_visited
    nodes_visited += 1
    
    if cv > max_val:
        max_val = cv
        best_mask = mask
    if level == n:
        return

    if prune and bound(level, cw, cv) <= max_val:
        return

    # Nhánh 1: Chọn đồ vật level (thử trước vì tỉ số v/w cao)
    if cw + items[level].w <= W:
        dfs(level + 1, cw + items[level].w, cv + items[level].v, mask | (1 << level), prune)
    
    # Nhánh 2: Không chọn đồ vật level
    dfs(level + 1, cw, cv, mask, prune)

def solve(prune):
    global max_val, best_mask, nodes_visited
    max_val = 0
    best_mask = 0
    nodes_visited = 0
    dfs(0, 0, 0, 0, prune)
    
    print(f"Giá trị lớn nhất: {max_val}")
    selected = [items[i].name for i in range(n) if (best_mask & (1 << i))]
    print(f"Tập đồ vật được chọn: {selected}")
    print(f"Số nút đã duyệt: {nodes_visited}")

print("--- KHÔNG CẮT NHÁNH ---")
solve(False)

print("\n--- CÓ CẮT NHÁNH ---")
solve(True)