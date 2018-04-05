#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const double PI = 3.1415926535;

int n;
double x_1, y_1, x_2, y_2, ans, rad[10], x[10], y[10];
int used[10], order[10];

inline double min(double a, double b) { return a < b ? a : b; }
inline double max(double a, double b) { return a > b ? a : b; }
inline double sqr(double a) { return a * a; }
inline double getdis(double x_1, double y_1, double x_2, double y_2) { return sqrt(sqr(x_1 - x_2) + sqr(y_1 - y_2)); }

void upd()
{
	double sum = 0.0;
	for (int i = 1; i <= n; i++)
	{
		rad[order[i]] = min(min(abs(x[order[i]] - x_1), abs(x[order[i]] - x_2)), min(abs(y[order[i]] - y_1), abs(y[order[i]] - y_2)));
		for (int j = 1; j < i; j++)
			rad[order[i]] = min(rad[order[i]], getdis(x[order[i]], y[order[i]], x[order[j]], y[order[j]]) - rad[order[j]]);
		if (rad[order[i]] < 0) rad[order[i]] = 0.0;
		sum += sqr(rad[order[i]]) * PI;
	}
	ans = max(ans, sum);
}

void dfs(int now)
{
	if (now > n) { upd(); return; }
	for (int i = 1; i <= n; i++)
		if (!used[i])
		{
			used[i] = 1, order[now] = i;
			dfs(now + 1);
			used[i] = 0;
		}
}

int main()
{
	scanf("%d%lf%lf%lf%lf", &n, &x_1, &y_1, &x_2, &y_2);
	for (int i = 1; i <= n; i++) scanf("%lf%lf", x + i, y + i);
	ans = 0.0;
	memset(used, 0, sizeof(used));
	memset(order, 0, sizeof(order));
	dfs(1);
	printf("%.0lf", round(abs((x_1 - x_2) * (y_1 - y_2)) - ans));
	return 0;
}
