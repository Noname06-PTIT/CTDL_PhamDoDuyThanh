import sys
from collections import deque

def doi_tien_tham_lam(coins, S):
    coins = sorted(coins, reverse=True)
    count = 0
    ans = []
    for c in coins:
        if S >= c:
            q = S // c
            count += q
            ans.extend([c] * q)
            S %= c
    return count, ans

def doi_tien_qhd(coins, S):
    dp = [float('inf')] * (S + 1)
    dp[0] = 0
    trace = [0] * (S + 1)
    for i in range(1, S + 1):
        for c in coins:
            if i >= c and dp[i - c] + 1 < dp[i]:
                dp[i] = dp[i - c] + 1
                trace[i] = c
    ans = []
    curr = S
    while curr > 0:
        ans.append(trace[curr])
        curr -= trace[curr]
    return dp[S], ans

# Chương trình kiểm chứng độc lập bằng BFS
def kiem_chung_bfs(coins, S):
    if S == 0: return 0, []
    trace_coin = [-1] * (S + 1)
    trace_prev = [-1] * (S + 1)
    visited = [False] * (S + 1)
    visited[0] = True
    queue = deque([0])
    
    while queue:
        u = queue.popleft()
        if u == S: break
        for c in coins:
            v = u + c
            if v <= S and not visited[v]:
                visited[v] = True
                trace_prev[v] = u
                trace_coin[v] = c
                queue.append(v)
                
    if not visited[S]: return -1, []
    ans = []
    curr = S
    while curr != 0:
        ans.append(trace_coin[curr])
        curr = trace_prev[curr]
    return len(ans), ans

if __name__ == "__main__":
    bo_du_lieu = [
        ([1, 4, 6, 9], 12),
        ([1, 5, 10, 20, 50], 85),
        ([1, 3, 7, 12], 20),
        ([1, 2, 5, 10], 38),
        ([1, 6, 10], 12),
        ([1, 4, 5, 15, 20], 23)
    ]

    for i, (coins, S) in enumerate(bo_du_lieu, 1):
        tl_count, tl_ans = doi_tien_tham_lam(coins, S)
        qhd_count, qhd_ans = doi_tien_qhd(coins, S)
        bfs_count, _ = kiem_chung_bfs(coins, S) # Chương trình kiểm chứng
        
        # Kiểm tra xem QHD và kiểm chứng BFS có khớp nhau không
        assert qhd_count == bfs_count, f"LỖI KIỂM CHỨNG BỘ {i}: QHD({qhd_count}) != BFS({bfs_count})"
        
        is_correct = "Có" if tl_count == qhd_count else "Không"
        print(f"Bộ {i}:")
        print(f"  - Tham lam : {tl_count} tờ, chi tiết {tl_ans}")
        print(f"  - Tối ưu   : {qhd_count} tờ, chi tiết {qhd_ans}")
        print(f"  - Kiểm chứng BFS khớp: {bfs_count} tờ")
        print(f"  => Tham lam đúng? {is_correct}\n")