#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define self(x) (3 * (x) - 2)
#define eat(x) (3 * (x) - 1)
#define enemy(x) (3 * (x))

const int N = 5e5 + 7;

int n, m, d, x, y, ans = 0;
int fa[N * 3];

int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }
void link(int x, int y) { fa[getfa(x)] = getfa(y); }

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n * 3; i++) fa[i] = i;
	while (m--)
	{
		scanf("%d%d%d", &d, &x, &y);
		if (x > n || y > n) { ans++; continue; }
		if (d == 1)
		{
			if (getfa(eat(x)) == getfa(self(y))) { ans++; continue; }
			if (getfa(eat(y)) == getfa(self(x))) { ans++; continue; }
			link(self(x), self(y)), link(eat(x), eat(y)), link(enemy(x), enemy(y));
		}
		else
		{
			if (x == y) { ans++; continue; }
			if (getfa(eat(y)) == getfa(self(x))) { ans++; continue; }
			if (getfa(self(x)) == getfa(self(y))) { ans++; continue; }
			link(self(x), enemy(y)), link(eat(x), self(y)), link(enemy(x), eat(y));
		}
	}
	printf("%d\n", ans);
	return 0;
}
