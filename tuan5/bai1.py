# Thêm đường dẫn tới thư mục chứa cau_truc.py để import
import sys
sys.path.append(r"d:\Tai_lieu\CTDL_PhamDoDuyThanh\Chuong5_Goi_sinh_vien_Python_Julia\Chuong5_SinhVien\python")
from cau_truc import DSLK

def dem_gia_tri(L: DSLK, x: int) -> int:
    dem = 0
    p = L.dau
    while p is not None:
        if p.gt == x:
            dem += 1
        p = p.ke
    return dem

if __name__ == "__main__":
    # Test thử với danh sách 2 -> 1 -> 2 -> 2
    L = DSLK([2, 1, 2, 2])
    kq = dem_gia_tri(L, 2)
    print("Danh sách:", L.gia_tri())
    print("Số lần xuất hiện của x = 2 là:", kq)  # Kết quả: 3
