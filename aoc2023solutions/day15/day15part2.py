def aoc_hash(string):
    out = 0
    for i in string:
        out += ord(i)
        out *= 17
        out %= 256
    return out

f = open('input.txt', 'r')
file = f.read().strip().split(',')
#file = "rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7".strip().split(',')
boxes = []
for i in range(256):
    boxes.append([])
total_sum = 0
for i in file:
    if '=' in i:
        hashed_loc = aoc_hash(i.split('=')[0])
        if i.split('=')[0] in [x[0] for x in boxes[hashed_loc]]:
            boxes[hashed_loc][[x[0] for x in boxes[hashed_loc]].index(i.split('=')[0])] = (i.split('=')[0], int(i.split('=')[1])) #horrifying spaghetti
        else:
            boxes[hashed_loc].append((i.split('=')[0], int(i.split('=')[1])))
    if '-' in i:
        hashed_loc = aoc_hash(i.split('-')[0])
        try:
            boxes[hashed_loc].pop([x[0] for x in boxes[hashed_loc]].index(i.split('-')[0]))
        except:
            pass

for i in enumerate(boxes):
    for j in enumerate(i[1]):
        total_sum += (j[0] + 1) * j[1][1] * (i[0] + 1)

print(total_sum)
