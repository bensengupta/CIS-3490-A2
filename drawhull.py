import matplotlib
import matplotlib.pyplot as plt

matplotlib.use('svg')

with open("data_A2_Q2.txt") as f:
    lines = f.readlines()

def floateq(a, b):
    return abs(a - b) < 0.0000000001

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

x = []
y = []
points = []

for line in lines:
    parts = line.strip().split('   ')
    x.append(float(parts[0]))
    y.append(float(parts[1]))

hullPointsStr = """
  1156.3   24.3
  3943.7   32.0
  5616.9   37.6
  6265.4   73.0
  6434.5   1065.1
  6416.4   3607.9
  6382.1   5517.2
  6163.4   6092.8
  5961.6   6274.5
  5561.2   6328.5
  4336.6   6384.0
  3839.0   6397.2
  2238.7   6426.4
  1769.3   6414.2
  484.1   6266.3
  128.3   6091.3
  120.9   6008.0
  30.8   3064.0
  28.3   1205.6
  122.9   621.9
  145.7   517.0
  272.6   240.1
"""
hullPoints = []
for line in hullPointsStr.strip().split('\n'):
    p1, p2 = line.strip().split('   ')
    hullPoints.append((float(p1), float(p2)))

hx = list(map(lambda p: p[0], hullPoints))
hy = list(map(lambda p: p[1], hullPoints))

plt.scatter(x, y, alpha=0.4, marker='.', s=2)

for i in range(len(hullPoints)):
    x1, y1 = hullPoints[i]
    x2, y2 = hullPoints[(i + 1) % len(hullPoints)]
    plt.plot([x1, x2], [y1, y2], alpha=0.4, lw=1, color='yellow', marker='none')

plt.scatter(hx, hy, marker='.', s=3, color='red')

plt.savefig('plot.png', dpi=600)

