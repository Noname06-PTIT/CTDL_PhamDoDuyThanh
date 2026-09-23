"""Hoàn thành bốn hàm. Giữ nguyên tên, tham số và quy ước trả về."""
from cau_truc import DSLK, NganXep, HangDoiVong, so_nguyen
BAN = "Sinh viên"


def dem_gia_tri(L: DSLK, x: int) -> int:
    """Đếm nút có gt == x; duyệt bằng ke, không thay đổi L."""
    dem = 0
    p = L.dau
    while p is not None:
        if p.gt == x:
            dem += 1
        p = p.ke
    return dem



def xoa_tat_ca(L: DSLK, x: int) -> int:
    """Xoá mọi nút có gt == x; trả số nút xoá, cập nhật n đúng."""
    so_xoa = 0

    # 1. Xoá tất cả các nút x liên tiếp ở đầu danh sách
    while L.dau is not None and L.dau.gt == x:
        L.dau = L.dau.ke
        so_xoa += 1

    # Nếu sau khi xoá đầu mà danh sách rỗng
    if L.dau is None:
        L.n -= so_xoa
        return so_xoa

    # 2. Xoá các nút x ở giữa hoặc cuối danh sách
    truoc = L.dau
    p = L.dau.ke
    while p is not None:
        if p.gt == x:
            # Xoá nút p: nối thẳng truoc sang nút sau của p, KHÔNG dời truoc
            truoc.ke = p.ke
            so_xoa += 1
            p = p.ke
        else:
            # Giữ nút p: truoc tiến lên vị trí p
            truoc = p
            p = p.ke

    # Cập nhật lại số lượng nút thực tế
    L.n -= so_xoa
    return so_xoa


def lay_nhieu(s: NganXep, k: int) -> list[int]:
    """Lấy đúng k giá trị theo LIFO; k sai thì báo ValueError trước khi sửa s."""
    # Kiểm tra k phải là int (không phải bool) và 0 <= k <= số phần tử
    if type(k) is not int or type(k) is bool or not (0 <= k <= len(s.a)):
        raise ValueError(f"k không hợp lệ: k={k!r} (cần 0 <= k <= {len(s.a)})")
    
    ket_qua: list[int] = []
    for _ in range(k):
        gt = s.lay()
        if gt is not None:
            ket_qua.append(gt)
    return ket_qua


def xem_k(q: HangDoiVong, k: int) -> list[int]:
    """Đọc k phần tử đầu FIFO; không sửa a, dau, so, n; k sai báo ValueError."""
    # Kiểm tra k hợp lệ
    if type(k) is not int or type(k) is bool or not (0 <= k <= q.so):
        raise ValueError(f"k không hợp lệ: k={k!r} (cần 0 <= k <= {q.so})")
    
    return [q.a[(q.dau + i) % q.n] for i in range(k)]
