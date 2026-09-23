struct Item
    name::String
    w::Float64
    v::Float64
    ratio::Float64
end

# Dữ liệu chuẩn mục C của đề bài
const W = 14.0
raw_items = [
    Item("A", 4.0, 19.0, 19.0 / 4.0),
    Item("B", 7.0, 25.0, 25.0 / 7.0),
    Item("C", 3.0,  7.0,  7.0 / 3.0),
    Item("D", 3.0,  8.0,  8.0 / 3.0),
    Item("E", 3.0,  9.0,  9.0 / 3.0),
    Item("F", 10.0, 21.0, 21.0 / 10.0)
]

items = sort(raw_items, by = x -> x.ratio, rev = true)
n = length(items)

max_val = 0.0
best_mask = 0
nodes_visited = 0

function bound(level::Int, cw::Float64, cv::Float64)
    if cw > W return 0.0 end
    b = cv
    w_curr = cw
    for i in level:n
        if w_curr + items[i].w <= W
            w_curr += items[i].w
            b += items[i].v
        else
            b += (W - w_curr) * items[i].ratio
            break
        end
    end
    return b
end

function dfs(level::Int, cw::Float64, cv::Float64, mask::Int, prune::Bool)
    global max_val, best_mask, nodes_visited
    nodes_visited += 1
    
    if cv > max_val
        max_val = cv
        best_mask = mask
    end
    if level > n return end

    if prune && bound(level, cw, cv) <= max_val
        return
    end

    if cw + items[level].w <= W
        dfs(level + 1, cw + items[level].w, cv + items[level].v, mask | (1 << (level - 1)), prune)
    end
    dfs(level + 1, cw, cv, mask, prune)
end

function solve(prune::Bool)
    global max_val = 0.0
    global best_mask = 0
    global nodes_visited = 0
    dfs(1, 0.0, 0.0, 0, prune)
    
    println("Gia tri lon nhat: ", max_val)
    print("Tap do vat chon: ")
    for i in 1:n
        if best_mask & (1 << (i - 1)) != 0
            print(items[i].name, " ")
        end
    end
    println()
    println("So nut da duyet: ", nodes_visited)
end

println("--- KHONG CAT NHANH ---")
solve(false)

println("\n--- CO CAT NHANH ---")
solve(true)