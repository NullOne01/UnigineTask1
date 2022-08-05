import sys
import random
import numpy as np


def main():
    data_file_name = str(sys.argv[1])
    data_file = open(data_file_name, 'w')

    units_num = int(sys.argv[2])

    angle = random.uniform(30, 180)
    view_distance = random.uniform(1, 5)

    print(f"Angle: {angle}, Distance: {view_distance}")
    data_file.write(f"{angle} {view_distance}\n")

    print(f"Generating {units_num} units...")
    for i in range(units_num):
        x = random.uniform(-100, 100)
        y = random.uniform(-100, 100)
        view_x = random.uniform(-1, 1)
        view_y = random.uniform(-1, 1)

        view_vec = np.array([view_x, view_y])
        normalized_view = view_vec / np.sqrt(np.sum(view_vec ** 2))

        print(f"X: {x}, Y: {y}, ViewX: {normalized_view[0]}, ViewY: {normalized_view[1]}")
        data_file.write(f"{x} {y} {normalized_view[0]} {normalized_view[1]}\n")

    print(f"Generated!")
    data_file.close()


if __name__ == "__main__":
    main()
