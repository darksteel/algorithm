/* Author: Pan Gu
 * Data file: http://spark-public.s3.amazonaws.com/algo1/programming_prob/IntegerArray.txt
 * The file contains all the 100,000 integers between 1 and 100,000 (including both) in some random order( no integer is repeated).
 * Your task is to find the number of inversions in the file given (every row has a single integer between 1 and 100,000). Assume your array is from 1 to 100,000 and ith row of the file gives you the ith entry of the array.
 * Write a program and run over the file given. The numeric answer should be written in the space.
 * So if your answer is 1198233847, then just type 1198233847 in the space provided without any space / commas / any other punctuation marks. You can make upto 5 attempts, and we'll count the best one for grading.
 * (We do not require you to submit your code, so feel free to choose the programming language of your choice, just type the numeric answer in the following space)
*/
#include <cstdio>
#define N 100000
typedef long long ll;
int a[N+10], buf[N+10];
ll count(int *a, int n)
{
	if(n < 2) return 0;
	int m = n/2;
	ll ret = count(a, m) + count(a+m, n-m);
	int i, j, k;
	for(i = 0, j = m, k = 0; i < m; i++) {
		while(j < n && a[j] < a[i])
			buf[k++] = a[j++];
		ret += j - m;
		buf[k++] = a[i];
	}
	for(i = 0; i < k; i++) a[i] = buf[i];
	return ret;
}
int main()
{
	freopen("IntegerArray.txt", "r", stdin);
	for(int i = 0; i < N; i++) scanf("%d", &a[i]);
	printf("%lld\n", count(a, N));
}
