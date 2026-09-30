 #include <stdio.h>
#include <stdlib.h>
#include <math.h>

double num_comput_integral_l_re(double left_boundary_a,
                                double right_boundary_b,
                                unsigned int intervals);

double num_comput_integral_r_re(double left_boundary_a,
                                double right_boundary_b,
                                unsigned int intervals);

double num_comput_integral_trapezoid(double left_boundary_a,
                                     double right_boundary_b,
                                     unsigned int intervals);

double num_comput_integral_Simps(double left_boundary_a,
                                 double right_boundary_b,
                                 unsigned int intervals);

double integrand_expression(double x);

int main()
{
    double left_boundary_a = 0;
    double right_boundary_b = 0;
    double measurement_error = 0;
    double integral_s = 0;
    double I1 = 0;
    double I2 = 0;
    double Delta = 0;

    unsigned int intervals;
    unsigned int N;
    unsigned int variant;

    while (1)
    {
        printf("\nEnter the left boundary\n");
        printf("a = ");
        scanf("%lf", &left_boundary_a);

        printf("\nEnter the right boundary\n");
        printf("b = ");
        scanf("%lf", &right_boundary_b);

        do
        {
            printf("\nEnter the number of partition intervals (N > 0)\n");
            printf("N = ");
            scanf("%u", &intervals);

        }
        while (intervals == 0);

        do
        {
            printf("\nEnter the measurement error");
            printf("\n0.00001 <= error <= 0.001");
            printf("\nerror = ");

            scanf("%lf", &measurement_error);

        }
        while (measurement_error < 0.00001 ||
               measurement_error > 0.001);

        do
        {
            printf("\nChoose the method of calculating:\n");

            printf("1. Left Rectangles\n");
            printf("2. Right Rectangles\n");
            printf("3. Trapezoid method\n");
            printf("4. Simpson method\n");

            printf("Variant = ");

            scanf("%u", &variant);

            if (variant < 1 || variant > 4)
            {
                printf("\nYou are mistaken\n");
            }

        }
        while (variant < 1 || variant > 4);

        if (variant == 4)
        {
            while (intervals % 2 != 0)
            {
                printf("\nFor Simpson method N must be even");
                printf("\nEnter N again: ");

                scanf("%u", &intervals);
            }
        }

        switch (variant)
        {
            case 1:
            {
                integral_s =
                    num_comput_integral_l_re(left_boundary_a,
                                             right_boundary_b,
                                             intervals);

                break;
            }

            case 2:
            {
                integral_s =
                    num_comput_integral_r_re(left_boundary_a,
                                             right_boundary_b,
                                             intervals);

                break;
            }

            case 3:
            {
                integral_s =
                    num_comput_integral_trapezoid(left_boundary_a,
                                                  right_boundary_b,
                                                  intervals);

                break;
            }

            case 4:
            {
                integral_s =
                    num_comput_integral_Simps(left_boundary_a,
                                              right_boundary_b,
                                              intervals);

                break;
            }
        }

        printf("\n----------------------------------");

        printf("\na = %.2lf", left_boundary_a);
        printf("\nb = %.2lf", right_boundary_b);

        printf("\nN = %u", intervals);

        printf("\nIntegral = %.10lf", integral_s);

        printf("\nMeasurement error = %.8lf",
               measurement_error);

        printf("\n----------------------------------");

        N = intervals;

        while (1)
        {
            switch (variant)
            {
                case 1:
                {
                    I1 =
                        num_comput_integral_l_re(left_boundary_a,
                                                 right_boundary_b,
                                                 N);

                    I2 =
                        num_comput_integral_l_re(left_boundary_a,
                                                 right_boundary_b,
                                                 N + 2);

                    break;
                }

                case 2:
                {
                    I1 =
                        num_comput_integral_r_re(left_boundary_a,
                                                 right_boundary_b,
                                                 N);

                    I2 =
                        num_comput_integral_r_re(left_boundary_a,
                                                 right_boundary_b,
                                                 N + 2);

                    break;
                }

                case 3:
                {
                    I1 =
                        num_comput_integral_trapezoid(left_boundary_a,
                                                      right_boundary_b,
                                                      N);

                    I2 =
                        num_comput_integral_trapezoid(left_boundary_a,
                                                      right_boundary_b,
                                                      N + 2);

                    break;
                }

                case 4:
                {
                    I1 =
                        num_comput_integral_Simps(left_boundary_a,
                                                  right_boundary_b,
                                                  N);

                    I2 =
                        num_comput_integral_Simps(left_boundary_a,
                                                  right_boundary_b,
                                                  N + 2);

                    break;
                }
            }

            Delta = fabs(I1 - I2);

            if (Delta <= measurement_error)
            {
                break;
            }

            N += 2;
        }

        printf("\n\nRequired number of intervals:");

        printf("\nN = %u", N);

        printf("\nI1 = %.10lf", I1);

        printf("\nI2 = %.10lf", I2);

        printf("\nDelta = %.10lf", Delta);

        printf("\n\n");
    }

    return 0;
}

double num_comput_integral_l_re(double left_boundary_a,
                                double right_boundary_b,
                                unsigned int intervals)
{
    double integral_s = 0;
    double x = 0;
    double h;

    unsigned int i;

    h = (right_boundary_b - left_boundary_a) / intervals;

    x = left_boundary_a;

    for (i = 0; i < intervals; i++)
    {
        integral_s += integrand_expression(x);

        x += h;
    }

    return integral_s * h;
}

double num_comput_integral_r_re(double left_boundary_a,
                                double right_boundary_b,
                                unsigned int intervals)
{
    double integral_s = 0;
    double x = 0;
    double h;

    unsigned int i;

    h = (right_boundary_b - left_boundary_a) / intervals;

    x = left_boundary_a + h;

    for (i = 0; i < intervals; i++)
    {
        integral_s += integrand_expression(x);

        x += h;
    }

    return integral_s * h;
}

double num_comput_integral_trapezoid(double left_boundary_a,
                                     double right_boundary_b,
                                     unsigned int intervals)
{
    double integral_s = 0;
    double x = 0;
    double h;

    unsigned int i;

    h = (right_boundary_b - left_boundary_a) / intervals;

    integral_s =
        (integrand_expression(left_boundary_a) +
         integrand_expression(right_boundary_b)) / 2.0;

    for (i = 1; i < intervals; i++)
    {
        x = left_boundary_a + i * h;

        integral_s += integrand_expression(x);
    }

    return integral_s * h;
}

double num_comput_integral_Simps(double left_boundary_a,
                                 double right_boundary_b,
                                 unsigned int intervals)
{
    double integral_s = 0;
    double x = 0;
    double h;

    unsigned int i;

    h = (right_boundary_b - left_boundary_a) / intervals;

    integral_s =
        integrand_expression(left_boundary_a) +
        integrand_expression(right_boundary_b);

    for (i = 1; i < intervals; i++)
    {
        x = left_boundary_a + i * h;

        if (i % 2 != 0)
        {
            integral_s +=
                4 * integrand_expression(x);
        }
        else
        {
            integral_s +=
                2 * integrand_expression(x);
        }
    }

    return integral_s * h / 3.0;
}

double integrand_expression(double x)
{
    return 1.0 / (pow(x, 2) - 1.0);
}