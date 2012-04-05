/* Author: Pan Gu
 * Data file: http://spark-public.s3.amazonaws.com/algo1/programming_prob/kargerAdj.txt
 * Data file: http://spark-public.s3.amazonaws.com/algo1/programming_prob/SCC.txt
 * The file contains the adjacency list representation of a simple undirected graph. There are 40 vertices labeled 1 to 40. The first column in the file represents the vertex label, and the particular row (other entries except the first column) tells all the vertices that the vertex is adjacent to. So for example, the 6th row looks liks : "6 29 32 37 27 16". This just means that the vertex with label 6 is adjacent to (i.e., shares an edge with) the vertices with labels 29, 32, 37, 27 and 16.
 *
 * Your task is to code up and run the randomized contraction algorithm for the min cut problem and use it on the above graph to compute the min cut. (HINT: Note that you'll have to figure out an implementation of edge contractions. Initially, you might want to do this naively, creating a new graph from the old every time there's an edge contraction. But you also think about more efficient implementations.) (WARNING: As per the video lectures, please make sure to run the algorithm many times with different random seeds, and remember the smallest cut that you ever find). Write your numeric answer in the space provided. So e.g., if your answer is 5, just type 5 in the space provided.
*/
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
