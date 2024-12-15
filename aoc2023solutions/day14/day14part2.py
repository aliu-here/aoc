def shift(loc, file, dir):
    mapping = {"n":[-1, 0], "w":[0, -1], "e":[0, 1], "s":[1, 0]}
    direction = mapping[dir]
    curr_index = loc[:]
    while True:
        curr_index[0] += direction[0]
        curr_index[1] += direction[1]
        if curr_index[0] < 0 or curr_index[0] >= len(file) or curr_index[1] < 0 or curr_index[1] >= len(file[0]):
            return file
        curr_char = file[curr_index[0]][curr_index[1]]
        if curr_char == 'O' or curr_char == "#":
            return file
        file[curr_index[0]][curr_index[1]] = "O"
        file[curr_index[0] - direction[0]][curr_index[1] - direction[1]] = "."

def cycle(file):
    for dir in 'nwse':
        if dir == 's' or dir == 'e':
            for i in enumerate(file[::-1]):
                for j in enumerate(i[1][::-1]):
                    if j[1] == "O":
                        curr_index = [len(file) - i[0] - 1, len(file[0]) - j[0] - 1]
                        file = shift(curr_index, file, dir)
        else:
            for i in enumerate(file):
                for j in enumerate(i[1]):
                    if j[1] == "O":
                        curr_index = [i[0], j[0]]
                        file = shift(curr_index, file, dir)
    return file


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
prior_cycle_result = {}
cyclenum = 1

file = cycle(file)

while '\n'.join([''.join(x) for x in file]) not in prior_cycle_result.keys():
    prior_cycle_result['\n'.join([''.join(x) for x in file])] = cyclenum
    file = cycle(file)
    cyclenum += 1

cycle_start = prior_cycle_result['\n'.join([''.join(x) for x in file])]
cycle_length = cyclenum - prior_cycle_result['\n'.join([''.join(x) for x in file])]

print(cycle_length, cycle_start)
extra_cycles = (1000000000 - cycle_start) % cycle_length
print(extra_cycles)
do_extra = cycle_length - extra_cycles
for i in range(extra_cycles):
    file = cycle(file)

out = 0
for i in enumerate(file):
    out += i[1].count("O") * (len(file) - i[0])

print(out)
