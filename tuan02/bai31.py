import sys

def main():
    data = sys.stdin.buffer.read().split()
    # data là list các bytes — ta duyệt qua lần lượt
    n = int(data[0])
    x = int(data[1])

    tong = x
    min_val = x
    max_val = x

    for i in range(2, n + 1):
        x = int(data[i])
        tong += x
        if x < min_val:
            min_val = x
        if x > max_val:
            max_val = x

    avg = tong / n   # Python: / đã là chia thực
    sys.stdout.write(f"{tong} {avg:.4f} {min_val} {max_val}\n")

main()