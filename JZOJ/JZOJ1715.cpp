#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 20;
const double eps = 1e-8;

inline double sqr(double a) { return a * a; }
inline double swap(double &a, double &b) { double t = a; a = b, b = t; }

int n;
double a[N][N], b[N], c[N][N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n + 1; i++)
		for (int j = 1; j <= n; j++)
			scanf("%lf", &a[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			c[i][j] = 2 * (a[i][j] - a[i + 1][j]);
			b[i] += sqr(a[i][j]) - sqr(a[i + 1][j]);
		}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
			if (fabs(c[j][i]) > eps)
			{
				for (int k = 1; k <= n; k++) swap(c[i][k], c[j][k]);
				swap(b[i], b[j]);
			}
		for (int j = 1; j <= n; j++)
		{
			if (i == j) continue;
			double res = c[j][i] / c[i][i];
			for (int k = 1; k <= n; k++) c[j][k] -= c[i][k] * res;
			b[j] -= b[i] * res;
		}
	}
	for (int i = 1; i <= n; i++) printf("%.3lf ", b[i] / c[i][i]);
	return 0;
}
