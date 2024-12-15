
def printfile(file):
    for i in file:
        print(''.join(i))

f = open("input.txt", 'r')
file = f.read().strip().split('\n')



#file = 
"""
...#......
.......#..
#.........
..........
......#...
.#........
.........#
..........
.......#..
#...#.....
""".strip().split('\n')
file = [list(x) for x in file]

printfile(file)

vertstretchindices = []
horizstretchindices = []

for i in range(len(file[0])):
    vertline = [x[i] for x in file]
    if vertline == ["."] * len(file):
        vertstretchindices.append(i)

for i in enumerate(file):
    if i[1] == ["."] * len(i[1]):
        horizstretchindices.append(i[0])

newlist = []
for i in enumerate(file):
    temp = []
    for j in enumerate(i[1]):
        temp.append(j[1])
        if j[0] in vertstretchindices:
            temp.append('.')
    newlist.append(temp)
    print(temp, i[0])
    if i[0] in horizstretchindices:
        newlist.append(['.'] * len(temp))

file = newlist
printfile(newlist)

galaxycoord = []

for i in enumerate(file):
    for j in enumerate(i[1]):
        if j[1] == "#":
            galaxycoord.append([i[0], j[0]])

out = 0
paircount = 0
for i in enumerate(galaxycoord):
    for j in enumerate(galaxycoord[i[0] + 1:]):
        dist = abs(j[1][1] - i[1][1]) + abs(j[1][0] - i[1][0])
        out += dist
        print(i[0], j[0], dist)
        paircount += 1


print(out)
print(paircount)
