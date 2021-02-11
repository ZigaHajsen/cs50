#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long credit_number = get_long("Number: ");
    long number = credit_number;
    
    //check number length
    int count = 0;
    while (number != 0)
    {
        number /= 10;
        count++;
    }
    
    // compare length to possible lengths
    if (count == 16 || count == 15 || count == 13)
    {  
        // checking for MASTERCARD or VISA
        if (count == 16) 
        {
            // getting first 2 numbers 
            number = credit_number;
            int trunkate = count - 2;
            while (trunkate != 0)
            {
                number /= 10;
                trunkate--;
            }
            
            
            // check first 2 numbers
            if (number == 51 || number == 52 || number == 53 || number == 54 || number == 55)
            {
                number = credit_number;
                trunkate = count;
                int position = 1;
                int isolated;
                int odd = 0;
                int even = 0;
                int sum;
                int validate;
                int remaning;
                while (trunkate != 0)
                {
                    isolated = number % 10;
                    number /= 10;
                    
                    remaning = position % 2;
                    
                    if (remaning == 0)
                    {
                        if (isolated * 2 > 9)
                        {
                            int temp_sum;
                            int temporary = isolated * 2;
                            
                            temp_sum = temporary % 10;
                            temporary /= 10;
                            
                            odd = temp_sum + temporary + odd;
                            
                        } 
                        else 
                        {
                            odd = (isolated * 2) + odd;
                        }
                    }
                    else 
                    {
                        even = isolated + even;
                    }
                    trunkate--;
                    position++;
                }
                
                sum = even + odd;
                validate = sum % 10;
                if (validate == 0)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            // check if VISA
            else 
            {
                // getting first number
                number /= 10;

                // check first number
                if (number == 4)
                {
                    number = credit_number;
                    trunkate = count;
                    int position = 1;
                    int isolated;
                    int odd = 0;
                    int even = 0;
                    int sum;
                    int validate;
                    int remaning;
                    while (trunkate != 0)
                    {
                        isolated = number % 10;
                        number /= 10;
                        
                        remaning = position % 2;
                        
                        
                        if (remaning == 0)
                        {
                            if (isolated * 2 > 9)
                            {
                                int temp_sum;
                                int temporary = isolated * 2;
                                
                                temp_sum = temporary % 10;
                                temporary /= 10;
                                
                                odd = temp_sum + temporary + odd;
                                
                            } 
                            else 
                            {
                                odd = (isolated * 2) + odd;
                            }
                        }
                        else 
                        {
                            even = isolated + even; 
                        }
                        
                        trunkate--;
                        position++;
                    }
                    
                    sum = even + odd;
                    validate = sum % 10;
                    
                
                    if (validate == 0)
                    {
                        printf("VISA\n");
                    }
                    else
                    {
                        printf("INVALID\n");
                    }
                } 
                else 
                {
                    printf("INVALID\n");
                }
            }
        }
        // checking for AMEX
        if (count == 15)
        {
            // getting first 2 numbers 
            number = credit_number;
            int trunkate = count - 2;
            while (trunkate != 0)
            {
                number /= 10;
                trunkate--;
            }
            
            // check first 2 numbers
            if (number == 34 || number == 37)
            {
                number = credit_number;
                trunkate = count;
                int position = 1;
                int isolated;
                int odd = 0;
                int even = 0;
                int sum;
                int validate;
                int remaning;
                while (trunkate != 0)
                {
                    isolated = number % 10;
                    number /= 10;
                    
                    remaning = position % 2;
                    
                    
                    if (remaning == 0)
                    {
                        if (isolated * 2 > 9)
                        {
                            int temp_sum;
                            int temporary = isolated * 2;
                            
                            temp_sum = temporary % 10;
                            temporary /= 10;
                            
                            odd = temp_sum + temporary + odd;
                            
                        } 
                        else 
                        {
                            odd = (isolated * 2) + odd;
                        }
                    }
                    else 
                    {
                        even = isolated + even; 
                    }
                    trunkate--;
                    position++;
                }
                
                sum = even + odd;
                validate = sum % 10;
                
                if (validate == 0)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                
            }
            else
            {
                printf("INVALID\n");
            }
        }
        // checking VISA
        if (count == 13)
        {
            // getting first number
            number = credit_number;
            int trunkate = count - 1;
            while (trunkate != 0)
            {
                number /= 10;
                trunkate--;
            }
            
            // check first number
            if (number == 4)
            {
                number = credit_number;
                trunkate = count;
                int position = 1;
                int isolated;
                int odd = 0;
                int even = 0;
                int sum;
                int validate;
                int remaning;
                while (trunkate != 0)
                {
                    isolated = number % 10;
                    number /= 10;
                    
                    remaning = position % 2;
                    
                    
                    if (remaning == 0)
                    {
                        if (isolated * 2 > 9)
                        {
                            int temp_sum;
                            int temporary = isolated * 2;
                            
                            temp_sum = temporary % 10;
                            temporary /= 10;
                            
                            odd = temp_sum + temporary + odd;
                            
                        } 
                        else 
                        {
                            odd = (isolated * 2) + odd;
                        }
                    }
                    else 
                    {
                        even = isolated + even; 
                    }
                    trunkate--;
                    position++;
                }
                
                sum = even + odd;
                validate = sum % 10;
                
                if (validate == 0)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            } 
            else 
            {
                printf("INVALID\n");
            }
        }
    
    } 
    else 
    {
        printf("INVALID\n");
    }
}