def allzero(list):
    if list == []:
        return False
    for i in list:
        if i != 0:
            return False
    return True
f = open("input.txt", 'r')
file = f.read().strip().split('\n')
sum = 0
for i in file:
    nums = [int(x) for x in i.split()]
    difflist = [nums]
    diffs = []
    newdiffs = []
    for j in range(1, len(nums)):
        newdiffs.append(nums[j] - nums[j-1])
    diffs = newdiffs
    difflist.append(diffs)
    while not allzero(newdiffs):
        newdiffs = []
        for j in range(1, len(diffs)):
            newdiffs.append(diffs[j] - diffs[j-1])
        diffs = newdiffs
        difflist.append(diffs)
    nextnum = 0
    for j in enumerate(difflist[::-1]):
        nextnum = j[1][0] - nextnum
    sum += nextnum

print(sum)
