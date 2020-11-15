from os import listdir
from os.path import isfile, join

def getList(dirname):
    onlyfiles = [join(dirname, f) for f in listdir(dirname) if isfile(join(dirname, f)) and f[-1] == "h"]
    return onlyfiles

def countLines(list):
    counter = 0

    for path in list:
        file = open(path, "r")
        lines = file.readlines()
        counter += len(lines)

    return counter

list = getList("/Users/kali/Documents/Programming/Unit/C++/uamp/app")
list += getList("/Users/kali/Documents/Programming/Unit/C++/uamp/app/src")
print(countLines(list))
