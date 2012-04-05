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
