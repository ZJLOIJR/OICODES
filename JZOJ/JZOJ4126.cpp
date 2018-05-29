#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
const int LEN = 4e6 + 7;
const int P = 9191891;
 
int tmp[P];
int s, t, n, m, cnt = 0, len = 0, goal, arrlen = 0;
char st[LEN], str[LEN];
ull sum[LEN], pow[LEN], arr[LEN];
ll ans = 0;
 
inline ull hashval(int l, int r) { return sum[r] - sum[l - 1] * pow[r - l + 1]; }
 
int main()
{
    pow[0] = 1; for (int i = 1; i <= LEN - 7; i++) pow[i] = pow[i - 1] * 29;
    scanf("%d%d%d%d", &s, &t, &n, &m); getchar();
    for (char ch = getchar(); ch != EOF; ch = getchar()) if (ch >= 'a' && ch <= 'z') st[++cnt] = ch;
    if (n < m)
    {
        for (int i = s * n + 1; i <= cnt; i++) str[++len] = st[i];
        for (int i = 1; i <= s * n; i++) str[++len] = st[i];
        n ^= m ^= n ^= m;
        s ^= t ^= s ^= t;
    }
    else for (int i = 1; i <= cnt; i++) str[++len] = st[i];
    for (int i = 1; i <= len; i++) sum[i] = sum[i - 1] * 29 + str[i] - 'a';
    for (int i = s * n + 1; i <= len; i += m) arr[++arrlen] = hashval(i, i + m - 1);
    sort(arr + 1, arr + arrlen + 1);
    goal = n + m >> 1;
    for (int i = 1; i <= s * n; i += n)
    {
        ull goalval = hashval(i + goal, i + n - 1);
        for (int j = i; j <= i + m; j++)
            if (hashval(j, j + (n - goal) - 1) == goalval)
            {
                int l = j - 1, r = j + (n - goal);
                ull ret = hashval(r, i + goal - 1) * pow[l - i + 1] + hashval(i, l);
                int ls = lower_bound(arr + 1, arr + arrlen + 1, ret) - arr, rs = upper_bound(arr + 1, arr + arrlen + 1, ret) - arr - 1;
                if (arr[ls] != ret) continue;
                if (tmp[ret % P] != i) ans += rs - ls + 1;
                tmp[ret % P] = i;
            }
    }
    printf("%lld\n", ans);
    return 0;
}
