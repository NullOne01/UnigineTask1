import sys
import numpy as np
from matplotlib.patches import Wedge
import matplotlib.pyplot as plt

data_file_name = str(sys.argv[1])
data_file = open(data_file_name, 'r')

line = data_file.readline()

sector_angle = float(line.split()[0])
view_distance = float(line.split()[1])

print(f"View distance: {view_distance}")
print(f"Sector angle: {sector_angle}")

origin_list = []
view_list = []
while True:
    # Get next line from file
    line = data_file.readline()

    # if line is empty
    # end of file is reached
    if not line:
        break

    sub_lines = line.split()
    origin_list.append((float(sub_lines[0]), float(sub_lines[1])))
    view_list.append((float(sub_lines[2]), float(sub_lines[3])))

data_file.close()

origin_arr = np.array(origin_list)
view_arr = np.array(view_list)

# View vector
plt.quiver(origin_arr[:, 0], origin_arr[:, 1], view_arr[:, 0] * view_distance, view_arr[:, 1] * view_distance,
           angles='xy', scale_units='xy', scale=1)
# Unit pos
plt.plot(origin_arr[:, 0], origin_arr[:, 1], 'go')

# Sector
fig = plt.figure(1)
ax = fig.gca()
right_vec = [1, 0]
for i in range(len(origin_list)):
    origin_pair = origin_list[i]
    view_pair = view_arr[i]

    angle = np.math.atan2(np.linalg.det([right_vec, view_pair]), np.dot(right_vec, view_pair))
    angle_deg = np.degrees(angle)

    fov = Wedge(origin_pair, view_distance, angle_deg - sector_angle / 2, angle_deg + sector_angle / 2, color="r", alpha=0.5)
    ax.add_artist(fov)

ax.set_aspect('equal')
plt.tight_layout()
plt.show()
