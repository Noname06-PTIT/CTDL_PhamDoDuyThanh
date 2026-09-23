"""Kiểm thử bổ sung cho bài tập Chương 5 (test_them.py)."""
import unittest
from cau_truc import DSLK, NganXep, HangDoiVong
import bai_lam


class TestThem(unittest.TestCase):
    def test_lay_nhieu_k_la_bool(self):
        """Tình huống biên: k truyền vào là True (kiểu bool).
        Trong Python bool là con của int, nhưng quy ước yêu cầu từ chối bool.
        """
        s = NganXep()
        s.day(10)
        s.day(20)
        with self.assertRaises(ValueError):
            bai_lam.lay_nhieu(s, True)
        # Ngăn xếp phải giữ nguyên
        self.assertEqual(s.a, [10, 20])

    def test_xoa_tat_ca_gia_tri_am_va_trung_o_duoi(self):
        """Tình huống biên: Giá trị x âm, xuất hiện dồn dập ở cuối danh sách.
        L = [5, -3, 7, -3, -3], xoá x = -3.
        """
        L = DSLK([5, -3, 7, -3, -3])
        so_xoa = bai_lam.xoa_tat_ca(L, -3)
        self.assertEqual(so_xoa, 3)
        self.assertEqual(L.gia_tri(), [5, 7])
        self.assertEqual(L.n, 2)

    def test_xem_k_hang_doi_k_am(self):
        """Tình huống dữ liệu không hợp lệ: k âm (k = -1) với hàng đợi."""
        q = HangDoiVong(3)
        q.them(100)
        q.them(200)
        q.them(300)
        with self.assertRaises(ValueError):
            bai_lam.xem_k(q, -1)
        # Trạng thái hàng đợi giữ nguyên
        self.assertEqual(q.so, 3)
        self.assertEqual(q.a, [100, 200, 300])


if __name__ == '__main__':
    unittest.main()
