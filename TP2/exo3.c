//TODO:faire l'exo du

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int nbtour = 10;
int a, b, nb[2] = {0, 0};

sem_t s1, s2, s3, s4;

void *joueur1(void *x)
{
    while (nbtour > 0)
    {
        a = rand() % 3;
        printf("la valeur du joueur1 est %d\n", a);
        sem_post(&s1); // réveiller l'arbitre  qui est bloqué
        sem_wait(&s3); //attendre que l'arbitre termine
    }
    //printf("joueur1\n");
    return NULL;
}

void *joueur2(void *x)
{
    while (nbtour > 0)
    {
        b = rand() % 3;
        printf("la valeur du joueur2 est %d\n", b);
        sem_post(&s2); // réveiller l'arbitre qui est bloqué
        sem_wait(&s4); //attendre que l'arbitre termine
    }

    //printf("joueur2\n");
    return NULL;
}

void *arbitre(void *x)
{
    while (nbtour > 0)
    {

        sem_wait(&s1);
        sem_wait(&s2); //0= feuille  1=pierre   2=ciseau
        if (a == 0)
        {
            if (b == 1)
                nb[0]++;
            if (b == 2)
                nb[1]++;
        }
        if (a == 1)
        {
            if (b == 0)
                nb[1]++;
            if (b == 2)
                nb[0]++;
        }
        if (a == 2)
        {
            if (b == 0)
                nb[0]++;
            if (b == 1)
                nb[1]++;
        }
        nbtour--;
        sem_post(&s3);
        sem_post(&s4);
    }
    //printf("arbitre \n");

    // pthread_exit((void*) nb);

    return NULL;
}

int main(void)
{
    pthread_t j1, j2, A;
    int c[2], i;

    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);
    sem_init(&s3, 0, 0);
    sem_init(&s4, 0, 0);

    pthread_create(&j1, NULL, joueur1, NULL);
    pthread_create(&j2, NULL, joueur2, NULL);
    pthread_create(&A, NULL, arbitre, NULL);

    if (pthread_join(j1, NULL))
        perror("pthread_join");

    if (pthread_join(j2, NULL))
        perror("pthread_join");

    if (pthread_join(A, NULL))
        //    if (pthread_join(a, (void**)c))
        perror("pthread_join");
    for (i = 0; i < 2; i++)
        printf("le resultat est %d\n", nb[i]);

    printf("Fin du pere\n");
    return (EXIT_SUCCESS);
}
