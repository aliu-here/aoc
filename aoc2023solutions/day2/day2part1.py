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

colours = {'red':12, 'green':13, 'blue':14}

sum = 0
#print(file)
skip = False

for game in enumerate(file):
    skip = False
    for j in game[1]:
        for n in j:
            for draw in n:
                if colours[draw[1]] < int(draw[0]):
                    sum += game[0] + 1
#                    print(game[0] + 1)
                    skip = True
                    break
            if skip:
                break
        if skip:
            break

sum = int((len(file) * (len(file) + 1)/2) - sum)

print(sum)
