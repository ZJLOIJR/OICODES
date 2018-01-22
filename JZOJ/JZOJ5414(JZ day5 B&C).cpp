#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const ll P = 998244353;
const int N = 100007;

int n, k, pos;
ll a, ans = 0, cnt[40], f[N];

inline ll min(ll a, ll b) { return a < b ? a : b; }

ll power(ll x, ll y)
{
	ll ret = 1;
	while (y) { if (y & 1) ret = ret * x % P; x = x * x % P, y >>= 1; }
	return ret;
}

ll C(ll n, ll m)
{
	if (m > n) return 0;
	return f[n] * power(f[m], P - 2) % P * power(f[n - m], P - 2) % P;
}

inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

int main()
{
	freopen("card.in", "r", stdin);
	freopen("card.out", "w", stdout);

	n = read(), k = read();
	for (int i = 1; i <= n; i++) 
	{
		a = read(), pos = 1;
		while (a) { if (a & 1) cnt[pos]++; a >>= 1, pos++; }
	}
	f[0] = 1; for (int i = 1; i <= n; i++) f[i] = f[i - 1] * i % P;
	for (int i = 1; i <= 31; i++)
		for (int j = 1; j <= min(k, cnt[i]); j += 2)
			ans = (ans + C(cnt[i], j) * C(n - cnt[i], k - j) % P * (1 << (i - 1)) % P) % P;
	printf("%lld\n", ans);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}