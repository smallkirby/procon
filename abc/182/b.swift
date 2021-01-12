import Foundation

func readInts() -> [Int]{
    return readLine()!.split(separator: " ").map{Int($0)!}
}

let N = readInts()[0]
let A = readInts()
var maxgcd = 0
var king = 0

for i in 2...A.max()!{
    var counter = 0
    for a in A{
        if a%i==0{
            counter += 1
        }
    }
    //print("counter: \(counter)")
    if maxgcd < counter{
        maxgcd = counter
        king = i
    }
}
print(king)
