A = [8, 3, 5]

print("Day ban dau:", A)

for i in range(len(A)):
    # Tìm giá trị nhỏ nhất từ i đến cuối mảng
    min_value = min(A[i:])
    
    # Gán đè, KHÔNG swap
    A[i] = min_value
    
    print(f"i = {i}: min = {min_value} -> A = {A}")

print("Day ket qua:", A)