#include "bits/stdc++.h"
#include <chrono>
#include <thread>

// Function to apply rotation transformation about the X-axis
void tranformation_rotation_about_x_axis(std::vector<std::tuple<float, float, float>> &points, float theta)
{
    float cos_theta = std::cos(theta);
    float sin_theta = std::sin(theta);

    for (auto &point : points)
    {
        float y_dash = std::get<1>(point) * cos_theta - std::get<2>(point) * sin_theta;
        float z_dash = std::get<1>(point) * sin_theta + std::get<2>(point) * cos_theta;
        std::get<1>(point) = y_dash;
        std::get<2>(point) = z_dash;
    }
}

// Function to apply rotation transformation about the Y-axis
void tranformation_rotation_about_y_axis(std::vector<std::tuple<float, float, float>> &points, float theta)
{
    float cos_theta = std::cos(theta);
    float sin_theta = std::sin(theta);

    for (auto &point : points)
    {
        float x_dash = std::get<0>(point) * cos_theta + std::get<2>(point) * sin_theta;
        float z_dash = -std::get<0>(point) * sin_theta + std::get<2>(point) * cos_theta;
        std::get<0>(point) = x_dash;
        std::get<2>(point) = z_dash;
    }
}

// Normalize 3D coordinates to fit within the terminal dimensions
float normalizeX(float x, float width)
{
    return (x + 1.0f) * 0.5f * width;
}

float normalizeY(float y, float height)
{
    return (y + 1.0f) * 0.5f * height;
}

// Project 3D coordinates to 2D (orthographic projection)
std::pair<float, float> project3DTo2D(float x, float y, int width, int height)
{
    return {normalizeX(x, width), normalizeY(y, height)};
}

// Draw a point on the grid
void drawPoint(int x, int y, char **grid, int width, int height, float z, float max_z, float min_z)
{
    float one_third = min_z + (max_z - min_z) / 3;
    float two_third = one_third + (max_z - min_z) / 3;

    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        if (z < one_third)
        {
            grid[y][x] = '*';
        }
        else if (z < two_third)
        {
            grid[y][x] = 'O';
        }
        else if (z > two_third)
        {
            grid[y][x] = '0';
        }
    }
}

// Print the grid to the terminal
void printGrid(char **grid, int width, int height)
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
}

// Function to reset the grid
void resetGrid(char **grid, int width, int height)
{
    for (int i = 0; i < height; ++i)
    {
        std::fill(grid[i], grid[i] + width, ' ');
    }
}

void animation(std::vector<std::tuple<float, float, float>> points, int width, int height, char **grid)
{
    float theta = 0;

    while (true)
    {
        resetGrid(grid, width, height);

        tranformation_rotation_about_y_axis(points, theta);

        // Project and draw each point on the grid
        float max_z = INT_MIN;
        float min_z = INT_MAX;
        for (const auto &point : points)
        {
            if (max_z <= std::get<2>(point))
            {
                max_z = std::get<2>(point);
            }
            if (min_z >= std::get<2>(point))
            {
                min_z = std::get<2>(point);
            }
        }

        for (const auto &point : points)
        {

            auto [x, y, z] = point;
            auto [px, py] = project3DTo2D(x, y, width, height);
            drawPoint(static_cast<int>(px), static_cast<int>(py), grid, width, height, float(z), max_z, min_z);
        }

        // Print the grid to the terminal
        printGrid(grid, width, height);

        if (theta > 2 * M_PI)
        {
            theta = 0;
        }
        theta += (0.01) * M_PI / 90.0f;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    const int width = 80;    // Terminal width
    const int height = 24;   // Terminal height
    float theta_Deg = 90.0f; // Convert degrees to radians
    float theta = theta_Deg * M_PI / 180.0f;

    // Create the grid and initialize it with spaces
    char **grid = new char *[height];
    for (int i = 0; i < height; ++i)
    {
        grid[i] = new char[width];
        std::fill(grid[i], grid[i] + width, ' ');
    }

    const float R = 0.6f; // Major radius of the torus
    const float r = 0.2f; // Minor radius of the torus
    const int numSteps = 100;

    // Generate points on the torus surface
    std::vector<std::tuple<float, float, float>> points;
    for (int i = 0; i < numSteps; ++i)
    {
        float theta_i = i * 2.0f * M_PI / numSteps;
        for (int j = 0; j < numSteps; ++j)
        {
            float phi = j * 2.0f * M_PI / numSteps;
            float x = (R + r * std::cos(theta_i)) * std::cos(phi);
            float y = (R + r * std::cos(theta_i)) * std::sin(phi);
            float z = r * std::sin(theta_i);
            points.emplace_back(x, y, z);
        }
    }

    // Uncomment this line to start the animation
    animation(points, width, height, grid);

    // Clean up
    for (int i = 0; i < height; ++i)
    {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}
