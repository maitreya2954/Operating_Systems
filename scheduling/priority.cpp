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
	cout<<"enter the at, bt and priority : ";
	obj[i].pid=i+1;
	cin>>obj[i].at>>obj[i].bt>>obj[i].priority;
	obj[i].visited=false;
	obj[i].rt=obj[i].bt;
	}
	priority_np(obj,n);
	cout<<"*******************************************PRIORITY NON-PREEMPTIVE********************************"<<endl<<endl;
	printpriority(obj,n);
	
	return 0;
}