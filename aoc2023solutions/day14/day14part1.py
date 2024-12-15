def printfile(file):
    for i in file:
        print(''.join(i))

f = open("input.txt", 'r')
file = f.read().strip().split('\n')
#file = 
"""
O....#....
O.OO#....#
.....##...
OO.#O....O
.O.....O#.
O.#..O.#.#
..O..#O..O
.......O..
#....###..
#OO..#....
""".strip().split('\n')
file = [list(x) for x in file]

for i in enumerate(file):
    for j in enumerate(i[1]):
        if j[1] == "O":
            vertline = [x[i[0]] for x in file]
            curr_index = [i[0], j[0]]
            while True:
                curr_index[0] -= 1
                curr_char = file[curr_index[0]][curr_index[1]]
                if curr_char == 'O' or curr_char == "#" or curr_index[0] == -1:
                    break
                file[curr_index[0]][curr_index[1]] = "O"
                file[curr_index[0] + 1][curr_index[1]] = "."
out = 0
for i in enumerate(file):
    out += i[1].count("O") * (len(file) - i[0])

print(out)
