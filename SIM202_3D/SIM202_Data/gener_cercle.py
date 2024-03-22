import math
import pyperclip

def discretize_circle(x, y, radius, num_sides):
    points = []

    theta = 2.0 * math.pi / num_sides

    for i in range(num_sides):
        cx = x + radius * math.cos(theta * i)
        cy = y + radius * math.sin(theta * i)
        points.append((cx, cy))

    return points[::-1]

x = float(input())
y = float(input())
radius = float(input())
num_sides = 32

points = discretize_circle(x, y, radius, num_sides)

# pyperclip.copy(" ".join([str(p[0])+" "+str(p[1]) for p in points]))
print(" ".join([str(p[0])+" "+str(p[1]) for p in points]))