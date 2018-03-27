#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const ll P = 19940417;

ll n, m;

void swap(ll &a, ll &b) { ll t = a; a = b, b = t; }
ll min(ll a, ll b) { return a < b ? a : b; }

ll solve(ll n, ll m)
{
	ll sum = 0;
	for (ll l = 1, r; l <= m; l = r + 1)
	{
		r = min(n / (n / l), m);
		sum = (sum + (n / l) * (l + r) % P * (r - l + 1) % P * 9970209 % P) % P;
	}
	return sum;
}

inline ll sqrsum(ll n)
{ return n * (n + 1) % P * (2 * n + 1) % P * 3323403 % P; }

int main()
{
	scanf("%lld%lld", &n, &m);
	if (n > m) swap(n, m);
	ll ansn = (n * n - solve(n, n) + P) % P,
	   ansm = (m * m - solve(m, m) + P) % P;
	ll anssame = (n * n % P * m % P - m * solve(n, n) % P + P - n * solve(m, n) % P + P) % P;
	for (ll l = 1, r; l <= n; l = r + 1)
	{
		r = min(n, min(n / (n / l), m / (m / l)));
		anssame = (anssame + (n / l) * (m / l) % P * (sqrsum(r) - sqrsum(l - 1) + P) % P) % P;
	}
	printf("%lld\n", (ansn * ansm % P - anssame + P) % P);
	return 0;
}
