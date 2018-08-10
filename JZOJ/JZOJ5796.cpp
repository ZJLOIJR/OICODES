#include <cstdio>
#include <cstring>
#include <cstdlib>
#define bit(n) (1 << ((n) - 1))

typedef long long ll;
const int M = 10;

ll n, k[M + 7], f[1 << (M * 2)], lcm[1 << M], ans;
int m, ok[1 << (M * 2)];

ll getgcd(ll a, ll b) { return b ? getgcd(b, a % b) : a; }
ll getlcm(ll a, ll b) { return a / getgcd(a, b) * b; }

void exgcd(ll a, ll b, ll &x, ll &y)
{
	if (!b) { x = 1, y = 0; return; }
	exgcd(b, a % b, y, x);
	y -= (a / b) * x;
}

ll work(ll a, ll b)
{
	ll x, y;
	exgcd(a, b, x, y);
	while (x >= b) x -= b;
	while (x < 0) x += b;
	return x * a;
}

int main()
{
	freopen("sazetak.in", "r", stdin);
	freopen("sazetak.out", "w", stdout);
	
	scanf("%lld%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%lld", k + i);
	for (int s = 1; s <= (1 << m) - 1; s++)
	{
		lcm[s] = 1;
		for (int i = 1; i <= m; i++)
		{
			if (bit(i) & s) lcm[s] = getlcm(lcm[s], k[i]);
			if (lcm[s] > n) { lcm[s] = 0; break; }
		}
	}
	for (int s = 1; s <= (1 << (2 * m)) - 1; s++) ok[s] = ((s >> m) > 0) && ((s & ((1 << m) - 1)) > 0);
	for (int s1 = 1; s1 <= (1 << m) - 1; s1++)
		if (lcm[s1])
			for (int s2 = 1; s2 <= (1 << m) - 1; s2++)
				if (lcm[s2])
					if (getgcd(lcm[s1], lcm[s2]) == 1)
					{
						ll x1 = work(lcm[s1], lcm[s2]);
						if (n - x1 - 1 >= 0) f[s1 + (s2 << m)] = (n - x1 - 1) / getlcm(lcm[s1], lcm[s2]) + 1;
					}
	for (int i = 1; i <= 2 * m; i++)
		for (int s = (1 << (2 * m)) - 1; s; s--)
			if (ok[s])
				if (s & bit(i))
					if (ok[s - bit(i)])
						f[s - bit(i)] -= f[s];
	for (int s = 1; s <= (1 << (2 * m)) - 1; s++) ans += f[s];
	for (int i = 1; i <= m; i++) if (n % k[i] == 1) ans++;
	printf("%lld\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
