#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Assign the R, G, and B of each pixel to the current average of the three
            RGBTRIPLE current_rgb = image[row][col];
            int average_value = (int)((current_rgb.rgbtBlue + current_rgb.rgbtGreen + current_rgb.rgbtRed) / 3.0 + 0.5);

            RGBTRIPLE new_rgb = {.rgbtRed = average_value, .rgbtGreen = average_value, .rgbtBlue = average_value};

            image[row][col] = new_rgb;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2.0; col++)
        {
            // Swap each pixel with the pixel on the opposite column (reflect across a vertical line through the middle of the image)
            RGBTRIPLE temp = image[row][col];
            image[row][col] = image[row][width - col - 1];
            image[row][width - col - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Where the new RGBTRIPLEs are stored so that all operations are performed on ORIGINAL RGB values
    RGBTRIPLE new_image[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Assign the R, G, and B values of each pixel to the average R, G, and B values of the 3x3 square of pixels centered around it
            RGBTRIPLE current_rgb = image[row][col];

            int sum_red = 0, sum_green = 0, sum_blue = 0;
            double num_counted = 0; // Stored as a double so the rounding works later on

            for (int r = row - 1; r <= row + 1; r++)
            {
                for (int c = col - 1; c <= col + 1; c++)
                {
                    if (r >= 0 && r < height && c >= 0 && c < width)
                    {
                        RGBTRIPLE adjacent_rgb = image[r][c];

                        sum_red += adjacent_rgb.rgbtRed;
                        sum_green += adjacent_rgb.rgbtGreen;
                        sum_blue += adjacent_rgb.rgbtBlue;

                        num_counted++;
                    }
                }
            }

            // The final R, G, and B values, [r, g, b]
            int final_rgb[3];

            final_rgb[0] = (int)(sum_red / num_counted + 0.5);
            final_rgb[1] = (int)(sum_green / num_counted + 0.5);
            final_rgb[2] = (int)(sum_blue / num_counted + 0.5);

            for (int i = 0; i < 3; i++)
            {
                if (final_rgb[i] < 0)
                {
                    final_rgb[i] = 0;
                }
                else if (final_rgb[i] > 255)
                {
                    final_rgb[i] = 255;
                }
            }

            RGBTRIPLE new_rgb = {.rgbtRed = final_rgb[0], .rgbtGreen = final_rgb[1], .rgbtBlue = final_rgb[2]};

            // Save this new RGB value to its proper location in the image, but in the duplicate 2D array
            new_image[row][col] = new_rgb;
        }
    }

    // Replace the old RGB values with new RGB valyes
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = new_image[row][col];
        }
    }
}


int clamp(int value, int min, int max)
{
    if (value >= max)
    {
        return max;
    }
    else if (value <= min)
    {
        return min;
    }
    else
    {
        return value;
    }
}

// Kernel initialization
int kernelX[3][3] =
        {
                {-1, 0, 1},
                {-2, 0, 2},
                {-1, 0, 1}
        };

int kernelY[3][3] =
        {
                {-1, -2, -1},
                {0,  0,  0},
                {1,  2,  1}
        };

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Where the new RGBTRIPLEs are stored so that all operations are performed on ORIGINAL RGB values
    RGBTRIPLE new_image[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Assign the R, G, and B values of each pixel to the weighted sum using the kernel's values as weights
            RGBTRIPLE current_rgb = image[row][col];

            // The computed Gx and Gy values the for R, G, and B channels, respectively
            int Gx[3] = {0, 0, 0}, Gy[3] = {0, 0, 0};
            int starting_r = row - 1, starting_c = col - 1;

            for (int r = starting_r; r <= row + 1; r++)
            {
                for (int c = starting_c; c <= col + 1; c++)
                {
                    if (r >= 0 && r < height && c >= 0 && c < width)
                    {
                        RGBTRIPLE this_rgb = image[r][c];

                        int gx_factor = kernelX[r - starting_r][c - starting_c];
                        int gy_factor = kernelY[r - starting_r][c - starting_c];

                        // Update Gx and Gy
                        Gx[0] += this_rgb.rgbtRed * gx_factor;
                        Gx[1] += this_rgb.rgbtGreen * gx_factor;
                        Gx[2] += this_rgb.rgbtBlue * gx_factor;

                        Gy[0] += this_rgb.rgbtRed * gy_factor;
                        Gy[1] += this_rgb.rgbtGreen * gy_factor;
                        Gy[2] += this_rgb.rgbtBlue * gy_factor;
                    }
                }
            }

            // Gx and Gy have been calculated, now determine the final channel values

            // The final RGB values, [r, g, b]
            int final_rgb[3];

            for (int i = 0; i < 3; i++)
            {
                int this_value = (int)(sqrt(pow(Gx[i], 2) + pow(Gy[i], 2)) + 0.5);

                if (this_value < 0)
                {
                    this_value = 0;
                }
                else if (this_value > 255)
                {
                    this_value = 255;
                }

                final_rgb[i] = this_value;
            }

            // All the values have been determined, create and save new RGBTRIPLE
            RGBTRIPLE new_rgb = {.rgbtRed = final_rgb[0], .rgbtGreen = final_rgb[1], .rgbtBlue = final_rgb[2]};

            // Save this new RGB value to its proper location in the image, but in the duplicate 2D array
            new_image[row][col] = new_rgb;
        }
    }

    // Replace the old RGB values with new RGB valyes
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = new_image[row][col];
        }
    }
}
