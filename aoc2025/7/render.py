import os

os.system(f"mkdir -p render")
os.system(f"rm -r render/*")
os.system(f"./vis")
os.chdir(f"render")
file = open("0.ppm", "r", encoding="latin_1")
print(file.readline())
dims = [int(x) for x in file.readline().split()]
scale_factor = 1080 / max(dims)
os.system(f"ffmpeg -r 5 -f image2 -i %d.ppm -vf scale=iw*{scale_factor}:ih*{scale_factor} vis1.gif")

os.chdir("..")
os.system(f"rm -r render/*.ppm")
os.system(f"./vis2")
os.chdir(f"render")
file = open("0.ppm", "r", encoding="latin_1")
print(file.readline())
dims = [int(x) for x in file.readline().split()]
scale_factor = 1080 / max(dims)
os.system(f"ffmpeg -r 5 -f image2 -i %d.ppm -vf scale=iw*{scale_factor}:ih*{scale_factor} vis2.gif")
