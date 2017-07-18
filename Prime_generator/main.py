import itertools


def primes():
    """
    Функция-генератор возвращает простое число по теореме Вильсона
    Теорема Вильсона: Натуральное число p > 1 является простым тогда и только тогда, когда (p - 1)! + 1
    делится на p
    """
    num = 2
    while True:
        factorial = 1
        for n in range(2, num):
            factorial *= n
        if (factorial + 1) % num == 0:
            yield num
        num += 1


print(list(itertools.takewhile(lambda x : x <= 31, primes())))
# [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31]
