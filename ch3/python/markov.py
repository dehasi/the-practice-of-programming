#!/usr/bin/python3

import sys
from random import randint

NONWORD = "\n"
MAXGEN = 10000
NPREF = 2

statetab = {}


def add(prefix, w):
    if len(prefix) == NPREF:
        statetab[tuple(prefix)] = statetab.get(tuple(prefix), [])
        statetab[tuple(prefix)].append(w)
        prefix.pop()
    prefix.append(w)


def build(prefix, file):
    for line in file:
        for word in line.split():
            add(prefix, word)


def generate(nwords):
    prefix = ["\n", "\n"]

    while(nwords > 0):
        suffix = statetab[tuple(prefix)]
        word = suffix[randint(0, len(suffix)-1)]

        if word == NONWORD:
            break

        print(word)
        prefix.pop()
        prefix.append(word)
        nwords -=1


if __name__ == '__main__':
    prefix = ["\n", "\n"]
    build(prefix, sys.stdin)
    generate(MAXGEN)
