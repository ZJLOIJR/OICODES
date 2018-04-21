#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e5 + 3;
const ll P = 131071;

int t, tot = 0, check[N], prime[N / 10];
ll n, m, jc[N], phi[N];

ll pow(ll x, ll p)
{
	ll ret = 1;
	while (p)
	{
		if (p & 1) ret = ret * x % P;
		x = x * x % P;
		p >>= 1;
	}
	return ret;
}

int main()
{
	freopen("coprime.in", "r", stdin);
	freopen("coprime.out", "w", stdout);

	jc[1] = 1; for (int i = 2; i <= N - 3; i++) jc[i] = jc[i - 1] * i % P;
	phi[1] = 1;
	for (int i = 2; i <= N - 3; i++)
	{
		phi[i] = phi[i - 1];
		if (!check[i]) phi[i] = phi[i] * (i - 1) % P * pow(i, P - 2) % P, prime[++tot] = i;
		for (int j = 1; j <= tot; j++)
		{
			if (i * prime[j] > N - 3) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	scanf("%d", &t);
	while (t--)
	{
		scanf("%lld%lld", &n, &m);
		printf("%lld\n", phi[m] * jc[n] % P % P);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
