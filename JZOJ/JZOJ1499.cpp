#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

const int N = 1e5 + 3;

int n, m, tot = 0;
int fa[N], dis[N];
map<string, int> tid;
string a, b, c;

void init()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fa[i] = i, dis[i] = -1;
	for (int i = 1; i <= n; i++)
	{
		cin >> a >> b >> c;
		if (!id[a]) id[a] = ++tot;
		if (!id[b]) id[b] = ++tot;
		
	}
}

int main()
{
	init();
	solve();
	return 0;
}
