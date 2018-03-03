#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

int T, k, a, b, c, d, e, f, x, y;

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &k);
		if (k == 0)
		{
			scanf("%d:%d:%d %d:%d:%d", &a, &b, &c, &d, &e, &f);
			x = a * 60 * 60 + b * 60 + c;
			y = d * 60 * 60 + e * 60 + f;
			printf("%d\n", (y - x + 86400) % 86400);
		}
		else
		{
			scanf("%d:%d:%d %d", &a, &b, &c, &d);
			x = a * 60 * 60 + b * 60 + c;
			x = (x + d) % 86400;
			a = x / 3600, b = x % 3600 / 60, c = x % 60;
			printf("%02d:%02d:%02d\n", a, b, c);
		}
	}
	return 0;
}