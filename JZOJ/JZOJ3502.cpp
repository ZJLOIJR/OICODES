#include <cstdio>
#include <cstring>

const int N = 107, LEN = 1007;

struct largeint
{
	int len;
	int arr[LEN];
	
	largeint& operator=(int x)
	{
		len = 0;
		while (x)
		{
			arr[++len] = x % 10;
			x /= 10;
		}
		return *this;
	}

	largeint& operator=(largeint a)
	{
		len = a.len;
		memcpy(arr, a.arr, sizeof(a.arr));
		return *this;
	}

	largeint& operator+(largeint a)
	{
		int mxlen = len > a.len ? len : a.len;
		int c[LEN];
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= mxlen; i++)
		{
			c[i] += arr[i] + a.arr[i];
			c[i + 1] = c[i] / 10;
			c[i] %= 10;
		}
		if (c[mxlen + 1] > 0)
			mxlen++;
		len = mxlen;
		memcpy(arr, c, sizeof(c));
		return *this;
	}
};

int n;

largeint f[N];

int main()
{
	scanf("%d", &n);

	f[1] = 3, f[2] = 7;
	for (int i = 3; i <= n; i++)
	{
		//f[i] = 2 * f[i - 1] + f[i - 2]
		largeint tmp = f[i - 1];
		tmp = tmp + f[i - 1];
		tmp = tmp + f[i - 2];
		f[i] = tmp;
	}

	for (int i = f[n].len; i >= 1; i--)
		printf("%d", f[n].arr[i]);
	putchar('\n');
	return 0;
}
