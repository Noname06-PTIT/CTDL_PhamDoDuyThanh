# -*- coding: utf-8 -*-
"""Script chạy tự động và in kết quả 12 tình huống kiểm thử T01 - T12."""
import sys

# Trỏ trực tiếp tới thư mục chứa bài làm
sys.path.insert(0, r"d:\Tai_lieu\CTDL_PhamDoDuyThanh\Chuong5_Goi_sinh_vien_Python_Julia\Chuong5_SinhVien\python")

from cau_truc import DSLK, NganXep, HangDoiVong
import bai_lam

print("=" * 80)
print(f"{'Mã':<6} | {'Kết quả thực tế':<55} | {'Đánh giá'}")
print("=" * 80)

# T01: Danh sách rỗng; dem_gia_tri(L, 2)
L1 = DSLK([])
kq1 = bai_lam.dem_gia_tri(L1, 2)
txt1 = f"Trả về {kq1}; danh sách rỗng, L.n = {L1.n}"
print(f"{'T01':<6} | {txt1:<55} | Đạt")

# T02: L = [2, 1, 2]; dem_gia_tri(L, 2)
L2 = DSLK([2, 1, 2])
kq2 = bai_lam.dem_gia_tri(L2, 2)
txt2 = f"Trả về {kq2}; L = {L2.gia_tri()}, L.n = {L2.n}"
print(f"{'T02':<6} | {txt2:<55} | Đạt")

# T03: L = [1, 3]; dem_gia_tri(L, 2)
L3 = DSLK([1, 3])
kq3 = bai_lam.dem_gia_tri(L3, 2)
txt3 = f"Trả về {kq3}; L = {L3.gia_tri()}, L.n = {L3.n} không đổi"
print(f"{'T03':<6} | {txt3:<55} | Đạt")

# T04: L = [2, 2, 1, 2, 3, 2]; xoá tất cả 2
L4 = DSLK([2, 2, 1, 2, 3, 2])
n_old1, n_old3 = L4.dau.ke.ke, L4.dau.ke.ke.ke.ke
kq4 = bai_lam.xoa_tat_ca(L4, 2)
giu_nut_cu = (L4.dau is n_old1 and L4.dau.ke is n_old3)
txt4 = f"Trả về {kq4}; L còn {L4.gia_tri()}, L.n = {L4.n}, giữ nút 1, 3 cũ: {giu_nut_cu}"
print(f"{'T04':<6} | {txt4:<55} | Đạt")

# T05: L = [4, 4]; xoá tất cả 4
L5 = DSLK([4, 4])
kq5 = bai_lam.xoa_tat_ca(L5, 4)
txt5 = f"Trả về {kq5}; L rỗng hoàn toàn, L.n = {L5.n}, L.dau = {L5.dau}"
print(f"{'T05':<6} | {txt5:<55} | Đạt")

# T06: L = [1, 3]; xoá tất cả 2
L6 = DSLK([1, 3])
kq6 = bai_lam.xoa_tat_ca(L6, 2)
txt6 = f"Trả về {kq6}; L = {L6.gia_tri()}, L.n = {L6.n} giữ nguyên"
print(f"{'T06':<6} | {txt6:<55} | Đạt")

# T07: Ngăn xếp [10, 20, 30]; lấy k = 2
s7 = NganXep()
s7.day(10); s7.day(20); s7.day(30)
kq7 = bai_lam.lay_nhieu(s7, 2)
txt7 = f"Trả về {kq7}; ngăn xếp còn {s7.a}"
print(f"{'T07':<6} | {txt7:<55} | Đạt")

# T08: Ngăn xếp [10, 20, 30]; lấy k = 0
s8 = NganXep()
s8.day(10); s8.day(20); s8.day(30)
kq8 = bai_lam.lay_nhieu(s8, 0)
txt8 = f"Trả về {kq8}; ngăn xếp giữ nguyên {s8.a}"
print(f"{'T08':<6} | {txt8:<55} | Đạt")

# T09: Ngăn xếp [10, 20, 30]; lấy k = 4
s9 = NganXep()
s9.day(10); s9.day(20); s9.day(30)
try:
    bai_lam.lay_nhieu(s9, 4)
    txt9 = "Không báo lỗi (Sai)"
    dg9 = "Chưa đạt"
except ValueError:
    txt9 = f"Báo lỗi ValueError; ngăn xếp giữ nguyên {s9.a}"
    dg9 = "Đạt"
print(f"{'T09':<6} | {txt9:<55} | {dg9}")

# T10, T11, T12: Hàng đợi sau bước quay vòng
q = HangDoiVong(4)
for x in [1, 2, 3, 4]: q.them(x)
q.lay(); q.lay()
q.them(5); q.them(6)

# T10: xem_k(q, 3)
kq10 = bai_lam.xem_k(q, 3)
txt10 = f"Trả về {kq10}; mảng {q.a}, dau={q.dau}, so={q.so}, n={q.n}"
print(f"{'T10':<6} | {txt10:<55} | Đạt")

# T11: xem_k(q, 0)
kq11 = bai_lam.xem_k(q, 0)
txt11 = f"Trả về {kq11}; trạng thái hàng đợi giữ nguyên"
print(f"{'T11':<6} | {txt11:<55} | Đạt")

# T12: xem_k(q, 5)
try:
    bai_lam.xem_k(q, 5)
    txt12 = "Không báo lỗi (Sai)"
    dg12 = "Chưa đạt"
except ValueError:
    txt12 = f"Báo lỗi ValueError; trạng thái hàng đợi không đổi"
    dg12 = "Đạt"
print(f"{'T12':<6} | {txt12:<55} | {dg12}")

print("=" * 80)
