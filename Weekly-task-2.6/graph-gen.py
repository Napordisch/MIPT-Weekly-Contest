from random import randint
edges = set()
n = randint(1, 20000)
# n = 20000
m = randint(1, 200000)
# m = 1
print(n, m)
for i in range(m):
  src = randint(1, n)
  dst = randint(1, n)
  while (src == dst):
    src = randint(1, n)
    dst = randint(1, n)
  
  edges.add((src, dst))


for i in edges:
  print(i[0], i[1])