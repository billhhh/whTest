#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main()
{
	int n;
	cin>>n;
	while(n--)
	{
		vector<char> vec;
		string ch;
		vec.push_back(' ');
		cin>>ch;
		for(int i=0;i<ch.length();i++)
		{
			vec.push_back(ch[i]);
			if( vec.back()-1 == *(vec.end()-2) || vec.back()-2 == *(vec.end()-2))
			{
				vec.pop_back();
				vec.pop_back();
			}
		}
		if(vec.size()==1)
			cout<<"0"<<endl;
		else
		{
			vector<bool>flags;
			flags.push_back(false);
			flags.push_back(false);
			for(int i =3;i<vec.size();i++)
			{
				flags.push_back(false);
				int j;
				for(j = i-2;j>0;j--){
					if(flags.at(j)==false){
						if((vec.at(i)-1) == vec.at(j) || vec.at(i)-2 == vec.at(j))
						{
							flags.at(i-1)=true;
							flags.at(j-1)=true;
						}
					}
				}
			}
			int k = 0;
			for(int i = 0 ;i<flags.size();i++){
				if(flags.at(i)==false)
					k++;
			}
			cout<<k<<endl;
		}

	}
	return 0;
}
