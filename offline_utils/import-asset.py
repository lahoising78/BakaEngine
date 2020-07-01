#! /usr/bin/python3

import sys

files = []
fromLink = False

for arg in sys.argv[1:]:
    print(arg)

    if arg == '-l':
        fromLink = True
    else:
        files.append(arg)

print('file' + str(files))
print('from link: ' + str(fromLink))