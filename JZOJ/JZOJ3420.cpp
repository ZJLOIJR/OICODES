#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 20, S = 1 << N;
const double INF = 2333333333333.0;

int n, full;
double x[N + 7], y[N + 7], f[S], dis[N + 7][N + 7];

inline int bit(int n) { return 1 << (n - 1); }
inline double sqr(double x) { return x * x; }
inline double getdistance(double x_1, double y_1, double x_2, double y_2)
{ return sqrt(sqr(x_1 - x_2) + sqr(y_1 - y_2)); }
inline double min(double a, double b) { return a < b ? a : b; }

int main()
{
	scanf("%d", &n);
	full = (1 << n) - 1;
	for (int i = 1; i <= n; i++) scanf("%lf%lf", x + i, y + i);
	for (int i = 1; i <= n - 1; i++) for (int j = i + 1; j <= n; j++) dis[i][j] = getdistance(x[i], y[i], x[j], y[j]);
	memset(f, 127, sizeof(f));
	f[0] = 0;
	for (int s = 0; s <= full; s++)
		for (int i = 1; i <= n - 1; i++)
		{
			if (s & bit(i)) continue;
			for (int j = i + 1; j <= n; j++)
			{
				if (s & bit(j)) continue;
				int next_s = s | bit(i) | bit(j);
				f[next_s] = min(f[next_s], f[s] + dis[i][j]);
			}
			break;
		}
	printf("%.2lf\n", f[full]);
	return 0;
}
