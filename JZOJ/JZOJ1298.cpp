#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e3 + 5e2 + 3;

int n, s, dis, mo;
int a[N], f[N][N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int min(int a, int b) { return a < b ? a : b; }

int main()
{
	freopen("graze2.in", "r", stdin);
	freopen("graze2.out", "w", stdout);

	memset(f, 0x3f, sizeof(f));
	n = read(), s = read();
	dis = (s - 1) / (n - 1), mo = (s - 1) % (n - 1);
	for (int i = 1; i <= n; i++) a[i] = read();
	sort(a + 1, a + n + 1);
	f[1][0] = a[1] - 1;
	for (int i = 2; i <= n; i++)
	{
		f[i][0] = f[i - 1][0] + abs(a[i] - (i * dis - dis + 1));
		for (int j = 1; j <= min(i - 1, mo); j++)
			f[i][j] = min(f[i - 1][j], f[i - 1][j - 1]) + abs(a[i] - (i * dis - dis + j + 1));
	}
	printf("%d\n", f[n][mo]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
