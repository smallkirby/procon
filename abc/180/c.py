import itertools
from sys import stdin
from functools import *
import math

N = int(stdin.readline().rstrip())

lows, highs = [],[]
i = 1
while i*i <= N:
  if N%i == 0:
    lows.append(i)
    if i != N//i:
      highs.append(N//i)
  i += 1

for i in lows+highs[::-1]:
  print(i)