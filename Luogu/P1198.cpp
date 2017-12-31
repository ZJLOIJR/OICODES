#pragma GCC optimize(3)
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 200007;
typedef long long ll;

int q, n, len, tot, cnt = 0, l, r;
int b[N], lef[N / 100], rig[N / 100];
ll d, t = 0, ans = 0, a[N], mx[N / 100];
char c;

inline ll max(ll a, ll b) { return a > b ? a : b; }
inline ll min(ll a, ll b) { return a < b ? a : b; }

inline ll read()
{
	ll x = 0, f = 0;
	char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + ch - '0';
	return f ? -x : x;
}

void init()
{
	q = read(), d = read();
	n = q, len = sqrt(n), tot = n / len;
	if (n % len)
		tot++;
	for (int i = 1; i <= n; i++)
		b[i] = (i - 1) / len + 1;
	for (int i = 1; i <= tot; i++)
		mx[i] = 0, lef[i] = (i - 1) * len + 1, rig[i] = i * len;
}

void solve()
{
	while (q--)
	{
		scanf(" %c", &c);
		if (c == 'Q')
		{
			l = read();
			ans = 0;
			r = cnt, l = cnt - l + 1;
			for (int i = l; i <= min(r, rig[b[l]]); i++)
				ans = max(ans, a[i]);
			for (int i = r; i >= max(l, lef[b[r]]); i--)
				ans = max(ans, a[i]);
			for (int i = b[l] + 1; i <= b[r] - 1; i++)
				ans = max(ans, mx[i]);
			t = ans;
			printf("%lld\n", ans);
		}
		else
		{
			l = read();
			a[++cnt] = (t + l) % d;
			if (a[cnt] > mx[b[cnt]])
				mx[b[cnt]] = a[cnt];
		}
	}
}

int main()
{
	init();
	solve();
	return 0;
}
