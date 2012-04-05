/* Author: Pan Gu 
 * Data file: http://spark-public.s3.amazonaws.com/algo1/programming_prob/QuickSort.txt
 * The file contains all of the integers between 1 and 10,000 (inclusive) in unsorted order (with no integer repeated). The integer in the ith row of the file gives you the ith entry of an input array.
 *
 * Your task is to compute the total number of comparisons used to sort the given input file by QuickSort. As you know, the number of comparisons depends on which elements are chosen as pivots, so we'll ask you to explore three different pivoting rules.
 * You should not count comparisons one-by-one. Rather, when there is a recursive call on a subarray of length m, you should simply add m−1 to your running total of comparisons. (This is because the pivot element will be compared to each of the other m−1 elements in the subarray in this recursive call.)

 * WARNING: The Partition subroutine can be implemented in several different ways, and different implementations can give you differing numbers of comparisons. For this problem, you should implement the Partition subroutine as it is described in the video lectures (otherwise you might get the wrong answer). 
 * 1. First element as median
 * 2. Last element as mediam
 * 3. Median of therr (first last and middle)
*/
#include <cstdio>
#include <algorithm>
using namespace std;
typedef int (*P)(int *, int, int);
int p1(int *a, int l, int r) { return l; }
int p2(int *a, int l, int r) { return r; }
int p3(int *a, int l, int r)
{ 
	int m = (l + r)/2;
	if(a[l] < a[m]) return a[m] < a[r] ? m : (a[l] < a[r] ? r : l);
	return a[l] < a[r] ? l : (a[m] < a[r] ? r : m);
}
P p[3] = {p1, p2, p3};
int getCount(int *a, int l, int r, P pivot)
{
	if(r - l < 1) return 0;
	int p = pivot(a, l, r);
	swap(a[l], a[p]);
	int i, j;
	for(i = j = l + 1; j <= r; j++)
		if(a[j] < a[l]) swap(a[i++], a[j]);
	swap(a[l], a[i-1]);
	return r - l + getCount(a, l, i - 2, pivot) + getCount(a, i, r, pivot);
}
int main()
{
	freopen("QuickSort.txt", "r", stdin);
	int a[10010], b[10010];
	int i, j, k;
	for(i = 0; scanf("%d", &a[i]) > 0; i++);
	for(j = 0; j < 3; j++) {
		for(k = 0; k < i; k++) b[k] = a[k];
		printf("%d\n", getCount(b, 0, i - 1, p[j]));
	}
	return 0;
}
