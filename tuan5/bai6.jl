function doi_tien_tham_lam(coins, S)
    coins_sorted = sort(coins, rev=true)
    count = 0
    ans = Int[]
    for c in coins_sorted
        if S >= c
            q = S ÷ c
            count += q
            append!(ans, fill(c, q))
            S %= c
        end
    end
    return count, ans
end

function doi_tien_qhd(coins, S)
    dp = fill(typemax(Int) ÷ 2, S + 1)
    trace = zeros(Int, S + 1)
    dp[1] = 0 # Ứng với số tiền 0 (Julia đánh chỉ số từ 1)

    for i in 2:(S + 1)
        sum_val = i - 1
        for c in coins
            if sum_val >= c && dp[i - c] + 1 < dp[i]
                dp[i] = dp[i - c] + 1
                trace[i] = c
            end
        end
    end

    ans = Int[]
    curr = S
    while curr > 0
        push!(ans, trace[curr + 1])
        curr -= trace[curr + 1]
    end
    return dp[S + 1], ans
end

# Chương trình kiểm chứng độc lập bằng BFS
function kiem_chung_bfs(coins, S)
    if S == 0 return 0 end
    visited = falses(S + 1)
    visited[1] = true
    queue = Int[1]
    steps = 0
    
    while !isempty(queue)
        len = length(queue)
        for _ in 1:len
            u_idx = popfirst!(queue)
            u = u_idx - 1
            if u == S return steps end
            for c in coins
                v = u + c
                if v <= S && !visited[v + 1]
                    visited[v + 1] = true
                    push!(queue, v + 1)
                end
            end
        end
        steps += 1
    end
    return -1
end

# Bộ dữ liệu và phần thực thi in kết quả
bo_du_lieu = [
    ([1, 4, 6, 9], 12),
    ([1, 5, 10, 20, 50], 85),
    ([1, 3, 7, 12], 20),
    ([1, 2, 5, 10], 38),
    ([1, 6, 10], 12),
    ([1, 4, 5, 15, 20], 23)
]

for (i, (coins, S)) in enumerate(bo_du_lieu)
    tl_count, tl_ans = doi_tien_tham_lam(coins, S)
    qhd_count, qhd_ans = doi_tien_qhd(coins, S)
    bfs_count = kiem_chung_bfs(coins, S)
    
    @assert qhd_count == bfs_count "LỖI KIỂM CHỨNG BỘ $i: QHD và BFS không khớp!"
    
    is_correct = tl_count == qhd_count ? "Có" : "Không"
    println("Bộ $i:")
    println("  - Tham lam : $tl_count tờ, chi tiết $tl_ans")
    println("  - Tối ưu   : $qhd_count tờ, chi tiết $qhd_ans")
    println("  - Kiểm chứng BFS khớp: $bfs_count tờ")
    println("  => Tham lam đúng? $is_correct\n")
end