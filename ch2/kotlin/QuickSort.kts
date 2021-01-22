fun swap(array: Array<Int>, i: Int, j: Int) {
    val tmp = array[i]
    array[i] = array[j]
    array[j] = tmp
}

fun qsort(array: Array<Int>, start: Int = 0, end: Int) {
    if (start >= end) return

    val pivot = start + (end - start) / 2
    swap(array, start, pivot)

    var last = start
    for (i in start..end - 1) {
        if (array[start] > array[i]) {
            ++last
            swap(array, last, i)
        }
    }

    swap(array, start, last)
    qsort(array, start, last)
    qsort(array, last + 1, end)

}

var array = arrayOf(1, 3, 2, 4)
array.forEach { print("%d ".format(it)) }
println()
qsort(array, 0, 4)
array.forEach { print("%d ".format(it)) }
println()
var ints = arrayOf(6, 5, 4, 3, 2, 1, 0)
ints.forEach { print("%d ".format(it)) }
println()
qsort(ints, 0, ints.size)
ints.forEach { print("%d ".format(it)) }
println()
