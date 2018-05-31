#include <cmath>
#include <cstdio>

int x, y;
double tx, ty;

int main()
{
	scanf("%d%d", &x, &y);
	if (x == 0 && y == 0) printf("125.00 125.00\n");
	else if (x == 0 && y == 250) printf("125.00 0.00\n");
	else if (x == 250 && y == 0) printf("0.00 125.00\n");
	else if (x == 0)
	{
		if (31250.0 / y <= 250) printf("%.2lf 0.00\n", 31250.0 / y);
		else printf("%.2lf %.2lf\n", 31250.0 / (250.0 - y), 250.0 - 31250.0 / (250.0 - y));
	}
	else if (y == 0)
	{
		if (31250.0 / x <= 250) printf("0.00 %.2lf\n", 31250.0 / x);
		else printf("%.2lf %.2lf\n", 250.0 - 31250.0 / (250.0 - x), 31250.0 / (250.0 - x));
	}
	else if (x + y == 250)
	{
		if (31250.0 / y <= 250) printf("%.2lf 0.00\n", 250.0 - 31250.0 / y);
		else if (31250.0 / x <= 250) printf("0.00 %.2lf\n", 250.0 - 31250.0 / x);
	}
	return 0;
}
