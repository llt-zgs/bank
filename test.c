#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
int main()
{
	printf("%u\n",ftok(".",102));
	printf("%u\n",ftok(".",201));
}


