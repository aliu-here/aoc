f = open('input.txt', 'r')
file = f.read().strip().split('\n\n')
seeds = [int(x) for x in file[0].split(':')[1].strip().split()]

maps = [[[int(j) for j in i.split()] for i in x.split('\n')[1:]] for x in file[1:]]


#print(maps)
blocks = []

for i in range(0, len(seeds), 2):
    blocks.append([seeds[i],seeds[i] + seeds[i+1] - 1])
print(blocks)

for map in maps:
    newblocks = []
    map = sorted(map, key=lambda x:x[1])
#    print("\n\nnew map")
#    print(f"{map=}")
    for block in blocks:
        #        print()
        temp = [block]
        endthisit = False
        it = 0
#        print(f"{temp=}")
        while it < len(temp):
            #            print(f"{temp[it]=}")
            start = temp[it][0]
            end = temp[it][1]
            for line in map:
                startlessthanmin = start < line[1]
                endgreaterthanmin = line[1] + line[2] - 1 < end 
                startinrange = line[1] <= start <= line[1] + line[2] - 1
                endinrange = line[1] <= end <= line[1] + line[2] - 1
                startresult = line[0] + (start - line[1])
                endresult = line[0] + (end - line[1])
 #               print(f"{startinrange=}, {endinrange=}, {line=}")
                if startinrange and endinrange:
                    temp.pop(it)
                    temp.append([startresult, endresult])
                    endthisit = True
                    break
                if startinrange and not endinrange:
                    temp.pop(it)
                    temp.append([startresult, line[0] + line[2] - 1])
                    temp.append([line[1] + line[2], end])
                    endthisit = True
                    break
                if not startinrange and endinrange:
                    temp.pop(it)
                    temp.append([line[0], endresult])
                    temp.append([start, line[1] - 1])
                    endthisit = True
                    break
                if startlessthanmin and endgreaterthanmin:
                    temp.pop(it)
                    temp.append([start, line[1] - 1])
                    temp.append([line[1], end])
                    break
            it += 1
 #           print(f"{it=}, {temp=}")
        newblocks += temp
    blocks = newblocks
        
#print(blocks)
blocks = sorted(blocks, key=lambda x:x[0])
#print(blocks)
print(blocks[0][0])
