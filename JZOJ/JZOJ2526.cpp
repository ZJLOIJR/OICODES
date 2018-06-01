#include <map>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int n, ans = 0;
string a[21], b[21], c[21];
map<string, int> buc;

void dfs(int x, int y)
{
	ans = max(ans, y);
	if (x > n) return;
	if (y + n - x + 1 <= ans) return;
	if (!buc[a[x]] && !buc[b[x]] && !buc[c[x]])
	{
		buc[a[x]]++, buc[b[x]]++, buc[c[x]]++;
		dfs(x + 1, y + 1);
		buc[a[x]]--, buc[b[x]]--, buc[c[x]]--;
	}
	dfs(x + 1, y);
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i];
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}
