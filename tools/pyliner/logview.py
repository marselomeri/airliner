import argparse
import curses
import glob
import os
import re


def get_lines(lines, number, search):
    num = 1
    ret = []
    for line in lines:
        if re.search(search, line[1]):
            ret.append(line)
            num += 1
        if num > number:
            break
    return ret


def line_level(line):
    try:
        level = line.split(' - ')[2]
    except IndexError:
        level = 'CRITICAL'
    table = {
        'NOTSET': 0,
        'DEBUG': 0,
        'INFO': 1,
        'WARNING': 2,
        'ERROR': 3,
        'CRITICAL': 3
    }
    return table[level]


def log_view(stdscr, filename):
    # Load log file
    with open(filename) as fp:
        log_lines = list(enumerate(fp.readlines()))

    stdscr.clear()
    stdscr.refresh()

    # Start colors in curses
    curses.start_color()
    curses.init_pair(1, curses.COLOR_GREEN, curses.COLOR_BLACK)
    curses.init_pair(2, curses.COLOR_YELLOW, curses.COLOR_BLACK)
    curses.init_pair(3, curses.COLOR_RED, curses.COLOR_BLACK)
    curses.init_pair(4, curses.COLOR_BLACK, curses.COLOR_WHITE)
    curses.init_pair(5, curses.COLOR_BLACK, curses.COLOR_CYAN)

    k = 0
    start_line = 0
    len_log = len(log_lines)
    start_column = 0

    # Loop where k is the last character pressed
    while k != ord('q'):

        # Initialization
        stdscr.clear()
        height, width = stdscr.getmaxyx()

        # Key Bindings
        x_vel = 1
        y_vel = 2

        if k == curses.KEY_DOWN:
            start_line += x_vel
        elif k == curses.KEY_UP:
            start_line -= x_vel
        elif k == curses.KEY_LEFT:
            start_column -= y_vel
        elif k == curses.KEY_RIGHT:
            start_column += y_vel
        elif k == curses.KEY_NPAGE:
            start_line += 10 * x_vel
        elif k == curses.KEY_PPAGE:
            start_line -= 10 * x_vel
        elif k == curses.KEY_HOME:
            start_column -= 10 * y_vel
        elif k == curses.KEY_END:
            start_column += 10 * y_vel

        # Bound starting line
        start_line = min(len_log - height + 1, start_line)
        start_line = max(0, start_line)
        min_line = start_line

        # Status Bar State
        status_height = 1

        # Filter Lines
        search = 'INFO'
        num_lines = height - status_height
        filter_lines = filter(lambda l: re.search(search, l[1]) is not None,
                              log_lines)
        display_lines = filter_lines[min_line:min_line+num_lines+1]

        # Left Header
        max_line = display_lines[-1][0]
        left_reserve = len(str(max_line))

        # Bound column
        start_column = max(0, start_column)
        start_column = min(len(max(display_lines, key=len)) - 2, start_column)

        # Display Log file
        for display_line, line in enumerate(display_lines):
            color = curses.color_pair(line_level(line[1]))
            left = '{:>{x}}'.format(line[0], x=left_reserve)

            visible_line = line[1][start_column:start_column+width-(len(left)+2)]
            display = '{}  {}'.format(left, visible_line)
            stdscr.addstr(display_line, 0, display, color)
            try:
                pass
            except Exception as e:
                stdscr.addstr(0, 0, str(e)[:width-10], color)

        # Render status bar
        statusbarstr = "Press 'q' to exit | STATUS BAR | Pos: {} / {}".format(
            start_line, len(filter_lines))
        stdscr.attron(curses.color_pair(5))
        stdscr.addstr(height - 1, 0, statusbarstr)
        stdscr.addstr(height - 1, len(statusbarstr),
                      " " * (width - len(statusbarstr) - 1))
        stdscr.attroff(curses.color_pair(5))

        # Refresh the screen
        stdscr.refresh()

        # Wait for next input
        k = stdscr.getch()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Log Viewer for Pyliner'
    )
    parser.add_argument('--filename')

    args = parser.parse_args()
    filename = args.filename

    if filename is None:
        log_files = glob.glob('logs/*')
        filename = max(log_files, key=os.path.getctime)

    if not os.path.isfile(filename):
        print('filename must exist.')
        exit(1)

    curses.wrapper(log_view, filename)
