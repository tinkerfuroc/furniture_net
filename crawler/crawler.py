import requests
import re
import os

labels = ['Chair', 'Table', 'Sofa']

for label in labels:
    find_id = re.compile(r'\<a href="\?a=download&amp;id=(\w+)" title="Download')
    for i in range(1, 1+24*1, 24):
        url = 'http://archive3d.net/?tag=' + label + '&page=' + str(i)
        print ('getting ' + url)
        r = requests.get(url)
        cont = r.content
        cont = cont.decode('utf-8')
        label_ids = find_id.findall(cont)
        for label_id in label_ids:
            r = requests.get(u'http://archive3d.net/?a=download&do=get&id='+label_id)
            filename = './data/'+label+'/'+label_id+'.zip'
            print ('writing '+filename)
            f = open(filename, 'wb')
            f.write(r.content)
            f.close()
            
