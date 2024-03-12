from random import randint
amount_of_vertexes = randint(1, 100000)
amount_of_edges = randint(0, 100000)

for i in range(amount_of_edges):
    vertex1 = randint(0, amount_of_vertexes)
    vertex2 = randint(0, amount_of_vertexes)

    while vertex1 == vertex2:
        vertex1 = randint(0, amount_of_vertexes)
        vertex2 = randint(0, amount_of_vertexes)

    print(vertex1, vertex2)
