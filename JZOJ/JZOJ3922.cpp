#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e6 + 3, INF = 0x3f3f3f3f;

int q, x, ltop = 0, rtop = 0, lsta[N], rsta[N], sum[N], mx[N];
char opt;

inline int max(int a, int b) { return a > b ? a : b; }

int main()
{
	scanf("%d", &q);
	for (int i = 0; i <= q; i++) mx[i] = -INF;
	while (q--)
	{
		scanf(" %c ", &opt);
		if (opt == 'I')
		{
			scanf("%d", &x);
			lsta[++ltop] = x, sum[ltop] = sum[ltop - 1] + x, mx[ltop] = max(mx[ltop - 1], sum[ltop]);
		}
		else if (opt == 'D') mx[ltop] = -INF, lsta[ltop] = sum[ltop] = 0, ltop--;
		else if (opt == 'L')
		{
			if (ltop) rsta[++rtop] = lsta[ltop--];
		}
		else if (opt == 'R')
		{
			if (rtop)
			{
				x = rsta[rtop--];
				lsta[++ltop] = x, sum[ltop] = sum[ltop - 1] + x, mx[ltop] = max(mx[ltop - 1], sum[ltop]);
			}
		}
		else if (opt == 'Q')
		{
			scanf("%d", &x);
			printf("%d\n", mx[x]);
		}
	}
	return 0;
}
