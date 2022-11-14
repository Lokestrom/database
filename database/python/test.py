from multiprocessing.connection import wait
from write import *
import time

def main():
    temp, lys, fukt, vfar, vret = 0,0,0,0,0

    tid = time.localtime()
    lastDay = tid.tm_mday
    fileName = f"{tid.tm_mday}.{tid.tm_mon}.{tid.tm_year}.db"

    fil = writeFile(fileName)
    fil.addColumns(["tid", "temp", "lys", "fukt", "vfar", "vret"])
    for i in range(0,1):
        tid = time.localtime()
        if(tid.tm_mday != lastDay):
            lastDay = tid.tm_mday
            fil.close()
            fileName = f"{tid.tm_mday}.{tid.tm_mon}.{tid.tm_year}.db"
            fil.open(fileName)
            fil.addColumns(["tid", "temp", "lys", "fukt", "vfar", "vret"])
        fil.addDataFloat([tid.tm_hour*100 + tid.tm_min, temp, lys, fukt, vfar, vret])
        


main()