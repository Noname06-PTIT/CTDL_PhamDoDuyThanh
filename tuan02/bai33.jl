# Duyệt qua từng dòng cho đến khi hết file (tương đương while(cin >> n) trong C++)
for line in eachline(stdin)
    # Bỏ qua dòng trống (nếu có)
    if isempty(strip(line))
        continue
    end
    
    # Ép kiểu chuỗi sang số nguyên (Int64 trong Julia chứa được tới 9.2 * 10^18)
    n = parse(Int, strip(line))
    
    count = 0
    total_sum = 0
    
    # Vòng lặp O(log_10(n))
    while n > 0
        d = n % 10           # Lấy chữ số cuối cùng
        total_sum += d       # Cộng vào tổng
        count += 1           # Đếm số chữ số
        n = div(n, 10)       # Chia nguyên trong Julia (có thể viết n = n ÷ 10)
    end
    
    # In ra với 2 khoảng trắng (tương đương cout << count << "  " << sum << endl;)
    println(count, "  ", total_sum)
end