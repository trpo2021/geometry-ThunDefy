#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AreaAndPer(double r) {
	const double pi = 3.1415926535;
	double area = pi * (r * r);
	double per = 2 * pi * r;
	printf("Area = %5.3lf\n", area);
	printf("Perimetr = %5.3lf\n", per);
}

char* strlwr(char* str) // Функция которая переводит все буквы в нижний регистр
{
	unsigned char* p = (unsigned char*)str;

	while (*p) {
		*p = tolower((unsigned char)*p);
		p++;
	}

	return str;
}

int interects(int num_fig)
{
	int n = 0, i, j, i_inf = -1;
	int Anum = 0, Ax1 = 0, Ay1 = 0, Ax2 = 0, Ay2 = 0,
		Bnum = 0, Bx1 = 0, By1 = 0, Bx2 = 0, By2 = 0;
	int count_interects = 0;

	char ch, * info[500];
	FILE* dt;

	dt = fopen("circles_data.txt", "r");

	while ((ch = getc(dt)) != EOF)
	{
		if (ch != ' '); else n++;
	}
	rewind(dt);

	for (i = 0; i < n; i++) {
		info[i] = (char*)malloc(128 * sizeof(char));
		fscanf(dt, "%s", info[i]);
	}

	rewind(dt);

	double** data;
	data = (double**)malloc(num_fig * sizeof(double));
	for (i = 0; i < num_fig; i++) {
		data[i] = (double*)malloc(4 * sizeof(double));
		i_inf++;
		for (j = 0; j < 4; j++) {
			data[i][j] = atof(info[i_inf]);
			i_inf++;
		}
	}

	for (i = 0; i < num_fig; i++) {
		Anum = data[i][0];
		Ax1 = data[i][1] + data[i][3];
		Ax1 = data[i][2] + data[i][3];
		Ax2 = data[i][1] - data[i][3];
		Ax2 = data[i][2] - data[i][3];
		for (j = i + 1; j < num_fig; j++) {
			Bnum = data[j][0];
			Bx1 = data[j][1] + data[j][3];
			Bx1 = data[j][2] + data[j][3];
			Bx2 = data[j][1] - data[j][3];
			Bx2 = data[j][2] - data[j][3];
			if (Ax1 >= Bx2 && Ax2 <= Bx1 && Ay1 >= By2 && Ay2 <= By1){
				count_interects++;
				printf("\n~ Circle %d intersects circle %d ~\n", Anum, Bnum);
				}
		}
	}
	fclose(dt);
	return count_interects;
}

int Check_commadn(char input[], double* x, double* y, double* r)
{
	int  i, j, j2, in = 1, end = 0,
		have_bracket = 0, comma = 0, no_comma = 1, miss_token = 0, XtoY = 0;
	char* cmd, * chX, * chY, * chR;

	char intg[] = "1234567890",
		letter[]
		= "QqWwEeRrTtYyUuIiOoPpAaSsDdFfGgHhJjKkLlZzXxCcVvBbNnMm~!@#№$;%%^:"
		"&?*=+_}{|)(?><\"\'";

	cmd = malloc(200);
	strcpy(cmd, input);

	cmd = strtok(cmd, "(");
	cmd = strtok(cmd, " ");
	strlwr(cmd);

	if (strcmp(cmd, "f") == 0 || strcmp(cmd, "F") == 0) {
		printf("\nData entry completed.\n");
		return 2;
	}

	if (strcmp(cmd, "circle") != 0) {
		printf("expected 'circle' not a '%s'\n", cmd);
		return 0;
	}

	for (i = 0; input[i] != '\0'; i++) {
		if (input[i] == '(')
			have_bracket = 1;
		end++;
	}

	if (have_bracket == 0) {
		printf("Error: expected '('\n");
		return 0;
	}

	if (have_bracket) {
		if (input[end - 1] != ')') {
			printf("Error at column %d: expected ')' in the end of function \n", end);
			return 0;
		}

		for (i = 0; input[i] != '('; i++)
			in++;

		for (i = in; input[i] != ')'; i++) {
			if (input[i] == ',')
				no_comma = 0;
		}
		if (no_comma) {
			printf("Error: expected ','\n");
			return 0;
		}

		for (; in != end - 1; in++) { // Проверки в скобках (  )
			for (j = 0; j < (int)sizeof(letter) - 1; j++) {
				if (input[in] == letter[j]) {
					printf("Error at column %d expected '<integer>' or "
						"'<double>' , now '%c'\n",
						in,
						input[in]);
					return 0;
				}
			}

			if (input[in] == ',') {
				comma++;
				if (comma > 1) {
					printf("Error at column %d extra ','\n", in);
					return 0;
				}
			}
		}
	}

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
		for (j = 0; j < (int)sizeof(intg) - 1; j++) {
			if (chX[i] == intg[j]) miss_token++;
		}
	}
	if (miss_token == 0) {
		printf("Error : miss token X\n"); return 0;
	}
	miss_token = 0;

	for (i = 0; i < size; i++) {
		for (j = 0; j < (int)sizeof(intg) - 1; j++) {
			if (chY[i] == intg[j]) miss_token++;
		}
	}
	if (miss_token == 0) {
		printf("Error : miss token Y\n");
		return 0;
	}
	miss_token = 0;

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
		for (j = 0; j < (int)sizeof(intg) - 1; j++) {
			if (chR[i] == intg[j]) miss_token++;
		}
	}
	if (miss_token == 0) {
		printf("Error : miss token R\n"); return 0;
	}

	*x = (double)atof(chX);
	*y = (double)atof(chY);
	*r = (double)atof(chR);

	if (*r < 0 || *r == 0) { printf("Error : token R must be more than zero \n"); return 0; }

	printf("\nCmd = %s\n", cmd);
	printf("\nX = %5.3lf\n", *x);
	printf("Y = %5.3lf\n", *y);
	printf("R = %5.3lf\n", *r);

	free(chX);
	free(chY);
	free(chR);
	free(cmd);

	return 1;
}

void save_data(int num_fig, double x, double y, double r) {
	FILE* data;
	data = fopen("circles_data.txt", "a");
	fprintf(data, "%d", num_fig);
	fputs(" ", data);
	fprintf(data, "%4.3f", x);
	fputs(" ", data);
	fprintf(data, "%4.3f", y);
	fputs(" ", data);
	fprintf(data, "%4.3f", r);
	fputs(" ", data);
	fputs("|", data);
	fputs(" ", data);
	fclose(data);
}

