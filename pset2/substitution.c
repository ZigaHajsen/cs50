#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else 
    {
        
        // Get key
        string key = argv[1];
        
        // Validate key
        // check if 26 char
        if (strlen(key) == 26)
        {
            // check if unique char in string
            for (int i = 0; i < 26; i++)
            {
                // check if alphabetical char
                if (!isalpha(key[i]))
                {
                    printf("Provide alphabetical characters\n");
                    return 1;
                }
                else
                {
                    for (int j = i + 1; j < 26; j++)
                    {
                        // convert to lowercase and check if same
                        if (tolower(key[i]) == tolower(key[j]))
                        {
                            printf("Provide unique characters\n");
                            return 1;
                        }
                    }
                }
            }
        }  
        else 
        {
            printf("Provide 26 character key\n");
            return 1;
        }
        
        // Get plaintext
        string plain_text = get_string("plaintext: ");
        int text_length = strlen(plain_text);
        
        // Encipher
        printf("ciphertext: ");
        char cipher_text[text_length];
        for (int i = 0; i < text_length; i++)
        {
            // if alphabetical character envrypt
            if (isalpha(plain_text[i]))
            {
                // check if upper or lower case and encrypt
                switch (plain_text[i])
                {
                    case 65:
                        cipher_text[i] = toupper(key[0]);
                        break;
                    case 97:
                        cipher_text[i] = tolower(key[0]);
                        break;
                    case 66:
                        cipher_text[i] = toupper(key[1]);
                        break;
                    case 98:
                        cipher_text[i] = tolower(key[1]);
                        break;
                    case 67:
                        cipher_text[i] = toupper(key[2]);
                        break;
                    case 99:
                        cipher_text[i] = tolower(key[2]);
                        break;
                    case 68:
                        cipher_text[i] = toupper(key[3]);
                        break;
                    case 100:
                        cipher_text[i] = tolower(key[3]);
                        break;
                    case 69:
                        cipher_text[i] = toupper(key[4]);
                        break;
                    case 101:
                        cipher_text[i] = tolower(key[4]);
                        break;
                    case 70:
                        cipher_text[i] = toupper(key[5]);
                        break;
                    case 102:
                        cipher_text[i] = tolower(key[5]);
                        break;
                    case 71:
                        cipher_text[i] = toupper(key[6]);
                        break;
                    case 103:
                        cipher_text[i] = tolower(key[6]);
                        break;
                    case 72:
                        cipher_text[i] = toupper(key[7]);
                        break;
                    case 104:
                        cipher_text[i] = tolower(key[7]);
                        break;
                    case 73:
                        cipher_text[i] = toupper(key[8]);
                        break;
                    case 105:
                        cipher_text[i] = tolower(key[8]);
                        break;
                    case 74:
                        cipher_text[i] = toupper(key[9]);
                        break;
                    case 106:
                        cipher_text[i] = tolower(key[9]);
                        break;
                    case 75:
                        cipher_text[i] = toupper(key[10]);
                        break;
                    case 107:
                        cipher_text[i] = tolower(key[10]);
                        break;
                    case 76:
                        cipher_text[i] = toupper(key[11]);
                        break;
                    case 108:
                        cipher_text[i] = tolower(key[11]);
                        break;
                    case 77:
                        cipher_text[i] = toupper(key[12]);
                        break;
                    case 109:
                        cipher_text[i] = tolower(key[12]);
                        break;
                    case 78:
                        cipher_text[i] = toupper(key[13]);
                        break;
                    case 110:
                        cipher_text[i] = tolower(key[13]);
                        break;
                    case 79:
                        cipher_text[i] = toupper(key[14]);
                        break;
                    case 111:
                        cipher_text[i] = tolower(key[14]);
                        break;
                    case 80:
                        cipher_text[i] = toupper(key[15]);
                        break;
                    case 112:
                        cipher_text[i] = tolower(key[15]);
                        break;
                    case 81:
                        cipher_text[i] = toupper(key[16]);
                        break;
                    case 113:
                        cipher_text[i] = tolower(key[16]);
                        break;
                    case 82:
                        cipher_text[i] = toupper(key[17]);
                        break;
                    case 114:
                        cipher_text[i] = tolower(key[17]);
                        break;
                    case 83:
                        cipher_text[i] = toupper(key[18]);
                        break;
                    case 115:
                        cipher_text[i] = tolower(key[18]);
                        break;
                    case 84:
                        cipher_text[i] = toupper(key[19]);
                        break;
                    case 116:
                        cipher_text[i] = tolower(key[19]);
                        break;
                    case 85:
                        cipher_text[i] = toupper(key[20]);
                        break;
                    case 117:
                        cipher_text[i] = tolower(key[20]);
                        break;
                    case 86:
                        cipher_text[i] = toupper(key[21]);
                        break;
                    case 118:
                        cipher_text[i] = tolower(key[21]);
                        break;
                    case 87:
                        cipher_text[i] = toupper(key[22]);
                        break;
                    case 119:
                        cipher_text[i] = tolower(key[22]);
                        break;
                    case 88:
                        cipher_text[i] = toupper(key[23]);
                        break;
                    case 120:
                        cipher_text[i] = tolower(key[23]);
                        break;
                    case 89:
                        cipher_text[i] = toupper(key[24]);
                        break;
                    case 121:
                        cipher_text[i] = tolower(key[24]);
                        break;
                    case 90:
                        cipher_text[i] = toupper(key[25]);
                        break;
                    case 122:
                        cipher_text[i] = tolower(key[25]);
                        break;
                    default:
                        break;
                }
                // print encrypted char
                printf("%c", cipher_text[i]);
            }
            else
            {
                // print same char if not alphabetical
                printf("%c", plain_text[i]);
            }
        }
        // go next line
        printf("\n");
    }
}