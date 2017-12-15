#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20007, M = 200007;

inline int read()
{
	int sum = 0, f = 1;

	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;

		c = getchar();
	}

	while (c >= '0' && c <= '9')
	{
		sum = (sum << 1) + (sum << 3) + c - '0';

		c = getchar();
	}

	return sum * f;
}

struct Graph
{
	int edge_total;

	int st[N], nx[M], len[M], to[M];
	
	void init()
	{
		memset(st, 0, sizeof(st));
		memset(nx, 0, sizeof(nx));
		edge_total = 0;
	}
	
	void add_edge(int _from, int _to, int _len)
	{
		edge_total++;
		to[edge_total] = _to;
		len[edge_total] = _len;
		nx[edge_total] = st[_from];
		st[_from] = edge_total;
	}
} g1, g2;

int n, m, u, v, w;

void init()
{
	g1.init();

	n = read(), m = read();

	for (int i = 1; i <= m; i++)
	{
		u = read(), v = read(), w = read();
		g1.add_edge(u, v, w);
		g1.add_edge(v, u, w);
	}
}

struct node { int id, val; };

int operator<(node x, node y) { return x.val > y.val; }

int dis[N], vis[N];
priority_queue<node> q;

void Dijkstra()
{
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	
	dis[1] = 0;
	q.push((node){1, 0});

	while (!q.empty())
	{
		node u = q.top();
		q.pop();
		
		if (vis[u.id])
			continue;

		vis[u.id] = 1;
		
		for (int i = g1.st[u.id]; i; i = g1.nx[i])
		{
			int v = g1.to[i];
			if (dis[u.id] + g1.len[i] < dis[v])
			{
				dis[v] = dis[u.id] + g1.len[i]; 
				q.push((node){v, dis[v]});
			}
		}
	}
}

void dfs(int u)
{
	vis[u] = 1;
	for (int i = g1.st[u]; i; i = g1.nx[i])
	{
		int v = g1.to[i];
		if (dis[v] + g1.len[i] == dis[u])
		{
			g2.add_edge(u, v, g1.len[i]);
			g2.add_edge(v, u, g1.len[i]);

			if (!vis[v])
				dfs(v);
		}
	}
}

void build_graph()
{
	memset(vis, 0, sizeof(vis));
	dfs(n);
}

void output_answers()
{

}

int main()
{
	init();
	Dijkstra();
	build_graph();
	output_answers();
	return 0;
}
