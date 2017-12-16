#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 200007;
typedef long long ll;

inline ll read()
{
	ll x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = (x << 1) + (x << 3) + c - '0';
		c = getchar();
	}
	return x * f;
}

ll a[N], b[N];
int n, m;
ll k;

void init()
{
	n = read(), m = read(), k = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= m; i++)
		b[i] = read();

	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
}

int check(long long x)
{
	int top = m;
	ll cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		while (top > 0 && a[i] * b[top] >= x) top--;
		cnt += top;
	}
	return cnt < k;
}

void solve()
{
	ll l = a[1] * b[1], r = a[n] * b[m], ans;

	while (l <= r)
	{
		ll mid = (l + r) >> 1;
		if (check(mid))
			l = mid + 1, ans = mid;
		else
			r = mid - 1;
	}

	printf("%lld\n", ans);
}

int main()
{
	init();
	solve();
	return 0;
}
