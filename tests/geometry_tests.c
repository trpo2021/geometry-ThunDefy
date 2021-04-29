#include "ctest.h"
#include "libgeometry/Source.c"

CTEST(Check_commadn, Error_cmd)
{
    double x=0, y=0, r=0;
    char str[] = {"Krug(2 4, 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_no_1st_bracket)
{
    double x=0, y=0, r=0;
    char str[] = {"circle 2 4, 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_no_2nd_bracket)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(2 4, 2"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_no_comma)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(2 4 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_wrong_format)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(Y 4, 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_wrong_format2)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(2 &, 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_wrong_format3)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(/ _, %)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_wrong_format4)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(( 2 4, 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_extra_comma)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(2, 4, 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_extra_comma2)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(2, , 4 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_extra_comma3)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(, , , , , , , , , , , 2 4 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_extra_token)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(2 4, 8 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_extra_token2)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(2 8 4, 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_extra_token3)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(2 8  9 1 1 5 5 4, 2 7 3 8 5 6 6 6)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_extra_token4)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(2 4, 2) 92"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_extra_token5)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(2 4, 2) circle(2 4, 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_miss_token_X)
{
    double x=0, y=0, r=0;
    char str[] = {"circle( 4, 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_miss_token_Y)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(2  , 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_miss_token_R)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(2 4, )"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Error_R_is_zero)
{
    double x=0, y=0, r=0;
    char str[] = {"circle(2 4, 0)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, All_good)
{
    double x=0, y=0, r=0;
    char str[] = {"Circle(2 4, 2)"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 1;

    ASSERT_EQUAL(expected, real);
}

CTEST(Check_commadn, Exit)
{
    double x=0, y=0, r=0;
    char str[] = {"F"};
    int real = Check_commadn(str,&x,&y,&r);

    int expected = 2;

    ASSERT_EQUAL(expected, real);
}

CTEST(interects, count_of_inters_0)
{
	FILE* data;
	int num_fig = 1;
	char str[] = {"Circle(2 4, 2)"};	
	data = fopen("circles_data.txt", "w");
	fclose(data);	
	double x = 0, y = 0, r = 0;
	Check_commadn(str, &x, &y, &r);
	save_data(num_fig, x, y, r);
	interects(num_fig);
    	int expected = 0;
    	int real = interects(num_fig);

    ASSERT_EQUAL(expected, real);
}

CTEST(interects, count_of_inters_1)
{
	FILE* data;
	int num_fig = 2;

	char circle1[] = {"Circle(3 4, 2)"}, circle2[] = {"Circle(4 4, 2)"};
	
	data = fopen("circles_data.txt", "w");
	fclose(data);
	
	double x = 0, y = 0, r = 0;
	Check_commadn(circle1, &x, &y, &r);
	save_data(num_fig, x, y, r);
	
	x = 0; y = 0; r = 0;
	Check_commadn(circle2, &x, &y, &r);
	save_data(num_fig, x, y, r);
	
	interects(num_fig);
    	int expected = 1;
    	int real = interects(num_fig);

    ASSERT_EQUAL(expected, real);
}

CTEST(interects, count_of_inters_3)
{
	FILE* data;
	int num_fig = 3;
	
	char circle1[] = {"Circle(2 4, 2)"}, circle2[] = {"Circle(4 4, 2)"}, 
	circle3[] = {"Circle(5 8, 7)"};
	
	data = fopen("circles_data.txt", "w");
	fclose(data);
	
	double x = 0, y = 0, r = 0;
	Check_commadn(circle1, &x, &y, &r);
	save_data(num_fig, x, y, r);
	
	x = 0; y = 0; r = 0;
	Check_commadn(circle2, &x, &y, &r);
	save_data(num_fig, x, y, r);
	
	x = 0; y = 0; r = 0;
	Check_commadn(circle3, &x, &y, &r);
	save_data(num_fig, x, y, r);
	
	interects(num_fig);
    	int expected = 3;
    	int real = interects(num_fig);

    ASSERT_EQUAL(expected, real);
}

CTEST(interects, count_of_inters_0_with_few_circle)
{
	FILE* data;
	int num_fig = 4;

	char circle1[] = {"Circle(2 2, 2)"}, circle2[] = {"Circle(8 8, 2)"},
	circle3[] = {"Circle(16 16, 2)"}, circle4[] = {"Circle(32 32, 2)"};
	
	data = fopen("circles_data.txt", "w");
	fclose(data);
	
	double x = 0, y = 0, r = 0;
	Check_commadn(circle1, &x, &y, &r);
	save_data(num_fig, x, y, r);	
	x = 0; y = 0; r = 0;
	Check_commadn(circle2, &x, &y, &r);
	save_data(num_fig, x, y, r);
	x = 0; y = 0; r = 0;
	Check_commadn(circle3, &x, &y, &r);
	save_data(num_fig, x, y, r);
	x = 0; y = 0; r = 0;
	Check_commadn(circle4, &x, &y, &r);
	save_data(num_fig, x, y, r);
	
	interects(num_fig);
    	int expected = 0;
    	int real = interects(num_fig);

    ASSERT_EQUAL(expected, real);
}
