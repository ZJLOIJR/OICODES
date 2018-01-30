#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e3 + 3;

int n, d, p, q;
int x[N], y[N], fixed[N], fa[N];
char ch;

inline int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }
inline double sqr(double x) { return x * x; }
inline double getdis(double x1, double y1, double x2, double y2) { return sqrt(sqr(x1 - x2) + sqr(y1 - y2)); }

int main()
{
	scanf("%d%d", &n, &d);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", x + i, y + i);
		fa[i] = i;
	}
	while (~scanf(" %c%d", &ch, &p))
	{
		if (ch == 'O')
		{
			if (fixed[p]) continue;
			fixed[p] = 1;
			for (int i = 1; i <= n; i++)
				if (i != p && fixed[i] && getdis(x[p], y[p], x[i], y[i]) <= d)
					fa[getfa(p)] = getfa(i);
		}
		else
		{
			scanf("%d", &q);
			if (getfa(p) == getfa(q) && fixed[p] && fixed[q])
				printf("SUCCESS\n");
			else
				printf("FAIL\n");
		}
	}
	return 0;
}