#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 13;
const ll P = 10000007;

int n, m, h, t, p, q;
ll st = 0LL, en, que1[1000100], que2[1000100], pow[N];
int a[N * N], b[N * N];
ll used1[P], used2[P];
int ans, dis1[P], dis2[P];

inline int min(int a, int b) { return a < b ? a : b; }
ll swaparr(ll S, int x, int y)
{
	x = n - x, y = n - y;
	ll numx = (S / pow[x]) % n, numy = (S / pow[y]) % n;
	return S - numx * pow[x] - numy * pow[y] + numx * pow[y] + numy * pow[x];
}

ll find(ll arr[], ll x)
{
	ll i = x % P;
	while (arr[i] && arr[i] != x) i = (i == P) ? 0 : i + 1;
	return i;
}

int main()
{
	scanf("%d%d", &n, &m); ans = n * n;
	pow[0] = 1; for (int i = 1; i <= n; i++) pow[i] = pow[i - 1] * n;
	for (int i = 0; i < n; i++) en = en * n + i;
	for (int i = 1, x; i <= n; i++) scanf("%d", &x), st = st * n + (x - 1);
	for (int i = 1; i <= m; i++) scanf("%d%d", a + i, b + i);
	h = p = 1, t = q = 0;
	que1[++t] = st, que2[++q] = en;
	while (h <= t && p <= q)
	{
		ll S = que1[h++], T = que2[p++];
		ll tmpS = find(used1, S), tmpT = find(used2, T);
		if (dis1[tmpS] < ans)
			for (int i = 1; i <= m; i++)
			{
				ll nx = swaparr(S, a[i], b[i]);
				ll tmpnx = find(used1, nx), tpnx = find(used2, nx);
				used1[tmpnx] = used2[tpnx] = nx;
				if (!dis1[tmpnx] && nx != st) dis1[tmpnx] = dis1[tmpS] + 1, que1[++t] = nx;
				if (dis2[tpnx] || nx == en) ans = min(ans, dis1[tmpnx] + dis2[tpnx]);
			}
		if (dis2[tmpT] < ans)
			for (int i = 1; i <= m; i++)
			{
				ll nx = swaparr(T, a[i], b[i]);
				ll tmpnx = find(used2, nx), tpnx = find(used1, nx);
				used2[tmpnx] = used1[tpnx] = nx;
				if (!dis2[tmpnx] && nx != en) dis2[tmpnx] = dis2[tmpT] + 1, que2[++q] = nx;
				if (dis1[tpnx] || nx == st) ans = min(ans, dis1[tpnx] + dis2[tmpnx]);
			}
	}
	printf("%d\n", ans);
	return 0;
}
