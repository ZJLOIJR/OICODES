#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int max(int a, int b) { return a > b ? a : b; }
const int N = 15;

int n, full;
int a[N + 3], b[N + 3], c[N + 3];
int f[1 << N][N + 3][3]; //0: a * b 1: a * c 2: b * c

void swap(int &a, int &b) { int t = a; a = b, b = t; }
int bit(int x) { return 1 << (x - 1); }

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", a + i, b + i, c + i);
	full = (1 << n) - 1;
	for (int s = 0; s <= full; s++)
		for (int i = 1; i <= n; i++)
		{
			if ((!(bit(i) & s) && s)) continue;
			for (int j = 0; j < 3; j++)
			{
				int a1 = a[i], b1 = b[i], c1 = c[i];
				if (j == 1) swap(b1, c1);
				if (j == 2) swap(a1, c1);
				for (int k = 1; k <= n; k++)
				{
					if (bit(k) & s) continue;
					for (int l = 0; l < 3; l++)
					{
						int a2 = a[k], b2 = b[k], c2 = c[k];
						if (l == 1) swap(b2, c2);
						if (l == 2) swap(a2, c2);
						if ((a2 <= a1 && b2 <= b1) || (a2 <= b1 && b2 <= a1) || !s)
							f[s | bit(k)][k][l] = max(f[s | bit(k)][k][l], f[s][i][j] + c2);
					}
				}
			}
		}
	int ans = 0;
	for (int i = 1; i <= full; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 0; k < 3; k++)
				ans = max(ans, f[i][j][k]);
	printf("%d\n", ans);
	return 0;
}
