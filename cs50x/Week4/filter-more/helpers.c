#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each pixel in the image
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            // Calculate the average of the red, green, and blue values
            int grayscale =
                round((image[m][n].rgbtRed + image[m][n].rgbtGreen + image[m][n].rgbtBlue) / 3.0);
            
            // Set the red, green, and blue values to the calculated grayscale value
            image[m][n].rgbtRed = grayscale;
            image[m][n].rgbtGreen = grayscale;
            image[m][n].rgbtBlue = grayscale;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row of the image
    for (int m = 0; m < height; m++)
    {
        // Iterate only until the midpoint of the row to swap pixels
        for (int n = 0; n < width / 2; n++)
        {
            // Swap the pixel with its corresponding pixel on the other side of the row
            RGBTRIPLE swap = image[m][n];
            image[m][n] = image[m][width - n - 1];
            image[m][width - n - 1] = swap;
        }
    }
}

// Blurs image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; // Temporary copy of the image

    // Iterate over each pixel in the image
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            // Initialize totals for the RGB values and the count of neighboring pixels
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int count = 0;

            // Iterate over the neighboring pixels (3x3 grid centered around the current pixel)
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int new_m = m + i;
                    int new_n = n + j;

                    // Check if the neighboring pixel is within the image bounds
                    if (new_m >= 0 && new_m < height && new_n >= 0 && new_n < width)
                    {
                        // Accumulate the RGB values
                        totalRed += image[new_m][new_n].rgbtRed;
                        totalGreen += image[new_m][new_n].rgbtGreen;
                        totalBlue += image[new_m][new_n].rgbtBlue;
                        count++; // Keep track of how many valid neighbors
                    }
                }
            }

            // Compute the average RGB values and store them in the temporary array
            temp[m][n].rgbtRed = round(totalRed / (float) count);
            temp[m][n].rgbtGreen = round(totalGreen / (float) count);
            temp[m][n].rgbtBlue = round(totalBlue / (float) count);
        }
    }

    // Copy the blurred image back to the original array
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n] = temp[m][n];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; // Temporary copy of the image
    
    // Sobel operator kernels for detecting edges in x and y directions
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Iterate over each pixel in the image
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            // Initialize gradient values for RGB channels
            int RedX = 0, RedY = 0, GreenX = 0, GreenY = 0, BlueX = 0, BlueY = 0;

            // Iterate over the neighboring pixels (3x3 grid) for applying Sobel filter
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int new_m = m + i;
                    int new_n = n + j;

                    // Check if the neighboring pixel is within the image bounds
                    if (new_m >= 0 && new_m < height && new_n >= 0 && new_n < width)
                    {
                        // Apply the Gx and Gy kernels to the RGB channels
                        RedX += Gx[i + 1][j + 1] * image[new_m][new_n].rgbtRed;
                        RedY += Gy[i + 1][j + 1] * image[new_m][new_n].rgbtRed;
                        GreenX += Gx[i + 1][j + 1] * image[new_m][new_n].rgbtGreen;
                        GreenY += Gy[i + 1][j + 1] * image[new_m][new_n].rgbtGreen;
                        BlueX += Gx[i + 1][j + 1] * image[new_m][new_n].rgbtBlue;
                        BlueY += Gy[i + 1][j + 1] * image[new_m][new_n].rgbtBlue;
                    }
                }
            }

            // Compute the final gradient magnitude for each RGB channel using the Sobel formula
            int finalRed = round(sqrt((RedX * RedX) + (RedY * RedY)));
            int finalGreen = round(sqrt((GreenX * GreenX) + (GreenY * GreenY)));
            int finalBlue = round(sqrt((BlueX * BlueX) + (BlueY * BlueY)));

            // Clamp values to ensure they stay within [0, 255]
            // Clamp the red channel
            if (finalRed > 255)
            {
                temp[m][n].rgbtRed = 255;
            }
            else
            {
                temp[m][n].rgbtRed = finalRed;
            }

            // Clamp the green channel
            if (finalGreen > 255)
            {
                temp[m][n].rgbtGreen = 255;
            }
            else
            {
                temp[m][n].rgbtGreen = finalGreen;
            }

            // Clamp the blue channel
            if (finalBlue > 255)
            {
                temp[m][n].rgbtBlue = 255;
            }
            else
            {
                temp[m][n].rgbtBlue = finalBlue;
            }
        }
    }

    // Copy the edge-detected image back to the original array
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n] = temp[m][n];
        }
    }
}
