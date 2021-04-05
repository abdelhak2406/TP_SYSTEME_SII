#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define Nbth 10

pthread_t tid[Nbth];
pthread_cond_t cond;
pthread_mutex_t mutex;
int Nbarrives = 0; //variable accessible pour toutes les threads en lect/ecrit*/

void rdv()
{
    pthread_mutex_lock(&mutex); //un seule thread à la fois peut etre actif à l'interieur du moniteur, cad execute une procedure du moniteur
    Nbarrives++;
    if (Nbarrives > 5)
        pthread_cond_wait(&cond, &mutex); //v(mutex); p(cond);
    /*une thread qui execute cond wait est bloquée systematiquement mais le sémaphore mutex est libéré
pour permettre à d'autre thread à accéder à la variable.
la liberation de mutex et le blocage sont fait de maniere atomique.
Lorsque la condition est signalée, cette thread est révéillée et acquiert à nouveau le mutex afin de retester  
la variable et etre la seule à le faire*/
    Nbarrives--; 
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

void *fonct(void *k)
{
    printf(" voiture veut aller  %d se garer terminee\n", (int)k);
    rdv();
    printf("suite de la thread num %d \n", (int)k);
}
void main()
{
    int i;
    pthread_mutex_init(&mutex, 0);
    pthread_cond_init(&cond, 0);

    for (i = 0; i < Nbth; i++)
        pthread_create(tid + i, 0, fonct, (void *)i);
    for (i = 0; i < Nbth; i++)
        pthread_join(tid[i], NULL);

} /*  */