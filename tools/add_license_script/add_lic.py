""" 
Script to prepend license to files in a dir

Usage:
python3 add_lic.py -f [list of file types. Ex: 'a,b,c'] -l [path to license file] -d [path of dir to walk and prepend license]
"""

import argparse
import os
import sys
import glob

def prepend_lic(lic_path, file_path):
	with open(lic_path, 'r') as lic:
		license = lic.read()
		with open(file_path, 'r+') as f:
			content = f.read()
			f.seek(0,0)
			f.write(license + '\n' + content)

if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Autogenerate a cFS app.')
	parser.add_argument('-f','--file_types', help='File types to prepend license to (Ex: \'a,b,c\')')
	parser.add_argument('-l','--license_file', help='Path to license txt file')
	parser.add_argument('-d','--target_dir', help='Directory to walk and apply license to')
	args = vars(parser.parse_args())

	# Verify minimun args present
	file_types = args['file_types']
	license_file = args['license_file']
	target_dir = args['target_dir']
	if not file_types or not license_file or not target_dir:
		print("Error: Missing required args")
		sys.exit(1)

	file_types = file_types.split(',')

	# Validate paths
	if not os.path.isfile(license_file):
		print("Error: Invalid license file")
		sys.exit(1)

	if not os.path.exists(target_dir):
		print("Error: Invalid target dir")
		sys.exit(1)

	# Recur into target dir
	for file_path in glob.glob(target_dir + '**/*', recursive=True):
		file_split = file_path.split('/')
		if file_split[-1].split('.')[-1] in file_types:
			print("Adding license to:", file_path)
			prepend_lic(license_file, file_path)

	
