#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include<math.h>


sem_t np,nv;
int n=10,k=0,tab[10],t=0,q=0,td;
int art;

void deposer(int art){
    tab[q] = art;
    q = (q+1) % n;
    printf("depot... %d\n",art);
/*     sleep(1); */
}

void prelever(int art){
    art = tab[t];
    printf("art = %d\n",art);
    t = (t+1)% n;
/*     sleep(1); */
}

void *producteur(void *x)
{
    while (1)
    { 
    art = rand(); 
    
    sem_wait(&nv);//verifier nombre cases vides
        deposer(art);
        
    sem_post(&np); // réveiller consommateur

    }
   
    //printf("joueur1\n");
    return NULL;
}


void *consomateur(void *x)
{
   while(1){ 
    sem_wait(&np);//verifier nombre cases pleines
       prelever(art);
    sem_post(&nv); // réveiller 
   }
    //printf("joueur1\n");
    return NULL;

}

int main(int argc, char const *argv[])
{       
    pthread_t produ,conso;
        sem_init(&np, 0, 0);
        sem_init(&nv, 0, n);

        pthread_create(&produ, NULL, producteur, NULL);
        pthread_create(&conso, NULL, consomateur, NULL);

    if (pthread_join(produ, NULL))
        perror("pthread_join");
        return 0;
}
/* 
int main(int argc, char const *argv[])
{       
    pthread_t produ[10],conso[16];
        sem_init(&np, 0, 0);
        sem_init(&nv, 0, n);

        for (int i = 0; i < 10; i++)    
        {
            pthread_create(&produ[i], NULL, producteur, NULL);
            pthread_create(&conso[i], NULL, consomateur, NULL);
        }
        for (int i = 10; i < 16; i++)
        {
            pthread_create(&conso[i], NULL, consomateur, NULL);
        }
         
        for (int i = 0; i < 10; i++)    
        {
           pthread_join(produ[i], NULL);
        }
        for (int i = 10; i < 16; i++)
        {
           pthread_join(conso[i], NULL);
        }
        return 0;
}
 */