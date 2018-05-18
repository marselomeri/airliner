"""
This script executes the given Pyliner-dependant script in a wrapped environment
so that if the given script fails during execution a predetermined fail-safe
executes in its place.

Note:
    Script is incomplete. Currently only prints tracebacks of errors.
    TODO Problem is how to take control of vehicles in command by script.
        Somehow the script needs to request access through Execliner.

Usage:
    python execliner.py script.py
"""

import argparse
import imp
import traceback

from pyliner_exceptions import PylinerError

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Executes the given script in a Pyliner environment.'
    )
    parser.add_argument('script', help='Name of script to execute.')
    args = parser.parse_args()
    try:
        script = imp.load_source('main', args.script)
        print(dir(script))
        if 'main' in dir(script):
            print('Found main')
    except ImportError as e:
        print('Unable to import the given script.')
        traceback.print_exc()
    except PylinerError as e:
        print('Pyliner Error:')
        traceback.print_exc()
    except StandardError as e:
        print('Generic script failure.')
        traceback.print_exc()
