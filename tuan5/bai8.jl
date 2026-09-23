using Printf

# 1. Liệt kê toàn bộ câu độ dài 3 và tính điểm
function dfs_liet_ke(P, current_sentence, current_score, L, best_sent, best_score)
    if length(current_sentence) == L
        println("  Câu: ", join(current_sentence, " "), " - Điểm: ", current_score)
        if current_score > best_score
            return copy(current_sentence), current_score
        end
        return best_sent, best_score
    end
    last_word = current_sentence[end]
    if haskey(P, last_word)
        for (w, p) in P[last_word]
            best_sent, best_score = dfs_liet_ke(P, [current_sentence; w], current_score * p, L, best_sent, best_score)
        end
    end
    return best_sent, best_score
end

function liet_ke_va_tinh_diem(P, start_word, L)
    best_sent = String[]
    best_score = -1.0
    return dfs_liet_ke(P, [start_word], 1.0, L, best_sent, best_score)
end

# 2 & 3. Beam Search
function beam_search(P, start_word, L, k)
    beam = [([start_word], 1.0)]
    for _ in 1:(L-1)
        new_beam = Tuple{Vector{String}, Float64}[]
        for (cau, d) in beam
            tt = cau[end]
            if haskey(P, tt)
                for (w, p) in P[tt]
                    push!(new_beam, ([cau; w], d * p))
                end
            end
        end
        sort!(new_beam, by = x -> x[2], rev = true)
        beam = new_beam[1:min(k, length(new_beam))]
    end
    return beam[1]
end

# 4. Viterbi
function viterbi(cau, nhan, pi, A, B)
    T = length(cau)
    f = [Dict{String, Float64}() for _ in 1:T]
    tu = [Dict{String, Union{String, Nothing}}() for _ in 1:T]
    
    for t in nhan
        f[1][t] = get(pi, t, 0.0) * get(get(B, t, Dict()), cau[1], 0.0)
        tu[1][t] = nothing
    end
    
    for i in 2:T
        for t in nhan
            tot = nothing; gt = -1.0
            for s in nhan
                x = f[i-1][s] * get(get(A, s, Dict()), t, 0.0)
                if x > gt
                    gt = x; tot = s
                end
            end
            f[i][t] = gt * get(get(B, t, Dict()), cau[i], 0.0)
            tu[i][t] = tot
        end
    end
    
    cuoi = argmax(f[T])
    day = [cuoi]
    for i in T:-1:2
        push!(day, tu[i][day[end]])
    end
    return reverse(day), f[T][cuoi]
end

# Chương trình kiểm chứng vét cạn
function vet_can_viterbi(cau, nhan, pi, A, B)
    best_seq = String[]
    best_prob = -1.0
    n = length(cau)
    
    for mask in 0:(1<<n - 1)
        seq = String[]
        for i in 1:n
            if (mask & (1 << (n - i))) != 0
                push!(seq, nhan[2])
            else
                push!(seq, nhan[1])
            end
        end
        
        prob = get(pi, seq[1], 0.0) * get(get(B, seq[1], Dict()), cau[1], 0.0)
        for i in 2:n
            prob *= get(get(A, seq[i-1], Dict()), seq[i], 0.0) * get(get(B, seq[i], Dict()), cau[i], 0.0)
        end
        
        if prob > best_prob
            best_prob = prob
            best_seq = seq
        end
    end
    return best_seq, best_prob
end

P = Dict(
    "em" => Dict("học" => 0.52, "đi" => 0.48),
    "học" => Dict("bài" => 0.40, "toán" => 0.35, "vẽ" => 0.25),
    "đi" => Dict("chợ" => 0.58, "bơi" => 0.22, "ngủ" => 0.20)
)

println("--- Liệt kê toàn bộ câu độ dài 3 ---")
best_cau, best_diem = liet_ke_va_tinh_diem(P, "em", 3)
println("Liệt kê: câu tốt nhất $(join(best_cau, ' ')) $(round(best_diem, digits=4))\n")

println("--- Beam Search ---")
for k in 1:3
    kq = beam_search(P, "em", 3, k)
    println("Beam k=$k : $(join(kq[1], ' ')) - Điểm: $(kq[2])")
end
println("-"^40)

nhan = ["N", "V"]
pi = Dict("N" => 0.6, "V" => 0.4)
A = Dict("N" => Dict("N" => 0.35, "V" => 0.65), "V" => Dict("N" => 0.70, "V" => 0.30))
B = Dict(
    "N" => Dict("em" => 0.35, "học" => 0.10, "bài" => 0.40, "toán" => 0.30),
    "V" => Dict("em" => 0.05, "học" => 0.45, "bài" => 0.05, "toán" => 0.02)
)
cau = ["em", "học", "bài", "toán"]

day_nhan, xs = viterbi(cau, nhan, pi, A, B)
println("\n--- Viterbi ---")
println("Day nhan : ", day_nhan)
println("Xac suat : ", @sprintf("%.9f", xs))

vc_nhan, vc_xs = vet_can_viterbi(cau, nhan, pi, A, B)
println("\n--- Vét cạn đối chiếu ---")
println("Day nhan : ", vc_nhan)
println("Xac suat : ", @sprintf("%.9f", vc_xs))

# Đối chiếu chương trình chính và kiểm chứng độc lập
@assert day_nhan == vc_nhan "LỖI KIỂM CHỨNG: Viterbi không khớp với Vét cạn!"