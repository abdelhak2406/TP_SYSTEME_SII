//TODO: Fix stack smashing error!!
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<math.h>
/*
    while wait(&status!=-1)
        !atendre que tout les processus ce finisse
*/
int main(int argc, char const *argv[])
{
    pid_t childs[3],pids[3];
    int i, status[3];
    for ( i = 0; i < 3; i++)
    {
        childs[i] = fork();
        if (childs[i]==-1)
        {
            printf("erreur fork %d",i);
            exit(-1);
        }else if(childs[i]==0){
            //i eme fils
            int x = rand();
            exit (x);
        }
        
    }
    while ((pids[i]=wait(&status[i]))!=-1)
    {
        if (WIFEXITED(status[i]))
            {       
                status[i] = WEXITSTATUS(status[i]);
                printf("le processus fils ayant le PID %d sait terminer avec le code %d\n",pids[i],status[i]);
            }
        else{
                printf("status error i= %d",i);
                exit(-1);
            }
        i++;
    }    
        int resultat = status[0]*status[1] + status[2];
        printf("resultat= %d",resultat);

}