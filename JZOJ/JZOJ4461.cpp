#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 7;

int n, m, ans = 0;
int h[N];

int maxval[N][20], lg[N];

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

void RMQ()
{
	lg[0] = -1;
	for (int i = 1; i <= n; i++)
		maxval[i][0] = h[i], lg[i] = lg[i >> 1] + 1;
	for (int j = 1; (1 << j) <= n; j++)
		for (int i = 1; i + (1 << (j - 1)) <= n; i++)
			maxval[i][j] = max(maxval[i][j - 1], maxval[i + (1 << (j - 1))][j - 1]);
}

inline int qry_max(int l, int r)
{
	int le = r - l + 1;
	return max(maxval[l][lg[le]], maxval[r - (1 << lg[le]) + 1][lg[le]]);
}

int main()
{
	freopen("light.in", "r", stdin);
	freopen("light.out", "w", stdout);
			
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", h + i);
	RMQ();
	for (int i = 1; i <= n; i++)
	{
		int ans = 0;
		if (i != 1)
			for (int j = 0; j <= 500; j++)
			{
				int right = i - j * j - 1, left = max(i - (j + 1) * (j + 1), 1);
				ans = max(ans, qry_max(left, right) - h[i] + j + 1);
				if (left == 1) break;
			}
		if (i != n)
			for (int j = 0; j <= 500; j++)
			{
				int left = i + j * j + 1, right = min(i + (j + 1) * (j + 1), n);
				ans = max(ans, qry_max(left, right) - h[i] + j + 1);
				if (right == n) break;
			}
		printf("%d\n", ans);
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}