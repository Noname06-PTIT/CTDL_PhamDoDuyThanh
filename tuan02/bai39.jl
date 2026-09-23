using Random
using Printf

# --- CÁCH 1: O(n^3) ---
function max_subarray_c1(a)
    n = length(a)
    best = a[1]
    for i in 1:n
        for j in i:n
            cur_sum = 0
            for k in i:j
                cur_sum += a[k]
            end
            if cur_sum > best
                best = cur_sum
            end
        end
    end
    return best
end

# --- CÁCH 2: O(n^2) ---
function max_subarray_c2(a)
    n = length(a)
    best = a[1]
    prefix = zeros(Int, n + 1)
    for i in 1:n
        prefix[i + 1] = prefix[i] + a[i]
    end
    for i in 1:n
        for j in i:n
            cur_sum = prefix[j + 1] - prefix[i]
            if cur_sum > best
                best = cur_sum
            end
        end
    end
    return best
end

# --- CÁCH 3: Kadane O(n) ---
function max_subarray_c3(a)
    best = a[1]
    cur = a[1]
    for i in 2:length(a)
        cur = max(a[i], cur + a[i])
        best = max(best, cur)
    end
    return best
end

# --- 1. CHẠY TEST BẮT BUỘC ---
function run_manual_tests()
    tests = [
        ([4, -3, 5, -2, -1, 2, 6, -9], 11),
        ([-5, -2, -9], -2),
        ([1, 2, 3, 4], 10),
        ([-2, 1, -3, 4, -1, 2, 1, -5, 4], 6),
        ([0, -1, 0], 0)
    ]
    println("=== KET QUA TEST BAT BUOC ===")
    for (i, (arr, expected)) in enumerate(tests)
        r1, r2, r3 = max_subarray_c1(arr), max_subarray_c2(arr), max_subarray_c3(arr)
        status = (r1 == r2 == r3 == expected) ? "PASS" : "FAIL"
        @printf "Test %d: %s (C1=%d, C2=%d, C3=%d, Expected=%d)\n" i status r1 r2 r3 expected
    end
end

# --- 2. KIỂM THỬ TỰ ĐỘNG ---
function run_auto_test()
    println("\n=== KIEM THU TU DONG (1000 TESTS) ===")
    for _ in 1:1000
        n = rand(1:50)
        a = rand(-50:50, n)
        r1, r2, r3 = max_subarray_c1(a), max_subarray_c2(a), max_subarray_c3(a)
        if !(r1 == r2 == r3)
            println("FAIL! Phan vi du: ", a)
            @printf "C1=%d, C2=%d, C3=%d\n" r1 r2 r3
            return
        end
    end
    println("OK")
end

# --- 3. ĐO THỜI GIAN ---
function benchmark(arr, func)
    start = time_ns()
    func(arr)
    return (time_ns() - start) / 1e9
end

function run_benchmark()
    println("\n=== BANG THOI GIAN VA DOI CHIEU ===")
    sizes = [200, 400, 800]
    results = Dict("C1 (O(n^3))" => [], "C2 (O(n^2))" => [], "C3 (O(n))" => [])
    
    Random.seed!(42)
    arrays = [rand(-1000:1000, n) for n in sizes]
    
    for (name, func) in [("C1 (O(n^3))", max_subarray_c1), ("C2 (O(n^2))", max_subarray_c2), ("C3 (O(n))", max_subarray_c3)]
        for arr in arrays
            push!(results[name], benchmark(arr, func))
        end
    end

    @printf "%-15s | %-10s | %-10s | %-10s | %-15s | %-15s\n" "Thoi gian (s)" "n=200" "n=400" "n=800" "T(400)/T(200)" "T(800)/T(400)"
    println("-" ^ 90)
    
    for name in ["C1 (O(n^3))", "C2 (O(n^2))", "C3 (O(n))"]
        t = results[name]
        r1 = t[1] > 0 ? t[2] / t[1] : 0
        r2 = t[2] > 0 ? t[3] / t[2] : 0
        @printf "%-15s | %-10.4f | %-10.4f | %-10.4f | %-15.2f | %-15.2f\n" name t[1] t[2] t[3] r1 r2
    end
end

# Chạy main
run_manual_tests()
run_auto_test()
run_benchmark()