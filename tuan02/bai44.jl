using Random
using Printf
using Plots

function selection_sort!(arr)
    n = length(arr)
    for i in 1:n-1
        min_idx = i
        for j in i+1:n
            if arr[j] < arr[min_idx]
                min_idx = j
            end
        end
        if min_idx != i
            arr[i], arr[min_idx] = arr[min_idx], arr[i]
        end
    end
end

# Bẫy 2: Julia biên dịch JIT o lan goi dau. BAT BUOC goi truoc khi bấm giờ
selection_sort!(rand(1:10000, 100))

# Bẫy 1: Bo qua dong do dau tien (Warmup cache)
arr_warmup = rand(1:10000, 500)
selection_sort!(arr_warmup)

sizes = [500, 1000, 2000, 4000]
num_runs = 3
times = Float64[]

println("Chay moi mốc $num_runs lan va lay gia tri nho nhat:")
for n in sizes
    min_t = Inf
    for _ in 1:num_runs
        arr = rand(1:n*10, n) # Tạo mảng ngẫu nhiên mới
        # Bẫy 3: Dùng @elapsed (tương đương perf_counter)
        t = @elapsed selection_sort!(arr)
        min_t = min(min_t, t)
    end
    push!(times, min_t)
    @printf("n = %4d: %.6f s\n", n, min_t)
end

println("\n--- Bang ty le T(2n)/T(n) ---")
for i in 2:length(sizes)
    ratio = times[i] / times[i-1]
    @printf("T(%d)/T(%d) = %.2f\n", sizes[i], sizes[i-1], ratio)
end

# === VE DO THI ===
p = plot(sizes, times, 
    label="Thoi gian thuc te", 
    marker=:circle, lw=2, 
    xlabel="Kich thuoc mang n", 
    ylabel="Thoi gian (giay)", 
    title="Do thi thoi gian thuat toan O(n^2)", 
    xscale=:log10, yscale=:log10, # Bẫy 4: Thang log-log
    legend=:topleft)

# Đường lý thuyết c·n²
c = times[1] / (sizes[1]^2)
theoretical = [c * (n^2) for n in sizes]
plot!(p, sizes, theoretical, 
    label="Duong ly thuyet c*n^2", 
    marker=:x, lw=2, ls=:dash)

# Lưu ảnh
savefig(p, "plot_o_n2_julia.png")
println("\nDa luu do thi vao file 'plot_o_n2_julia.png'")