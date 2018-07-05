#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const ll P = 7528443412579576937LL;

ll b, d, n, m;

ll plus(ll a, ll b)
{
	ll x = P - a;
	if (b < x) return a + b;
	else return b - x;
}

ll multi(ll a, ll b)
{
	ll ret = 0;
	while (b)
	{
		if (b & 1) ret = plus(ret, a);
		a = plus(a, a), b >>= 1;
	}
	return ret;
}

struct matrix
{
	ll arr[2][2];
	matrix operator*(matrix a)
	{
		matrix ret; memset(ret.arr, 0, sizeof(ret.arr));
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					ret.arr[i][j] = plus(ret.arr[i][j], multi(arr[i][k], a.arr[k][j]));
		return ret;
	}
};

int main()
{
	freopen("jxamfe.in", "r", stdin);
	freopen("jxamfe.out", "w", stdout);
	
	scanf("%lld%lld%lld", &b, &d, &n);
	if (n == 0) printf("1\n");
	else if (n == 1) printf("%lld\n", b % P);
	else
	{
		m = n--;
		matrix bas, mov, ret;
		bas.arr[0][0] = b, bas.arr[0][1] = 2, bas.arr[1][0] = bas.arr[1][1] = 0;
		mov.arr[0][0] = b, mov.arr[0][1] = 1, mov.arr[1][0] = -(b * b - d) / 4, mov.arr[1][1] = 0;
		ret.arr[0][0] = ret.arr[1][1] = 1, ret.arr[0][1] = ret.arr[1][0] = 0;
		while (n)
		{
			if (n & 1) ret = ret * mov;
			mov = mov * mov, n >>= 1;
		}
		bas = bas * ret;
		if (m & 1 || b * b == d) printf("%lld\n", bas.arr[0][0]);
		else
		{
			if (bas.arr[0][0] < 1) printf("%lld\n", bas.arr[0][0] - 1 + P);
			else printf("%lld\n", bas.arr[0][0] - 1);
		}
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
