#include <iostream>
#include <string>
#include <iomanip>
#include "newschedule.cpp"

using namespace std;


int main()
{
	int n;
	cout<<"FCFS and SJF"<<endl<<"Enter number of processes:";
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
    cout<<"*****************************************************************************************************"<<endl<<endl;
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
	cout<<"****************************************FILE FIRST COME FIRST SERVE**************************************"<<endl;
	fcfs(obj,n);
    print(obj, n);
    cout<<"******************************************FILE SHORTEST JOB FIRST****************************************"<<endl;
    sjf(obj,n);
    print(obj, n);

    cout<<"*****************************************************************************************************"<<endl<<endl;
	for(int i=0;i<n;i++)
	{
	obj[i].pid=i+1;
	obj[i].rt=obj[i].bt;
	obj[i].visited=true;
	}
	srt(obj,n);
	cout<<"*****************************************************************************************************"<<endl<<endl;
	for(int i=0;i<n;i++)
	{
	cout<<"priority : ";
	obj[i].pid=i+1;
	cin>>obj[i].priority;
	obj[i].visited=false;
	obj[i].rt=obj[i].bt;
	}
	priority_np(obj,n);
	cout<<"*******************************************PRIORITY NON-PREEMPTIVE********************************"<<endl<<endl;
	printpriority(obj,n);

	for(int i=0;i<n;i++)
	{
	obj[i].pid=i;
	obj[i].rt=obj[i].bt;
	obj[i].completed=false;
	}
	cout<<"*******************************************PRIORITY PREEMPTIVE********************************"<<endl<<endl;
	priority_pre(obj,n);
	printpriorityrt(obj,n);

	for(int i=0;i<n;i++)
	{
	obj[i].pid=i+1;
	cin>>obj[i].at>>obj[i].bt;
	}
	cout<<"*******************************************HIGHEST RESPONSE RATIO NEXT********************************"<<endl<<endl;
	HRRN(obj,n);
	print(obj,n);

	int tq;
	cout<<"Enter Time Quantum: ";
	cin>>tq;
	for(int i=0;i<n;i++)
	{
	obj[i].pid=i;
	obj[i].rt=obj[i].bt;
	obj[i].visited=false;
	}
	cout<<"*******************************************ROUND ROBIN********************************"<<endl<<endl;
	RoundRobin(obj,n,tq);
	printrt(obj,n);

	return 0;
}