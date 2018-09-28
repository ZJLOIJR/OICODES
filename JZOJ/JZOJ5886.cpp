#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 2e3 + 7;
const ll P1 = 1e9 + 7, P2 = 19260817;

int T;
int n, m;
char map[N][N];
ll b1[N], b2[N];

int main()
{
	freopen("rect.in", "r", stdin);
	freopen("rect.out", "w", stdout);

	scanf("%d", &T);
	while (T--)
	{
		memset(b1, 0, sizeof(b1));
		memset(b2, 0, sizeof(b2));
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf(" %c", &map[i][j]);
		int flag = 1;
		for (int i = 1; i <= n; i++)
		{
			if (!flag) break;
			ll sum1 = 0, sum2 = 0;
			for (int j = 1; j <= m; j++) sum1 = (sum1 * 2 % P1 + (map[i][j] == '#')) % P1;
			for (int j = 1; j <= m; j++) sum2 = (sum2 * 2 % P2 + (map[i][j] == '#')) % P2;
			for (int j = 1; j <= m; j++)
				if (map[i][j] == '#')
				{
					if (b1[j] && (sum1 != b1[j] || sum2 != b2[j])) { flag = 0; break; }
					if (!b1[j]) b1[j] = sum1, b2[j] = sum2;
				}
		}
		printf(flag ? "Yes\n" : "No\n");
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
