#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define BLOCK_SIZE 512
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage ./revover image\n");
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error occured opening file.\n");
        return 1;
    }
    
    // open memory card
    typedef uint8_t BYTE;
    BYTE buffer[BLOCK_SIZE];
    size_t bytes_read;
    bool first_jpeg = false;
    bool found_jpeg = false;
    FILE *current_file;
    char current_file_name[8];
    int current_file_number = 0;
    
    // repeat until end of card
    while (true)
    {
        // read 512 bytes into buffer
        bytes_read = fread(buffer, sizeof(BYTE), BLOCK_SIZE, file);
        if (bytes_read == 0)
        {
            break; //end of file
        }
        
        // if start new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            found_jpeg = true;
            // if first jpeg
            // mark first jpeg
            if (!first_jpeg)
            {
                first_jpeg = true;
            }
            else
            {
                // close the current file
                fclose(current_file);
            }
            
            // open new file
            sprintf(current_file_name, "%03i.jpg", current_file_number);
            current_file = fopen(current_file_name, "w");
            fwrite(buffer, sizeof(BYTE), bytes_read, current_file);
            current_file_number++;
        }
        else
        {
            // if already found jpeg, keep writing to it
            if (found_jpeg)
            {
                fwrite(buffer, sizeof(BYTE), bytes_read, current_file);
            }
        }
    }
    
    fclose(file);
    fclose(current_file);
    return 0;

}