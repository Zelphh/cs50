#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avrg =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = avrg;
            image[i][j].rgbtGreen = avrg;
            image[i][j].rgbtRed = avrg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE buffer = image[i][j];

            image[i][j] = image[i][(width - 1) - j];

            image[i][(width - 1) - j] = buffer;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;
            float pixelCounter = 0.0;

            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    if (i + h >= 0 && i + h < height && j + w >= 0 && j + w < width)
                    {
                        redSum += copy[i + h][j + w].rgbtRed;
                        greenSum += copy[i + h][j + w].rgbtGreen;
                        blueSum += copy[i + h][j + w].rgbtBlue;
                        pixelCounter++;
                    }
                }
            }

            image[i][j].rgbtRed = round(redSum / pixelCounter);
            image[i][j].rgbtGreen = round(greenSum / pixelCounter);
            image[i][j].rgbtBlue = round(blueSum / pixelCounter);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    int redDiference; // sqrt(pow(2, gx) + pow(2, gy))
    int greenDiference;
    int blueDiference;

    for (int i = 0; i < height; i++) // Loop through the columns of image
    {
        for (int j = 0; j < width; j++) // Loop through the lines of image
        {
            int redGx = 0;
            int greenGx = 0;
            int blueGx = 0;

            int redGy = 0;
            int greenGy = 0;
            int blueGy = 0;

            // Loop araund one pixel (3x3)
            for (int h = -1; h < 2; h++) // Columns
            {
                for (int w = -1; w < 2; w++) // Lines
                {
                    if (i + h >= 0 && i + h < height && j + w >= 0 && j + w < width)
                    {
                        redGx += copy[i + h][j + w].rgbtRed * gx[h + 1][w + 1];
                        redGy += copy[i + h][j + w].rgbtRed * gy[h + 1][w + 1];

                        greenGx += copy[i + h][j + w].rgbtGreen * gx[h + 1][w + 1];
                        greenGy += copy[i + h][j + w].rgbtGreen * gy[h + 1][w + 1];

                        blueGx += copy[i + h][j + w].rgbtBlue * gx[h + 1][w + 1];
                        blueGy += copy[i + h][j + w].rgbtBlue * gy[h + 1][w + 1];
                    }
                }
            }

            redDiference = round(sqrt(pow(redGx, 2) + pow(redGy, 2)));
            if (redDiference > 255)
                redDiference = 255;

            greenDiference = round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)));
            if (greenDiference > 255)
                greenDiference = 255;

            blueDiference = round(sqrt(pow(blueGx, 2) + pow(blueGy, 2)));
            if (blueDiference > 255)
                blueDiference = 255;

            image[i][j].rgbtRed = redDiference;
            image[i][j].rgbtGreen = greenDiference;
            image[i][j].rgbtBlue = blueDiference;
        }
    }
}
