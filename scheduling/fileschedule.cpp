#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "newschedule.cpp"

using namespace std;

string filename(int i)
{
	string wc="wc ";
	return wc+to_string(i)+".txt -w";
}
string stat(int i)
{
	string sta="stat -c \"%Y\" ";
	return sta+to_string(i)+".txt";
}
int main()
{
	int n;
	FILE *in;
	char buff[10];
	in = popen("ls *.txt | wc -w","r");
	fgets(buff, sizeof(buff), in);
	string number(buff);
	n=stoi(number);

	cout<<"Number of processes:"<<n<<endl;
	process obj[n];
	for(int i=0;i<n;i++)
	{
		
		in = popen(filename(i+1).c_str(),"r");
		fgets(buff, sizeof(buff), in);
		string number, s(buff);
		istringstream ss(s);
		getline(ss, number, ' ');
		obj[i].pid=i;
		obj[i].bt=stoi(number);
		//cout<<stat(i+1)<<endl;
		in = popen(stat(i+1).c_str(),"r");
		fgets(buff, sizeof(buff), in);
		string num(buff);
		obj[i].at=stoi(num);
	} 
	cout<<"****************************************FIRST COME FIRST SERVE**************************************"<<endl;
	fcfs(obj,n);
    print(obj, n);
    cout<<"******************************************SHORTEST JOB FIRST****************************************"<<endl;
    sjf(obj,n);
    print(obj, n);

	return 0;
}