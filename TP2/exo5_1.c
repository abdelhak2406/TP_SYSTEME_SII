#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include<math.h>


sem_t mutexPiste;
int prio; //prio


void *aterrire(void *id)
{
    long idAvion = (long)id;

   sleep(rand()%10);//attendre entre 1 et 10
   printf("Avion %ld souhaite aterrire!\n",idAvion) ;
   sem_wait(&mutexPiste);
    sleep(3);
   printf("Avion %ld aterrisaage reussi piste Libérer\n",idAvion) ;
   sem_post(&mutexPiste);
     
   
   
    //printf("joueur1\n");
    return NULL;
}


void *decolle(void *id)
{
    long idAvion = (long)id;

   sleep(rand()%10);//attendre entre 1 et 10
   printf("Avion %ld souhaite decolle!\n",idAvion) ;
   sem_wait(&mutexPiste);
    sleep(5);
   printf("Avion %ld decollage reussi! Piste Libérer\n",idAvion) ;
   sem_post(&mutexPiste);
     
    
    //printf("joueur1\n");
    return NULL;

}

int main(int argc, char const *argv[])
{      //argv[1] : nbr avion devant decollé
        //argv[2] : nbr avion devant atterir


       
    printf("argc %d\n",argc);

    if(argc==3){
        int nbAvionDecole= atoi(argv[1]);
        int nbAvionAterr = atoi(argv[2]);

        pthread_t threadDecol[nbAvionDecole],threadAterr[nbAvionAterr];
        sem_init(&mutexPiste, 0, 1);
        
        printf("nombre d'avions souhaitant aterire: %d \n",nbAvionAterr);
        printf("nombre d'avions souhaitant decolle: %d \n",nbAvionDecole);

        
        
        for (long i = 0; i < nbAvionDecole; i++)
        {
            pthread_create(&threadDecol[i],NULL,decolle,(void *)i);

        }
        //on commence de nbaviondecole pour avoir des ids differents pour chaque avion

        for(long i= nbAvionDecole; i<(nbAvionDecole+nbAvionAterr);i++) 
        {
            pthread_create(&threadAterr[i],NULL,aterrire,(void *)i);

        }

        
        for (long i = 0; i < nbAvionDecole; i++)
        {
           pthread_join(threadDecol[i],NULL);
        }
        //on commence de nbaviondecole pour avoir des ids differents pour chaque avion

        for(long i= nbAvionDecole; i<(nbAvionDecole+nbAvionAterr);i++) 
        {
            pthread_join(threadAterr[i],NULL);

        }
        printf("Piste vide\n");
    }else
        {
        printf("nombre d'arguments insuffisant");
        }
    
        return 0;
}