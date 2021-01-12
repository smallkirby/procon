func readInts() -> [Int]{
    return readLine()!.split(separator: " ").map{Int($0)!}
}

let nums = readInts()[0...1]
let A = nums[0]
let B = nums[1]
print(2*A+100 - B)
