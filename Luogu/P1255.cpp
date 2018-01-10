#include <cstdio>
#include <cstring>

const int LEN = 10007;

struct largeint
{
	int len;
	int arr[LEN];

	largeint operator=(int x)
	{ len = 0; while (x) arr[++len] = x % 10, x /= 10; }
	largeint operator=(largeint a)
	{ memcpy(arr, a.arr, sizeof(a.arr)), len = a.len; }
	void init() { len = 0, memset(arr, 0, sizeof(arr)); }

	largeint operator+(largeint a)
	{
		largeint b; b.init();
		int mxlen = len > a.len ? len : a.len;
		for (int i = 1; i <= mxlen; i++)
		{
			b.arr[i] += arr[i] + a.arr[i];
			b.arr[i + 1] = b.arr[i] / 10;
			b.arr[i] %= 10;
		}
		if (b.arr[mxlen + 1] > 0) mxlen++;
		b.len = mxlen;
		return b;
	}

	void print()
	{
		for (int i = len; i >= 1; i--) putchar(arr[i] + '0');
		putchar('\n');
	}
} a, b, c;

int n;

int main()
{
	scanf("%d", &n);
	if (n == 0) { printf("0\n"); return 0; }
	if (n == 1) { printf("1\n"); return 0; }
	if (n == 2) { printf("2\n"); return 0; }
	a = 1, b = 2, c = 0;
	for (int i = 3; i <= n; i++)
		c = a + b, a = b, b = c;
	c.print();
	return 0;
}
