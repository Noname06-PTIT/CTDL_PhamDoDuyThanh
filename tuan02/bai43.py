import sys
sys.setrecursionlimit(2000) # Tang gioi han de quy cho cach 2

LLONG_MAX = 2**63 - 1

def fib_recursive(n, counter):
    counter[0] += 1
    if n == 1 or n == 2:
        return 1
    return fib_recursive(n - 1, counter) + fib_recursive(n - 2, counter)

def fib_memo(n, memo):
    if n == 1 or n == 2:
        return 1
    if memo[n] != -1:
        return memo[n]
    
    f1 = fib_memo(n-1, memo) if memo[n-1] == -1 else memo[n-1]
    f2 = fib_memo(n-2, memo) if memo[n-2] == -1 else memo[n-2]
    
    if f1 > LLONG_MAX - f2:
        return -1
    memo[n] = f1 + f2
    return memo[n]

def fib_loop(n):
    if n == 1 or n == 2:
        return 1
    a, b = 1, 1
    for _ in range(3, n + 1):
        if a > LLONG_MAX - b:
            return -1
        a, b = b, a + b
    return b

def main():
    n = int(input())
    
    # Cach 1: De quy thuan
    if n <= 40:
        counter = [0] # Dung list de truyen tham chieu
        res1 = fib_recursive(n, counter)
        print(f"De quy thuan: F_{n} = {res1}, So loi goi = {counter[0]}")
    else:
        print("De quy thuan: Bo qua (n > 40 de tranh treo)")

    # Cach 2: Ghi nho
    memo = [-1] * (n + 1)
    res2 = fib_memo(n, memo)
    if res2 == -1:
        print("Ghi nho: Tran long long!")
    else:
        print(f"Ghi nho: F_{n} = {res2}")

    # Cach 3: Vong lap
    res3 = fib_loop(n)
    if res3 == -1:
        print("Vong lap: Tran long long!")
    else:
        print(f"Vong lap: F_{n} = {res3}")

if __name__ == '__main__':
    main()