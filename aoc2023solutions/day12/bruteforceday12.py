f = open("input.txt", 'r')
file = f.read().strip().split('\n')

#file = 
"""

???.### 1,1,3
.??..??...?##. 1,1,3
?#?#?#?#?#?#?#? 1,3,1,6
????.#...#... 4,1,1
????.######..#####. 1,6,5
?###???????? 3,2,1

""".strip().split('\n')

working_count = 0

for i in file:
    data = i.split(' ')
    seq = [x for x in data[0]]
    nums = [int(x) for x in data[1].split(',')]
    qmark_count = 0
    for j in seq:
        if j == "?":
            qmark_count += 1
    for j in range(1 << qmark_count):
        binary_str = list(format(j, 'b').zfill(qmark_count))
        map = {"0":'.', "1":"#"}
        for k in range(len(binary_str)):
            binary_str[k] = map[binary_str[k]]
        seq_copy = seq[:]
        counter = 0
        for k in enumerate(seq_copy):
            if k[1] == "?":
                seq_copy[k[0]] = binary_str[counter]
                counter += 1
        num_count = []
        curr_count = 0
        for k in seq_copy:
            if k == "#":
                curr_count += 1
            elif curr_count != 0:
                num_count.append(curr_count)
                curr_count = 0
        if curr_count != 0:
            num_count.append(curr_count)
        if num_count == nums:
            working_count += 1
print(working_count)
