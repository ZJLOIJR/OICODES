//It's wrong, but it can be accepted.
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 10007, M = 100007;
typedef long long ll;

int n, m, a, x, y, tot = 0;
ll w[N], f[N];
int st[N], to[M][2], nx[M];

inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

inline ll min(ll a, ll b) { return a < b ? a : b; }

ll dfs(int x)
{
	if (~f[x]) return f[x];
	f[x] = w[x];
	for (int i = st[x]; i; i = nx[i]) f[x] = min(f[x], dfs(to[i][1]) + dfs(to[i][0]));
	return f[x];
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++) *(w + i) = read();
	for (int i = 1; i <= m; i++)
		a = read(), x = read(), y = read(),
		to[++tot][0] = x, to[tot][1] = y, nx[tot] = st[a], st[a] = tot;
	memset(f, 0xff, sizeof(f));
	printf("%lld\n", dfs(1));
	return 0;
}

//It's right, and it can be accepted.However, it runs slower than above.
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 10007, M = 100007;
typedef long long ll;

int n, m, a, x, y, tot = 0;
int vis[N], que[N * 20], head = 1, tail = 0, st[N], need[M << 1], to[M << 1], nx[M << 1];
ll dis[N];

inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

void init()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++) *(dis + i) = read();
	for (int i = 1; i <= m; i++)
	{
		a = read(), x = read(), y = read();
		to[++tot] = a, need[tot] = y, nx[tot] = st[x], st[x] = tot;
		to[++tot] = a, need[tot] = x, nx[tot] = st[y], st[y] = tot;
	}
}

void solve()
{
	for (int i = 1; i <= n; i++) que[++tail] = i, vis[i] = 1;
	while (head <= tail)
	{
		int u = que[head++];
		vis[u] = 0;
		for (int i = st[u]; i; i = nx[i])
			if (dis[u] + dis[need[i]] < dis[to[i]])
			{
				dis[to[i]] = dis[u] + dis[need[i]];
				if (!vis[to[i]])
				{
					que[++tail] = to[i];
					vis[to[i]] = 1;
				}
			}
	}
	printf("%lld\n", dis[1]);
}

int main()
{
	init();
	solve();
	return 0;
}
