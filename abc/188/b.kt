import java.lang.Math.abs

fun main(args: Array<String>) {
    val N = readLine()!!.toDouble()
    val A = readLine()!!.split(" ").map(String::toInt)
    val B = readLine()!!.split(" ").map(String::toInt)
    var total = 0
    for(i in A.indices){
        total += A[i]*B[i]
    }
    if(total == 0)
        println("Yes")
    else
        println("No")
}