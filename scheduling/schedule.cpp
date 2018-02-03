#include <iostream>
#include <iomanip>
#include "schedule.h"

using namespace std;

void fcfs(int n)
{
	obj[0].ct=obj[0].bt+obj[0].at;
	obj[0].calculateTAT();
	obj[0].calculateWT();
	for (int i = 1; i < n; ++i)
	{
		if (obj[i].at>obj[i-1].ct)
		{
			obj[i].ct=obj[i].at+obj[i].bt;
		}
		else
		{
			obj[i].ct=obj[i-1].ct+obj[i].bt;
			
		}
		obj[i].calculateTAT();
		obj[i].calculateWT();
	}
}

void sort(int m, int n, int ct)
{
	if (obj[m].at<=ct)
	{
		for (int i = m+1; i < n; ++i)
		{
			if (obj[i].bt<obj[m].bt and obj[i].at<=ct)
			{
				int temp=obj[i].at;
				obj[i].at=obj[m].at;
				obj[m].at=temp;

				temp=obj[i].bt;
				obj[i].bt=obj[m].bt;
				obj[m].bt=temp;

				temp=obj[i].pid;
				obj[i].pid=obj[m].pid;
				obj[m].pid=temp;
			}
			if(obj[i].bt==obj[m].bt and obj[i].at<=ct)
			{
				if (obj[i].at<obj[m].at)
				{
					int temp=obj[i].at;
					obj[i].at=obj[m].at;
					obj[m].at=temp;

					temp=obj[i].bt;
					obj[i].bt=obj[m].bt;
					obj[m].bt=temp;

					temp=obj[i].pid;
					obj[i].pid=obj[m].pid;
					obj[m].pid=temp;
				}
			}
		}
		obj[m].ct=obj[m-1].ct+obj[m].bt;
		obj[m].calculateTAT();
		obj[m].calculateWT();
	}
	else
	{
		obj[m].ct=obj[m].at+obj[m].bt;
		obj[m].calculateTAT();
		obj[m].calculateWT();
	}
}

void sjf(int n)
{
	obj[0].ct=obj[0].at+obj[0].bt;
	obj[0].calculateTAT();
	obj[0].calculateWT();
	for (int i = 1; i < n; ++i)
	{
		sort(i,n,obj[i-1].ct);
	}

}

void print()
{
	cout<<"PID"<<setw(19)<<"AT"<<setw(19)<<"BT"<<setw(20)<<"CT"<<setw(20)<<"TAT"<<setw(20)<<"WT"<<endl;
	for (int i = 0; i < 5; ++i)
	{
		cout<<obj[i].pid<<setw(20)<<obj[i].at<<setw(20)<<obj[i].bt<<setw(20)<<obj[i].ct<<setw(20)<<obj[i].tat<<setw(20)<<obj[i].wt<<endl<<endl;
	}
}

void resetValues(int n)
{
	for (int i = 0; i < n; ++i)
	{
		obj[i].ct=obj[i].tat=obj[i].wt=0;
	}
}