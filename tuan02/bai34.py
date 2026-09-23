import sys

def dao_nguoc_so(n):
    # Quy ước: Tách dấu ra xử lý riêng, đảo phần trị tuyệt đối
    sign = -1 if n < 0 else 1
    abs_n = abs(n)
    
    rev = 0
    while abs_n > 0:
        rev = rev * 10 + abs_n % 10
        abs_n //= 10
        
    return sign * rev

# Xử lý đọc đến hết file (EOF)
for line in sys.stdin:
    line = line.strip()
    if line:
        n = int(line)
        print(dao_nguoc_so(n))