module BaiLam
using ..CauTruc
const BAN = "Sinh viên"
export dem_gia_tri, xoa_tat_ca!, lay_nhieu!, xem_k

struct ChuaHoanThanh <: Exception
    msg::String
end
Base.showerror(io::IO, e::ChuaHoanThanh) = print(io, e.msg)

"""Duyệt ke để đếm nút có gt == x. Không thay đổi L."""
function dem_gia_tri(L::DSLK, x)
    # Bài 1: danh sách rỗng trả về 0.
    throw(ChuaHoanThanh("Bài 1: cần hoàn thành dem_gia_tri trong julia/BaiLam.jl."))
end

"""Một lượt duyệt; xoá mọi nút có gt == x; cập nhật n; trả số nút đã xoá."""
function xoa_tat_ca!(L::DSLK, x)
    # Bài 2: không tạo lại danh sách và không cấp phát nút mới.
    throw(ChuaHoanThanh("Bài 2: cần hoàn thành xoa_tat_ca! trong julia/BaiLam.jl."))
end

"""Lấy đúng k giá trị LIFO. k sai phải báo ArgumentError trước khi sửa s."""
function lay_nhieu!(s::NganXep, k)
    # Bài 3: k nguyên, không phải Bool, 0 <= k <= số phần tử. k = 0 trả Int[].
    throw(ChuaHoanThanh("Bài 3: cần hoàn thành lay_nhieu! trong julia/BaiLam.jl."))
end

"""Đọc k giá trị FIFO; không sửa a, dau, so, n. k sai báo ArgumentError."""
function xem_k(q::HangDoiVong, k)
    # Bài 4: dau dùng chỉ số logic từ 0; truy cập Vector phải cộng 1.
    throw(ChuaHoanThanh("Bài 4: cần hoàn thành xem_k trong julia/BaiLam.jl."))
end
end # module
