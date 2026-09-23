# [DÁN MÃ NGUỒN PYTHON THUẬT TOÁN INSERTION SORT TẠI ĐÂY]
def insertion_sort(arr):
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        # Di chuyển các phần tử của arr[0..i-1] lớn hơn key
        # đến vị trí sau vị trí hiện tại của chúng
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

if __name__ == "__main__":
    A = [8, 3, 5, 1, 9, 2]
    print("Dãy ban đầu   :", A)
    insertion_sort(A)
    print("Dãy sau khi sx :", A)