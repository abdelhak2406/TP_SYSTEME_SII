#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{   
    //avec le execlp il ne reviens pas vers ce programme
    execlp("lsd","lsd",NULL);

    printf("Bonjour");
    return 0;
}
