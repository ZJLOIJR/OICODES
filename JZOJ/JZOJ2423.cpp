#include <cstdio>
#include <cstring>

const int P = 1234;

int n;
struct matrix
{
	int arr[2][2];
	matrix operator=(matrix a) { memcpy(arr, a.arr, sizeof(a.arr)); }
	matrix operator*(matrix a)
	{
		matrix ret; memset(ret.arr, 0, sizeof(ret.arr));
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					ret.arr[i][j] = (ret.arr[i][j] + arr[i][k] * a.arr[k][j] % P) % P;
		return ret;
	}
} bas, mov, ret;

int main()
{
	scanf("%d", &n);
	bas.arr[0][0] = bas.arr[0][1] = 1;
	mov.arr[0][0] = mov.arr[0][1] = mov.arr[1][0] = 1;
	ret.arr[0][0] = ret.arr[1][1] = 1;
	while (n)
	{
		if (n & 1) ret = ret * mov;
		mov = mov * mov, n >>= 1;
	}
	bas = bas * ret;
	printf("%d\n", (bas.arr[0][0] - 1 + P) % P);
	return 0;
}
