f = open("input.txt", 'r')
file = f.read().split('\n')

file = [line.split(':')[-1] for line in file]
file = [draws.split(';') for draws in file]
copy = []
for i in file:
    temp = []
    for j in i:
        if j != '':
            temp.append(j)
    if temp != []:
        copy.append(temp)


file = copy
file = [[rolls.split(',') for rolls in draws] for draws in file]

file = [[[[roll.strip().split(' ')] for roll in rolls] for rolls in draws] for draws in file] #cursed list comprehension


sum = 0
#print(file)
skip = False

for game in enumerate(file):
    skip = False
    colours = {"red":0, "blue":0, "green":0}
    for j in game[1]:
        for n in j:
            for draw in n:
                colours[draw[1]] = max(colours[draw[1]], int(draw[0]))
    power = colours["red"] * colours["blue"] * colours["green"]
    sum += power

print(sum)
