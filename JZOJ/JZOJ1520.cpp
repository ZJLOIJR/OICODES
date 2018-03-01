#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

const int N = 1e4 + 2e3 + 3;

int n, now;
map<string, int> st, en;
string a[N], b[N];

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i] >> b[i];
		st[a[i]] = i, en[b[i]] = i;
	}
	for (int i = 1; i <= n; i++)
		if (st[a[i]] && !en[a[i]])
		{ now = i; break; }
	while (now)
	{
		cout << a[now] << ' ' << b[now] << endl;
		now = st[b[now]];
	}
	return 0;
}
