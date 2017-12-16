#include <cstdio>
#include <cstring>

const int N = 10007, M = 500007;

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
template<class T>
struct heap
{
	int len;
	T a[N << 2];
	void init() { len = 0; }
	void swap(int x, int y)
	{
		T t = a[x];
		a[x] = a[y];
		a[y] = t;
	}
	void push(T x)
	{
		a[++len] = x;
		int now = len;
		while (now > 1 && a[now] < a[now >> 1])
		{
			swap(now, now >> 1);
			now >>= 1;
		}
	}
	T pop()
	{
		T ret = a[1];
		a[1] = a[len--];
		int now = 1, nx;
		while (now < len)
		{
			nx = now << 1;
			if (nx > len)
				break;
			if ((nx | 1) > len)
			{
				if (a[nx] < a[now])
					swap(now, nx);
				else
					break;
			}
			else
			{
				nx = a[nx] < a[nx | 1] ? nx : (nx | 1);
				if (a[nx] < a[now])
					swap(now, nx);
				else
					break;
			}
			now = nx;
		}
		return ret;
	}

	int empty() { return len == 0; }
};
int st[N], nx[M], to[M], len[M];
int tot = 0;
void add(int u, int v, int w)
{
	to[++tot] = v;
	nx[tot] = st[u];
	len[tot] = w;
	st[u] = tot;
}
int n, m, s, u, v, w;
void init()
{
	n = read(), m = read(), s = read();
	for (int i = 1; i <= m; i++)
	{
		u = read(), v = read(), w = read();
		add(u, v, w);
	}
}
struct node { int id, val; };
int operator<(node x, node y) { return x.val < y.val; }
int dis[N], vis[N];
heap<node> q;
void Dijkstra()
{
	for (int i = 1; i <= n; i++)
		dis[i] = 2147483647;
	memset(vis, 0, sizeof(vis));
	q.init();
	dis[s] = 0;
	q.push((node){s, 0});

	while (!q.empty())
	{
		node u = q.pop();
		if (vis[u.id])
			continue;
		vis[u.id] = 1;
		for (int i = st[u.id]; i; i = nx[i])
		{
			int v = to[i];
			if (dis[u.id] + len[i] < dis[v])
			{
				dis[v] = dis[u.id] + len[i]; 
				q.push((node){v, dis[v]});
			}
		}
	}
}
void solve()
{
	for (int i = 1; i <= n; i++)
		printf("%d ", dis[i]);
}
int main()
{
	init();
	Dijkstra();
	solve();
	return 0;
}
