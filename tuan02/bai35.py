import sys

# Cách 1: Kiểm tra từng số
def method1(n):
    count = 0
    total = 0
    primes = []
    for i in range(2, n + 1):
        if i < 2: continue
        is_p = True
        if i % 2 == 0 or i % 3 == 0:
            if i not in (2, 3): is_p = False
        if is_p:
            j = 5
            while j * j <= i:
                if i % j == 0 or i % (j + 2) == 0:
                    is_p = False
                    break
                j += 6
        if is_p:
            count += 1
            total += i
            if n <= 30:
                primes.append(str(i))
    
    if n <= 30:
        print(" ".join(primes) + f"  ({count} số)")
    elif n < 1000000:
        print(f"số lượng = {count}")
    else:
        print(f"số lượng = {count}, tổng = {total}")

# Cách 2: Sàng Eratosthenes
def method2(n):
    if n < 2: return
    is_p = [True] * (n + 1)
    is_p[0] = is_p[1] = False
    for i in range(2, int(n**0.5) + 1):
        if is_p[i]:
            for j in range(i * i, n + 1, i):
                is_p[j] = False
                
    count = 0
    total = 0
    primes = []
    for i in range(2, n + 1):
        if is_p[i]:
            count += 1
            total += i
            if n <= 30:
                primes.append(str(i))
                
    if n <= 30:
        print(" ".join(primes) + f"  ({count} số)")
    elif n < 1000000:
        print(f"số lượng = {count}")
    else:
        print(f"số lượng = {count}, tổng = {total}")

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    for token in input_data:
        n = int(token)
        method2(n) # Gọi sàng để tối ưu thời gian

if __name__ == "__main__":
    main()