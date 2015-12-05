/* 
* 
* funtion: stringToNumģ����
* 
* Date:2015-6-6
* 
*    Author: Bill Wang
*/

#pragma once

#include <iostream>
#include <sstream>	//ʹ��stringstream��Ҫ�������ͷ�ļ�
using namespace std;

//ģ�庯������string���ͱ���ת��Ϊ���õ���ֵ���ͣ��˷��������ձ������ԣ�
template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;    
}
