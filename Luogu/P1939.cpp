#include <cstdio>
#include <cstring>

const int P = 1000000007;

int t, n;

struct matrix
{
	int arr[4][4];

	void init()
	{
		memset(arr, 0, sizeof(arr));
	}

	int* operator[](int index)
	{
		return arr[index];
	}

	matrix& operator=(matrix a)
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
} bas, mov, ans;

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		if (n <= 3)
		{
			printf("1\n");
			continue;
		}
		n -= 3;
		bas.init();
		mov.init();
		ans.init();
		bas[1][1] = bas[1][2] = bas[1][3] = 1;
		mov[1][1] = mov[3][1] = mov[1][2] = mov[2][3] = 1;
		ans[1][1] = ans[2][2] = ans[3][3] = 1;
		while (n)
		{
			if (n & 1)
				ans = ans * mov;
			mov = mov * mov;
			n >>= 1;
		}
		ans = bas * ans;
		printf("%d\n", (ans[1][1] + P) % P);
	}
	return 0;
}
