#include <stdio.h>
#include <stdlib.h>

int main()
{

    char** Cards = (char**) malloc(sizeof(char*)*32);
    
    for (int i = 0; i < 32; i++) {
        Cards[i] = (char*)malloc(sizeof(char)*5);
    }

    printf("Hello world!\n");
    scanf("%c", character);
    return 0;
    
}
