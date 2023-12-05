#include <algorithm>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <vector>

using namespace std;

vector<int> medianFilter(vector<int>& signals, int window)
{
	vector<int> res(signals.size());
	for (size_t i{}; i < signals.size(); i++)
	{
		vector<int> v(window);
		v[v.size() / 2] = signals[i];
		int left_dif = i - window / 2;
		size_t right_dif = i + window / 2;
		for (size_t j{}; j < v.size() / 2; j++)
		{
			if (left_dif < 0)
			{
				v[j] = signals[0];
				left_dif++;
			}
			else
			{
				v[j] = signals[i + (j - v.size() / 2)];
			}
		}
		for (size_t j{v.size() - 1}; j > v.size() / 2; j--)
		{
			if (right_dif > signals.size() - 1)
			{
				v[j] = signals[signals.size() - 1];
				right_dif--;
			}
			else
			{
				v[j] = signals[i + (j - v.size() / 2)];
			}
		}
		sort(v.begin(), v.end());
		res[i] = v[v.size() / 2];
	}
	return res;
}

TEST(Test_Median_Filter, Subtest1)
{
	vector<int> signals{2, 80, 6, 3};
	int window = 3;
	vector<int> result = medianFilter(signals, window);
	ASSERT_THAT(result, ::testing::ElementsAre(2, 6, 6, 3));
}

TEST(Test_Median_Filter, Subtest2)
{
	vector<int> signals{2, 3, 4, 2, 5, 6, 7};
	int window = 5;
	vector<int> result = medianFilter(signals, window);
	ASSERT_THAT(result, ::testing::ElementsAre(2, 2, 3, 4, 5, 6, 7));
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	::testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
