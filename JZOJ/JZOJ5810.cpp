#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const ll P = 1e6 + 3;

ll n, m, f1, f2, cnt, p;

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
	freopen("random.in", "r", stdin);
	freopen("random.out", "w", stdout);

	scanf("%lld%lld", &n, &m);
	f2 = pow(pow(2, n), m - 1) % P;
	if (m - 1 >= P)
	{
		p = 2;
		while ((m - 1) / p > 0) cnt += (m - 1) / p, p = p * 2;
		f2 = f2 * pow(pow(2, cnt), P - 2) % P;
		printf("%lld %lld\n", f2, f2);
	}
	else
	{
		f1 = 1;
		for (int i = 1; i <= m - 1; i++) f1 = f1 * ((pow(2, n) - i + P) % P) % P;
		p = 2;
		while ((m - 1) / p > 0) cnt += (m - 1) / p, p = p * 2;
		f1 = f1 * pow(pow(2, cnt), P - 2) % P;
		f2 = f2 * pow(pow(2, cnt), P - 2) % P;
		printf("%lld %lld\n", (f2 - f1 + P) % P, f2);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
