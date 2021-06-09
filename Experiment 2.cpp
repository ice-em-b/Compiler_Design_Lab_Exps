#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int main() {
	vector <vector<int>>vec(20,vector<int> (3,0));
  
	string input;
	int i,j,len,a,b;

	cin>>input;
	len=input.length();
	i=0;
	j=1;
	while(i<len)
	{
		if(input[i]=='a'&&input[i+1]!='|'&&input[i+1]!='*')
		{
			vec[j][0]=j+1;
			j++;
		}
		if(input[i]=='b'&&input[i+1]!='|'&&input[i+1]!='*')
		{
			vec[j][1]=j+1;
			j++;
		}
		if(input[i]=='e'&&input[i+1]!='|'&&input[i+1]!='*')
		{
			vec[j][2]=j+1;
			j++;
		}
		if(input[i]=='a'&&input[i+1]=='|'&&input[i+2]=='b')
		{
			vec[j][2]=((j+1)*10)+(j+3);
			j++;
			vec[j][0]=j+1;
			j++;
			vec[j][2]=j+3;
			j++;
			vec[j][1]=j+1;
			j++;
			vec[j][2]=j+1;
			j++;
			i=i+2;
		}
		if(input[i]=='b'&&input[i+1]=='|'&&input[i+2]=='a')
		{
			vec[j][2]=((j+1)*10)+(j+3);
			j++;
			vec[j][1]=j+1;
			j++;
			vec[j][2]=j+3;
			j++;
			vec[j][0]=j+1;
			j++;
			vec[j][2]=j+1;
			j++;
			i=i+2;
		}
		if(input[i]=='a'&&input[i+1]=='*')
		{
			vec[j][2]=((j+1)*10)+(j+3);
			j++;
			vec[j][0]=j+1;
			j++;
			vec[j][2]=((j+1)*10)+(j-1);
			j++;
		}
		if(input[i]=='b'&&input[i+1]=='*')
		{
			vec[j][2]=((j+1)*10)+(j+3);
			j++;
			vec[j][1]=j+1;
			j++;
			vec[j][2]=((j+1)*10)+(j-1);
			j++;
		}
		if(input[i]==')'&&input[i+1]=='*')
		{
			vec[0][2]=((j+1)*10)+1;
			vec[j][2]=((j+1)*10)+1;
			j++;
		}
		i++;
	}
	
	for(int i=0;i<=j;i++)
	{
		if(vec[i][0]!=0)
			
			cout<<"\nvec("<<i<<",a)-->"<<vec[i][0];
		if(vec[i][1]!=0)
		
		
			cout<<"\nvec("<<i<<",b)-->"<<vec[i][1];
		if(vec[i][2]!=0)
		{
			if(vec[i][2]<10)
			
			
				cout<<"\nvec("<<i<<",e)-->"<<vec[i][2];
			else
					
				cout<<"\nvec("<<i<<",e)-->"<<vec[i][2]/10<<" and "<<vec[i][2]%10;
		}
	}
	return 0;
}
