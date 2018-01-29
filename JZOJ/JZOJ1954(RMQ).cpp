#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 507;

int n, q, X1, Y1, X2, Y2;
int f[N][N][10][10], lg[N];

inline void read(int& num)
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	num = f ? -x : x;
}
inline int max(int a, int b) { return a > b ? a : b; }

int main()
{
	read(n), read(q);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			read(f[i][j][0][0]);
	lg[1] = 0;
	for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
	for (int k = 0; (1 << k) <= n; k++)
		for (int l = 0; (1 << l) <= n; l++)
			if (k || l)
				for (int i = 1; i + (1 << k) - 1 <= n; i++)
					for (int j = 1; j + (1 << l) - 1 <= n; j++)
					{
						if (!k) f[i][j][k][l] = max(f[i][j][k][l - 1], f[i][j + (1 << (l - 1))][k][l - 1]);
						else if (!l) f[i][j][k][l] = max(f[i][j][k - 1][l], f[i + (1 << (k - 1))][j][k - 1][l]);
						else f[i][j][k][l] = max(f[i][j][k][l - 1], f[i][j + (1 << (l - 1))][k][l - 1]);
					}
	while (q--)
	{
		read(X1), read(Y1), read(X2), read(Y2);
		int lex = X2 - X1, ley = Y2 - Y1;
		printf("%d\n", max(
					max(f[X1][Y1][lg[lex]][lg[ley]], f[X2 - (1 << lg[lex]) + 1][Y2 - (1 << lg[ley]) + 1][lg[lex]][lg[ley]]),
					max(f[X1][Y2 - (1 << lg[ley]) + 1][lg[lex]][lg[ley]], f[X2 - (1 << lg[lex]) + 1][Y1][lg[lex]][lg[ley]])));
	}
	return 0;
}