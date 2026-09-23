# [DÁN MÃ NGUỒN PYTHON BÀI TOÁN KNN TẠI ĐÂY]
import math

def knn_classify(train_data, test_point, k):
    # train_data: list các tuple (x, y, label)
    # test_point: tuple (x, y)
    n = len(train_data)
    
    # Bước 1: Tính khoảng cách Euclidean từ điểm kiểm thử đến tất cả điểm huấn luyện
    distances = []
    for i in range(n):
        x_train, y_train, label = train_data[i]
        dist = math.sqrt((x_train - test_point[0])**2 + (y_train - test_point[1])**2)
        distances.append(dist)
    
    # Bước 2: Tạo mảng chỉ số và sắp xếp theo khoảng cách
    indices = list(range(n))
    # Sử dụng hàm sorted với key là khoảng cách của chỉ số đó
    indices.sort(key=lambda i: distances[i])
    
    # Bước 3: Đếm nhãn của K phần tử gần nhất
    class_count = {}
    for i in range(k):
        idx = indices[i]
        label = train_data[idx][2]
        class_count[label] = class_count.get(label, 0) + 1
        
    # Bước 4: Trả về nhãn có số phiếu cao nhất
    predicted_label = max(class_count, key=class_count.get)
    return predicted_label

# --- THỰC NGHIỆM ---
train_set = [(1, 1, 'A'), (2, 3, 'A'), (4, 2, 'B'), (5, 6, 'B'), (9, 9, 'B')]
test_sample = (3, 2)
K = 3
print(f"Mẫu kiểm thử: {test_sample} -> Phân loại vào nhóm: {knn_classify(train_set, test_sample, K)}")