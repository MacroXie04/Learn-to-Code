import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

s = np.linspace(0, 2, 300)

x4 = np.cos(s**3)
y4 = np.sin(s**3)
z4 = s**3

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')

ax.plot(x4, y4, z4, label=r'$\vec{r}_4(s) = \langle \cos (s^3), \sin (s^3), s^3 \rangle$', color='m')

ax.set_xlabel("X-axis")
ax.set_ylabel("Y-axis")
ax.set_zlabel("Z-axis")
ax.set_title("3D Parametric Curve")

plt.legend()
plt.show()

