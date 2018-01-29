#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e3 + 7;

int n, ans = 0;

int f[N], sum[N];

int main()
{
	cin >> n;

	for (int i = 1; i <= n / 2; i++)
		for (int j = i * 2; j <= n; j += i)
			sum[j] += i;
	
	for (int i = 1; i <= n; i++)
		for (int j = n; j >= i; j--)
			f[j] = max(f[j], f[j - i] + sum[i]),
			ans = max(ans, f[j]);

	cout << ans << endl;
	return 0;
}
