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

	int S_test; //���Ե�ĸ���
	int K_LED;    //K��LED�����
	int compareNum; //����ÿ�����Ե�Ƚϵ���

	cin>>S_test;

	int *endAnswer = new int[S_test]; //������

	for(int i=0;i<S_test;i++) //��������
	{
		cin>>K_LED>>compareNum; //K��LED����ܣ� ���Ե�����
		cin.ignore(); //������һ�еĻ��з�������

		vector<vector<int>>num_K_LED; //�洢ÿ��LED���ܵ�����

		for (int j=0;j<K_LED;j++) //����LED����� �Ͷ�����
		{
			char eachLine[100]; //ÿ�б�ʾ��Ӧ������ѵ����Ķ����ܵ����

			cin.getline(eachLine,100);//cin>>eachLine;      //ÿ��

			int servenLight[7] = {0};   //����LED��7��ָʾ���ĸ���
			int idx = 0; //�����±�
			for(int k=0;k<strlen(eachLine);k++) //ÿ��תΪ����
			{				
				if(eachLine[k]!=' ')
				{
					servenLight[idx] = int(eachLine[k] - '0'); //ȡ����
					idx++;
					if(idx == 7)
					{
						break;
					}
				}
			}

			vector<int > num_eachLED; //��¼����LED��servenLight[7]�����Ŀ�������Щ���֣�
			for (int deng_i = 0; deng_i <10;deng_i ++) //ѭ��0-9,���ϵļ���num_eachLED
			{
				bool rs = true;
				int idx = 0;

				while (servenLight[idx] !=0)  //��������ָʾ�ƶ��� ���������
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


		vector<int> totalNums; //��¼������ϳ���������
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
