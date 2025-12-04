import os

os.system(f"mkdir -p render")
os.system(f"rm -r render/*")
os.system(f"./p2vis")
os.chdir(f"render")
os.system(f"ffmpeg -r 100 -f image2 -i %d.ppm -vf scale=1080:1080 -sws_flags neighbor render.mp4")
