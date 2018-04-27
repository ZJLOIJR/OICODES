#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e3 + 3;
const ll P = 1e4 + 7;

ll a, b, k, n, m, f[N][N];

ll pow(ll a, ll b)
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
	scanf("%lld%lld%lld%lld%lld", &a, &b, &k, &n, &m);
	f[0][0] = 1;
	for (int i = 1; i <= k; i++)
	{
		f[i][0] = 1;
		for (int j = 1; j <= i; j++)
			f[i][j] = (f[i - 1][j] + f[i - 1][j - 1]) % P;
	}
	printf("%lld\n", f[k][n] * pow(a, n) % P * pow(b, m) % P);
	return 0;
}
