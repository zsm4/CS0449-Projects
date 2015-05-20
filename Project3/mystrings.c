#include <stdio.h>
#include <stdlib.h>

/*
    This program searching through a file's code printing all strings. May be useful for cracking the password protected files.    
*/    

main(int argc, char * argv[])
{
    if(argc != 2)
    {
        printf("You must enter a filename, exiting now.\n");
        exit(0);
    }
    FILE * file = fopen(argv[1],"rb");   //assume argv[1] is the filename
        
    if(file == 0)
    {
        printf("Could not open file, exiting.\n");
        exit(0);
    }

    char *buffer = calloc(5,sizeof(char));
    
    if(!buffer)
    {
        printf("Could not allocate enough memory for buffer, exiting.\n");
        exit(0);
    }
    
    char current = 0;
    int length = 0;
    int capacity = 4;

    //file opened correctly so read the bytes of the file
    //if 4 consecutive characters will ascii value between (32,126) print word
    while(fread(&current,sizeof(char),1,file)==1)
    {
        int value = (int)current;
        if(value>=32 && value<=126)
        {
            
            if(length<capacity)
            {
                buffer[length] = current;
            }
            else
            {
                capacity*=2;
                buffer = realloc(buffer,sizeof(char)*capacity+1);
                
                if(!buffer)
                {
                    printf("Could not allocate enough memory, exiting.");
                    exit(0);
                }
                buffer[length] = current;
            }
            
            length++;
        }
        else
        {
            if(length>3)
            {
                int i;
                for(i=0;i<length;i++)
                {
                    printf("%c",buffer[i]);
                }
                printf("\n");
            }
            length = 0;
            free(buffer);
            buffer = calloc(5,sizeof(char));
            capacity = 4;
        }

    }
    free(buffer);
}
