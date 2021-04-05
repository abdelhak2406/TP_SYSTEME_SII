#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
/*Le probléme est que tout les thread s'arretent quand le pére s'arrete.
 et donc il faut trouvé un moyén pour qu'il puisse les attendre */

long compteur[3];
/* fonction executee par chaque thread */
void *fonc_thread(void *k)
{
    long j;
    j = (long)k;
    printf("Thread numero %ld :mon tid est %ld\n", j, pthread_self());
        
    for (int var = 0; var < 20; var++)
    {   compteur[j]++;
        printf("%ld \n", compteur[j]);
    }
}

int main()
{
    long i, num;
    pthread_t pth_id[3];

    //creation des threads 
    for (num = 0; num < 3; num++)
    {
        pthread_create(&pth_id[num], 0, fonc_thread, (void *)num);
        printf("Main: thread numero %ld creee: id = %ld\n", num, pth_id[num]);
        //pour eviter le probleme il faut faire un equivalent a wait
        //pthread_join(pth_id[num],NULL);//le probleme ici c'est qu'il 
                                        //est obliger d'attendre la fin du thread actuellement creer
    }
    for ( i = 0; i < 3; i++)//attendre la terminaison des thread
    {
        pthread_join(pth_id[i],NULL);
    }
    

    exit(0);
}