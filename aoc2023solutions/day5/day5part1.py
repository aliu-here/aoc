f = open('input.txt', 'r')
file = f.read().strip().split('\n\n')
seeds = [int(x) for x in file[0].split(':')[1].strip().split()]

maps = [[[int(j) for j in i.split()] for i in x.split('\n')[1:]] for x in file[1:]]
#print(maps)
dictionaries = []


minloc = 2**1024 #thats probably enough

for i in seeds:
    #    print()
    result = i
    for j in maps:
        for k in j:
           dest = k[0]
           source = k[1]
           rangelen = k[2]
           if source <= result <= source + rangelen - 1:
               result = dest + (result - source)
               break
    minloc = min(minloc, result)

print(minloc)

