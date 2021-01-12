import Foundation

func readInts() -> [Int]{
    return readLine()!.split(separator: " ").map{Int($0)!}
}

extension StringProtocol{
    subscript(offset: Int) -> Character{
        self[index(startIndex, offsetBy: offset)]
    }
}

var Nstr = readLine()!
var counter = 20 // >18

if Int(Nstr)!%3 == 0{
    print(0)
    exit(0)
}

/* N<10**18だから探索範囲は2**18で全列挙可能 */
for i in 1..<Int(truncating: (NSDecimalNumber(decimal: pow(2,Nstr.count)))){
    var now: Int = 0
    var cur = i
    for j in 0..<Nstr.count{
        if (cur&1) == 1{
            now += Int(String(Nstr[Nstr.count-1 - j]))!
        }
        cur >>= 1
        if cur <= 0{
            break
        }
    }

    let elims = Nstr.count - String(i, radix:2).filter{$0=="1"}.count
    if now%3 == 0 && counter > elims {
        counter = elims
    }
}

if counter != 20{
    print(counter)
}else{
    print(-1)
}
