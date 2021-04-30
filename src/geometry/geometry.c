#include "LibSource.h"
#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE* data;
    int all_fine = 1;
    int num_fig = -1;
    int check_result = 0;

    printf("\nEnter the point X , point Y and radius for each "
           "circle.\nFor example: circle(0 0, 1.5)\n");

    data = fopen("circles_data.txt", "w");
    fclose(data);

    while (1) {
        num_fig++;
        double x = 0, y = 0, r = 0;
        char input[80];
        printf("\n~~~~~~~~~~~~~~~~~~~\n");
        gets(input);
        printf("~~~~~~~~~~~~~~~~~~~\n");

        check_result = Check_commadn(input, &x, &y, &r);
        if (check_result == 0) {
            all_fine = 0;
            break;
        }
        if (check_result == 2)
            break;
        if (check_result == 1) {
            save_data(num_fig, x, y, r);
            AreaAndPer(r);
            printf("\nIf you're done enter F\n");
        }
    }
    if (all_fine)
        interects(num_fig);
}