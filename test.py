import numpy as np 
dx = 0.5
num = 0

for i in np.arange(0, 1+dx, dx):
    for j in np.arange(0, 1+dx, dx):
        for k in np.arange(0, 1+dx, dx):
            print("{", f"{i:.3}, {j:.3}, {k:.3}", "},")
            num += 1

print(num)
