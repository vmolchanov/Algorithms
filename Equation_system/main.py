# -*- coding:utf-8 -*-
import numpy as np


def calc_gauss_method(matr):
    left_item = 0

    # create of the triangular matrix
    while left_item != len(matr):
        index = left_item + 1

        while index != len(matr):
            matr[index] -= matr[left_item] * matr[index][left_item] / matr[left_item][left_item]
            index += 1

        left_item += 1

    # if no solutions
    zeros_str = 0
    is_zeroes_str = True

    for i in range(len(matr)):
        for j in range(len(matr)):
            if matr[i][j] != 0:
                is_zeroes_str = False
                break

        if is_zeroes_str:
            if matr[i][len(matr)] != 0:
                return "No solutions"
            zeros_str += 1
        else:
            is_zeroes_str = True

    # else
    rang = len(matr) - zeros_str

    if rang < len(matr):
        return "Many solutions"

    ans = [0 for i in range(len(matr))]
    step = len(matr) - 1
    amount = 0.0

    while step >= 0:
        for j in range(step + 1, len(matr)):
            amount += matr[step][j] * ans[j]

        amount = -amount
        ans[step] = (matr[step][len(matr)] + amount) / matr[step][step]
        step -= 1
        amount = 0

    return ans


def get_det(matr):
    if matr.size == 4:
        return matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0]

    minor = 0
    det = 0

    while minor < len(matr):
        new_matr = []
        new_matr = np.array(new_matr)

        for i in range(1, len(matr)):
            for j in range(len(matr)):
                if j != minor:
                    new_matr = np.append(new_matr, matr[i][j])

        new_matr = new_matr.reshape((len(matr) - 1, len(matr) - 1))

        if minor % 2 == 0:
            det += matr[0][minor] * get_det(new_matr)
        else:
            det -= matr[0][minor] * get_det(new_matr)

        minor += 1

    return det


def calc_kramer_method(matr):
    y = [ matr[i][len(matr)] for i in range(len(matr)) ]

    matr = np.array([ [ matr[i][j] for j in range(len(matr)) ] for i in range(len(matr)) ])
    ans = []
    common_det = get_det(matr)

    if common_det == 0:
        return "Not defined, use the method of Gaussian!"

    local_det = []

    for j in range(len(matr)):
        new_matr = np.array(matr)

        for i in range(len(new_matr)):
            new_matr[i][j] = y[i]

        local_det.append(get_det(new_matr))

    for i in range(len(y)):
        ans.append(local_det[i] / common_det)

    return ans


def fwrite(arr, path):
    with open(path, "w") as fout:
        if type(arr) == str:
            fout.write(arr + "\n")
        else:
            for i in range(len(arr)):
                fout.write("x" + str(i) + ": " + str(arr[i]) + "\n")


if __name__ == "__main__":
    n = None
    matr = []
    
    with open("../txt/input.txt") as fin:
        n = int(fin.readline())
        for i in range(n):
            matr.append(fin.readline().strip().split(" "))

    matr = np.array(matr, dtype="float64")

    gauss = calc_gauss_method(matr)
    fwrite(gauss, "../txt/gauss.txt")

    kramer = calc_kramer_method(matr)
    fwrite(kramer, "../txt/kramer.txt")
