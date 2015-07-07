#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;
#define ull int

ull n, buf[500000];
long long ans;

void merge(ull left, ull right)
{
	ull middle = (left + right) / 2;

	vector <ull> tmp(buf + left, buf + right + 1);

	for (int i = left, j = 0, k = middle - left + 1; i <= right; i++)
	{
		if (j > middle - left) buf[i] = tmp[k++];
		else if (k > right - left) buf[i] = tmp[j++];
		else
		{
			if (tmp[j] < tmp[k])
			{
				buf[i] = tmp[j++];
			}
			else
			{
				buf[i] = tmp[k++];
				ans++;
				ans += (middle - left + 1) - j - 1;
			}
		}
	}
}

void MergeSort(ull left, ull right)
{
	if (left >= right) return;

	MergeSort(left, (left + right) / 2);
	MergeSort((left + right) / 2 + 1, right);
	merge(left, right);
}

int main()
{
	do
	{
		scanf("%d", &n);

		if (n)
		{
			ans = 0;
			for (int i = 0; i < n; i++) scanf("%d", buf + i);

			MergeSort(0, n - 1);

			printf("%lld\n", ans);
		}

	} while (n);

}