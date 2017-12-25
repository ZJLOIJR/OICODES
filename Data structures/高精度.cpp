struct largeint
{
	int len;
	int arr[LEN];

	largeint& operator=(int x)
	{
		len = 0;
		while (x)
		{
			arr[++len] = x % 10;
			x /= 10;
		}
		return *this;
	}

	largeint& operator=(largeint a)
	{
		len = a.len;
		memcpy(arr, a.arr, sizeof(a.arr));
		return *this;
	}

	largeint operator+(largeint a)
	{
		int mxlen = len > a.len ? len : a.len;
		largeint tmp;
		memset(tmp.arr, 0, sizeof(tmp.arr));
		tmp.len = 0;
		for (int i = 1; i <= mxlen; i++)
		{
			tmp.arr[i] += arr[i] + a.arr[i];
			tmp.arr[i + 1] = tmp.arr[i] / 10;
			tmp.arr[i] %= 10;
		}
		if (tmp.arr[mxlen + 1] > 0)
			mxlen++;
		tmp.len = mxlen;
		return tmp;
	}
};
