from random import randint

n = randint(1, 100)
print(n + 1)

s = randint(1, 10 ** 6)
print(s)

numbers = '1 '
for i in range(n):
  numbers += str(randint(1, 10 ** 6)) + ' '
print(numbers)