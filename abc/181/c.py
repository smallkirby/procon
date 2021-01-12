import itertools
from sys import stdin

'''
N<=10**2だから、全探索はC(N,3)<10**6
全探索でいける
'''

N = int(stdin.readline().rstrip())
G = []
counter = 0
for i in range(N):
  tx,ty = [float(x) for x in stdin.readline().rstrip().split(" ")]
  G.append((tx,ty))

hoge = []
for (a,b,c) in itertools.combinations(G, 3):
  if b[0]==a[0] or c[0]==a[0]:
    if a[0] == c[0] and a[0] == b[0]:
      print("Yes")
      exit(0)
    continue

  if (b[1]-a[1])/(b[0]-a[0]) == (c[1]-a[1])/(c[0]-a[0]):
    print("Yes")
    exit(0)

print("No")

#print(list(reversed(sorted(list(map(lambda n: abs(n), hoge))))))
