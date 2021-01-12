import java.lang.Math.abs

fun main(args: Array<String>) {
    val (x,y) = readLine()!!.split(" ").map(String::toInt)
    if(kotlin.math.abs(x - y) <=2)
        println("Yes")
    else
        println("No")
}