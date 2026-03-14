#include <stdio.h>

/*
 * Program: Rectangle Calculator
 * This program calculates the area and perimeter of a rectangle
 * based on user input for length and width.
 */

int main() {
    // Declare variables for rectangle dimensions and results
    double length;
    double width;
    double area;
    double perimeter;

    // Prompt user for input
    printf("Enter the length of the rectangle: ");
    scanf("%lf", &length);

    printf("Enter the width of the rectangle: ");
    scanf("%lf", &width);

    // Validate input: ensure positive values
    if (length <= 0 || width <= 0) {
        printf("Error: Length and width must be positive numbers.\n");
        return 1; // Return error code
    }

    // Calculate area and perimeter
    area = length * width;
    perimeter = 2 * (length + width);

    // Display results
    printf("\n--- Results ---\n");
    printf("Length: %.2f\n", length);
    printf("Width: %.2f\n", width);
    printf("Area: %.2f\n", area);
    printf("Perimeter: %.2f\n", perimeter);

    return 0; // Successful execution
}
