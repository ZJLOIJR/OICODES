#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;

int a, b, n;

struct matrix
{
	int arr[2][2];
	matrix operator*(matrix a)
	{
		matrix ret;
		memset(ret.arr, 0, sizeof(ret.arr));
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					ret.arr[i][j] = (ret.arr[i][j] + arr[i][k] * a.arr[k][j]) % 7;
		return ret;
	}
} bas, mov, ret;

int main()
{
	while (1)
	{
		scanf("%d%d%d", &a, &b, &n);
		if (!a && !b && !n) break;
		if (n == 1 || n == 2) printf("1\n");
		else
		{
			n -= 2;
			bas.arr[0][0] = bas.arr[0][1] = 1, bas.arr[1][0] = bas.arr[1][1] = 0;
			mov.arr[0][0] = a, mov.arr[0][1] = 1, mov.arr[1][0] = b, mov.arr[1][1] = 0;
			ret.arr[0][0] = ret.arr[1][1] = 1, ret.arr[0][1] = ret.arr[1][0] = 0;
			while (n)
			{
				if (n & 1) ret = ret * mov;
				mov = mov * mov, n >>= 1;
			}
			bas = bas * ret;
			printf("%d\n", bas.arr[0][0]);
		}
	}
	return 0;
}
