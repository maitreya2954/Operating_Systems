#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define max 50
 //void mergesort(int a[],int ,int ,int);
void partition(int a[],int low,int high){
 
  if(low<high){
  int mid=(low+high)/2;
  partition(a,low,mid);
  partition(a,mid+1,high);1
  sleep(1)
 // mergesort(a,low,mid,high);
  }
 }

void mergesort(int a[],int low,int mid,int high){
   int i,j,k,l,r;
   int temp[max];
   i=low;
   l=low;
   
   k=mid+1;
   while(l<=mid && k<=high){
   if(a[l]<a[k]){
   temp[i]=a[l];
   l++;
   }
   else{
   temp[i]=a[k];
   k++;
   }
   i++;
   }
   while(l<=mid){
   temp[i]=a[l];
   l++;
   i++;
   }
   while(k<=high){
   temp[i]=a[k];
   k++;
   i++;
  }
  for(j=0;j<=high;j++)
   a[j]=temp[j];
}

int main(){
  int a[max],n;
  printf("Enter the number of elementts");
  scanf("%d",&n);
  printf("\nEnter elements");
  for(int i=0;i<n;i++)
  scanf("%d",&a[i]);
  
  int pid=vfork();
  if(pid==0){
  partition(a,0,n-1);
  }

 else{
   wait(NULL);
   mergesort(a,0,(n-1)/2,n-1);
   for(int i=0;i<n;i++)
  printf("%d\t",a[i]);
	}
return 0;
}
