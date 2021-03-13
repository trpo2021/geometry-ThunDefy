#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* strlwr(char* str) // Функция которая переводит все буквы в нижний регистр
{
	unsigned char* p = (unsigned char*)str;

	while (*p) {
		*p = tolower((unsigned char)*p);
		p++;
	}

	return str;
}

int main()
{
	char intg[] = "1234567890",
		letter[]

		= "QqWwEeRrTtYyUuIiOoPpAaSsDdFfGgHhJjKkLlZzXxCcVvBbNnMm~!@#№$;%%^:"
		"&?*=+_}{|)(?><\"\'";

	printf("\nEnter the point X , point Y and radius for each "
		"circle.\nFor example: circle(0 0, 1.5)\n");

	while (1) {
		char input[80];
		int  i, j, j2, in = 1, end = 0,
			fl1 = 0, com = 0, err1 = 0, err3 = 0, err4 = 0,
			err6 = 1, err7 = 0, XtoY = 0;
		char* cmd, * chX, * chY, * chR;

		printf("\n~~~~~~~~~~~~~~~~~~~\n");

		gets(input);

		cmd = malloc(200);
		strcpy(cmd, input);

		cmd = strtok(cmd, "(");
		cmd = strtok(cmd, " ");
		strlwr(cmd);
		if (strcmp(cmd, "f") == 0 || strcmp(cmd, "F") == 0) {
			printf("\nData entry completed.\n");
			break;
		}

		if (strcmp(cmd, "circle") != 0) {
			printf("expected 'circle' not a '%s'\n", cmd);
			return 0;
		}

		for (i = 0; input[i] != '\0'; i++) {
			if (input[i] == '(')
				fl1 = 1;
			end++;
		}

		if (fl1 == 0) {
			printf("Error: expected '('\n");
			err1 = 1;
		}

		if (fl1 == 1) {
			if (input[end - 1] != ')') {
				printf("Error at column %d: expected ')' in the end of function\n", end);
				return 0;
			}

			for (i = 0; input[i] != '('; i++)
				in++;

			for (i = in; input[i] != ')'; i++) {
				if (input[i] == ',')
					err6 = 0;
			}
			if (err6 == 1) {
				printf("Error: expected ','\n");
				return 0;
			}

			for (; in != end - 1; in++) { // Проверки в скобках (  )
				for (j = 0; j < sizeof(letter) - 1; j++) {
					if (input[in] == letter[j]) {
						printf("Error at column %d expected '<integer>' or "
							"'<double>' , now '%c'\n",
							in,
							input[in]);
						err3 = 1;
					}
				}

				if (input[in] == ',') {
					com++;
					if (com > 1) {
						printf("Error at column %d extra ','\n", in);
						err4 = 1;
					}
				}
			}
		}

		if (err1 == 0 && err3 == 0 && err4 == 0 && err6 == 0) {
			for (i = 0, in = 0; input[i] != '('; i++)
				in++;
			chX = malloc(10 * sizeof(int));
			chY = malloc(10 * sizeof(int));
			int size = 10 * sizeof(int) - 1;
			in++;
			for (j = 0, j2 = 0; input[in] != ','; in++) {
				if (XtoY == 0) {
					chX[j] = input[in];
					j++;
					if (atoi(chX) != 0 && input[in] == ' ')
						XtoY = 1;
				}
				if (XtoY == 1) {
					chY[j2] = input[in];
					j2++;
					if (atoi(chX) != 0 && atoi(chY) != 0 && input[in] == ' ') {
						for (i = in; input[i] != ','; i++) {
							if (input[i] != ' ') {
								printf("Error at column %d: unexpected token\n",
									i);
								return 0;
							}
						}
					}
				}
			}
			for (i = 0; i < size; i++) {
				for (j = 0; j < sizeof(intg) - 1; j++) {
					if (chX[i] == intg[j]) err7++;
				}
			}
			if (err7 == 0) {
				printf("Error : miss token X\n"); return 0;
			}
			err7 = 0;

			for (i = 0; i < size; i++) {
				for (j = 0; j < sizeof(intg) - 1; j++) {
					if (chY[i] == intg[j]) err7++;
				}
			}
			if (err7 == 0) {
				printf("Error : miss token Y\n");
				return 0;
			}
			err7 = 0;

			chR = malloc(10);
			for (j = 0, in++; input[in] != ')'; in++) {
				chR[j] = input[in];
				j++;

				if (atof(chR) != 0 && input[in] == ' ') {
					for (i = in; input[i] != ')'; i++) {
						if (input[i] != ' ') {
							printf("Error at column %d: unexpected token\n", i);
							return 0;
						}
					}
				}
			}

			for (i = 0; i < size; i++) {
				for (j = 0; j < sizeof(intg) - 1; j++) {
					if (chR[i] == intg[j]) err7++;
				}
			}
			if (err7 == 0) {
				printf("Error : miss token R\n"); return 0;
			}

			double x = (double)atof(chX);
			double y = (double)atof(chY);
			double r = (double)atof(chR);
			if (r < 0 || r == 0) { printf("Error : token R must be more than zero \n"); return 0; }

			printf("\nCmd = %s\n", cmd);
			printf("\nX = %5.3lf\n", x);
			printf("Y = %5.3lf\n", y);
			printf("R = %5.3lf\n", r);
			printf("\nIf you're done enter F\n");

			free(chX);
			chX=NULL;
			free(chY);
			chY=NULL;
			free(chR);
			chR=NULL;
			free(cmd);
			cmd=NULL;
		}
		else
			return 0;
	}
}
