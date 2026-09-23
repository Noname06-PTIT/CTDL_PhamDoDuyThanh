n = int(input())
# Đọc số lượng phần tử n từ dòng đầu tiên
# int() chuyển dữ liệu từ chuỗi sang số nguyên


a = list(map(int, input().split()))
# input()              : đọc một dòng dữ liệu
# .split()             : tách dòng thành các phần tử dựa vào dấu cách
# map(int, ...)        : chuyển từng phần tử từ chuỗi sang số nguyên
# list(...)            : tạo danh sách a chứa các số nguyên
# Ví dụ:
# Input:  3 -1 4 1 5
# a = [3, -1, 4, 1, 5]

total = sum(a)
# sum(a) tính tổng tất cả các phần tử trong danh sách a
# Ví dụ: 3 + (-1) + 4 + 1 + 5 = 12

max_value = max(a)
# max(a) tìm giá trị lớn nhất trong danh sách a
# Ví dụ: max([3, -1, 4, 1, 5]) = 5

print(total, max_value)
# In tổng và giá trị lớn nhất