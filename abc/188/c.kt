import java.lang.Math.abs
import java.lang.Math.pow
import kotlin.math.pow

lateinit var A: List<Int>
var last: Int = 0

fun hoge(start: Int, end: Int): Int{
    if(end-start == 1){
        return if(A[start] > A[end]) start
                else end
    }
    val num: Int = (end - start + 1)/2
    val a = hoge(start, start+num-1)
    val b = hoge(start+num, end)
    return if(A[a] > A[b]){
        last = b
        a
    }else{
        last = a
        b
    }
}

fun main(args: Array<String>) {
    val N = readLine()!!.toInt()
    A = readLine()!!.split(" ").map(String::toInt)

    if(N==1){
        if(A[0]>A[1])
            println("2")
        else
            println("1")
    }else{
        hoge(0, 2.toDouble().pow(N.toDouble()).toInt() - 1)
        println(last+1)
    }
}