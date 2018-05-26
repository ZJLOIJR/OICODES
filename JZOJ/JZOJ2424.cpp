#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const ll P = 1234;
ll x, y, n;
struct matrix
{
	ll arr[2][2];
	matrix operator*(matrix a)
	{
		matrix ret; memset(ret.arr, 0, sizeof(ret.arr));
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					ret.arr[i][j] = (ret.arr[i][j] + arr[i][k] * a.arr[k][j] % P + P) % P;
		return ret;
	}
} bas, mov, ret;

int main()
{
	scanf("%lld%lld%lld", &x, &y, &n); n--;
	bas.arr[0][0] = x, bas.arr[0][1] = 2;
	mov.arr[0][0] = x, mov.arr[0][1] = 1, mov.arr[1][0] = -y;
	ret.arr[0][0] = ret.arr[1][1] = 1;
	while (n)
	{
		if (n & 1) ret = ret * mov;
		mov = mov * mov, n >>= 1;
	}
	bas = bas * ret;
	printf("%lld\n", bas.arr[0][0]);
	return 0;
}
