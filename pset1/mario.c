#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get user input between 1 and 8 inclusive
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);
    
    for (int i = 1; i <= height; i++)
    {
        int empty = height - i;
        int hash = i;
        
        // print spaces
        while (empty > 0)
        {
            printf(" ");
            empty--;
        }
        // print #
        while (hash > 0) 
        {
            printf("#");
            hash--;
        }
        // print line between 
        printf("  ");
        
        // print remaining # and new line
        hash = i;
        while (hash > 0) 
        {
            printf("#");
            hash--;
        }
        printf("\n");
    }
}