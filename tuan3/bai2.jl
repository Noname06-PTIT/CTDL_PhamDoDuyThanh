# [DÁN MÃ NGUỒN JULIA THUẬT TOÁN INSERTION SORT TẠI ĐÂY - Lưu ý 1-based indexing]
function insertion_sort!(arr::Vector{Int})
    n = length(arr)
    # Julia dùng 1-based indexing, nên vòng lặp bắt đầu từ 2
    for i in 2:n
        key = arr[i]
        j = i - 1
        # Di chuyển các phần tử lớn hơn key lên một vị trí
        while j >= 1 && arr[j] > key
            arr[j + 1] = arr[j]
            j -= 1
        end
        arr[j + 1] = key
    end
    return arr
end

function main()
    A = [8, 3, 5, 1, 9, 2]
    println("Dãy ban đầu   : ", A)
    insertion_sort!(A)
    println("Dãy sau khi sx : ", A)
end

main()