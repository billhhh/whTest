// wangyi_first.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <cmath>
#include <map>

using namespace std;

//
vector<int> handle_linestring(string tempstring)
{
	string lvs_tempstr;
	vector<int>  lvi_targetv;
	int i = 0;
	while (i < tempstring.size())
	{

		if (tempstring[i] != 32)
		{
			lvs_tempstr.push_back(tempstring[i]);
			if (i == tempstring.size() - 1&&lvs_tempstr.size()!=0)
			{
				/*cout << lvs_tempstr << endl;*/
				lvi_targetv.push_back(atoi(lvs_tempstr.c_str()));
				lvs_tempstr.clear();
			}
		}
		else
		{
			if (lvs_tempstr.size() != 0)
			{
				/*cout << lvs_tempstr << endl;*/
				lvi_targetv.push_back(atoi(lvs_tempstr.c_str()));
				lvs_tempstr.clear();
			}
		}
		i++;
	}
	return lvi_targetv;
}
//
vector<int>  handle_teststring(string  tempstring)
{
	vector<int> lvb_numset;
	int i=0;
	while (i < tempstring.size())
	{
		if (tempstring[i] != 32)
		{
			lvb_numset.push_back(atoi(&tempstring[i]));
		}
		++i;
	}
	return lvb_numset;
}

vector<vector<int>> get_pronumset(vector<vector<int>>  temporiginenum)
{
	int lednum_set[10][8]={ 
		{0,1, 1, 1, 0, 1, 1, 1 },
		{0,0, 0, 1, 0, 0, 1, 0 },
		{0,1, 0, 1, 1, 1, 0, 1 },
		{0,1, 0, 1, 1, 0, 1, 1 },
		{0, 0, 1, 1, 1, 0, 1, 0 },
		{0, 1, 1, 0, 1, 0, 1, 1 },
		{0, 1, 1, 0, 1, 1, 1, 1 },
		{0, 1, 0, 1, 0, 0, 1, 0 },
		{0, 1, 1, 1, 1, 1, 1, 1 },
		{0, 1, 1, 1, 1, 0, 1, 1 }
	};

	vector<vector<int>> lvv_targetset;
	for (auto iterator = temporiginenum.begin(); iterator != temporiginenum.end(); ++iterator)
	{
		vector<int> lvv_temptest = *iterator;
		vector<int> lvv_tempmidnum;
		for (int i = 0; i < 10; i++)
		{
			auto j = lvv_temptest.begin();
			for (; j != lvv_temptest.end(); ++j)
			{
				if (!lednum_set[i][*j])
					break;
			}
			if (j == lvv_temptest.end())
			{
				lvv_tempmidnum.push_back(i);
			}
		}

		lvv_targetset.push_back(lvv_tempmidnum);
	}
	return lvv_targetset;
}


int find_start(vector<vector<int>> testnumset, int k,int n,bool &is_continue)
{
	vector<int> lvv_temp;
	int target_pos = 0;
	int iterator=1;
	bool is_find=false;
	for (; iterator < k; ++iterator)
	{
		lvv_temp = testnumset[iterator];
		auto j = lvv_temp.begin();
		vector<int> lvv_satisfy;
		for (; j != lvv_temp.end(); ++j)
		{
			if ((*j)*pow(10, k - iterator-1) < n )
			{
				lvv_satisfy.push_back(*j);
			}

		}

		if (lvv_satisfy.size() == 0)
		{
			is_continue = false;
			return 0;

		}


		else
		{
			if (lvv_satisfy.size() == 1 && lvv_satisfy[0] == 0) continue;
			else
			{
				target_pos = iterator;
				break;
			}
		}


	}
	return target_pos;
}



int get_result(vector<vector<int>> testnumset,int k,int n)
{
	int lvi_result = 1;
	if (testnumset.size() != k)
	{
		cout << "fail" << endl;
		return 0;
	}
	int count1 = 0;
	vector<int> first = testnumset[0];
	auto i_first = first.begin();
	for (; i_first != first.end(); ++i_first)
	{
		if (*i_first == 0)	break;
	}
	if (i_first == first.end())
	{
		return 0;
	}
	bool is_continue = true;
	int lvi_start = find_start(testnumset, k, n,is_continue);
	if (is_continue == false)
	{
		return 0;
	}
	vector<int> lvv_start = testnumset[lvi_start];
	int count_num = 0;
	for (auto i = lvv_start.begin(); i != lvv_start.end(); ++i)
	{
		if ((*i)*pow(10, k - lvi_start - 1) < n)
		{
			++count_num;
		}
	}
	lvi_result *= count_num;
	for (int i = lvi_start + 1; i < k; ++i)
	{
		lvi_result *= testnumset[i].size();
	}

	return lvi_result;
}

int main()
{
	vector<int> lvv_result;
	string s1, s2, s3;
	getline(cin, s1);
	int test_num = handle_linestring(s1).at(0);

	int count1 = 0;
	while (count1 < test_num)
	{
		//cin >> s2;

		getline(cin, s2);

		/*cout << s2<< endl;*/
		int k = handle_linestring(s2).at(0);
		int n = handle_linestring(s2).at(1);
		int count2 = 0;
		vector<vector<int>> test_insset;
		while (count2 < k)
		{
			getline(cin, s3);
			vector<int> lvv_tempins=handle_teststring(s3);
			test_insset.push_back(lvv_tempins);
			++count2;
		}
		vector<vector<int>> lvv_convertproset = get_pronumset(test_insset);
		lvv_result.push_back(get_result(lvv_convertproset, k, n));
		test_insset.clear();
		lvv_convertproset.clear();
		++count1;
	}

	for (auto i = lvv_result.begin(); i != lvv_result.end(); ++i)
	{
		cout << *i << endl;
	}
}
