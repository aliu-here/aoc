def printfile(file):
    for i in file:
        print(''.join(i))

def trace(patterns, position, direction):
    mapping = {'n':[-1, 0], 's':[1, 0], 'e':[0, 1], 'w':[0, -1]}
    curr_index = position[:]
    while True:
        curr_index[0] += mapping[direction][0]
        curr_index[1] += mapping[direction][1]
        if curr_index[0] < 0 or curr_index[1] < 0 or curr_index[0] >= len(patterns) or curr_index[1] >= len(patterns[0]):
            printfile(patterns)
            print(direction,  position)
            print()
            return patterns
        curr_char = patterns[curr_index[0]][curr_index[1]]
        if curr_char in '/\\|-':
#            patterns[curr_index[0]][curr_index[1]] = '#'
            break
        patterns[curr_index[0]][curr_index[1]] = '#'
    printfile(patterns)
    print(direction, curr_char, position)
    print()
    right_reflect_dict = {'s':'w', 'e':'n', 'n':'e', 'w':'s'}
    left_reflect_dict = {'s':'e', 'w':'n', 'e':'s', 'n':'w'}
    if curr_char == '/':
        patterns = trace(patterns, curr_index, right_reflect_dict[direction])
    if curr_char == '\\':
        patterns = trace(patterns, curr_index, left_reflect_dict[direction])
    if curr_char == '|' and (direction == 'w' or direction == 'e'):
        patterns = trace(patterns, curr_index, 'n')
        patterns = trace(patterns, curr_index, 's')
    if curr_char == '-' and (direction == 'n' or direction == 's'):
        patterns = trace(patterns, curr_index, 'e')
        patterns = trace(patterns, curr_index, 'w')
    if curr_char == '|' and (direction == 's' or direction == 'n') or curr_char == '-' and (direction == 'e' or direction == 'w'):
        patterns = trace(patterns, curr_index, direction)
    return patterns

file = """
.|...\\....
|.-.\\.....
.....|-...
........|.
..........
.........\\
..../.\\\\..
.-.-/..|..
.|....-|.\\
..//.|....
""".strip().split('\n')

file = [list(x) for x in file]
new_file = trace(file, [0, 0], 'e')
printfile(new_file)
