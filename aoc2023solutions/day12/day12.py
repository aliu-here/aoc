"""def find_known_loc_and_length(string):
    known_loc_and_length = [[0, 0]]
    loc = 0
    length = 0
    for i in enumerate(string):
        if length == 0 and i[1] == "#":
            loc = i[0]
            length += 1 
        elif i[1] == "#":
            length += 1 
        elif length != 0:
            known_loc_and_length.append([loc, length])
            length = 0
    if length != 0:
        known_loc_and_length.append([loc, length])
    known_loc_and_length.append([len(string) - 1, 0])
    return known_loc_and_length

def choose(a, b):
    out = 1
    for i in range(b):
        out *= (a - i) / (b - i)
    if not out.is_integer():
        return int(out)
    return 0

def match_to_num_list(string, num_list):
    curr_contiguous = num_list[0]
    way_sum = 0
    known_loc_and_pos = find_known_loc_and_length(string)
    doesnt_work = True
    print(known_loc_and_pos)
    print(string, num_list)
    if len(known_loc_and_pos) == 2:
        print("all ?")
        num_list_sum = sum(num_list)
        diff = len(string) - num_list_sum
        min_division_chars = len(num_list) - 1
        if diff <= min_division_chars:
            return 0
        return choose(diff + min_division_chars - 1, min_division_chars - 1)
    if string[0] == "?":
        print("?")
        copy1 = string[:]
        copy1[0] = "."
        copy2 = string[:]
        copy2[0] = "#"
        way_sum += match_to_num_list(copy1, num_list)
        way_sum += match_to_num_list(copy2, num_list)
    if string[0] == "#":
        print("#")
        for i in enumerate(known_loc_and_pos[1:-1]):
            endloc = i[1][0] + i[1][1]
            print(i)
            if endloc == curr_contiguous:
                doesnt_work = False
                way_sum += match_to_num_list(string[known_loc_and_pos[i[0] + 1][0] + 1:], num_list[1:])
        if doesnt_work:
            return 0
    return way_sum"""

#f = open('input.txt', 'r')
#file = f.read().strip().split()
file = """
?#?#?# 1,3
""".strip().split('\n')

total_sum = 0

for line in file:
    split_line = line.split(' ')
    contiguous_numbers = [int(x) for x in split_line[1].split(',')]
    spring_list = [x for x in split_line[0]]
    for i in range(2):
        spring_list = spring_list[min(spring_list.index("?"), spring_list.index("#")):][::-1]
    forward_sharp_idx = spring_list.index("#")
    backward_sharp_idx = spring_list[::-1].index("#")
    if backward_sharp_idx < forward_sharp_idx:
        #        line_count = match_to_num_list(spring_list[::-1], contiguous_numbers[::-1])
        pass
    else:
        #        line_count = match_to_num_list(spring_list, contiguous_numbers)
        pass
    print(line_count)
