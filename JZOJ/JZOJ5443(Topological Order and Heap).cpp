#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 100007, M = 100007;

int n, m, u, v, tot = 0;

int to[M], nx[M], st[N], rd[N], vis[N], ans[N];

priority_queue<int, vector<int>, greater<int> > q;

void init()
{
	scanf("%d%d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &u, &v);
		to[i] = v, nx[i] = st[u], st[u] = i;
		rd[v]++;
	}

	for (int i = 1; i <= n; i++)
		if (!rd[i])
		{
			q.push(i);
			vis[i] = 1;
		}
}

void solve()
{
	while (!q.empty())
	{
		int u = q.top();
		q.pop();

		ans[++tot] = u;

		for (int i = st[u]; i; i = nx[i])
		{
			int v = to[i];
			if (!vis[v])
			{
				rd[v]--;
				if (!rd[v])
				{
					q.push(v);
					vis[v] = 1;
				}
			}
		}
	}

	if (tot < n)
		printf("-1\n");
	else
	{
		for (int i = 1; i <= tot; i++)
			printf("%d ", ans[i]);
		putchar('\n');
	}
}

int main()
{
	freopen("dictionary.in", "r", stdin);
	freopen("dictionary.out", "w", stdout);
	init();
	solve();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
