#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e3 + 7;

int T, n, h, r, s, t;
int x[N], y[N], z[N], fa[N];

int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }
void link(int x, int y) { fa[getfa(x)] = getfa(y); }

double sqr(double a) { return a * a; }
double getdis(double X1, double Y1, double Z1, double X2, double Y2, double Z2)
{
	return sqrt(sqr(X1 - X2) + sqr(Y1 - Y2) + sqr(Z1 - Z2));
}

int main()
{
	freopen("cheese.in", "r", stdin);
	freopen("cheese.out", "w", stdout);

	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d%d", &n, &h, &r);
		for (int i = 1; i <= n + 2; i++) fa[i] = i;
		s = n + 1, t = n + 2;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d%d%d", x + i, y + i, z + i);
			if (z[i] - r <= 0) link(s, i);
			if (z[i] + r >= h) link(i, t);
			for (int j = 1; j <= i - 1; j++)
				if (2.0 * r >= getdis(x[i], y[i], z[i], x[j], y[j], z[j]))
					link(i, j);
		}
		printf(getfa(s) == getfa(t) ? "Yes\n" : "No\n");
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
