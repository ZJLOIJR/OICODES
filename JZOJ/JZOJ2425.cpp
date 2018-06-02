#include <cstdio>
#include <cstring>

const int P = 1000;

int T, n;

struct matrix
{
	int arr[2][2];
	matrix operator*(matrix a)
	{
		matrix ret; memset(ret.arr, 0, sizeof(ret.arr));
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					ret.arr[i][j] = (ret.arr[i][j] + arr[i][k] * a.arr[k][j] % P + P) % P;
		return ret;
	}
};

int solve(int n)
{
	n--;
	matrix bas, mov, ret;
	bas.arr[0][0] = 6, bas.arr[0][1] = 2, bas.arr[1][0] = bas.arr[1][1] = 0;
	mov.arr[0][0] = 6, mov.arr[1][0] = -4, mov.arr[0][1] = 1, mov.arr[1][1] = 0;
	ret.arr[0][0] = ret.arr[1][1] = 1, ret.arr[1][0] = ret.arr[0][1] = 0;
	while (n)
	{
		if (n & 1) ret = ret * mov;
		mov = mov * mov, n >>= 1;
	}
	bas = bas * ret;
	return (bas.arr[0][0] - 1 + P) % P;
}

int main()
{
	scanf("%d", &T);
	for (int i = 1; i <= T; i++)
	{
		scanf("%d", &n);
		printf("Case \#%d: %03d\n", i, solve(n));
	}
	return 0;
}
