import sys

def is_perfect_square(n):
    lo, hi = 0, 10**9              # vì n ≤ 10^18 nên sqrt(n) ≤ 10^9
    while lo <= hi:
        mid = (lo + hi) // 2
        sq = mid * mid
        if sq == n:
            return True
        elif sq < n:
            lo = mid + 1
        else:
            hi = mid - 1
    return False

def main():
    data = sys.stdin.buffer.read().split()
    for tok in data:               # ← xử lý MỌI số trong input
        n = int(tok)
        print("YES" if is_perfect_square(n) else "NO")

main()