#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int average = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //reflect to temporary image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        int p = 0;
        for (int j = width - 1; j >= 0; j--, p++)
        {
            temp[i][p] = image[i][j];
        }
    }
    
    //copy to final image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // look neighbouring pixels
            int count = 0;
            int row_cords[] = {i - 1, i, i + 1};
            int col_cords[] = {j - 1, j, j + 1};
            float total_r = 0;
            float total_g = 0;
            float total_b = 0;
            
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    int cur_row = row_cords[x];
                    int cur_col = col_cords[y];
                    
                    // validate if neighbouring pixel is in picture
                    if (cur_row >= 0 && cur_row < height && cur_col >= 0 && cur_col < width)
                    {
                        RGBTRIPLE pixel = image[cur_row][cur_col];
                        total_r += pixel.rgbtRed;
                        total_g += pixel.rgbtGreen;
                        total_b += pixel.rgbtBlue;
                        count++;
                    }
                }
            }
            
            // set temp image values
            temp[i][j].rgbtRed = round(total_r / count);
            temp[i][j].rgbtGreen = round(total_g / count);
            temp[i][j].rgbtBlue = round(total_b / count);
        }
    }
    
    //copy to final image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}

// Detect edgescd
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
