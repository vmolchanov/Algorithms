# Алгоритм Рабина-Карпа

## Подготовка

Пусть на вход функции подаются два аргумента:

* srt - исходная строка;
* substr - строка, которую нужно найти.

## Алгоритм

1. Получаем хеш substr;
2. Встаем в начало строки str;
3. Берем подстроку длины substr;
4. Сравниваем хеш этой подстроки с хешем substr. Если хеши равны, то переходим к шагу 5, иначе переходим к шагу 6;
5. Сравниваем строки посимвольно. Если все символы равны, то переходим к шагу 7, иначе к шагу 6;
6. Если длины строки str хватает, чтобы получить очередную подстроку длины substr, то сдвигаемся на один символ и возвращаемся к шагу 3, иначе возвращаем -1;
7. Возвращает индекс первого символа из подстроки str.