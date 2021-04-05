#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
int main(int argc, char const *argv[])//argument count, argument vector!
{   float n ;
    if (argc>1)
    {   
        if ( atoi(argv[1])==1 ){
            // lancer carrer
            execlp ("./","car",argv[2], NULL);

        }else if (atoi(argv[1]==2))
        {   
                //lacer racine
            execlp ("./","rac",argv[2], NULL);
        }else
        {
            printf("Invalid argument");
        }
        
    }
    else{
        printf("No arguments!");
    }
    return 0;
}
