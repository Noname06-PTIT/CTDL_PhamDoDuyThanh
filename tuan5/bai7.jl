function chon_hoat_dong(hd, tieu_chi)
    if tieu_chi == "ket_thuc"
        sort!(hd, by = x -> x[2])
    elseif tieu_chi == "bat_dau"
        sort!(hd, by = x -> x[1])
    elseif tieu_chi == "ngan_nhat"
        sort!(hd, by = x -> x[2] - x[1])
    elseif tieu_chi == "it_chong_lan"
        chong_lan = []
        for i in 1:length(hd)
            count = 0
            for j in 1:length(hd)
                if i != j && !(hd[i][2] <= hd[j][1] || hd[j][2] <= hd[i][1])
                    count += 1
                end
            end
            push!(chong_lan, (count, hd[i]))
        end
        sort!(chong_lan, by = x -> x[1])
        hd = [x[2] for x in chong_lan]
    end
    
    ans = String[]
    het = -1
    for (s, f, id) in hd
        if s >= het
            push!(ans, id)
            het = f
        end
    end
    return ans
end

# Chương trình kiểm chứng độc lập bằng Vét cạn (Brute-force)
function kiem_chung_vet_can(hd)
    n = length(hd)
    for r in n:-1:1
        for mask in 1:(1 << n - 1)
            if count_ones(mask) != r
                continue
            end
            subset = []
            for i in 1:n
                if (mask >> (i - 1)) & 1 == 1
                    push!(subset, hd[i])
                end
            end
            sort!(subset, by = x -> x[2])
            valid = true
            for i in 1:length(subset)-1
                if subset[i][2] > subset[i+1][1]
                    valid = false
                    break
                end
            end
            if valid
                return r
            end
        end
    end
    return 0
end

# Khởi tạo dữ liệu và chạy
s = [1, 2, 2, 3, 4, 6, 8, 9, 11, 12]
f = [5, 5, 6, 4, 8, 9, 11, 14, 13, 15]
hd = [(s[i], f[i], "H$(i)") for i in 1:10]

kq_ket_thuc = chon_hoat_dong(copy(hd), "ket_thuc")
kq_vet_can = kiem_chung_vet_can(hd)

# Đối chiếu chương trình chính và kiểm chứng độc lập
@assert length(kq_ket_thuc) == kq_vet_can "LỖI KIỂM CHỨNG: Tham lam không khớp với Vét cạn!"

println("Ket thuc som nhat : ", kq_ket_thuc)
println("Bat dau som nhat  : ", chon_hoat_dong(copy(hd), "bat_dau"))
println("Ngan nhat         : ", chon_hoat_dong(copy(hd), "ngan_nhat"))
println("It chong lan nhat : ", chon_hoat_dong(copy(hd), "it_chong_lan"))
println("-"^30)
println("So nhieu nhat that su (Vet can kiem chung): ", kq_vet_can)