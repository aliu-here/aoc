import curses

import time

class vis:
    def __init__(self):
        curses.curs_set(0)
        curses.start_color()
        curses.use_default_colors()
        for i in range(0, 23):
            curses.init_pair(i + 1, i + 233, -1)
        curses.init_pair(24, 0, 10)

        file = open("input.txt", "r")
        lines = [x[::-1][1:] for x in file.readlines()]

        self.idx = len(lines[0]) - 1
        self.whole = curses.newwin(11, 80, 0, 0)

        self.drawborders()
        self.whole.refresh()

        offset = 0
        fps = 20
        vals = []
        total = 0
        while True:
            self.drawborders()
            self.whole.addstr(1, 1,"Advent of Code 2025, Day 6 Part 2".center(78))
            for i in range(len(lines)):
                for j in range(72):
                    if (j + offset >= len(lines[i])):
                        break
                    dist = j-72
                    color = None
                    if (j == 0):
                        color = curses.color_pair(24)
                    else: 
                        intensity = 22-int(22 - 0.00408889 * (dist)**2) #calculated from quadratic fitting
                        color = curses.color_pair(intensity + 1)
                    self.whole.addch(i+3, 75-j-1, lines[i][j + offset], color)

            col = ""
            for i in range(len(lines)):
                if (offset >= len(lines[i])):
                    break
                self.whole.addch(i + 3, 75 + 1, lines[i][offset])
                if (lines[i][offset] != ' '):
                    col += lines[i][offset]
            if (col != ''):
                if (col[-1].isdecimal()):
                    vals.append(col)
                else:
                    vals.append(col[:-1])
            op = " ? "
            if (col != '' and not (col[-1].isdecimal())):
                op = " " + col[-1] + " "
                tmp = int(vals[0])
                for i in range(1, len(vals)):
                    if op == " * ":
                        tmp *= int(vals[i])
                    else:
                        tmp += int(vals[i])
                total += tmp
                self.whole.addstr(9, 1, f"total: {total}".ljust(39) + f"{op.join(vals)} = {tmp}".rjust(39))
                vals = []
            else:
                self.whole.addstr(9, 1, f"total: {total}".ljust(39) + f"{op.join(vals)}".rjust(39))
            self.whole.refresh()
            time.sleep(1/fps)
            offset += 1
    def drawborders(self):
        self.whole.clear()
        self.whole.border()
        self.whole.addch(2, 0, curses.ACS_LTEE)
        self.whole.addch(2, 79, curses.ACS_RTEE)
        for i in range(1, 79):
            self.whole.addch(2, i, curses.ACS_HLINE)
        
        self.whole.addch(8, 0, curses.ACS_LTEE)
        self.whole.addch(8, 79, curses.ACS_RTEE)
        for i in range(1, 79):
            self.whole.addch(8, i, curses.ACS_HLINE)
        for i in range(3, 8):
            self.whole.addch(i, 75, curses.ACS_VLINE)
        self.whole.addch(2, 75, curses.ACS_TTEE)
        self.whole.addch(8, 75, curses.ACS_BTEE)

def main(stdscr):
    stdscr.getch()
    vis()
curses.wrapper(main)
