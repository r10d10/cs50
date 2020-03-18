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
    int sumR, sumG, sumB, d;
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
                    if ((i + ii >= 0) && (i + ii < height) && (j + jj >= 0) && (j + jj < width))
                    {
                        sumR += temp[i + ii][j + jj].rgbtRed;
                        sumG += temp[i + ii][j + jj].rgbtGreen;
                        sumB += temp[i + ii][j + jj].rgbtBlue;

                        d++;
                    }
                }
            }
                image[i][j].rgbtBlue = round(sumB / d);
                image[i][j].rgbtRed = round(sumR / d);
                image[i][j].rgbtGreen = round(sumG / d);

        }
    }
    return;
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int sumXR, sumXG, sumXB, d, sumYR, sumYG, sumYB;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((i == 0) && (j == 0))
            {
                sumXB = (image[i + 1][j + 1].rgbtBlue) + (2 * image[i + 1][j].rgbtBlue) + ( image[i + 1][j + 1].rgbtBlue);
                sumXR = (image[i + 1][j + 1].rgbtRed) + (2 * image[i + 1][j].rgbtRed) + ( image[i + 1][j + 1].rgbtRed);
                sumXG = (image[i + 1][j + 1].rgbtGreen) + (2 * image[i + 1][j].rgbtGreen) + ( image[i + 1][j + 1].rgbtGreen);

                // Sobel operator - Gy
                sumYB = (image[i + 1][j + 1].rgbtBlue) + (2 * image[i][j + 1].rgbtBlue) + ( image[i + 1][j + 1].rgbtBlue);
                sumYR = (image[i + 1][j + 1].rgbtRed) + (2 * image[i][j + 1].rgbtRed) + ( image[i + 1][j + 1].rgbtRed);
                sumYG = (image[i + 1][j + 1].rgbtGreen) + (2 * image[i][j + 1].rgbtGreen) + ( image[i + 1][j + 1].rgbtGreen);
                break;
            }

            if ((i + 1 == height) && (j + 1 == width))
            {
                // Sobel operator - Gx
                sumXB = (-image[i - 1][j - 1].rgbtBlue) + (-2 * image[i - 1][j].rgbtBlue);
                sumXR = (-image[i - 1][j - 1].rgbtRed) + (-2 * image[i - 1][j].rgbtRed);
                sumXG = (-image[i - 1][j - 1].rgbtGreen) + (-2 * image[i - 1][j].rgbtGreen);

                // Sobel operator - Gy
                sumYB = (-image[i - 1][j - 1].rgbtBlue) + (-2 * image[i][j - 1].rgbtBlue);
                sumYR = (-image[i - 1][j - 1].rgbtRed) + (-2 * image[i][j - 1].rgbtRed);
                sumYG = (-image[i - 1][j - 1].rgbtGreen) + (-2 * image[i][j - 1].rgbtGreen);
                break;
            }


            if ((i == 0) && (j != 0))
            {
                sumXB = (image[i + 1][j + 1].rgbtBlue) + (2 * image[i + 1][j].rgbtBlue) + ( image[i + 1][j + 1].rgbtBlue);
                sumXR = (image[i + 1][j + 1].rgbtRed) + (2 * image[i + 1][j].rgbtRed) + ( image[i + 1][j + 1].rgbtRed);
                sumXG = (image[i + 1][j + 1].rgbtGreen) + (2 * image[i + 1][j].rgbtGreen) + ( image[i + 1][j + 1].rgbtGreen);

                // Sobel operator - Gy
                sumYB = (image[i + 1][j + 1].rgbtBlue) + (-2 * image[i][j - 1].rgbtBlue) + (2 * image[i][j + 1].rgbtBlue) + ( image[i + 1][j + 1].rgbtBlue);
                sumYR = (image[i + 1][j + 1].rgbtRed) + (-2 * image[i][j - 1].rgbtRed) + (2 * image[i][j + 1].rgbtRed) + ( image[i + 1][j + 1].rgbtRed);
                sumYG = (image[i + 1][j + 1].rgbtGreen) + (-2 * image[i][j - 1].rgbtGreen) + (2 * image[i][j + 1].rgbtGreen) + ( image[i + 1][j + 1].rgbtGreen);
            }
            else
            {
                if ((i != 0) && (j == 0))
                {
                    // Sobel operator - Gx
                    sumXB = (image[i + 1][j + 1].rgbtBlue) + (-2 * image[i - 1][j].rgbtBlue) + (2 * image[i + 1][j].rgbtBlue) + (-image[i - 1][j + 1].rgbtBlue) + ( image[i + 1][j + 1].rgbtBlue);
                    sumXR = (image[i + 1][j + 1].rgbtRed) + (-2 * image[i - 1][j].rgbtRed) + (2 * image[i + 1][j].rgbtRed) + (-image[i - 1][j + 1].rgbtRed) + ( image[i + 1][j + 1].rgbtRed);
                    sumXG = (image[i + 1][j + 1].rgbtGreen) + (-2 * image[i - 1][j].rgbtGreen) + (2 * image[i + 1][j].rgbtGreen) + (-image[i - 1][j + 1].rgbtGreen) + ( image[i + 1][j + 1].rgbtGreen);

                    // Sobel operator - Gy
                    sumYB = (image[i + 1][j + 1].rgbtBlue) + (2 * image[i][j + 1].rgbtBlue) + (-image[i - 1][j + 1].rgbtBlue) + ( image[i + 1][j + 1].rgbtBlue);
                    sumYR = (image[i + 1][j + 1].rgbtRed) + (2 * image[i][j + 1].rgbtRed) + (-image[i - 1][j + 1].rgbtRed) + ( image[i + 1][j + 1].rgbtRed);
                    sumYG = (image[i + 1][j + 1].rgbtGreen) + (2 * image[i][j + 1].rgbtGreen) + (-image[i - 1][j + 1].rgbtGreen) + ( image[i + 1][j + 1].rgbtGreen);

                }
                else
                {
                    if ((i + 1 == height) && (j + 1 != width))
                    {
                         // Sobel operator - Gx
                        sumXB = (-image[i - 1][j - 1].rgbtBlue) + (-2 * image[i - 1][j].rgbtBlue) + (-image[i - 1][j + 1].rgbtBlue);
                        sumXR = (-image[i - 1][j - 1].rgbtRed) + (-2 * image[i - 1][j].rgbtRed) + (-image[i - 1][j + 1].rgbtRed);
                        sumXG = (-image[i - 1][j - 1].rgbtGreen) + (-2 * image[i - 1][j].rgbtGreen) + (-image[i - 1][j + 1].rgbtGreen);

                        // Sobel operator - Gy
                        sumYB = (-image[i - 1][j - 1].rgbtBlue) + (-2 * image[i][j - 1].rgbtBlue) + (2 * image[i][j + 1].rgbtBlue) + (-image[i - 1][j + 1].rgbtBlue);
                        sumYR = (-image[i - 1][j - 1].rgbtRed) + (-2 * image[i][j - 1].rgbtRed) + (2 * image[i][j + 1].rgbtRed) + (-image[i - 1][j + 1].rgbtRed);
                        sumYG = (-image[i - 1][j - 1].rgbtGreen) + (-2 * image[i][j - 1].rgbtGreen) + (2 * image[i][j + 1].rgbtGreen) + (-image[i - 1][j + 1].rgbtGreen);
                    }
                    else
                    {
                        if ((i + 1 != height) && (j + 1 == width))
                        {
                            // Sobel operator - Gx
                            sumXB = (-image[i - 1][j - 1].rgbtBlue) + (-2 * image[i - 1][j].rgbtBlue) + (2 * image[i + 1][j].rgbtBlue);
                            sumXR = (-image[i - 1][j - 1].rgbtRed) + (-2 * image[i - 1][j].rgbtRed) + (2 * image[i + 1][j].rgbtRed);
                            sumXG = (-image[i - 1][j - 1].rgbtGreen) + (-2 * image[i - 1][j].rgbtGreen) + (2 * image[i + 1][j].rgbtGreen);

                             // Sobel operator - Gy
                            sumYB = (-image[i - 1][j - 1].rgbtBlue) + (-2 * image[i][j - 1].rgbtBlue);
                            sumYR = (-image[i - 1][j - 1].rgbtRed) + (-2 * image[i][j - 1].rgbtRed);
                            sumYG = (-image[i - 1][j - 1].rgbtGreen) + (-2 * image[i][j - 1].rgbtGreen);

                        }
                        else
                        {
                            // Sobel operator - Gx
                            sumXB = (-image[i - 1][j - 1].rgbtBlue) + (image[i + 1][j + 1].rgbtBlue) + (-2 * image[i - 1][j].rgbtBlue) + (2 * image[i + 1][j].rgbtBlue) + (-image[i - 1][j + 1].rgbtBlue) + ( image[i + 1][j + 1].rgbtBlue);
                            sumXR = (-image[i - 1][j - 1].rgbtRed) + (image[i + 1][j + 1].rgbtRed) + (-2 * image[i - 1][j].rgbtRed) + (2 * image[i + 1][j].rgbtRed) + (-image[i - 1][j + 1].rgbtRed) + ( image[i + 1][j + 1].rgbtRed);
                            sumXG = (-image[i - 1][j - 1].rgbtGreen) + (image[i + 1][j + 1].rgbtGreen) + (-2 * image[i - 1][j].rgbtGreen) + (2 * image[i + 1][j].rgbtGreen) + (-image[i - 1][j + 1].rgbtGreen) + ( image[i + 1][j + 1].rgbtGreen);

                            // Sobel operator - Gy
                            sumYB = (-image[i - 1][j - 1].rgbtBlue) + (image[i + 1][j + 1].rgbtBlue) + (-2 * image[i][j - 1].rgbtBlue) + (2 * image[i][j + 1].rgbtBlue) + (-image[i - 1][j + 1].rgbtBlue) + ( image[i + 1][j + 1].rgbtBlue);
                            sumYR = (-image[i - 1][j - 1].rgbtRed) +  (image[i + 1][j + 1].rgbtRed) + (-2 * image[i][j - 1].rgbtRed) + (2 * image[i][j + 1].rgbtRed) + (-image[i - 1][j + 1].rgbtRed) + ( image[i + 1][j + 1].rgbtRed);
                            sumYG = (-image[i - 1][j - 1].rgbtGreen) + (image[i + 1][j + 1].rgbtGreen) + (-2 * image[i][j - 1].rgbtGreen) + (2 * image[i][j + 1].rgbtGreen) + (-image[i - 1][j + 1].rgbtGreen) + ( image[i + 1][j + 1].rgbtGreen);

                        }
                    }
                }
            }

            d = sqrt(sumXB * sumXB + sumYB * sumYB);
            if (d <= 0)
            {
                image[i][j].rgbtBlue = 0;
            }
            else
            {
                if (d >= 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = d;
                }
            }


            d = sqrt(sumXG * sumXG + sumYG * sumYG);
            if (d <= 0)
            {
                image[i][j].rgbtGreen = 0;
            }
            else
            {
                if (d >= 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = d;
                }
            }


            d = sqrt(sumXR * sumXR + sumYR * sumYR);
            if (d <= 0)
            {
                image[i][j].rgbtRed = 0;
            }
            else
            {
                if (d >= 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = d;
                }
            }
        }
    }
    return;
}