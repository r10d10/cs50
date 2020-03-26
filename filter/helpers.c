#include "helpers.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float sum = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen +image[i][j].rgbtRed;
            image[i][j].rgbtBlue = (BYTE)round(sum / 3);
            image[i][j].rgbtRed = (BYTE)round(sum / 3);
            image[i][j].rgbtGreen = (BYTE)round(sum / 3);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE a = 0, b = 0, c = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= round((width - 1 ) / 2); j++)
        {
            a = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = a;

            b = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = b;

            c = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = c;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float sumR, sumG, sumB, d;
    RGBTRIPLE temp[height][width];

    //makes an copie of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            temp[i][j] = image [i][j];
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumB = 0;
            sumR = 0;
            sumG = 0;
            d = 0;

            // finds the sum of the next blocks to each pixel
            for (int ii = -1; ii < 2; ii++)
            {
                // finds the sum of the next blocks to each pixel
                for (int jj = -1; jj < 2; jj++)
                {
                    if ((i + ii >= 0) && (i + ii < height) && (j + jj >= 0)
                    && (j + jj < width))
                    {
                        sumR += (float)temp[i + ii][j + jj].rgbtRed;
                        sumG += (float)temp[i + ii][j + jj].rgbtGreen;
                        sumB += (float)temp[i + ii][j + jj].rgbtBlue;

                        d++;
                    }
                }
            }
                image[i][j].rgbtBlue = (BYTE)round(sumB / (float)d);
                image[i][j].rgbtRed = (BYTE)round(sumR / (float)d);
                image[i][j].rgbtGreen = (BYTE)round(sumG / (float)d);

        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    
}
