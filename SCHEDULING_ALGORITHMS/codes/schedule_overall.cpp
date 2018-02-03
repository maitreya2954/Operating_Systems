
#include <iostream>
#include <string>
#include <iomanip>
#include "newschedule.cpp"

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

    FILE *in;
	char buff[10];
	in = popen("ls *.txt | wc -w","r");
	fgets(buff, sizeof(buff), in);
	string number(buff);
	n=stoi(number);

	cout<<"Number of processes:"<<n<<endl;
	process objF[n];
	for(int i=0;i<n;i++)
	{
		
		in = popen(filename(i+1).c_str(),"r");
		fgets(buff, sizeof(buff), in);
		string number, s(buff);
		istringstream ss(s);
		getline(ss, number, ' ');
		objF[i].pid=i;
		objF[i].bt=stoi(number);
		//cout<<stat(i+1)<<endl;
		in = popen(stat(i+1).c_str(),"r");
		fgets(buff, sizeof(buff), in);
		string num(buff);
		objF[i].at=stoi(num);
	} 
	cout<<"****************************************FCFS FILE**************************************"<<endl;
	fcfs(objF,n);
    print(objF, n);
    cout<<"******************************************SJF FILE****************************************"<<endl;
    sjf(objF,n);
    print(objF, n);
    cout<<"******************************************SRT****************************************"<<endl;
    cout<<"Enter number of processes:";
	cin>>n;
	process obj2[n];
	for(int i=0;i<n;i++)
	{
		cout<<"enter the at and bt";
		obj2[i].pid=i+1;
		cin>>obj2[i].at>>obj2[i].bt;
		obj2[i].rt=obj2[i].bt;
		obj2[i].visited=true;
	}
	srt(obj2,n);
	
	cout<<"******************************************HRRN****************************************"<<endl;
	cout<<"Enter number of processes:";
	cin>>n;
	process objH[n];
	for(int i=0;i<n;i++)
	{
		cout<<"enter the at and bt : ";
		objH[i].pid=i+1;
		cin>>objH[i].at>>objH[i].bt;
	}
	HRRN(objH,n);
	print(objH,n);
	cout<<"******************************************ROUND ROBIN****************************************"<<endl;
	int tq;
	cout<<"Enter number of processes: ";
	cin>>n;
	cout<<"Enter Time Quantum: ";
	cin>>tq;
	process objRR[n];
	for(int i=0;i<n;i++)
	{
		cout<<"enter the at and bt";
		objRR[i].pid=i;
		cin>>objRR[i].at>>objRR[i].bt;
		objRR[i].rt=objRR[i].bt;
		objRR[i].visited=false;
	}
	RoundRobin(objRR,n,tq);
	printrt(objRR,n);
	

	cout<<"*******************************************PRIORITY NON-PREEMPTIVE********************************"<<endl<<endl;
	cout<<"Enter number of processes:";
	cin>>n;
	process objNP[n];
	for(int i=0;i<n;i++)
	{
		cout<<"enter the at, bt and priority(LARGER NUMBER--->MORE PRIORITY) : ";
		objNP[i].pid=i+1;
		cin>>objNP[i].at>>objNP[i].bt>>objNP[i].priority;
		objNP[i].visited=false;
		objNP[i].rt=objNP[i].bt;
	}
	priority_np(objNP,n);
	printpriority(objNP,n);

	cout<<"*******************************************PRIORITY PREEMPTIVE********************************"<<endl<<endl;
	cout<<"Enter number of processes: ";
	cin>>n;
	process objPP[n];
	for(int i=0;i<n;i++)
	{
		cout<<"enter the at and bt and priority(LARGER NUMBER--->MORE PRIORITY) : ";
		objPP[i].pid=i;
		cin>>objPP[i].at>>objPP[i].bt>>objPP[i].priority;
		objPP[i].rt=objPP[i].bt;
		objPP[i].completed=false;
	}
	priority_pre(objPP,n);
	printpriorityrt(objPP,n);


	return 0;
}