import numpy as np
from scipy.signal import savgol_filter
from matplotlib import pyplot as plt
plt.rcParams['figure.dpi'] = 300
plt.rcParams['savefig.dpi'] = 300
plt.rcParams['font.size'] = 16
data=[]
f=open("data.txt", "r")
for k in f:
    data.append(float(k))
np.set_printoptions(precision=2)  # For compact display.
x = np.array(data)

xp=savgol_filter(x, 10, 2)
#xp=savgol_filter(x, 5, 2, mode='nearest')

dxp=[]
for i in range(1,len(xp)-1):
    dxp.append((xp[i+1]-xp[i-1])/2/0.01)

dxpp=savgol_filter(dxp, 20, 2)


t=0.52
T=[]
for i in range(len(dxpp)):
    T.append(t)
    t+=0.01

z=0
w=0
for i in range(len(T)):
    if dxpp[i]>w:
        w=dxpp[i]
        z=T[i]
    
print(z)
ax=plt.figure(figsize=(12,8))

plt.xlabel("Temperature")
plt.ylabel(r'$\frac{\partial U}{\partial T}$', fontsize=30)
plt.plot(T, dxpp)
plt.annotate('Critical Point', xy=(z, w), xytext=(2.5, 16000),
            arrowprops=dict(facecolor='black', shrink=0.05))
#plt.show()
plt.savefig("FirstD1.jpg")



