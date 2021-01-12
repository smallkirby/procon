fun main(args: Array<String>) {
    val (N,C) = readLine()!!.split(" ").map(String::toInt)
    val events = mutableMapOf<Int, Int>()
    val a = mutableListOf<Int>()
    val b = mutableListOf<Int>()
    val c = mutableListOf<Int>()
    for(i in 0 until N){
        val tmp = readLine()!!.split(" ").map(String::toInt)
        a.add(tmp[0])
        b.add(tmp[1])
        c.add(tmp[2])
        events[a[i]] = if(events.containsKey(a[i])) events[a[i]]!!+c[i] else c[i]
        events[b[i]+1] = if(events.containsKey(b[i]+1)) events[b[i]+1]!!-c[i] else -c[i]
    }

    var total: Long = 0L
    var current_price: Long = 0L
    var yesterday: Int = 0
    val endday = b.maxBy{it} ?: 0
    for((key,value) in events.toSortedMap()){
        //println("yesterday:${yesterday} today:${key} up:${value} total:${total} price:${current_price.coerceAtMost(C.toLong())}")
        total += current_price.coerceAtMost(C.toLong()).toLong() * (key - yesterday).toLong()
        if(key > endday)
            break
        current_price += value
        yesterday = key
    }
    println(total)
}