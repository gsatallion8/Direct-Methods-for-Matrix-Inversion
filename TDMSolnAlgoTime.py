from subprocess import call
call(["gcc", "ThomasAlgorithm.c","-o","ThomasAlgorithm"])
i=1
while i<10000:
	call(["./ThomasAlgorithm",str(i)])
	print i	
	i+=100
import matplotlib.pyplot as plt
import numpy as np

Thomas=np.loadtxt("Thomas_time.txt")
plt.plot(Thomas[:,0],Thomas[:,1])
plt.show()
