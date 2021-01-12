import itertools
from sys import stdin

N,A,B = [int(x) for x in stdin.readline().rstrip().split(" ")]
print(N-A+B)