n = parse(Int, readline())
# readline()           : đọc một dòng dữ liệu từ bàn phím dưới dạng chuỗi (String)
# parse(Int, ...)      : ép/chuyển đổi chuỗi đó sang kiểu số nguyên (Int)


a = parse.(Int, split(readline()))
# readline()           : đọc dòng tiếp theo chứa các phần tử
# split(...)           : tách chuỗi thành mảng các chuỗi con dựa vào khoảng trắng
# parse.(Int, ...)     : toán tử broadcasting (dấu chấm) áp dụng hàm parse
#(Int, ...)   lên từng phần tử trong mảng để chuyển thành số nguyên
# Ví dụ:
# Input:  3 -1 4 1 5
# a = [3, -1, 4, 1, 5]

total = sum(a)
# sum(a) tính tổng tất cả các phần tử trong mảng a
# Ví dụ: 3 + (-1) + 4 + 1 + 5 = 12

max_value = maximum(a)
# maximum(a) tìm giá trị lớn nhất trong mảng/tập hợp a
# (Lưu ý trong Julia: 'maximum' dùng cho mảng, còn 'max(x, y)' dùng so sánh các đối số rời rạc)
# Ví dụ: maximum([3, -1, 4, 1, 5]) = 5

println(total, " ", max_value)
# In ra tổng và giá trị lớn nhất kèm theo ký tự xuống dòng ở cuối
