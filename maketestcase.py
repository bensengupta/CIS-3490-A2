import random

numhullpoints = 7
points = [
    # hull points
    3.2, 5,
    2, 8.2,
    2.5, 10.5,
    4, 12,
    18.8, 10.2,
    12, 5,
    18.8, 8,
    # rest
    11.3, 11.1,
    4, 12,
    7, 5,
    5.1, 10,
    8, 9,
    12, 9,
    16, 10,
    18, 9,
    10, 5.8,
    4.2, 6.2,
    4.2, 9,
    6.8, 8,
    3.5, 11.5,
    10, 11,
    6.8, 6,
    15, 7,
    16, 6.8,
]


lines = []
for i in range(0, len(points), 2):
    x, y = round(float(points[i]), 1), round(float(points[i + 1]), 1)
    lines.append(f'  {str(x).rjust(6)}   {str(y).rjust(6)} \n')

print('Total hull points =', numhullpoints)
for i in range(0, numhullpoints * 2, 2):
    print(lines[i], end='')

random.shuffle(lines)

with open('testdata_A2_Q2.txt', 'w') as f:
    f.writelines(lines)