//TODO: parler avec la prof de l'exécution bizarre qu'il y'a avec sa solution  déja 1 quand il y'a repetition de donner car.
// et 2 quand j'ai suprimer le truc dans scanf, il ecrit 2 fis caractere = et donner caractere
/*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
char c;
int att = 0;//Solution avec attente active
void *fonc_thread_redacteur(void *v)
{
    printf("mon tidest %ld\n", pthread_self());
    do
    {   
        while (att == 0)
            ;
        printf("le cara recu est %c \n", c);
        att = 0;
    } while (c != 'f');
}

void *fonc_thread_lecteur(void *v)
{
    do
    { 
        while (att == 1)
            ;
        printf("donner car:\n");
        scanf(" %c", &c);
        att = 1;
    } while (c != 'f');
}

void main()
{
    pthread_t pth_id, pth_id1;
    //creation du thread 
    pthread_create(&pth_id, 0, fonc_thread_redacteur, NULL);
    printf("Main: thread creee: id = %ld\n", pth_id);

    pthread_create(&pth_id1, 0, fonc_thread_lecteur, NULL);
    printf("Main: thread creee: id = %ld\n", pth_id);

    pthread_join(pth_id, NULL);
    pthread_join(pth_id1, NULL);
}
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

char theChar = '\0';
sem_t s1, s2;
void *lire(void *name)
{
    while (theChar != 'F')
    {
        sem_wait(&s1); /* attendre mon tour */
        printf("donner un caractere\n");
        scanf("%c", &theChar);//
        //theChar=getchar();
        sem_post(&s2);
    }
    return NULL;
}

void *affichage(void *name)
{
    while (theChar != 'F')
    {
        sem_wait(&s2);
        printf("caractere = %c \n", theChar);
        sem_post(&s1);
    }
    return NULL;
}

int main(void)
{
    pthread_t afficheur, lecteur;

    sem_init(&s1, 0, 1);
    sem_init(&s2, 0, 0);
    pthread_create(&afficheur, NULL, affichage, NULL);
    pthread_create(&lecteur, NULL, lire, NULL);

    if (pthread_join(afficheur, NULL))
        perror("pthread_join");

    if (pthread_join(lecteur, NULL))
        perror("pthread_join");

    printf("Fin du pere\n");
    return (EXIT_SUCCESS);
}



//---------------------------------------------------------------------------


/*
a) Création de threads Int pthread_create(pthread_t *thread,const pthread_attr_t *attr, void *(*start_routine)(void*),void *arg); 
Cette primitive permet de créer un nouveau thread et retourne un code d'erreur dans le cas d'échec. 
    - Thread contient les informations d'identification sur le thread créé. 
    - Attr sont les attributs du thread à créer (peut être NULL).
    - start_routine est la fonction exécutée  par le thread.
        Le thread se termine lorsqu'il atteint la fin de la fonction (fin normale). Tous les threads créés sont détruits si le 
        thread principal (celui qui exécute le main()) se termine.
    - Arg est l'unique argument passé à la fonction start_routine.

2) Manipulation de sémaphores Les sémaphores sont définis dans le fichier semaphore.h. Un sémaphore est une variable de type sem_t. 
    a) Initialisation du sémaphore Int sem_init(sem_t *sem, int pshared, unsigned value);
    Cette primitive initialise le sémaphore sem à la valeur value.
    -Pshared permet de partager un sémaphore entre plusieurs processus. 
        * Si pshared vaut 0 le sémaphore ne peut pas être partagé qu’entre tâches d’un même processus. 
        * Si pshared n’est pas égal à 0, le sémaphore peut être partagé entre plusieurs processus.
    b) Destruction du sémaphore Int sem_destroy(sem_t * semaphore);
    c) P() du sémaphore Int sem_wait(sem_t * semaphore);
    d) V() du sémaphore Int sem_post(sem_t * semaphore); 
    e) Valeur du sémaphore Int sem_getvalue(sem_t * semaphore, int * sval);

*/
