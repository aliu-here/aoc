f = open("input.txt", "r")
file = f.read().split('\n')
digits = [str(x) for x in range(10)]
sum = 0
newfile = []

for i in file:
    for j in i:
        if j in digits:
            sum += int(j) * 10
#            print(j, end='')
            break
    for j in i[::-1]:
        if j in digits:
            sum += int(j)
#            print(j)
            break
print(sum)
