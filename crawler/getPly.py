import os
import subprocess
import re
import zipfile


filedir = r"."

for (dirpath, dirname, filenames) in os.walk(filedir):
    for filename in filenames:
        if filename.split('.')[-1] == 'zip':
            zippath = os.path.join(dirpath, filename)
            print ('unziping ' + zippath)
            newfolder = filename.split('.')[-2]
            outpath = os.path.join(dirpath, newfolder)
            try:
                z = zipfile.ZipFile(zippath)
                subprocess.call(['mkdir', outpath])
                subprocess.call(['mkdir', outpath.replace('data', 'ply')])

                for name in z.namelist():
                    if filename.split('.')[-1] == '3DS':
                        print ('extract ' + name + ' to ' + outpath)
                        z.extract(name, outpath)
            except:
                print ('Exception raised in unzipping.')
                continue

for (dirpath, dirname, filenames) in os.walk(filedir):
    for filename in filenames:
        if filename.split('.')[-1] == '3DS':
            path = os.path.join(dirpath, filename)
            outpath = path.replace('data', 'ply').replace('3DS', 'ply')
            print ('converting '+ path + ' to ' + outpath)
            try:
                
                subprocess.call(['meshlabserver', '-i', path, '-o', outpath])
            except:
                print ('meshlabserver failed.')
                continue

