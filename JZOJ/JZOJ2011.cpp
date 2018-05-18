#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 5e4 + 3;

int n, q, a, b;
int mi[N][20], mx[N][20], lg[N];

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

void RMQ()
{
	for (int j = 1; (1 << j) <= n; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			mi[i][j] = min(mi[i][j - 1], mi[i + (1 << (j - 1))][j - 1]),
			mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
	lg[1] = 0;
	for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
}

inline int qrymin(int l, int r)
{
	int len = r - l + 1;
	return min(mi[l][lg[len]], mi[r - (1 << lg[len]) + 1][lg[len]]);
}

inline int qrymax(int l, int r)
{
	int len = r - l + 1;
	return max(mx[l][lg[len]], mx[r - (1 << lg[len]) + 1][lg[len]]);
}

int main()
{
	memset(mi, 0x3f, sizeof(mi));
	memset(mx, 0, sizeof(mx));
	n = read(), q = read();
	for (int i = 1; i <= n; i++) mi[i][0] = mx[i][0] = read();
	RMQ();
	while (q--)
	{
		a = read(), b = read();
		printf("%d\n", qrymax(a, b) - qrymin(a, b));
	}
	return 0;
}
