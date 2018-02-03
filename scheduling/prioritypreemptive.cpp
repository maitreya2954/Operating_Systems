#include <iostream>
#include <iomanip>
#include <unistd.h>
using namespace std;

class process
{
public:
	int at,bt,ct,tat,wt,pid,rt;
	bool completed;
	int priority;
	void calculateTAT()
	{
		tat=ct-at;
	}
	void calculateWT()
	{
		wt=tat-bt;
	}
};

float averageWT(process obj[], int n)
{
	float sum=0.0;
	for (int i = 0; i < n; ++i)
	{
		sum=sum+obj[i].wt;
	}
	return sum/n;
}


void printpriorityrt(process obj[], int n)
{
	cout<<"PID"<<setw(15)<<"AT"<<setw(15)<<"BT"<<setw(15)<<"Priority"<<setw(13)<<"RT"<<setw(15)<<"CT"<<setw(15)<<"TAT"<<setw(15)<<"WT"<<endl;
	for (int i = 0; i < n; ++i)
	{
		cout<<obj[i].pid<<setw(15)<<obj[i].at<<setw(15)<<obj[i].bt<<setw(15)<<obj[i].priority<<setw(15)<<obj[i].rt<<setw(15)<<obj[i].ct<<setw(15)<<obj[i].tat<<setw(15)<<obj[i].wt<<endl<<endl;
	}
	cout<<"Average Waiting Time: "<<averageWT(obj,n)<<endl;
}

bool isDone(process obj[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		if(obj[i].rt!=0)
			return true;
	}
	return false;
}

int findMaxPriority(process obj[], int n, int time)
{
	int maxPriority=-1;
	int maxPriorityPid=-1;
	for (int i = 0; i < n; ++i)
	{
		if (obj[i].at<=time and !obj[i].completed and obj[i].priority>=maxPriority)
		{
			maxPriority=obj[i].priority;
			maxPriorityPid=i;
		}
	}
	return maxPriorityPid;
}

void priority_pre(process obj[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = i+1; j < n; ++j)
		{
			if (obj[i].at>obj[j].at)
			{
				int temp=obj[i].at;
				obj[i].at=obj[j].at;
				obj[j].at=temp;

				temp=obj[i].bt;
				obj[i].bt=obj[j].bt;
				obj[j].bt=temp;	

				temp=obj[i].pid;
				obj[i].pid=obj[j].pid;
				obj[j].pid=temp;

				temp=obj[i].rt;
				obj[i].rt=obj[j].rt;
				obj[j].rt=temp;

				temp=obj[i].priority;
				obj[i].priority=obj[j].priority;
				obj[j].priority=temp;
			}	
			else if (obj[i].at==obj[j].at and obj[i].priority<obj[j].priority)
			{
				int temp=obj[i].at;
				obj[i].at=obj[j].at;
				obj[j].at=temp;

				temp=obj[i].bt;
				obj[i].bt=obj[j].bt;
				obj[j].bt=temp;	

				temp=obj[i].pid;
				obj[i].pid=obj[j].pid;
				obj[j].pid=temp;

				temp=obj[i].rt;
				obj[i].rt=obj[j].rt;
				obj[j].rt=temp;

				temp=obj[i].priority;
				obj[i].priority=obj[j].priority;
				obj[j].priority=temp;
			}
		}
	}

	int time=obj[0].at;
	obj[0].rt--;
	
	time++;
	if (obj[0].rt==0)
	{
		obj[0].ct=time;
		obj[0].completed=true;
		cout<<"----"<<setw(20)<<"Process P0 Completed"<<endl;
	}
	cout<<"P0"<<"("<<obj[0].rt<<")"<<setw(20)<<"Time Elapsed: "<<time<<endl;
	while(isDone(obj,n))
	{
		int maxPriority=findMaxPriority(obj, n, time);
		
		obj[maxPriority].rt--;
		time++;cout<<"P"<<maxPriority<<"("<<obj[maxPriority].rt<<")"<<setw(20)<<"Time Elapsed: "<<time<<endl;
		if (obj[maxPriority].rt==0)
		{
			obj[maxPriority].completed=true;
			cout<<"----"<<setw(20)<<"Process P"<<maxPriority <<" Completed"<<endl;
			obj[maxPriority].ct=time;
		}
		sleep(1);
	}
	for (int i = 0; i < n; ++i)
	{
		obj[i].calculateTAT();
		obj[i].calculateWT();
	}

}


int  main(int argc, char const *argv[])
{
	int n;
	cout<<"Enter number of processes: ";
	cin>>n;
	process obj[n];
	for(int i=0;i<n;i++)
	{
	cout<<"enter the at and bt and priority: ";
	obj[i].pid=i;
	cin>>obj[i].at>>obj[i].bt>>obj[i].priority;
	obj[i].rt=obj[i].bt;
	obj[i].completed=false;
	}
	priority_pre(obj,n);
	printpriorityrt(obj,n);
	return 0;
}