N = int(input())
A = [0]  # Добавляем начальный элемент, так как нумерация начинается с 1
B = [0]
C = [0]

for _ in range(N):
    a, b, c = map(int, input().split())
    A.append(a)
    B.append(b)
    C.append(c)

dp = [0] * (N + 1)

for i in range(1, N + 1):
    dp[i] = min(dp[i-1] + A[i], dp[i-2] + B[i], dp[i-3] + C[i])

print(dp[N])