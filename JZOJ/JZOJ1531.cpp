#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e4 + 3;

struct largeint
{
	int arr[N], len;
	largeint operator=(int x)
	{
		len = 0; memset(arr, 0, sizeof(arr));
		while (x)
		{
			arr[++len] = x % 10;
			x /= 10;
		}
		return *this;
	}
	largeint operator+(largeint b)
	{
		int mxlen = len > b.len ? len : b.len;
		largeint c; c.len = 0; memset(c.arr, 0, sizeof(c.arr));
		for (int i = 1; i <= mxlen; i++)
		{
			c.arr[i] += arr[i] + b.arr[i];
			c.arr[i + 1] = c.arr[i] / 10;
			c.arr[i] %= 10;
		}
		if (c.arr[mxlen + 1]) mxlen++;
		c.len = mxlen;
		return c;
	}
	largeint operator=(largeint b)
	{
		len = b.len; memcpy(arr, b.arr, sizeof(b.arr));
	}
	void print()
	{
		for (int i = len; i >= 1; i--)
			printf("%d", arr[i]);
	}
} x, y, z;
int n;

int main()
{
	x = 1, y = 1, z = 2;
	scanf("%d", &n);
	if (n == 1) printf("1\n");
	else if (n == 2) printf("1\n");
	else
	{
		for (int i = 3; i <= n; i++)
			z = x + y, x = y, y = z;
		z.print();
	}
	return 0;
}
