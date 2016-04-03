#include<iostream>
#include<string>
using namespace std;

const int len = 10000;
bool f[len][len];

int getLongestPalindromic(string str){
    int max_len=0,start,end;
    const int len=str.size();

    int i=0,j=0;
    for(i=0;i<len;i++){
        for(j=i;j<len;j++){
            f[i][j]=false;
        }
    }
    for(i=len-1;i>=0;i--){  //注意 i与j的取值，如果 i=0开始，那么f(0,4)就会出错，因为，f(2,3)等中间很多子字符串并没有判断是否为回文 
        for(j=i;j<=len-1;j++){
            if(i==j){
                f[i][j]=true;
            }
            else if(j==i+1){
                if(str[i]==str[j]) {
                    f[i][j]=true;
                }
            }else if(j>i+1){
                if(str[i]==str[j]){
                    f[i][j]=f[i+1][j-1];
                }
            }
        }
    }
    for(i=0;i<len;i++){
        for(j=i;j<len;j++){
            if(f[i][j]==true){
                if(j-i+1>max_len){
                    max_len=j-i+1;
                    start=i;end=j;
                }
            }
        }
    }
	//cout<<"max_len="<<max_len<<"  start="<<start<<"  end="<<end<<endl;
	//cout<<str.substr(start,max_len)<<endl;
    return max_len;
}

int main(){
    string str="abcdba";
    int cnt=getLongestPalindromic(str);
	cout<<cnt<<endl;

    return 0;
}