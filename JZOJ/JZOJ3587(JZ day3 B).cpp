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
