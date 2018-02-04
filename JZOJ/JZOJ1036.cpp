#include <cstdio>
#include <cstring>

const int N = 17, P = 2009;

int n, len, T;
char c;

struct matrix
{
	int arr[N * 10][N * 10];

	matrix operator=(matrix a)
	{
		memcpy(arr, a.arr, sizeof(a.arr));
	}

	matrix operator*(matrix a)
	{
		matrix tmp;
		memset(tmp.arr, 0, sizeof(tmp.arr));
		for (int i = 1; i <= len; i++)
			for (int j = 1; j <= len; j++)
				for (int k = 1; k <= len; k++)
					tmp.arr[i][j] = (tmp.arr[i][j] + arr[i][k] * a.arr[k][j]) % P;
		return tmp;
	}
} a, b;

int main()
{
	memset(a.arr, 0, sizeof(a.arr));
	memset(b.arr, 0, sizeof(b.arr));
	scanf("%d%d", &n, &T);
	len = n * 10 + 10;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			scanf(" %c", &c);
			for (int k = 1; k < c - '0'; k++)
				a.arr[i * 10 + k][i * 10 + k + 1] = 1;
			if (c - '0')
				a.arr[i * 10 + c - '0'][j * 10 + 1] = 1;
		}
	for (int i = 1; i <= len; i++)
		b.arr[i][i] = 1;
	while (T)
	{
		if (T & 1)
			b = b * a;
		a = a * a;
		T >>= 1;
	}
	printf("%d\n", b.arr[11][n * 10 + 1]);
	return 0;
}