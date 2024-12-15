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
for i in file[1].split('\n'):
    data = i.split('=')
    node = data[0].strip()
    children = data[1][2:-1].split(',')
    nodes[node] = {'L':children[0].strip(), 'R':children[1].strip()}

steps = 0
currnode = "AAA"
while currnode != "ZZZ":
    currnode = nodes[currnode][seq[steps % len(seq)]]
    steps += 1

print(steps)
