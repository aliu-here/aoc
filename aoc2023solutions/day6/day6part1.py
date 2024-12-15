f = open("input.txt", "r")
file = f.read().splitlines()

times = [int(x) for x in file[0].split()[1:]]
recorddistances = [int(x) for x in file[1].split()[1:]]
product = 1

#print(times)

for time in enumerate(times):
    ways = 0
    for timeheld in range(time[1] + 1):
        distance = timeheld * (time[1] - timeheld)
        if distance > recorddistances[time[0]]:
            ways += 1
    product *= ways

print(product)
