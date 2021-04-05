
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>

sem_t mutexPiste1, mutexPiste2, mutexLibre1, mutexLibre2, fileAttente, mutextotal, mutexNb;
int piste1Libre = 1, piste2Libre = 1; //1 libre 0 occupé.
int nb = 0, total_avion;

void *aterrire(void *id)
{
    long idAvion = (long)id;
    sleep(rand() % 10);
    printf("Avion %ld souhaite aterrire! \n", idAvion);
    while(1)
    { 

        sem_wait(&mutexLibre1);
        if (piste1Libre)
        {
            piste1Libre = 0; //il faut d'abord dire que la piste n'est pas libre ensuite liberer
            sem_post(&mutexLibre1);

            sem_wait(&mutexPiste1);
            sleep(3);
            printf("Avion %ld aterrisaage reussi! piste 1\n", idAvion);
            sem_post(&mutexPiste1);

            sem_wait(&mutextotal);
            total_avion--;
            sem_post(&mutextotal);
            sem_wait(&mutexLibre1);
            piste1Libre = 1;
            sem_post(&mutexLibre1);

            sem_wait(&mutexNb);
            if (nb > 0)
            {
                nb--;
                sem_post(&fileAttente);
            }
            sem_post(&mutexNb);
            sem_post(&mutexLibre1); // pour liberer la poste a d'eventuelle avion en attente.
            return NULL; //il faut arreter le processus
        }
        sem_post(&mutexLibre1); //si il ne rentre pas dans la boucle on doit laisser les autres passer.
        sem_wait(&mutexLibre2);
        if (piste2Libre)
        {
            piste2Libre = 0; //d'abord dire que la piste 2 n'est pas dispo ensuite liberer
            sem_post(&mutexLibre2);

            sem_wait(&mutexPiste2);
            sleep(3);
            printf("Avion %ld aterrisaage reussi! piste 2\n", idAvion);

            sem_post(&mutexPiste2);

            sem_wait(&mutextotal);
            total_avion--;
            sem_post(&mutextotal);

            sem_wait(&mutexLibre2);
            piste2Libre = 1;
            sem_post(&mutexLibre2);

            sem_wait(&mutexNb);
            if (nb != 0)
            {
                nb--;
                sem_post(&fileAttente);
            }
            sem_post(&mutexNb);

            sem_post(&mutexLibre2);
            return NULL; //arreter le processus(l'avion)
        }
        sem_post(&mutexLibre2);
        sem_wait(&mutexNb);
        nb++;
        sem_post(&mutexNb);
        sem_wait(&fileAttente);
    }
    printf("hay si tu voit sa tu as merdé! :) ");
    return NULL;
}

void *decolle(void *id)
{
    long idAvion = (long)id;
    sleep(rand() % 10);
    printf("Avion %ld souhaite decolle! \n", idAvion);

    while(1){

        sem_wait(&mutexLibre1);
        if (piste1Libre)
        {
            piste1Libre = 0; //il faut d'abord dire que la piste n'est pas libre ensuite liberer
            sem_post(&mutexLibre1);

            sem_wait(&mutexPiste1);
            sleep(5);
            printf("Avion %ld decolage reussi! piste 1\n", idAvion);
            sem_post(&mutexPiste1);

            sem_wait(&mutextotal);
            total_avion--;
            sem_post(&mutextotal);
            
            sem_wait(&mutexLibre1);
            piste1Libre = 1;
            sem_post(&mutexLibre1);
            sem_wait(&mutexNb);
            if (nb > 0)
            {
                nb--;
                sem_post(&fileAttente);
            }
            sem_post(&mutexLibre1);
            return NULL; //il faut arreter le processus
        }
        sem_post(&mutexLibre1); //si il ne rentre pas dans la boucle on doit laisser les autres passer.
        sem_wait(&mutexLibre2);
        if (piste2Libre)
        {   
            piste2Libre = 0; //d'abord dire que la piste 2 n'est pas dispo ensuite liberer
            sem_post(&mutexLibre2);

            sem_wait(&mutexPiste2);
            sleep(5);
            printf("Avion %ld decolage reussi! piste 2\n", idAvion);

            sem_post(&mutexPiste2);

            sem_wait(&mutextotal);
            total_avion--;
            sem_post(&mutextotal);

            sem_wait(&mutexLibre2);
            piste2Libre = 1;
            sem_post(&mutexLibre2);

            sem_wait(&mutexNb);
            if (nb > 0)
            {
                nb--;
                sem_post(&fileAttente);
            }
            sem_post(&mutexNb);

            sem_post(&mutexLibre2);
            return NULL; //arreter le processus(l'avion)
        }
        sem_post(&mutexLibre2);
        sem_wait(&mutexNb);
        nb++;
        sem_post(&mutexNb);
        sem_wait(&fileAttente);
    }
    return NULL;
    //-------------------------------------------------------------
}

int main(int argc, char const *argv[])
{ //argv[1] : nbr avion devant decollé
    //argv[2] : nbr avion devant atterir

    printf("argc %d\n", argc);

    if (argc == 3)
    {
        int nbAvionDecole = atoi(argv[1]);
        int nbAvionAterr = atoi(argv[2]);
        total_avion = nbAvionDecole + nbAvionAterr;
        pthread_t threadDecol[nbAvionDecole], threadAterr[nbAvionAterr];
        sem_init(&mutexPiste1, 0, 1);
        sem_init(&mutexPiste2, 0, 1);
        sem_init(&mutexLibre1, 0, 1);
        sem_init(&mutexLibre2, 0, 1);
        sem_init(&fileAttente, 0, 0);
        sem_init(&mutextotal, 0, 1);
        sem_init(&mutexNb, 0, 1);

        printf("nombre d'avions souhaitant aterire: %d \n", nbAvionAterr);
        printf("nombre d'avions souhaitant decolle: %d \n", nbAvionDecole);

        for (long i = 0; i < nbAvionDecole; i++)
        {
            pthread_create(&threadDecol[i], NULL, decolle, (void *)i);
        }
        //on commence de nbaviondecole pour avoir des ids differents pour chaque avion

        for (long i = nbAvionDecole; i < (nbAvionDecole + nbAvionAterr); i++)
        {
            pthread_create(&threadAterr[i], NULL, aterrire, (void *)i);
        }

        for (long i = 0; i < nbAvionDecole; i++)
        {
            pthread_join(threadDecol[i], NULL);
        }
        //on commence de nbaviondecole pour avoir des ids differents pour chaque avion

        for (long i = nbAvionDecole; i < (nbAvionDecole + nbAvionAterr); i++)
        {
            pthread_join(threadAterr[i], NULL);
        }
        printf("Piste vide\n");
    }
    else
    {
        printf("nombre d'arguments insuffisant");
    }
    printf("total avion= %d\n",total_avion);
    return 0;
}