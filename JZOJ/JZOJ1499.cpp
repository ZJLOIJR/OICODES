#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

const int N = 1e5 + 3, PARALLEL = 0, INTERSECT = 1;

int n, m, tot = 0;
int fa[N << 1], dis[N << 1];
map<string, int> id;
string a, b, c;

inline int rel(string s)
{ if (s[0] == 'p') return 0; else return 1; }

inline int getfa(int x)
{
	if (fa[x] == x) return x;
	int father = getfa(fa[x]);
	dis[x] = (dis[x] + dis[fa[x]]) % 2;
	return fa[x] = father;
}

inline int get_relation(int u, int v)
{
	fa[u] = getfa(u), fa[v] = getfa(v);
	if (fa[u] != fa[v]) return -1;
	return (dis[u] + dis[v]) % 2;
}

void init()
{
	cin >> n >> m;
	for (int i = 1; i <= 2 * n; i++) fa[i] = i;
	for (int i = 1; i <= n; i++)
	{
		cin >> a >> b >> c;
		if (!id[a]) id[a] = ++tot;
		if (!id[b]) id[b] = ++tot;
		int tmp = get_relation(id[a], id[b]);
		if (tmp != -1 && rel(c) != tmp)
		{
			cout << "Waterloo" << endl;
			exit(0);
		}
		fa[id[a]] = id[b], dis[id[a]] = rel(c);
	}
}

void solve()
{
	while (m--)
	{
		cin >> a >> b;
		int tmp = get_relation(id[a], id[b]);
		if (tmp == PARALLEL)
			cout << "parallel" << endl;
		else if (tmp == INTERSECT)
			cout << "intersect" << endl;
		else
			cout << "unknown" << endl;
	}
}

int main()
{
	freopen("IN", "r", stdin);
	init();
	solve();
	return 0;
}
