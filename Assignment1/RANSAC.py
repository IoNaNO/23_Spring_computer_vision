# Autor: 1953921 Yuanzhe Chen
import numpy as np
import random
import math
import matplotlib.pyplot as plt

# input points
points=[
   (-2, 0), (0, 0.9), (2, 2.0), (3, 6.5), (4, 2.9), (5, 8.8), (6, 3.95), (8, 5.03), (10, 5.97),(12, 7.1), (13, 1.2), (14, 8.2), (16, 8.5),(18, 10.1)
]

# parameters
iterations=1000
threshold=0.5
THRESHOLD=10

# RANSAC
best_inliers=0
best_model=None
for _ in range(iterations):
    # randomly select two points
    sample_index=random.sample(range(len(points)),2)
    sample=[points[sample_index[0]],points[sample_index[1]]]

    # calculate the line slope and intercept
    slope=(sample[1][0]-sample[0][1])/(sample[1][0]-sample[0][0])
    intercept=sample[0][1]-slope*sample[0][0]

    inliers=0
    S=[]
    control=False
    # calculate the distance
    for point in points:
        distance=abs(slope*point[0]-point[1]+intercept)/math.sqrt(slope**2+1)
        ## count the inliers
        if(distance<threshold):
            inliers=inliers+1
            S.append(point)
        if(inliers>THRESHOLD):
            nS=np.array(S)
            x=nS[:,0]
            y=nS[:,1]
            A=np.vstack([x,np.ones(len(x))]).T
            best_model=np.linalg.lstsq(A,y,rcond=None)[0]
            control=True
            break
    
    # if the number of inliers excceed the THRESHOLD, terminate
    if(control):
        break

    # update the best inliers result and record its model
    if inliers>best_inliers:
        best_model=(slope,intercept)
        best_inliers=inliers

# show the result graphically
npoints=np.array(points)
## extract coordinates
x=npoints[:,0]
y=npoints[:,1]
## calculate the fitted line
x_line=np.linspace(np.min(x),np.max(x),100)
y_line=best_model[0]*x_line+best_model[1]
## plot the sample points and fitted line
plt.scatter(x,y,color='blue',label='sample points')
plt.plot(x_line,y_line,color='red',label=f'fitted line: y={best_model[0]:.2f}x+{best_model[1]:.2f}')
## show the plot
plt.xlabel('x')
plt.ylabel('y')
plt.title('Straight 2D line fit using RANSAC')
plt.legend()
plt.show()
