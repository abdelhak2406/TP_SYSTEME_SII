#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
int main(int argc, char const *argv[])//argument count, argument vector!
{   float n ;
    if (argc>1)
    {   printf("argv[1] = %s\n",argv[1]);
        n = atoi(argv[1]) ;//atoi convertit string en entier

        printf("sqrt %f = %f\n",n,sqrt(n));
    }
    else{
        printf("No arguments!");
    }
    return 0;
}
