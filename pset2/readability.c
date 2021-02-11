#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");

    // go over whole array and check for letters words and sentances
    int letters = 0;
    int words = 0;
    int sentances = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        // check if char is alphabetical
        if (isalpha(text[i]))
        {
            letters++;
        }
        // check if char is whitespace
        else if (isspace(text[i]))
        {
            words++;
        }
        // check if char is punctuation
        else
        {
            switch (text[i])
            {
                case '.':
                case '?':
                case '!':
                    sentances++;
                    break;
                default:
                    break;
            }
        }
    }
    // correct for word count missing 1
    words++;

    // calculate averages per 100 words
    float avg_letters = letters / (float) words * 100;
    float avg_sentances = sentances / (float) words * 100;
    
    //The Coleman-Liau index calculation and rounding
    float index = 0.0588 * avg_letters - 0.296 * avg_sentances - 15.8;
    index = round(index);
    
    // print apropriate grade
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    } 
    else
    {
        printf("Grade %i\n", (int) index);
    }
}