f = open("input.txt", 'r')
file = f.read().strip().split('\n')

file = [list(x) for x in file]

vertstretchindices = []
horizstretchindices = []

for i in range(len(file[0])):
    vertline = [x[i] for x in file]
    if vertline == ["."] * len(file):
        vertstretchindices.append(i)

for i in enumerate(file):
    if i[1] == ["."] * len(i[1]):
        horizstretchindices.append(i[0])

galaxycoord = []

for i in enumerate(file):
    for j in enumerate(i[1]):
        if j[1] == "#":
            galaxycoord.append([i[0], j[0]])

bout = 0
aout = 0

ascaleconstant = 2
bscaleconstant = 1000000

for i in enumerate(galaxycoord):
    for j in enumerate(galaxycoord[i[0] + 1:]):
        galaxyax = i[1][0]
        galaxyay = i[1][1]
        galaxybx = j[1][0]
        galaxyby = j[1][1]
        bdist = abs(galaxyax - galaxybx) + abs(galaxyay - galaxyby)
        adist = bdist
        #-1 to account because the original is included in stretch
        for k in horizstretchindices:
            if min(galaxyax, galaxybx) < k < max(galaxyax, galaxybx):
                bdist += bscaleconstant - 1
                adist += ascaleconstant - 1
        for k in vertstretchindices:
            if min(galaxyay, galaxyby) < k < max(galaxyay, galaxyby):
                bdist += bscaleconstant - 1
                adist += ascaleconstant - 1
        bout += bdist
        aout += adist


print("part a: ", aout)
print("part b: ", bout)
