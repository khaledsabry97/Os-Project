
import plotly.plotly as py
import plotly.tools as tls

import matplotlib.pyplot as plt

x = []
y = []
counter=0

with open(r'.\results.txt') as f :#write directory of the file
  
    
    for line in f: 
        z=line.split(' ') 
        for val in z:    
            if counter==0 :
                x.append(float(val)) #to take the x axis (time)
                counter=1 
            elif counter==1 :
                y.append(float(val)) #to take the y axis (process numbers)
                counter=0          
        

i = 0

z =[]
while i < len(y):
    if y[i]==-1 : #this is for the context switch
        y[i]=0.0
    if i + 1 < len(y):
        z.append(x[i+1] - x[i])
    else:
        z.append(0)
    i += 1
   

plt.bar(x, y, z, color="red",align="edge")
plt.show()


