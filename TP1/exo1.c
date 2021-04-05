#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include<math.h>
int main(int argc, char const *argv[])
{
    pid_t child1;
    child1 = fork();
    if (child1 == -1)
    {
        perror("fork!");
    }else if (child1==0)
    {
        printf("je suis le processus fils, mon PID est: %d .Et le PID de mon pere est: %d\n",getpid(),getppid());

    }else{
        printf("je suis le processus père, mon PID est: %d Et le PID de mon fils est %d\n",getpid(),child1);
    }

   return 0; 

    
}

