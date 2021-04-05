#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int carre(int n ){
    return n*n;
}

int main(int argc, char const *argv[])//argument count, argument vector!
{   int n ;
    if (argc>1)
    {   printf("argv[1] = %s\n",argv[1]);
        n = atoi(argv[1]) ;//atoi convertit string en entier

        printf("carre %d = %d\n",n,carre(n));
    }
    else{
        printf("No arguments!");
    }
    return 0;
}
