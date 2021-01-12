import itertools
from sys import stdin
from functools import *
import math


N = int(stdin.readline().rstrip())
x = [int(x) for x in stdin.readline().rstrip().split(" ")]

print(reduce(lambda _sum,a: _sum + abs(a), x, 0))
print(math.sqrt(reduce(lambda _sum, a: _sum + a**2, x, 0)))
print(max([abs(n) for n in x]))