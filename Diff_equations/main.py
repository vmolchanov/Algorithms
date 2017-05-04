# -*- coding: utf-8 -*-
import numpy as np
from constants import *
import matplotlib.pyplot as plt


def calc_diff_equations(func, x, y, h):
    k1 = func(x, y)
    k2 = func(x + h / 2, y + h / 2 * k1)
    k3 = func(x + h / 2, y + h / 2 * k2)
    k4 = func(x + h / 2, y + h / 2 * k3)

    return y + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4)


if __name__ == "__main__":

    # vector of arguments and fill its
    x = np.array([])
    num = a + h

    while num <= abs(b - a):
        x = np.append(x, num)
        num += h

    # vector of solutions
    y = np.array([y0])

    for i in x:
        y = np.append(y, calc_diff_equations(func, i, y[len(y) - 1], h))

    print(y[1:])

    # Verify
    verify_func = lambda x: (x - 1) / x ** 2
    verify_y = np.array([])

    for i in x:
        verify_y = np.append(verify_y, verify_func(i))

    print(verify_y)

    # graph of my solution and graph of right solution
    figure = plt.figure()
    plt.xlabel("x")
    plt.ylabel("y")
    plt.title("function")
    plt.plot(x, y[1:])
    plt.plot(x, verify_y)
    figure.savefig("graphs/function.png")

    # graph of mistakes
    mistakes = np.array([])
    new_h = np.array([])
    step = h

    while step <= 0.5:
        new_h = np.append(new_h, step)
        step += 0.01

    for spl in new_h:
        # vector of arguments and fill its
        new_x = np.array([])
        step = a + spl

        while step <= abs(b - a):
            new_x = np.append(new_x, step)
            step += spl

        # vector of solutions
        new_y = np.array([y0])

        for i in new_x:
            new_y = np.append(new_y, calc_diff_equations(func, i, new_y[len(new_y) - 1], spl))

        # verify
        new_verify_y = np.array([])
        
        for i in new_x:
            new_verify_y = np.append(new_verify_y, verify_func(i))

        mistakes = np.append(mistakes, np.mean ( np.abs( np.abs(new_y[1:]) - np.abs(new_verify_y) ) ) )

    print(mistakes)

    #graph of mistakes
    figure = plt.figure()
    plt.xlabel("step")
    plt.ylabel("mistake")
    plt.title("mistakes")
    plt.plot(new_h, mistakes)
    figure.savefig("graphs/mist.png")
