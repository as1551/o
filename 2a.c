#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>



void bubblesort(int arr [] , int n );
void printarr(int arr [] , int n );

int main (){

int n ;
printf("enter the no of integers:");
scanf("%d",&n);
int arr [n];
for(int i=0;i<n;i++){
scanf("%d",&arr[i]);
}


pid_t pid = fork();
if(pid<0){
perror("fork failed");
return 1;
}
else if(pid==0){

bubblesort(arr,n);
sleep(10);
printf("child_process : sorting array using bubble sort");


printarr(arr,n);

exit(0);

}
else{
bubblesort(arr,n);
//sleep(20);
//wait(NULL);
printf("parent process : sorting array using bubble sort");
printf("\n");
printarr(arr,n);
printf("parent exited: child becomed orphan ");
}
return 0;
}

void bubblesort(int arr [],int n ){

for(int i=0;i<n;i++){
    
    for(int j=0;j<n-i-1;j++){
    
    if(arr[j]>arr[j+1]){
    int temp=arr[j];
    arr[j]=arr[j+1];
    arr[j+1]=temp;
    
    }
    }
}

}

void printarr(int arr[],int n){
for(int i=0;i<n;i++){
printf("%d \t",arr[i]);
}
printf("\n");
}





