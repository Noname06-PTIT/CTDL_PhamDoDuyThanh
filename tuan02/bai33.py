import sys

while True:
    try:
        n = int(sys.stdin.readline())
        
        count = 0
        total_sum = 0
        
        while n > 0:
            d = n % 10
            total_sum += d
            count += 1
            n //= 10
            
        print(count, total_sum, sep="  ")
        
    except EOFError:
        break  # Bắt lỗi hết file thì dừng vòng lặp