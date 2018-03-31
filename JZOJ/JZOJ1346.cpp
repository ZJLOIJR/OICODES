#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e6 + 3;

int T, n;
int f[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 3) + (x << 1) + (c ^ '0');
	return f ? -x : x;
}
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

int dfs(int x)
{
	if (f[x] != -1) return f[x];
	int maxx = 0, minn = 666, tmp = x;
	while (tmp)
	{
		maxx = max(maxx, tmp % 10);
		if (tmp % 10) minn = min(minn, tmp % 10);
		tmp /= 10;
	}
	if (dfs(x - maxx) && dfs(x - minn)) f[x] = 0;
	else f[x] = 1;
	return f[x];
}

int main()
{
	T = read();
	memset(f, -1, sizeof(f));
	f[0] = 0;
	while (T--)
	{
		n = read();
		if (dfs(n)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
