from random import randint
amount_of_vertexes = randint(1, 100000)
amount_of_edges = randint(0, 100000)


print(amount_of_vertexes, amount_of_edges)

for i in range(0, amount_of_edges):
    print(randint(0, amount_of_vertexes), randint(0, amount_of_vertexes))
