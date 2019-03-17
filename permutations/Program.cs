using System;

class Program
{
    static void Main(string[] args)
    {
        const string LETTERS = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        const int MAX_LETTERS_COUNT = 33;

        Console.WriteLine("Введите количество используемых букв:");
        int m;
        do
        {
            m = Convert.ToInt32(Console.ReadLine());
        }
        while (m > MAX_LETTERS_COUNT);

        Console.WriteLine("Введите количество букв в слове:");
        int n = Convert.ToInt32(Console.ReadLine());

        //Permutations(n, m, LETTERS);
        RecursivePermutations(n, m, LETTERS);
    }

    /**
     * Метод, выводящий все перестановки букв в слове на экран.
     */
    static void Permutations(int wordLength, int lettersCount, string letters)
    {
        int wordsCount = (int)Math.Pow(lettersCount, wordLength);
        int wordCounter = 0;

        while (wordCounter != wordsCount)
        {
            int[] indexes = getIndexesFromOrder(lettersCount, wordCounter, wordLength);
            PrintWord(indexes, letters);
            wordCounter++;
        }
    }

    /**
     * Обертка для рекурсивного метода RecursivePermutationsInner.
     * Написал метод-обертку, чтобы постоянно не вычислять wordsCount.
     */
    static void RecursivePermutations(int wordLength, int lettersCount, string letters)
    {
        int wordsCount = (int)Math.Pow(lettersCount, wordLength);
        RecursivePermutationsInner(wordLength, lettersCount, letters, wordsCount);
    }

    /**
     * Рекурсивный метод, выводящий все перестановки букв в слове на экран.
     */
    static void RecursivePermutationsInner(
        int wordLength,
        int lettersCount,
        string letters,
        int wordsCount,
        int wordNumber = 0)
    {
        if (wordNumber == wordsCount)
        {
            return;
        }

        int[] indexes = getIndexesFromOrder(lettersCount, wordNumber, wordLength);
        PrintWord(indexes, letters);
        RecursivePermutationsInner(wordLength, lettersCount, letters, wordsCount, wordNumber + 1);
    }

    /**
     * Выводит слово на экран.
     */
    static void PrintWord(int[] indexes, string letters)
    {
        foreach (int index in indexes)
        {
            Console.Write(letters[index]);
        }
        Console.WriteLine();
    }

    /**
     * Переводит число из 10-й системы в счисления в систему счисления radix.
     */
    static int[] getIndexesFromOrder(int radix, int order, int length)
    {
        int[] indexes = new int[length];

        for (int i = 0; i < length; i++)
        {
            int digitPosition = length - i - 1;
            int numericWeight = (int)Math.Pow(radix, digitPosition);
            int index = order / numericWeight;

            indexes[i] = index;
            order -= index * numericWeight;
        }

        return indexes;
    }
}