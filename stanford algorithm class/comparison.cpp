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
