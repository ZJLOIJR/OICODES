#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20007, M = 200007;

//////////////////////////
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
//////////////////////////

struct Graph
{
	int edge_total;

	int st[N], nx[M], len[M], to[M], id[M];
	
	void init()
	{
		memset(st, 0, sizeof(st));
		memset(nx, 0, sizeof(nx));
		edge_total = 0;
	}
	
	void add_edge(int _from, int _to, int _len, int _id)
	{
		edge_total++;
		to[edge_total] = _to;
		len[edge_total] = _len;
		nx[edge_total] = st[_from];
		id[edge_total] = _id;
		st[_from] = edge_total;
	}
} g1, g2;

int n, m, u, v, w;

int ans[N];

//////////////////////////
void init()
{
	g1.init();

	n = read(), m = read();

	for (int i = 1; i <= m; i++)
	{
		u = read(), v = read(), w = read();
		g1.add_edge(u, v, w, i);
		g1.add_edge(v, u, w, i);
	}
}
//////////////////////////

//////////////////////////
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
//////////////////////////

//////////////////////////
void dfs_build_graph(int u)
{
	vis[u] = 1;
	for (int i = g1.st[u]; i; i = g1.nx[i])
	{
		int v = g1.to[i];
		if (dis[v] + g1.len[i] == dis[u])
		{
			g2.add_edge(u, v, g1.len[i], g1.id[i]);
			g2.add_edge(v, u, g1.len[i], g1.id[i]);

			if (!vis[v])
				dfs_build_graph(v);
		}
	}
}

void build_graph()
{
	memset(vis, 0, sizeof(vis));
	dfs_build_graph(n);
}
//////////////////////////

//////////////////////////

int dfn[N], low[N];
int dfsn = 0;

void dfs_tarjan(int u, int fa)
{
	low[u] = dfn[u] = ++dfsn;

	for (int i = g2.st[u]; i; i = g2.nx[i])
	{
		int v = g2.to[i];
		if (!dfn[v])
		{
			dfs_tarjan(v, g2.id[i]);
			low[u] = low[u] < low[v] ? low[u] : low[v];
			if (low[v] > dfn[u])
				ans[++ans[0]] = g2.id[i];
		}
		else if (dfn[v] < dfn[u] && g2.id[i] != fa)
			low[u] = low[u] < dfn[v] ? low[u] : dfn[v];
	}

}

void find_bridges()
{
	memset(vis, 0, sizeof(vis));
	dfs_tarjan(1, -1);
}

//////////////////////////

void output_answers()
{
	sort(ans + 1, ans + ans[0] + 1);
	printf("%d\n", ans[0]);
	for (int i = 1; i <= ans[0]; i++)
		printf("%d ", ans[i]);
}

int main()
{
	init();
	Dijkstra();
	build_graph();
	find_bridges();
	output_answers();
	return 0;
}
