while True:
    n = int(input("Height: "))
    if 1 <= n <= 8:
        break

for i in range(1, n + 1):
    print(" " * (n - i) + "#" * (i) + "  " + "#" * (i))
