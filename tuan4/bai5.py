import time

# Ma trận đề bài Sudoku mục E (0 là ô trống)
board = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9]
]

calls_count = 0

def is_valid(b, r, c, num):
    for i in range(9):
        if b[r][i] == num or b[i][c] == num:
            return False
    br, bc = 3 * (r // 3), 3 * (c // 3)
    for i in range(3):
        for j in range(3):
            if b[br + i][bc + j] == num:
                return False
    return True

def solve_sequential(b):
    global calls_count
    calls_count += 1
    for r in range(9):
        for c in range(9):
            if b[r][c] == 0:
                for num in range(1, 10):
                    if is_valid(b, r, c, num):
                        b[r][c] = num
                        if solve_sequential(b): 
                            return True
                        b[r][c] = 0
                return False
    return True

def solve_mrv(b):
    global calls_count
    calls_count += 1
    
    best_cell = None
    min_options = 10
    best_nums = []
    
    for r in range(9):
        for c in range(9):
            if b[r][c] == 0:
                opts = [n for n in range(1, 10) if is_valid(b, r, c, n)]
                if len(opts) < min_options:
                    min_options = len(opts)
                    best_cell = (r, c)
                    best_nums = opts
                    if min_options == 0: 
                        return False # Đi vào ngõ cụt
                    if min_options == 1: 
                        break
        if min_options == 1: 
            break

    if best_cell is None: 
        return True # Đã điền kín bảng
    
    r, c = best_cell
    for num in best_nums:
        b[r][c] = num
        if solve_mrv(b): 
            return True
        b[r][c] = 0
    return False

def run_solver(solver_name, solver_func):
    global calls_count, board
    b = [row[:] for row in board]
    calls_count = 0
    
    start = time.perf_counter()
    success = solver_func(b)
    end = time.perf_counter()
    
    print(f"--- {solver_name} ---")
    if success:
        print(f"Thoi gian chay: {end - start:.6f} giay")
        print(f"So loi goi de quy: {calls_count}")
    else:
        print("Khong tim thay loi giai!")

if __name__ == "__main__":
    run_solver("QUET TUAN TU", solve_sequential)
    print()
    run_solver("MRV", solve_mrv)