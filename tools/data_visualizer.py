import sys
import numpy as np
from matplotlib.patches import Wedge
import matplotlib.pyplot as plt


def draw_cell_list(bottom_left, top_right, side):
    bottom_right = [top_right[0], bottom_left[1]]
    top_left = [bottom_left[0], top_right[1]]

    sides = np.array([bottom_left, bottom_right, top_right, top_left, bottom_left])
    plt.plot(sides[:, 0], sides[:, 1])

    height = top_left[1] - bottom_right[1]
    width = bottom_right[0] - top_left[0]

    for i in range(int(height / side)):
        new_y = bottom_left[1] + (i + 1) * side
        plt.plot([bottom_left[0], bottom_right[0]], [new_y, new_y], color='orange')
    for i in range(int(width / side)):
        new_x = top_left[0] + (i + 1) * side
        plt.plot([new_x, new_x], [bottom_left[1], top_left[1]], color='orange')


def main():
    data_file_name = str(sys.argv[1])
    data_file = open(data_file_name, 'r')

    show_numbers = len(sys.argv) < 3 or sys.argv[2] == "yes"

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
    if show_numbers:
        for i in range(len(origin_list)):
            plt.text(origin_arr[i][0], origin_arr[i][1], str(i))

    # Sector
    fig = plt.figure(1)
    ax = fig.gca()
    right_vec = [1, 0]

    min_x = origin_arr[0][0]
    min_y = origin_arr[0][0]
    max_x = origin_arr[0][0]
    max_y = origin_arr[0][0]

    for i in range(len(origin_list)):
        origin_pair = origin_list[i]
        view_pair = view_arr[i]

        min_x = min(min_x, origin_pair[0])
        min_y = min(min_y, origin_pair[1])
        max_x = max(max_x, origin_pair[0])
        max_y = max(max_y, origin_pair[1])

        angle = np.math.atan2(np.linalg.det([right_vec, view_pair]), np.dot(right_vec, view_pair))
        angle_deg = np.degrees(angle)

        fov = Wedge(origin_pair, view_distance, angle_deg - sector_angle / 2, angle_deg + sector_angle / 2, color="r",
                    alpha=0.5)
        ax.add_artist(fov)

    # Drawing cell list
    draw_cell_list([min_x, min_y], [max_x, max_y], view_distance)

    plt.xlim([min_x - view_distance, max_x + view_distance])
    plt.ylim([min_y - view_distance, max_y + view_distance])
    ax.set_aspect('equal')
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
