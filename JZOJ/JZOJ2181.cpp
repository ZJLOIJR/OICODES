#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 207, M = 207;

int n, m, ans1 = 0, ans2 = 0;
int p[N], c[M], q[M];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

int main()
{
	n = read(), m = read();
	while (n || m)
	{
		ans1 = ans2 = 0;
		for (int i = 1; i <= n; i++)
			*(p + i) = read();
		for (int i = 1; i <= m; i++)
			*(c + i) = read(), *(q + i) = read();
		sort(p + 1, p + n + 1);
		for (int i = n; i >= 1; i--)
			for (int j = 1; j <= m; j++)
				if (c[j] && p[i] <= q[j])
				{
					ans1++, ans2 += p[i];
					c[j]--;
					break;
				}
		printf("%d %d\n", ans1, ans2);
		n = read(), m = read();
	}
	return 0;
}
