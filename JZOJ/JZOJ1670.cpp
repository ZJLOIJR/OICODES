#include <map>
#include <string>
#include <iostream>
using namespace std;

const int N = 53;

int T, n, mxval;
string mxname, name[N], give[N];
map<string, int> score;

int main()
{
	cin >> T;
	while (T--)
	{
		cin >> n;
		score = map<string, int>();
		for (int i = 1; i <= n; i++) cin >> name[i];
		for (int i = 1; i <= n; i++)
		{
			cin >> give[i];
			if (name[i] != give[i]) score[give[i]]++;
		}
		int flag = 1, cnt = 0, mxval = 0;
		for (int i = 1; i <= n; i++)
			if (score[name[i]] > mxval)
				mxval = score[name[i]];
		for (int i = 1; i <= n; i++)
			if (score[name[i]] == mxval)
			{
				mxname = name[i], cnt++;
				if (cnt > 1)
				{ cout << endl; flag = 0; break; }
			}
		if (flag) cout << mxname << endl;
	}
	return 0;
}
