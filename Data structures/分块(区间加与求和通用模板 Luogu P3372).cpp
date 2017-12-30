//#pragma GCC optimize(3)
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 100007;
typedef long long ll;

int n, q, op, l, r, len, tot;
ll val, ans, a[N], sum[N / 100], inc[N / 100];
int b[N], lef[N / 100], rig[N / 100];

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

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
	memset(inc, 0, sizeof(inc));
	n = read(), q = read();
	len = sqrt(n);
	tot = n / len;
	if (n % len)
		tot++;
	for (int i = 1; i <= n; i++)
		*(a + i) = read(), *(b + i) = (i - 1) / len + 1, sum[b[i]] += a[i];
	for (int i = 1; i <= tot; i++)
		lef[i] = (i - 1) * len + 1, rig[i] = i * len;
}

void solve()
{
	while (q--)
	{
		op = read(), l = read(), r = read();
		if (op == 1)
		{
			val = read();
			for (int i = l; i <= min(r, rig[b[l]]); i++)
				a[i] += val, sum[b[i]] += val;
			for (int i = r; i >= max(l, lef[b[r]]); i--)
				a[i] += val, sum[b[i]] += val;
			for (int i = b[l] + 1; i <= b[r] - 1; i++)
				inc[i] += val;
		}
		else
		{
			ans = 0;
			for (int i = l; i <= min(r, rig[b[l]]); i++)
				ans += a[i] + inc[b[i]];
			for (int i = r; i >= max(l, lef[b[r]]); i--)
				ans += a[i] + inc[b[i]];
			for (int i = b[l] + 1; i <= b[r] - 1; i++)
				ans += sum[i] + inc[i] * (rig[i] - lef[i] + 1);
			if (b[l] == b[r])
				ans -= a[l] + inc[b[l]] + inc[b[r]] + a[r];
			printf("%lld\n", ans);
		}
	}
}

int main()
{
	init();
	solve();
	return 0;
}
