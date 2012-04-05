#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define TURNS 2000
using namespace std;
int ne, nv, p[50];
pair<int, int> e[1000];
int root(int u) { return p[u] == u ? u : (p[u] = root(p[u])); }
int mincut()
{
	int m = ne - 1, ret = 0;
	for(int i = 1; i < nv; i++) p[i] = i;
	for(int i = 1; i < nv - 2; i++) {
		int now, u, v;
		while(true) {
			now = rand() % (m + 1);
			u = e[now].first, v = e[now].second;
			if(root(u) != root(v)) break;
			swap(e[now], e[m--]);
		}
		p[root(u)] = root(v);
	}
	for(int i = 0; i < ne; i++)
		if(root(e[i].first) != root(e[i].second)) ret++;
	return ret;
}
int main()
{
	srand(time(NULL));
	string line;
	freopen("kargerAdj.txt", "r", stdin);
	for(ne = 0, nv = 1; getline(cin, line); nv++) {
		int u, v;
		stringstream ss(line);
		ss >> u;
		while(ss >> v) if(u < v) e[ne++] = make_pair(u, v);
	}
	int ans = ne;
	for(int i = 0; i < TURNS; i++)
		ans = min(ans, mincut());
	cout << ans << endl;
	return 0;
}
