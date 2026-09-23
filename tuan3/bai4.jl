# [DÁN MÃ NGUỒN JULIA BÀI TOÁN KNN TẠI ĐÂY]
function knn_classify(train_data, test_point, k)
    n = length(train_data)
    
    # Bước 1: Tính khoảng cách Euclidean
    dists = [sqrt((point[1] - test_point[1])^2 + (point[2] - test_point[2])^2) for point in train_data]
    
    # Bước 2: Tạo mảng chỉ số và sắp xếp (Julia có hàm sortperm rất mạnh cho việc này)
    indices = sortperm(dists)
    
    # Bước 3: Đếm nhãn của K phần tử gần nhất
    class_count = Dict{String, Int}()
    for i in 1:k
        label = train_data[indices[i]][3]
        class_count[label] = get(class_count, label, 0) + 1
    end
    
    # Bước 4: Trả về nhãn có số phiếu cao nhất
    predicted_label = argmax(class_count)
    return predicted_label
end

# --- THỰC NGHIỆM ---
train_set = [(1, 1, "A"), (2, 3, "A"), (4, 2, "B"), (5, 6, "B"), (9, 9, "B")]
test_sample = (3, 2)
K = 3
println("Mẫu kiểm thử: $test_sample -> Phân loại vào nhóm: $(knn_classify(train_set, test_sample, K))")