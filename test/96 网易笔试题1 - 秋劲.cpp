#include <iostream>
#include <vector>
using namespace std;

void getNum(vector<vector<int>> numList, int deep, int temp, vector<int> &totalNums);

int main(void)
{
	int deng[10][7] = { {1,1,1,0,1,1,1},//0
	{0,0,1,0,0,1,0},
	{1,0,1,1,1,0,1},
	{1,0,1,1,0,1,1},
	{0,1,1,1,0,1,0},
	{1,1,0,1,0,1,1},
	{1,1,0,1,1,1,1},
	{1,0,1,0,0,1,0},//7
	{1,1,1,1,1,1,1},
	{1,1,1,1,0,1,1}//9
	};

	int S_test; //测试点的个数
	int K_LED;    //K个LED数码管
	int compareNum; //给定每个测试点比较的数

	cin>>S_test;

	int *endAnswer = new int[S_test]; //输出结果

	for(int i=0;i<S_test;i++) //测试用例
	{
		cin>>K_LED>>compareNum; //K个LED数码管， 测试的数字
		cin.ignore(); //忽略上一行的换行符！！！

		vector<vector<int>>num_K_LED; //存储每个LED可能的数字

		for (int j=0;j<K_LED;j++) //多少LED数码管 就多少行
		{
			char eachLine[100]; //每行表示对应数码管已点亮的二极管的情况

			cin.getline(eachLine,100);//cin>>eachLine;      //每行

			int servenLight[7] = {0};   //单个LED的7个指示灯哪个亮
			int idx = 0; //数组下标
			for(int k=0;k<strlen(eachLine);k++) //每行转为数字
			{				
				if(eachLine[k]!=' ')
				{
					servenLight[idx] = int(eachLine[k] - '0'); //取数字
					idx++;
					if(idx == 7)
					{
						break;
					}
				}
			}

			vector<int > num_eachLED; //记录单个LED中servenLight[7]中亮的可能是哪些数字？
			for (int deng_i = 0; deng_i <10;deng_i ++) //循环0-9,符合的加入num_eachLED
			{
				bool rs = true;
				int idx = 0;

				while (servenLight[idx] !=0)  //所有亮的指示灯都在 这个数字中
				{
					if(deng[deng_i][ servenLight[idx] -1] != 1)
					{
						rs = false;						
						break;
					}
					idx++;
				}
				if(rs)
				{
					num_eachLED.push_back(deng_i);
				}								
			}

			num_K_LED.push_back(num_eachLED);
		}


		vector<int> totalNums; //记录所有组合出来的数字
		int deep =0; 
		int temp =0;
		getNum(num_K_LED, deep, temp, totalNums);

		int count = 0;
		for (int totalNums_i = 0; totalNums_i < totalNums.size();totalNums_i++)
		{
			if(compareNum >= totalNums[totalNums_i])
			{
				count++;
			}
		}
		endAnswer[i] = count;
	}

	for(int i = 0; i<S_test; i++)
	{
		cout<<endAnswer[i]<<endl;
	}


	//system("pause");
	return 0;
}

void getNum(vector<vector<int>> numList, int deep, int temp, vector<int> &totalNums)
{
	if(deep < numList.size()-1)
	{
		for(int i=0; i < numList[deep].size(); i++)
		{
			int newInt = temp + numList[deep][i] * pow(10,numList.size()- deep -1);
			getNum(numList, deep+1, newInt,totalNums);
		}
	}
	else if(deep == numList.size()-1)
	{
		for(int i=0; i < numList[deep].size(); i++)
		{
			int newInt = temp + numList[deep][i] * pow(10,numList.size()- deep -1);
			totalNums.push_back(newInt);
		}
	}
}
