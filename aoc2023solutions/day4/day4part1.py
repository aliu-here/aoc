f = open("input.txt", 'r')
file = f.read().strip().split('\n')

new = []
for i in file:
    new.append(i.split(':')[1])
file = new
cards = []
for i in file:
    cards.append(i.split('|'))
sum = 0
for i in cards:
    winningnums = i[0].split()
    yournums = i[1].split()
    count = -1
    for j in yournums:
        if j in winningnums:
            count += 1
    if count >= 0:
        sum += 2**count

print(sum)
