import argparse
import imp
from logging import DEBUG, INFO
from os.path import basename

from pyliner.util import enable_logging


# TODO If going service route, use config file for setup


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('script')
    parser.add_argument('--log-dir')
    parser.add_argument('--log-file')
    parser.add_argument('-v', '--debug', action='store_true')

    args = parser.parse_args()

    if args.log_dir:
        enable_logging(
            log_dir=args.log_dir,
            log_file=args.log_file,
            script=basename(args.script),
            level=DEBUG if args.debug else INFO)

    imp.load_source('script', args.script)
