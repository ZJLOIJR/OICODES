#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 107;
const ll P = 1000000007LL;

int T, n, k, c;
ll sum, siz, f[N][2];
int tot = 1, st[N], to[N << 1], nx[N << 1], dep[N];
inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
inline int myabs(int x) { return x > 0 ? x : -x; }

ll pow(ll a, ll b)
{
	a %= P;
	ll ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % P;
		a = a * a % P, b >>= 1;
	}
	return ret;
}

void dfs(int u, int from)
{
	sum++;
	for (int i = st[u]; i; i = nx[i])
	{
		if (!dep[to[i]]) dep[to[i]] = dep[u] + 1, dfs(to[i], i);
		else if ((i ^ 1) != from) siz = myabs(dep[to[i]] - dep[u]) + 1;
	}
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		tot = 1;
		memset(st, 0, sizeof(st));
		memset(to, 0, sizeof(to));
		memset(nx, 0, sizeof(nx));
		memset(f, 0, sizeof(f));
		memset(dep, 0, sizeof(dep));
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; i++) scanf("%d", &c), add(i, c + 1), add(c + 1, i);
		f[1][1] = 1;
		for (int i = 2; i <= n; i++)
		{
			f[i][0] = (f[i - 1][1] * (k - 1) % P + f[i - 1][0] * (k - 2) % P) % P;
			f[i][1] = f[i - 1][0];
		}
		ll ans = 1;
		for (int i = 1; i <= n; i++)
			if (!dep[i])
			{
				dep[i] = 1, sum = 0, dfs(i, 0);
				ans = ans * f[siz][0] % P * k % P * pow(k - 1, sum - siz) % P;
			}
		printf("%lld\n", ans);
	}
	return 0;
}
