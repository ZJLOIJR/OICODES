#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const ll P = 998244353;

int n, m, rt, tot, d, num[207], cnt[207];
ll ans, ret, f[207][30 * 207];

ll quickpow(ll a, ll b)
{
	ll ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % P;
		a = a * a % P, b >>= 1;
	}
	return ret;
}

int main()
{
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);

	scanf("%d%d", &n, &m);
	rt = sqrt(n);
	for (int i = 2; i <= rt; i++)
		if (n % i == 0)
		{
			++tot;
			while (n % i == 0) cnt[tot]++, n /= i;
		}
	if (n > 1) cnt[++tot] = 1;
	d = 1;
	for (int i = 1; i <= tot; i++) d *= (cnt[i] + 1);
	ans = quickpow(d, 2 * m);
	ret = 1;
	for (int i = 1; i <= tot; i++)
	{
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for (int j = 1; j <= 2 * m; j++)
			for (int k = 0; k <= cnt[i] * m; k++)
				for (int l = 0; l <= cnt[i] && l <= k; l++)
					f[j][k] = (f[j][k] + f[j - 1][k - l]) % P;
		ret = ret * f[2 * m][cnt[i] * m] % P;
	}
	printf("%lld\n", ((ans - ret + P) % P * quickpow(2, P - 2) % P + ret) % P);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
