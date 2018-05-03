#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;

ll n, m;

struct matrix
{
	ll arr[2][2];
	matrix operator*(matrix a)
	{
		matrix ret;
		memset(ret.arr, 0, sizeof(ret.arr));
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					ret.arr[i][j] = (ret.arr[i][j] + arr[i][k] * a.arr[k][j] % m) % m;
		return ret;
	}
} base, mov, ret;

int main()
{
	scanf("%lld%lld", &n, &m);
	n -= 2;
	base.arr[0][0] = base.arr[0][1] = 1;
	mov.arr[0][0] = mov.arr[0][1] = mov.arr[1][0] = 1;
	ret.arr[0][0] = ret.arr[1][1] = 1;
	while (n)
	{
		if (n & 1) ret = ret * mov;
		mov = mov * mov;
		n >>= 1;
	}
	base = base * ret;
	printf("%lld\n", base.arr[0][0]);
	return 0;
}
