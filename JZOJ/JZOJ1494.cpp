#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int LEN = 1e6 + 3;

struct largeint
{
	int len, arr[LEN];

	void operator=(char* s)
	{
		memset(arr, 0, sizeof(arr));
		len = 0;
		while (*s != '\0')
		{
			arr[++len] = *s - '0';
			s++;
		}
		for (int i = 1; i <= len / 2; i++)
		{
			int t = arr[i]; arr[i] = arr[len - i + 1], arr[len - i + 1] = t;
		}
	}

	largeint operator*(largeint b)
	{
		largeint c;
		c.len = 0; memset(c.arr, 0, sizeof(c.arr));
		for (int i = 1; i <= len; i++)
			for (int j = 1; j <= b.len; j++)
			{
				c.arr[i + j - 1] += arr[i] * b.arr[j];
				c.arr[i + j] += c.arr[i + j - 1] / 10;
				c.arr[i + j - 1] %= 10;
			}
		c.len = c.arr[len + b.len] ? len + b.len : len + b.len - 1;
		return c;
	}

	void print()
	{
		for (int i = len; i >= 1; i--) printf("%d", arr[i]);
	}
} ans, tmp;
int n;
char str[LEN];

int main()
{
	ans.len = 1, ans.arr[1] = 1;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", str);
		tmp = str, ans = ans * tmp;
	}
	ans.print();
	return 0;
}
