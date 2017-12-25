#include <cstdio>
#include <cstring>

const int P = 10000;

int n, t, l, r;

struct matrix
{
	int arr[4][4];

	matrix operator=(matrix a)
	{
		memcpy(arr, a.arr, sizeof(a.arr));
	}

	matrix operator*(matrix a)
	{
		matrix tmp;
		memset(tmp.arr, 0, sizeof(tmp.arr));
		for (int i = 1; i <= 3; i++)
			for (int j = 1; j <= 3; j++)
				for (int k = 1; k <= 3; k++)
					tmp.arr[i][j] = (tmp.arr[i][j] + arr[i][k] * a.arr[k][j]) % P;
		return tmp;
	}
} bas, mov, ret; 

int solve(int ind)
{
	if (ind == 0)
		return 0;
	if (ind == 1)
		return 1;
	if (ind == 2)
		return 2;
	ind -= 2;
	memset(bas.arr, 0, sizeof(bas.arr));
	memset(mov.arr, 0, sizeof(mov.arr));
	bas.arr[1][1] = 2, bas.arr[1][2] = 1, bas.arr[1][3] = 1;
	mov.arr[1][1] = 1, mov.arr[2][1] = 1, mov.arr[3][1] = 1, mov.arr[2][2] = 1, mov.arr[2][3] = 1, mov.arr[2][3] = 1;
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			ret.arr[i][j] = 1;
	while (ind)
	{
		if (ind & 1)
			ret = ret * mov;
		mov = mov * mov;
		ind >>= 1;
	}
	ret = bas * ret;
	return ret.arr[1][1];
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &l, &r);
		printf("%d\n", solve(r) - solve(l - 1));
	}
	return 0;
}
