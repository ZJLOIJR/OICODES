#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 1e5 + 7;
const double eps = 1e-6;

int n, h;
vector<int> list[N];
double l, r, mid, ans;

int check()
{
	double sum = 0;
	for (int i = 1; i <= n; i++)
	{
		double mx = -1e9, ret = 0;
		int siz = list[i].size();
		for (int j = 0; j < siz; j++)
		{
			ret += list[i][j] - mid;
			if (ret > mx) mx = ret;
		}
		sum += mx;
	}
	return sum > 0;
}

int main()
{
	scanf("%d%d", &n, &h);
	for (int i = 1; i <= n; i++)
		for (int j = 1, a; j <= h; j++)
			scanf("%d", &a), list[i].push_back(a);
	l = 0.0, r = 1e9;
	while (r - l > eps)
	{
		mid = (l + r) / 2;
		if (check()) l = mid, ans = mid;
		else r = mid;
	}
	printf("%.4lf\n", ans);
	return 0;
}
