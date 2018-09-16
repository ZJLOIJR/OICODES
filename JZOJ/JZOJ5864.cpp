#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e6 + 7;

int n; ll x[6];

int tot, st[N], to[N * 6], nx[N * 6];
ll len[N * 6], dis[N];

int head, tail, vis[N], que[N * 20];
inline void add(int u, int v, ll w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

int main()
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", x + i);
	if (n == 2) printf("%lld\n", x[1] * x[2] - x[1] - x[2]);
	else
	{
		for (int i = 0; i < x[1]; i++)
			for (int j = 2; j <= n; j++)
				add(i, (i + x[j]) % x[1], x[j]);
		memset(dis, -1, sizeof(dis));
		memset(vis, 0, sizeof(vis));
		head = 1, que[tail = 1] = 0, vis[0] = 1, dis[0] = 0;
		while (head <= tail)
		{
			int u = que[head++];
			vis[u] = 0;
			for (int i = st[u]; i; i = nx[i])
			{
				int v = to[i];
				if (dis[v] == -1 || dis[u] + len[i] < dis[v])
				{
					dis[v] = dis[u] + len[i];
					if (!vis[v]) que[++tail] = v, vis[v] = 1;
				}
			}
		}
		ll ans = 0;
		for (int i = 1; i < x[1]; i++)
			if (dis[i] != -1 && dis[i] > ans)
				ans = dis[i];
		printf("%lld\n", ans - x[1]);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
