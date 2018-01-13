#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 200007;
const long long P1 = 217636919, P2 = 122420729;

int n, m, ans = 0;
char str[N];
map<int, int> h1, h2;
long long hash1[N], hash2[N], len1[N], len2[N];

int main()
{
	freopen("article.in", "r", stdin);
	freopen("article.out", "w", stdout);

	scanf("%d%d%s", &n, &m, str + 1);
	len1[0] = 1, len2[0] = 1;
	for (int i = 1; i <= n; i++)
		len1[i] = len1[i - 1] * 29 % P1,
		len2[i] = len2[i - 1] * 29 % P2;
	for (int i = 1; i <= n; i++)
		hash1[i] = (hash1[i - 1] * 29 + str[i] - 'a') % P1,
		hash2[i] = (hash2[i - 1] * 29 + str[i] - 'a') % P2;
	for (int i = m; i <= n; i++)
	{
		int hashval1 = (hash1[i] - hash1[i - m] * len1[m] % P1 + P1) % P1, hashval2 = (hash2[i] - hash2[i - m] * len2[m] % P2 + P2) % P2;
		if (!h1[hashval1] || !h2[hashval2])
			ans++;
		h1[hashval1] = 1;
		h2[hashval2] = 1;
	}
	printf("%d\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
