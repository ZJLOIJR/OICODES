#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e4 + 3;

int n, l, h, r, a, b;
int ans[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline void swap(int &a, int &b) { int t = a; a = b, b = t; }

int main()
{
	n = read(), l = read(), h = read(), r = read();
	for (int i = 1; i <= n; i++) ans[i] = h;
	for (int i = 1; i <= r; i++)
	{
		a = read(), b = read();
		int tmp = ans[a];
		if (a > b) swap(a, b);
		for (int j = a + 1; j <= b - 1; j++)
			if (ans[j] >= tmp)
			{
				for (int k = a + 1; k <= b - 1; k++) ans[k]--;
				break;
			}
	}
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
