import sys

def format_number(s: str) -> str:
    """Hàm chèn dấu cách cách nhau 3 chữ số từ phải sang trái"""
    res = []
    for i in range(len(s)):
        if (len(s) - i) % 3 == 0 and i != 0:
            res.append(" ")
        res.append(s[i])
    return "".join(res)

def solve(n: int):
    """Xử lý một test case duy nhất"""
    LLONG_MAX = 9223372036854775807
    f = 1
    overflow = False
    overflow_at_i = -1
    
    for i in range(1, n + 1):
        if f > LLONG_MAX // i:
            overflow = True
            overflow_at_i = i
            break
        f *= i
        
    if not overflow:
        print(format_number(str(f)))
    else:
        exact_fact = f
        for i in range(overflow_at_i, n + 1):
            exact_fact *= i
            
        print(f"TRAN SO ({n}! = {format_number(str(exact_fact))} > {format_number(str(LLONG_MAX))})")

def main():
    # Đọc tất cả các dòng từ đầu vào standard input
    lines = sys.stdin.read().splitlines()
    
    for line in lines:
        line = line.strip() # Xóa khoảng trắng/thụt dòng dư thừa
        if line:            # Bỏ qua những dòng trống (nếu có)
            n = int(line)
            solve(n)        # Gọi hàm xử lý cho từng số

if __name__ == '__main__':
    main()