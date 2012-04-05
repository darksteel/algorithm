#!/usr/bin/python
# see inversion.cpp for problem description
# Author: Pan Gu
def count(l):
    n = len(l);
    if n < 2: return 0, l;
    m = n/2;
    nl, ll = count(l[:m]);
    nr, lr = count(l[m:]);
    ret = nl + nr;
    i, j = 0, 0;
    for x in ll:
	while i < n-m and lr[i] < x:
	    l[j] = lr[i];
	    i, j = i+1, j+1;
	ret += i;
	l[j] = x;
	j += 1;
    l[j:] = lr[i:];
    return ret, l;
f = open("IntegerArray.txt");
l = [int(f.readline()) for i in xrange(100000)];
print count(l)[0];
