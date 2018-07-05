"""
Pyliner LogView

Enables the fast and easy browsing of Pyliner logs.

Usage:
    python logview.py [filename]
"""

import argparse
import curses
import glob
import os
import re
from abc import abstractmethod


class LogLine(object):
    def __init__(self, log_line, text):
        self.log_line = log_line
        self.text = text

    @property
    def level(self):
        """Return the curses color-pair number for the level of the line."""
        try:
            level = self.text.split(' - ')[2]
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


class FilterLine(LogLine):
    def __init__(self, filter_line, log_line):
        super(FilterLine, self).__init__(log_line.log_line, log_line.text)
        self.filter_line = filter_line


class ViewLine(FilterLine):
    def __init__(self, view_line, filter_line):
        super(ViewLine, self).__init__(filter_line.filter_line, filter_line)
        self.view_line = view_line


class LogView(object):
    def __init__(self, stdscr, log_name):
        # Curses Initialization
        # Start colors in curses
        curses.start_color()
        curses.init_pair(1, curses.COLOR_GREEN, curses.COLOR_BLACK)
        curses.init_pair(2, curses.COLOR_YELLOW, curses.COLOR_BLACK)
        curses.init_pair(3, curses.COLOR_RED, curses.COLOR_BLACK)
        curses.init_pair(4, curses.COLOR_BLACK, curses.COLOR_WHITE)
        curses.init_pair(5, curses.COLOR_BLACK, curses.COLOR_CYAN)

        # Application State
        self.exit = False
        self.log_name = log_name
        self.state = None
        self.stdscr = stdscr

        with open(self.log_name) as fp:
            self.log_lines = [LogLine(*x) for x in enumerate(fp.readlines())]

        self.state_map = {
            'NORMAL': NormalState,
            'GOTO': GotoState
        }

        # Useful for User Interaction
        self.filter = ''
        self.filter_lines = None
        self.apply_filter(lambda line: True)
        self.view_lines = None
        self.center_view(0)
        self.cursor_column = 0
        self.cursor_line = 0

    def apply_filter(self, func):
        """Set filter_lines to the lines filtered by func, and global_cursor
        to the closest previous filtered line."""
        if self.filter is func:
            return
        self.filter = func
        if isinstance(func, str):
            func = lambda line: line.text.contains(func)
        self.filter_lines = [FilterLine(*x) for x in 
                             enumerate(filter(func, self.log_lines))]
    
    def center_view(self, filter_index):
        """Set view_lines to contain lines centered around filter_index as much
        as possible."""
        h = self.height
        h2 = h / 2
        min_index = max(0, filter_index - h2)
        max_index = min(len(self.filter_lines), filter_index + h2)
        if min_index == 0:
            max_index = h - 1
        self.view_lines = [ViewLine(*x) for x in 
                           enumerate(self.filter_lines[min_index: max_index])]

    def cursor_move(self, lines):
        self.cursor_line = max(
            0, min(len(self.filter_lines), self.cursor_line + lines))
        self.in_view(self.cursor_line)
        
    @property
    def height(self):
        return self.stdscr.getmaxyx()[0]

    def in_view(self, filter_index):
        """Puts filter_index in view."""
        if filter_index not in (l.filter_line for l in self.filter_lines):
            self.center_view(filter_index)

    def key_press(self, key):
        if not self.state.handle_key(key):
            pass

    def state_change(self, state):
        if self.state is not None:
            self.state.exit()
        self.state = state
        state.enter()

    def run(self):
        self.state_change(self.state_map['NORMAL'](self))

        while not self.exit:
            # Wait for next input
            self.key_press(self.stdscr.getch())


class BaseState(object):
    def __init__(self, log_view):
        self.log_view = log_view

    def enter(self):
        pass

    def exit(self):
        pass

    @abstractmethod
    def handle_key(self, key):
        raise NotImplementedError()

    @property
    def stdscr(self):
        return self.log_view.stdscr


class NormalState(BaseState):
    def enter(self):
        self.redraw()

    def status_bar_render(self):
        len_filter = len(self.log_view.filter_lines)
        line_status = 'TOP' if self.log_view.cursor_line == 0 else\
            'BOT' if self.log_view.cursor_line == len_filter else\
            str(self.log_view.cursor_line)
        statusbarstr = "Press 'q' to exit | STATUS BAR | Pos: {} Col: {}" \
            .format(line_status, self.log_view.cursor_column)

        height, width = self.stdscr.getmaxyx()
        self.stdscr.attron(curses.color_pair(5))
        self.stdscr.addstr(height - 1, 0, statusbarstr)
        self.stdscr.addstr(height - 1, len(statusbarstr),
                      " " * (width - len(statusbarstr) - 1))
        self.stdscr.attroff(curses.color_pair(5))

    def handle_key(self, key):
        # Key Bindings
        x_vel = 1
        y_vel = 2
        
        if key == curses.KEY_DOWN:
            self.log_view.cursor_move(x_vel)
        elif key == curses.KEY_UP:
            self.log_view.cursor_move(-x_vel)
        elif key == curses.KEY_NPAGE:
            self.log_view.cursor_move(10 * x_vel)
        elif key == curses.KEY_PPAGE:
            self.log_view.cursor_move(-10 * x_vel)
        elif key == curses.KEY_LEFT:
            self.log_view.cursor_column -= y_vel
        elif key == curses.KEY_RIGHT:
            self.log_view.cursor_column += y_vel
        elif key == curses.KEY_HOME:
            self.log_view.cursor_column -= 10 * y_vel
        elif key == curses.KEY_END:
            self.log_view.cursor_column += 10 * y_vel
        elif key == ord('q'):
            self.log_view.exit = True

        self.redraw()

    def redraw(self):
        # Initialization
        self.stdscr.clear()
        height, width = self.stdscr.getmaxyx()

        # Determine lines to display
        display_lines = self.log_view.view_lines

        # Left Header
        max_line = display_lines[-1].log_line
        left_reserve = len(str(max_line))

        # Bound column
        longest_display = max(len(line.text) for line in display_lines)
        start_column = max(0, self.log_view.cursor_column)
        start_column = min(longest_display - 2, start_column)

        # Display Log file
        for line in display_lines:
            color = curses.color_pair(line.level)
            left = '{:>{x}}'.format(line.log_line, x=left_reserve)
            end_column = start_column + width - (len(left) + 2)
            visible_line = line.text[start_column:end_column]
            display = '{}  {}'.format(left, visible_line)
            try:
                self.stdscr.addstr(line.filter_line, 0, display, color)
            except Exception as e:
                self.stdscr.addstr(0, 0, str(e)[:width], color)

        self.status_bar_render()

        # Refresh the screen
        self.stdscr.refresh()


class GotoState(BaseState):
    @property
    def status_bar_height(self):
        return 1

    def status_bar_render(self):
        pass

    def handle_key(self, key):
        pass


def log_view(stdscr, filename):
    """Main function. Displays a log viewer with Python curses."""
    view = LogView(stdscr, filename)
    view.run()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Log Viewer for Pyliner'
    )
    parser.add_argument('filename', nargs='?',
                        help='Filename of log to view.')

    args = parser.parse_args()
    filename = args.filename

    if filename is None:
        log_files = glob.glob('logs/*')
        filename = max(log_files, key=os.path.getctime)

    if not os.path.isfile(filename):
        print('filename must exist.')
        exit(1)

    curses.wrapper(log_view, filename)
