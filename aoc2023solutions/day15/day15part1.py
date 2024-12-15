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
total_sum = 0
for i in file:
    total_sum += aoc_hash(i)

print(total_sum)
