// 目标总和.cpp: 定义控制台应用程序的入口点。
//
/*
您将获得一个非负整数列表，a1，a2，...，an和目标，S。现在您有2个符号+和-。对于每个整数，您应该从中选择一个+并-作为其新符号。

找出分配符号的方法，使整数之和等于目标S.
*/
#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

//分析：先全部做成加法，看看是否超过s，如果没有超过返回0，算出超过了K,然后剩下的任务就是往这列数里面
//插入减法，这样就变成了一个硬币找零的问题

int findTargetSumWays(vector<int>& nums, int S)
{
	int len = nums.size();
	vector<int>sum(len, 0);

	if (len <= 1)
	{
		return nums[0] == S;
	}

	for (int i = 0;i<len;i++)
	{
		sum[i] += nums[i];
	}

	if (sum[len-1] <= S)
	{
		return sum[len - 1] == S ? 1 : 0;
	}

	else
	{
		if (sum[len-1]%2 != 0)
		{
			return 0;
		}

		int sum_len = sum[len - 1] / 2;
		vector<vector<int>>dp(len, vector<int>(sum_len+1, 0));
		dp[0][0] = 1;

		for (int j = 1;j<len;j++)
		{
			for (int k = 1;k <= sum[len-1]/2;k++)
			{
				dp[j][k] = dp[j - 1][k - nums[j]] + dp[j - 1][k];
			}
		}

		for (int i = 0;i<dp[len-1].size();i++)
		{
			cout << dp[0][i] << endl;
		}

		return dp.back().back();
	}
}


int maxlen(vector<int>&nums, int S)
{
	int len = nums.size();
	if (len == 0)
	{
		return 0;
	}
	if (len == 1)
	{
		return nums[0] == S;
	}

	vector<vector<int>>ways(len, vector<int>(S+1, 0));
	ways[0][0] = 0;

	for (int i = 0;i<len;i++)
	{
		for (int j = 0;j<=S;j++)
		{
			if (j == 1 && i == 0 && nums[0] == j)
			{
				ways[i][j] = 1;
			}
			else
			{
				ways[i][j] == 0;
			}

			ways[i][j] = ways[i - 1][j - nums[i]] + ways[i - 1][j + nums[i]];
		}
	}

	return ways.back().back();
}


int findTargetSumWays1(vector<int>& nums, int S) {
	const int n = nums.size();
	const int sum = std::accumulate(nums.begin(), nums.end(), 0);
	if (sum < S) return 0;
	const int offset = sum;
	// ways[i][j] means total ways to sum up to (j - offset) using nums[0] ~ nums[i - 1].
	vector<vector<int>> ways(n + 1, vector<int>(sum + offset + 1, 0));
	ways[0][offset] = 1;
	for (int i = 0; i < n; ++i) 
	{
		for (int j = nums[i]; j < 2 * sum + 1 - nums[i]; ++j)
			if (ways[i][j]) 
			{
				ways[i + 1][j + nums[i]] += ways[i][j];
				ways[i + 1][j - nums[i]] += ways[i][j];
			}
	}

	return ways.back()[S + offset];
}

int main()
{
	vector<int>numb;
	for (int i = 0;i<5;i++)
	{
		numb.push_back(1);
	}
	cout << findTargetSumWays(numb, 1);
	system("pause");
    return 0;
}

