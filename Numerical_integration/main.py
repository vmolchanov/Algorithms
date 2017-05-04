# -*- coding:utf-8 -*-
import math
import random
import matplotlib.pyplot as plt


def calc_integral(function, a, b, n, method="rectangle_center"):
    """
    :param function: заданная функция
    :param a: нижний предел
    :param b: верхний предел
    :param n: количество отрезков a = x0, x1, ..., xn = b
    :param method: метод, с помощью которого вычисляется значение интеграла:
                   rectangle_center - метод центральных (средних) прямоугольников
                   rectangle_left - метод левых прямоугольников
                   rectangle_right - метод правых прямоугольников
                   trapeze - метод трапеций
                   simpson - метод Симпсона
                   montecarlo_rectangle - метод Монте-Карло (статистический метод прямоугольников)
                   montecarlo_geometrical - геометрический метод Монте-Карло
    """

    h = (b - a) / n

    # разобьем [a, b] на n отрезков, таких, что a = x0, x1, ..., xn = b
    x = [a + h * i for i in range(n)]
    integration_value = 0.0

    if method == "rectangle_center":
        for i in range(1, n):
            integration_value += h * function(x[i - 1] + h / 2)
    elif method == "rectangle_left":
        for i in range(n - 1):
            integration_value += h * function(x[i])
    elif method == "rectangle_right":
        for i in range(1, n):
            integration_value += h * function(x[i])
    elif method == "trapeze":
        integration_value = h / 2 * (function(x[0]) + function(x[n - 1]))
        for i in range(1, n - 1):
            integration_value += h * function(x[i])
    elif method == "simpson":
        integration_value = h / 3 * (function(x[0]) + function(x[n - 1]))
        for i in range(1, n - 1):
            integration_value += h / 3 * (4 if i % 2 == 1 else 2) * function(x[i])
    elif method == "montecarlo_rectangle":
        random_points = [function(random.uniform(a, b)) for i in range(n)]
        for i in range(n):
            integration_value += h * random_points[i]
    elif method == "montecarlo_geometrical":
        # Ограничим функцию квадратом со стороной b - a и "накидаем" в него n случайных точек
        random_x = [random.uniform(a, b) for i in range(n)]
        random_y = [random.uniform(0, b - a) for i in range(n)]

        count_of_points_under_graph = 0

        for i in range(n):
            if random_y[i] < function(random_x[i]):
                count_of_points_under_graph += 1
            integration_value = (b - a) ** 2 * count_of_points_under_graph / n

    return integration_value


if __name__ == "__main__":
    func = lambda x: x * math.exp(-x)
    a = 0
    b = 1
    n = 1000000

    # метод центральных (средних) прямоугольников
    method_1 = calc_integral(func, a, b, n)
    print("Метод центральных прямоугольников:", method_1)

    # метод левых прямоугольников
    method_2 = calc_integral(func, a, b, n, "rectangle_left")
    print("Метод левых прямоугольников:", method_2)

    # метод правых прямоугольников
    method_3 = calc_integral(func, a, b, n, "rectangle_right")
    print("Метод правых прямоугольников:", method_3)

    # метод трапеций
    method_4 = calc_integral(func, a, b, n, "trapeze")
    print("Метод трапеции:", method_4)

    # метод Симпсона
    method_5 = calc_integral(func, a, b, n, "simpson")
    print("Метод Симпсона:", method_5)

    # метод Монте-Карло (статистический метод прямоугольников)
    method_6 = calc_integral(func, a, b, n, "montecarlo_rectangle")
    print("Статистический метод прямоугольников:", method_6)

    # геометрический метод Монте-Карло
    method_7 = calc_integral(func, a, b, n, "montecarlo_geometrical")
    print("Геометрический метод Монте-Карло:", method_7)

    # Graphs

    center_rect = []
    left_rect = []
    right_rect = []
    trapeze = []
    simpson = []
    stat_monte_carlo = []
    geom_monte_carlo = []

    for i in range(1, 20):
        center_rect.append(calc_integral(func, a, b, i))
        left_rect.append(calc_integral(func, a, b, i, "rectangle_left"))
        right_rect.append(calc_integral(func, a, b, i, "rectangle_right"))
        trapeze.append(calc_integral(func, a, b, i, "trapeze"))
        simpson.append(calc_integral(func, a, b, i, "simpson"))
        stat_monte_carlo.append(calc_integral(func, a, b, i, "montecarlo_rectangle"))
        geom_monte_carlo.append(calc_integral(func, a, b, i, "montecarlo_geometrical"))


    n_arr = [i for i in range(1, 20)]

    figure = plt.figure()
    plt.xlabel("n")
    plt.ylabel("value")
    plt.plot(n_arr, center_rect, "b")
    plt.plot(n_arr, left_rect, "r")
    plt.plot(n_arr, right_rect, "g")
    plt.plot(n_arr, trapeze, "y")
    plt.plot(n_arr, simpson, "v")
    plt.plot(n_arr, stat_monte_carlo, "g")
    plt.plot(n_arr, geom_monte_carlo, "o")
    figure.show()
    plt.show()
