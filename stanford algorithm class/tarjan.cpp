#include <cstdio>
#include <list>
#include <algorithm>
#include <functional>
using namespace std;
list<int> e[875715];
int visited[875715], low[875715], idx[875715], st[875715];
int cnt = 0, sp = 0;
int tp[10];
void dfs(int u)
{
	list<int>::iterator it;
	visited[u] = 1;
	st[++sp] = u;
	idx[u] = low[u] = cnt++;
	for(it = e[u].begin(); it != e[u].end(); it++) {
		if(!visited[*it]) {
			dfs(*it);
			low[u] = min(low[u], low[*it]); 
		} 
		else if(visited[*it] == 1)
			low[u] = min(low[u], idx[*it]);
	}
	if(low[u] == idx[u]) {
		int v, n = 0;
		do {
			v = st[sp--];
			visited[v] = 2;
			n++;
		} while(v != u);
		tp[0] = n;
		make_heap(tp, tp+6, greater<int>());
	}
}
int main()
{
	freopen("SCC.txt", "r", stdin);
	int u,v;
	while(scanf("%d %d", &u, &v) > 0)
		e[u].push_back(v);
	for(int i = 0; i < 875715; i++)
		if(!visited[i]) dfs(i);
	for(int i = 5; i > 0; i--)
		printf("%d\n", tp[i]);
}
