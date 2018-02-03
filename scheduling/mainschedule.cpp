#include <iostream>
#include <string>
#include <iomanip>
#include "newschedule.cpp"

using namespace std;


int main()
{
	int n;
	cout<<"Enter number of processes:";
	cin>>n;
	process obj[n];
	for(int i=0;i<n;i++)
	{
	cout<<"enter the at and bt";
	obj[i].pid=i+1;
	cin>>obj[i].at>>obj[i].bt;
	} 
	cout<<"****************************************FIRST COME FIRST SERVE**************************************"<<endl;
	fcfs(obj,n);
    print(obj, n);
    cout<<"******************************************SHORTEST JOB FIRST****************************************"<<endl;
    sjf(obj,n);
    print(obj, n);


	return 0;
}