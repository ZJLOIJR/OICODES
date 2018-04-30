#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const ll P = 1e6 + 7;

struct matrix
{
	ll arr[2][2];
	matrix operator=(matrix a) { memcpy(arr, a.arr, sizeof(a.arr)); }
	matrix operator*(matrix a)
	{
		matrix ret;
		memset(ret.arr, 0, sizeof(ret.arr));
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					ret.arr[i][j] = (ret.arr[i][j] + arr[i][k] * a.arr[k][j]) % P;
		return ret;
	}
} base, mov, ret;

ll n, m, g;
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
ll getfib(ll x)
{
	if (x == 1 || x == 2) return 1;
	x -= 2;
	base.arr[0][0] = base.arr[0][1] = 1, base.arr[1][0] = base.arr[1][1] = 0;
	mov.arr[0][0] = mov.arr[0][1] = mov.arr[1][0] = 1, mov.arr[1][1] = 0;
	ret.arr[0][0] = ret.arr[1][1] = 1, ret.arr[0][1] = ret.arr[1][0] = 0;
	while (x)
	{
		if (x & 1) ret = ret * mov;
		mov = mov * mov;
		x >>= 1;
	}
	base = base * ret;
	return base.arr[0][0];
}

int main()
{
	scanf("%lld%lld", &n, &m);
	g = gcd(n, m);
	printf("%lld\n", getfib(g));
	return 0;
}
