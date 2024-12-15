def errors(list1, list2):
    out = 0
    for i,j in list1, list2:
        for k,l in i,j:
            if k != l:
                out += 1 
    return out

f = open("input.txt", 'r')
file = f.read().strip().split('\n\n')

file = [x.split('\n') for x in file]

known_horiz_pos = []
known_vert_pos = []
out_sum = 0

#print(file)

for block in file:
    temp = []
    for i in range(1, len(block) // 2 + 1):
        first_half = block[:i]
        sec_half = block[i:2*i]
        rev_first_half = block[::-1][:i]
        rev_sec_half = block[::-1][i:2*i]
        if first_half == sec_half[::-1]:
            out_sum += i * 100
            temp.append(i)
        if rev_first_half == rev_sec_half[::-1]:
            out_sum += (len(block) - i) * 100
            temp.append((len(block) - i))
    rotated_block = []
    known_horiz_pos.append(temp)
    temp = []
    for i in range(len(block[0])):
        rotated_block.append(''.join([x[i] for x in block]))
    for i in range(1, len(rotated_block) // 2 + 1):
        first_half = rotated_block[:i]
        sec_half = rotated_block[i:2*i]
        rev_first_half = rotated_block[::-1][:i]
        rev_sec_half = rotated_block[::-1][i:2*i]
        if first_half == sec_half[::-1]:
            out_sum += i
            temp.append(i)
        if rev_first_half == rev_sec_half[::-1]:
            out_sum += (len(rotated_block) - i)
            temp.append(len(rotated_block) - i)
    known_vert_pos.append(temp)

part2_out_sum = 0
for section in enumerate(file):
    inverse = {"#":".", ".":"#"}
    goto_next = False
    for a in range(len(section[1])):
        for b in range(len(section[1][0])):
#            print()
            block = [list(x) for x in section[1][:]]
            block[a][b] = inverse[section[1][a][b]]
            block = [''.join(x) for x in block]
#            print(block)
            for i in range(1, len(block) // 2 + 1):
                first_half = block[:i]
                sec_half = block[i:2*i]
                rev_first_half = block[::-1][:i]
                rev_sec_half = block[::-1][i:2*i]
#                print(first_half, sec_half)
#                print(rev_first_half, rev_sec_half)
                if first_half == sec_half[::-1] and i not in known_horiz_pos[section[0]]:
                    part2_out_sum += i * 100
                    goto_next = True
                if rev_first_half == rev_sec_half[::-1] and (len(block) - i) not in known_horiz_pos[section[0]]:
                    part2_out_sum += (len(block) - i) * 100
                    goto_next = True
            rotated_block = []
            if goto_next:
                break
            for i in range(len(block[0])):
                rotated_block.append(''.join([x[i] for x in block]))
            for i in range(1, len(rotated_block) // 2 + 1):
                first_half = rotated_block[:i]
                sec_half = rotated_block[i:2*i]
                rev_first_half = rotated_block[::-1][:i]
                rev_sec_half = rotated_block[::-1][i:2*i]
                if first_half == sec_half[::-1] and i not in known_vert_pos[section[0]]:
                    part2_out_sum += i
                    goto_next = True
                if rev_first_half == rev_sec_half[::-1] and (len(rotated_block) - i) not in known_vert_pos[section[0]]:
                    part2_out_sum += (len(rotated_block) - i)
                    goto_next = True
            if goto_next:
                break
        if goto_next:
            break

print("part 1:", out_sum)
print("part 2:", part2_out_sum)
