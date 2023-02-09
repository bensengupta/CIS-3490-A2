import matplotlib.pyplot as plt

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

for line in lines:
    parts = line.strip().split('   ')
    x.append(float(parts[0]))
    y.append(float(parts[1]))

hullPointsStr = """
  0   1156.3    24.3
  1   3943.7    32.0
  2   5616.9    37.6
  3   6265.4    73.0
  4   6434.5  1065.1
  5   6416.4  3607.9
  6   6382.1  5517.2
  7   6163.4  6092.8
  8   5961.6  6274.5
  9   5561.2  6328.5
 10   4336.6  6384.0
 11   3839.0  6397.2
 12   2238.7  6426.4
 13   1769.3  6414.2
 14    484.1  6266.3
 15    128.3  6091.3
 16    120.9  6008.0
 17     30.8  3064.0
 18     28.3  1205.6
 19    122.9   621.9
 20    145.7   517.0
 21    272.6   240.1
"""

hullX = []
hullY = []
for line in hullPointsStr.strip().split('\n'):
    label, hx, hy = list(filter(len, line.strip().split(' ')))
    hullX.append(float(hx))
    hullY.append(float(hy))

plt.scatter(x, y, alpha=0.4, marker='.', s=2)

labeloffset = max(max(hullX), max(hullY)) * 0.005

for i in range(len(hullX)):
    plt.plot(hullX[i], hullY[i], marker='.', markersize=3, color='red')
    plt.text(hullX[i] + labeloffset, hullY[i] + labeloffset, f"({round(hullX[i], 1)}, {round(hullY[i], 1)})", fontsize=3)


for i in range(len(hullX)):
    j = (i + 1) % len(hullX)
    plt.plot([hullX[i], hullX[j]], [hullY[i], hullY[j]], alpha=0.4, lw=1, color='yellow', marker='none')


plt.savefig('plot.png', dpi=600)

