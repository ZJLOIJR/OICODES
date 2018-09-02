#include <set>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int n;
double x1, y1, x2, y2;
set<double> s;

int main()
{
	while (1)
	{
		scanf("%d", &n);
		if (!n) break;
		for (int i = 1; i <= n; i++) scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
	}
	return 0;
}
