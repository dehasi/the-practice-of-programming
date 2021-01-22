package markov

import java.io.BufferedReader
import java.io.InputStream
import java.io.InputStreamReader
import java.io.StreamTokenizer
import java.io.StreamTokenizer.TT_EOF
import java.util.Random
import kotlin.math.abs

class Prefix() {
    companion object {
        val MULTIPLIER = 31
    }

    val pref = mutableListOf<String>()

    constructor(prefix: Prefix) : this() {
        prefix.pref.forEach { this.pref.add(it) }
    }

    constructor(n: Int, str: String) : this() {
        for (i in 0 until n) pref.add(str)
    }

    override fun hashCode(): Int {
        var h = 0
        for (i in 0 until pref.size)
            h = MULTIPLIER * h + pref[i].hashCode()
        return h
    }

    override fun equals(other: Any?): Boolean {
        if (other is Prefix) {
            for (i in 0 until pref.size)
                if (this.pref[i] != other.pref[i])
                    return false
            return true
        } else {
            return false
        }
    }
}

class Chain {
    companion object {
        val NPREF = 2 // size prefix
        val NONWORD = "\n" // "word" that can't appear
    }

    val statetab = mutableMapOf<Prefix, MutableList<String>>() // key = prefix, val = suffixes
    val prefix = Prefix(NPREF, NONWORD)
    val random = Random()

    fun build(input: InputStream) {
        val st = StreamTokenizer(BufferedReader(InputStreamReader(input)))

        st.resetSyntax() // remove default rules
        st.wordChars(0, Char.MAX_VALUE.toInt()) // turn on all chars
        st.whitespaceChars(0, ' '.toInt()) // except up to blank

        while (st.nextToken() != TT_EOF)
            add(st.sval)
        add(NONWORD)
    }

    private fun add(word: String) {
        if (!statetab.containsKey(prefix)) {
            statetab[Prefix(prefix)] = mutableListOf()
        }
        val suf = statetab[prefix]!!
        suf.add(word)
        prefix.pref.removeAt(0)
        prefix.pref.add(word)
    }

    fun generate(nwords: Int) {
        val prefix = Prefix(NPREF, NONWORD)

        for (i in 0 until nwords) {
            val suffixes = statetab[prefix]!!
            val r = abs(random.nextInt()) % suffixes.size
            val word = suffixes.elementAt(r)

            if (word == NONWORD) break

            println(word)
            prefix.pref.removeAt(0)
            prefix.pref.add(word)
        }
    }
}

class Markov {
    companion object {
        val MAXGEN = 10000
    }

    fun main() {
        val nwords = MAXGEN

        val chain = Chain()
        chain.build(System.`in`)
        chain.generate(nwords)
    }
}

class App {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            Markov().main()
        }
    }
}
