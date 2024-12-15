from math import lcm
def allendswithz(input):
    for i in input:
        if i[-1] != "Z":
            return False
    return True

f = open("input.txt", "r")
file = f.read().strip().split('\n\n')
seq = file[0]
nodes = {}
starts = []
regstart = "AAA"
for i in file[1].split('\n'):
    data = i.split('=')
    node = data[0].strip()
    if node[-1] == "A":
        starts.append(node)
    children = data[1][2:-1].split(',')
    nodes[node] = {'L':children[0].strip(), 'R':children[1].strip()}

part2steps = 0
times = []
for i in starts:
    start = i
    counter = 0
    while start[-1] != "Z":
        start = nodes[start][seq[counter % len(seq)]]
        counter += 1
    times.append(counter)

final = 1

for i in times:
    final = lcm(final, i)

print(final)
