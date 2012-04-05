/* Author: Pan Gu
 * The file contains the edges of a directed graph. Vertices are labeled as positive integers from 1 to 875714. Every row indicates an edge, the vertex label in first column is the tail and the vertex label in second column is the head (recall the graph is directed, and the edges are directed from the first column vertex to the second column vertex). So for example, the 11th row looks liks : "2 47646". This just means that the vertex with label 2 has an outgoing edge to the vertex with label 47646
 *
 * Your task is to code up the algorithm from the video lectures for computing strongly connected components (SCCs), and to run this algorithm on the given graph.
 *
 * Output Format: You should output the sizes of the 5 largest SCCs in the given graph, in decreasing order of sizes, separated by commas (avoid any spaces). So if your algorithm computes the sizes of the five largest SCCs to be 500, 400, 300, 200 and 100, then your answer should be "500,400,300,200,100". If your algorithm finds less than 5 SCCs, then write 0 for the remaining terms. Thus, if your algorithm computes only 3 SCCs whose sizes are 400, 300, and 100, then your answer should be "400,300,100,0,0".
*/
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
