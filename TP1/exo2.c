#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>
/*
    while wait(&status!=-1)
        !atendre que tout les processus ce finisse
*/

int main(int argc, char const *argv[])
{
    pid_t child1, pids[2];
    int i, status[2] = {0, 0};

    child1 = fork();
    if (child1 == -1)
    {
        perror("fork ne sait pas executer correctement");
    }
    else if (child1 == 0)
    {
        //fils 1
        int valeur2 = rand();
        printf("valeur aleatoire fils %d: %d\n", getpid(), valeur2);
        exit(valeur2);
    }
    else
    {
        //pere

        pid_t child2 = fork();
        if (child2 == -1)
        {
            perror("fork ne sait pas executer correctement");
        }
        else if (child2 == 0)
        {
            //fils 2
            srand(time(NULL));//pour avir differente valeurs
            int valeur = rand();
            printf("valeur aleatoire fils %d: %d\n", getpid(), valeur);
            exit(valeur);
        }
        else
        {
            i = 0;
            //pere
            while ((pids[i] = wait(&status[i])) != -1)
            {
                if (WIFEXITED(status[i]))
                {
                    status[i] = WEXITSTATUS(status[i]);
                    printf("le processus fils ayant le PID %d sait terminer avec le code %d\n", pids[i], status[i]);
                }
                i++;
            }
            if (status[0] > status[1])
                printf("%d\n", status[0]);
            else
                printf("%d\n", status[1]);
        }
    }
}
