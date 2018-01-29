#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 200007;
const ll P = 10007;

int n, u, v, tot = 0;
int st[N], to[N << 1], nx[N << 1];
ll w[N], ansmax = 0, anssum = 0;

inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

inline ll max(ll a, ll b) { return a > b ? a : b; }

int main()
{
	n = read();
	for (int i = 1; i <= n - 1; i++)
	{
		u = read(), v = read();
		to[++tot] = v, nx[tot] = st[u], st[u] = tot;
		to[++tot] = u, nx[tot] = st[v], st[v] = tot;
	}
	for (int i = 1; i <= n; i++) *(w + i) = read();
	for (int i = 1; i <= n; i++)
	{
		ll mx = 0, sum = 0;
		for (int j = st[i]; j; j = nx[j])
		{
			int v = to[j];
			ansmax = max(ansmax, w[v] * mx), anssum = (anssum + w[v] * sum) % P;
			mx = max(mx, w[v]), sum = (sum + w[v]) % P;
		}
	}
	printf("%lld %lld\n", ansmax, anssum * 2 % P);
	return 0;
}
