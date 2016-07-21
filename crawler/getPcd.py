import os
import re
import subprocess

filedir = r'.'
f = open(r'./pcd.sh', 'w')

for (dirpath, dirname, filenames) in os.walk(filedir):
    for filename in filenames:
        if filename.split('.')[-1] == 'ply':
            filepath = os.path.join(dirpath, filename)
            r = re.search(r'\./(Table|Chair|Sofa)/(\w+)', dirpath)
            labelname = r.group(1)
            idname = r.group(2)
            outpath = os.path.join(filedir, labelname, idname + r'.pcd')
            print ('try calling ply2pcd from ' + filepath + ' to ' + outpath)
            try:
                f.write(r'./ply2pcd '+'"'+filepath+'" '+outpath+'\n')
            except:
                continue
