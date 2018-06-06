#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef long long ll;
const int N = 13;

int n, m, h, t, p, q, ans;
ll st = 0LL, en, que1[1000010], que2[1000010], pow[N];
int a[N * N], b[N * N];
map<ll, int> dis1, dis2;

inline int min(int a, int b) { return a < b ? a : b; }
ll swaparr(ll S, int x, int y)
{
	x = n - x, y = n - y;
	ll numx = (S / pow[x]) % n, numy = (S / pow[y]) % n;
	return S - numx * pow[x] - numy * pow[y] + numx * pow[y] + numy * pow[x];
}

int main()
{
	scanf("%d%d", &n, &m); ans = 666666666;
	pow[0] = 1; for (int i = 1; i <= n; i++) pow[i] = pow[i - 1] * n;
	for (int i = 0; i < n; i++) en = en * n + i;
	for (int i = 1, x; i <= n; i++) scanf("%d", &x), st = st * n + (x - 1);
	for (int i = 1; i <= m; i++) scanf("%d%d", a + i, b + i);
	h = p = 1, t = q = 0;
	que1[++t] = st, que2[++q] = en;
	while (h <= t && p <= q)
	{
		ll S = que1[h++], T = que2[p++];
		if (dis1[T] < ans)
			for (int i = 1; i <= m; i++)
			{
				ll nx = swaparr(S, a[i], b[i]);
				if (!dis1[nx] && nx != st) dis1[nx] = dis1[S] + 1, que1[++t] = nx;
				if (dis2[nx] || nx == en) ans = min(ans, dis1[nx] + dis2[nx]);
			}
		if (dis2[T] < ans)
			for (int i = 1; i <= m; i++)
			{
				ll nx = swaparr(T, a[i], b[i]);
				if (!dis2[nx] && nx != en) dis2[nx] = dis2[T] + 1, que2[++q] = nx;
				if (dis1[nx] || nx == st) ans = min(ans, dis1[nx] + dis2[nx]);
			}
	}
	printf("%d\n", ans);
	return 0;
}
