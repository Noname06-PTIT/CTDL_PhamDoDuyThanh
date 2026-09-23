n = int(input())
arr = list(map(int, input().split()))

chan = le = am = 0

for x in arr:
    if x < 0:
        am += 1
        
    # Cach nay hoat dong tot tren Python, va cung an toan nhung cach khac
    if x % 2 != 0:
        le += 1
    else:
        chan += 1

print(f"chẵn {chan}, lẻ {le}, âm {am}")