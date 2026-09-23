import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        print("nghiêm ngặt: YES — không giảm: YES")
        return
        
    n = int(input_data[0])
    
    if n <= 1:
        print("nghiêm ngặt: YES — không giảm: YES")
        return
        
    arr = [int(x) for x in input_data[1:n+1]]
    
    is_strict = True
    is_non_decr = True
    
    # Chỉ số i chạy từ 0 đến n-2
    for i in range(n - 1):
        if arr[i] > arr[i + 1]:
            is_strict = False
            is_non_decr = False
        elif arr[i] == arr[i + 1]:
            is_strict = False
            
        if not is_strict and not is_non_decr:
            break
            
    res_strict = "YES" if is_strict else "NO"
    res_non_decr = "YES" if is_non_decr else "NO"
    
    # In đúng định dạng dấu gạch ngang dài
    print(f"nghiêm ngặt: {res_strict} — không giảm: {res_non_decr}")

if __name__ == "__main__":
    solve()