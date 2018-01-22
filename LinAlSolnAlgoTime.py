from subprocess import call
call(["gcc", "MatrixGenerator.c","-o","MatrixGenerator"])
call(["gcc", "GaussElimination.c","-o","GaussElimination"])
call(["gcc", "LUDecomposition.c","-o","LUDecomposition"])
call(["gcc", "MatrixInversionMethod.c","-o","MatrixInversionMethod"])

i=1
while i<20:
	call(["./MatrixGenerator",str(i)])
	call(["./MatrixInversionMethod"])
	i+=1

i=1
while i<1000:
	call(["./MatrixGenerator",str(i)])
	call(["./GaussElimination"])
	call(["./LUDecomposition"])
	i+=1

while i<10000:
	call(["./ThomasAlgorithm",str(i)])
	print i	
	i+=100



import matplotlib.pyplot as plt
import numpy as np

LUD=np.loadtxt("LUD_time.txt")
Gauss=np.loadtxt("Gauss_time.txt")
Coff=np.loadtxt("Coff_time.txt")
Thomas=np.loadtxt("Thomas_time.txt")

#Tridiagonal Matrix algorithm:
plt.plot(Thomas[:,0],Thomas[:,1])
plt.show()

#Naive Matrix inversion:
plt.plot(Coff[:,0],Coff[:,1])
plt.show()

#Gaussian Elimination:
plt.plot(Gauss[:,0],Gauss[:,1])
plt.show()

#LU Decomposition:
plt.plot(LUD[:,0],LUD[:,1])
plt.show()
