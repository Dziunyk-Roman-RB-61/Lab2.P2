#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//----------------Оголошення прототипів функцій----------------

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


//----------------Головна функція програми----------------

int main()
{
//----------------Оголошення та ініціалізація змінних----------------

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


//----------------Організація багаторазового виконання програми----------------

    while (1)
    {
 //----------------Введення лівої межі інтегрування----------------

        printf("\nEnter the left boundary\n");
        printf("a = ");
        scanf("%lf", &left_boundary_a);


        //----------------Введення правої межі інтегрування----------------

        printf("\nEnter the right boundary\n");
        printf("b = ");
        scanf("%lf", &right_boundary_b);


//----------------Введення кількості проміжків розбиття----------------

        do
        {
            printf("\nEnter the number of partition intervals (N > 0)\n");
            printf("N = ");
            scanf("%u", &intervals);

        }
        while (intervals == 0);

//----------------Введення заданої похибки обчислення----------------

        do
        {
            printf("\nEnter the measurement error");
            printf("\n0.00001 <= error <= 0.001");
            printf("\nerror = ");

            scanf("%lf", &measurement_error);

        }
        while (measurement_error < 0.00001 ||
               measurement_error > 0.001);


//----------------Введення варіанту методу обчислення----------------

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


        //----------------Перевірка кількості проміжків для методу Сімпсона----------------

        if (variant == 4)
        {
            while (intervals % 2 != 0)
            {
                printf("\nFor Simpson method N must be even");
                printf("\nEnter N again: ");

                scanf("%u", &intervals);
            }
        }


//----------------Вибір методу обчислення визначеного інтеграла----------------

        switch (variant)
        {
//----------------Обчислення методом лівих прямокутників----------------

            case 1:
            {
                integral_s =
                    num_comput_integral_l_re(left_boundary_a,
                                             right_boundary_b,
                                             intervals);

                break;
            }


//----------------Обчислення методом правих прямокутників----------------

            case 2:
            {
                integral_s =
                    num_comput_integral_r_re(left_boundary_a,
                                             right_boundary_b,
                                             intervals);

                break;
            }


//----------------Обчислення методом трапецій----------------

            case 3:
            {
                integral_s =
                    num_comput_integral_trapezoid(left_boundary_a,
                                                  right_boundary_b,
                                                  intervals);

                break;
            }


//----------------Обчислення методом Сімпсона----------------

            case 4:
            {
                integral_s =
                    num_comput_integral_Simps(left_boundary_a,
                                              right_boundary_b,
                                              intervals);

                break;
            }
        }


 //----------------Виведення результатів обчислення----------------

        printf("\n----------------------------------");

        printf("\na = %.2lf", left_boundary_a);
        printf("\nb = %.2lf", right_boundary_b);

        printf("\nN = %u", intervals);

        printf("\nIntegral = %.10lf", integral_s);

        printf("\nMeasurement error = %.8lf",
               measurement_error);

        printf("\n----------------------------------");


//----------------Присвоєння початкового значення кількості проміжків----------------

        N = intervals;


//----------------Визначення кількості проміжків при заданій похибці----------------

        while (1)
        {
 //----------------Обчислення значень інтегралів I1 та I2----------------

            switch (variant)
            {
 //----------------Метод лівих прямокутників----------------

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


//----------------Метод правих прямокутників----------------

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


//----------------Метод трапецій----------------

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


//----------------Метод Сімпсона----------------

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


//----------------Обчислення абсолютної похибки----------------

            Delta = fabs(I1 - I2);


//----------------Перевірка відповідності заданій похибці----------------

            if (Delta <= measurement_error)
            {
                break;
            }


//----------------Збільшення кількості проміжків на два----------------

            N += 2;
        }


 //----------------Виведення кінцевих результатів обчислення----------------

        printf("\n\nRequired number of intervals:");

        printf("\nN = %u", N);

        printf("\nI1 = %.10lf", I1);

        printf("\nI2 = %.10lf", I2);

        printf("\nDelta = %.10lf", Delta);

        printf("\n\n");
    }


//----------------Завершення виконання програми----------------

    return 0;
}


//----------------Функція обчислення інтеграла методом лівих прямокутників----------------

double num_comput_integral_l_re(double left_boundary_a,
                                double right_boundary_b,
                                unsigned int intervals)
{
//----------------Оголошення та ініціалізація змінних----------------

    double integral_s = 0;
    double x = 0;
    double h;

    unsigned int i;


//----------------Обчислення кроку інтегрування----------------

    h = (right_boundary_b - left_boundary_a) / intervals;


//----------------Встановлення початкового значення аргументу----------------

    x = left_boundary_a;


//----------------Обчислення суми значень підінтегральної функції----------------

    for (i = 0; i < intervals; i++)
    {
        integral_s += integrand_expression(x);

        x += h;
    }

    //----------------Повернення обчисленого значення інтеграла----------------

    return integral_s * h;
}


//----------------Функція обчислення інтеграла методом правих прямокутників----------------

double num_comput_integral_r_re(double left_boundary_a,
                                double right_boundary_b,
                                unsigned int intervals)
{
 //----------------Оголошення та ініціалізація змінних----------------

    double integral_s = 0;
    double x = 0;
    double h;

    unsigned int i;


//----------------Обчислення кроку інтегрування----------------

    h = (right_boundary_b - left_boundary_a) / intervals;


//----------------Встановлення початкового значення аргументу----------------

    x = left_boundary_a + h;


//----------------Обчислення суми значень підінтегральної функції----------------

    for (i = 0; i < intervals; i++)
    {
        integral_s += integrand_expression(x);

        x += h;
    }


//----------------Повернення обчисленого значення інтеграла----------------

    return integral_s * h;
}


//----------------Функція обчислення інтеграла методом трапецій----------------

double num_comput_integral_trapezoid(double left_boundary_a,
                                     double right_boundary_b,
                                     unsigned int intervals)
{
//----------------Оголошення та ініціалізація змінних----------------

    double integral_s = 0;
    double x = 0;
    double h;

    unsigned int i;


//----------------Обчислення кроку інтегрування----------------

    h = (right_boundary_b - left_boundary_a) / intervals;


//----------------Обчислення початкового значення суми----------------

    integral_s =
        (integrand_expression(left_boundary_a) +
         integrand_expression(right_boundary_b)) / 2.0;


//----------------Обчислення суми значень у внутрішніх точках----------------

    for (i = 1; i < intervals; i++)
    {
        x = left_boundary_a + i * h;

        integral_s += integrand_expression(x);
    }


//----------------Повернення обчисленого значення інтеграла----------------

    return integral_s * h;
}


//----------------Функція обчислення інтеграла методом Сімпсона----------------

double num_comput_integral_Simps(double left_boundary_a,
                                 double right_boundary_b,
                                 unsigned int intervals)
{
//----------------Оголошення та ініціалізація змінних----------------

    double integral_s = 0;
    double x = 0;
    double h;

    unsigned int i;


//----------------Обчислення кроку інтегрування----------------

    h = (right_boundary_b - left_boundary_a) / intervals;


    //----------------Обчислення початкового значення суми----------------

    integral_s =
        integrand_expression(left_boundary_a) +
        integrand_expression(right_boundary_b);


 //----------------Обчислення суми відповідно до методу Сімпсона----------------

    for (i = 1; i < intervals; i++)
    {
        x = left_boundary_a + i * h;


        //----------------Обробка точок з непарним номером----------------

        if (i % 2 != 0)
        {
            integral_s +=
                4 * integrand_expression(x);
        }


//----------------Обробка точок з парним номером----------------

        else
        {
            integral_s +=
                2 * integrand_expression(x);
        }
    }


//----------------Повернення обчисленого значення інтеграла----------------

    return integral_s * h / 3.0;
}


//----------------Функція обчислення підінтегрального виразу----------------

double integrand_expression(double x)
{
    return 1.0 / (pow(x, 2) - 1.0);
}