#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 1000000
#define MAXE 6000000
int first[MAXN], fst[MAXN], next[MAXE], nxt[MAXE], from[MAXE], to[MAXE];
int n = 875715, cnt, visited[MAXN], finish[MAXN], top[10];
pair<int, int> p[MAXN];
void dfs1(int u)
{
	visited[u] = 1;
	for(int e = first[u]; e > 0; e = next[e])
		if(!visited[to[e]]) dfs1(to[e]);
	finish[u] = cnt++;
}
int dfs2(int v)
{
	int ret = 1;
	visited[v] = 1;
	for(int e = fst[v]; e > 0; e = nxt[e])
		if(!visited[from[e]]) ret += dfs2(from[e]);
	return ret;
}
void kosaraju()
{
	for(int i = 1; i < n; i++) if(!visited[i]) dfs1(i);
	for(int i = 1; i < n; i++) p[i] = make_pair(finish[i], i);
	sort(p+1, p+n);
	memset(visited, 0, sizeof(visited));
	for(int i = n-1; i > 0; i--) {
		if(visited[p[i].second]) continue;
		top[5] = dfs2(p[i].second);
		for(int j = 4; j >= 0; j--)
			if(top[j] < top[j+1]) swap(top[j], top[j+1]);
	}
}
int main()
{
	freopen("SCC.txt", "r", stdin);
	for(int i = 1; scanf("%d %d", &from[i], &to[i]) > 0; i++) {
		int u = from[i], v = to[i];
		next[i] = first[u]; nxt[i] = fst[v];
		first[u] = fst[v] = i;
	}
	kosaraju();
	for(int i = 0; i < 5; i++) printf("%d\n", top[i]);
	return 0;
}
