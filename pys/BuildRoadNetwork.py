#This program has two functions:
#1. transfer csv into cplusplus-friendly txt
#2. merge intersections with eps = 1e-5

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.path import Path
import matplotlib.patches as patches

m = 0
mapDict = dict()
edgeDict = dict()
pointDict = dict()

def readCSV():
    filename = '../data/RoadNetworkTemp.csv'
    rwgs = pd.read_csv(filename)
    rwgs = rwgs.values

    m = rwgs.shape[0] - 1
    print(m)

    rwgs = rwgs[1:, 0:2]
    for i in range(m):
        if rwgs[i][0] != 1:
            tmpx = int(rwgs[i][0] * 1e5)
            tmpy = int(rwgs[i][1] * 1e5)
            #if tmpx >= 3125000 and tmpx <= 3128000 and tmpy >= 12155000 and tmpy <= 12158000: 
            mapDict[(int(rwgs[i][0] * 1e5), int(rwgs[i][1] * 1e5))] = 1
    cntn = 0
    for i in mapDict.keys():
        cntn += 1
        mapDict[i] = cntn
        pointDict[cntn] = i
    print(cntn)
    u = mapDict[(int(rwgs[0][0] * 1e5), int(rwgs[0][1] * 1e5))]
    connect = True
    for i in range(1, m):
        if rwgs[i][0] == 1:
            connect = False
            continue
        try:
            v = mapDict[(int(rwgs[i][0] * 1e5), int(rwgs[i][1] * 1e5))]
        except:
            continue
        if connect == True:
            if u != v:
                edgeDict[(min(u, v), max(u, v))] = 1
        u = v
        connect = True
    cntm = 0
    for i in edgeDict.keys():
        cntm += 1
        edgeDict[i] = cntm
    print(cntm)

    with open('../data/roadraw.txt','w') as f:
        f.write("%d %d\n" % (cntn, cntm))
        for i in pointDict.keys():
            f.write("%d %d\n" % (pointDict[i][1]*1, pointDict[i][0]*1))
        for i in edgeDict.keys():
            f.write("%d %d\n" % (i[0], i[1]))

#to mark the empty lines with 1, otherwise empty lines are ignored;
def preAna():
    with open('../data/RoadNetworkTemp.csv', 'w') as f:
        for line in open('../data/RoadNetwork.csv', 'r'):
            if len(line) < 2:
                f.write("1\n")
            else:
                f.write(line)

preAna()
readCSV()

