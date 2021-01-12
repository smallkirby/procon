from sys import stdin

N = int(stdin.readline().rstrip())
counter = 0
for i in range(N):
  a,b = [int(x) for x in stdin.readline().rstrip().split(" ")]
  counter += (b-a+1)*(a+b)/2

print(int(counter))