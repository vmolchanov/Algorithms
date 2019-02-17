using System;

class Program
{
    static void Main(string[] args)
    {
        int kaleidoscopeSize = GetKaleidoscopeSizeFromInputStream("Введите размер калейдоскопа (половина стороны)");
        int[,] kaleidoscope = MakeKaleidoscope(kaleidoscopeSize);
        PrintKaleidoscope(kaleidoscope);
    }

    /**
     * Запрашивает у пользователя размер половины стороны калейдоскопа
     */
    static int GetKaleidoscopeSizeFromInputStream(String message)
    {
        const int MIN_VALUE = 3;
        const int MAX_VALUE = 20;

        int size;

        Console.WriteLine(message);

        while (true)
        {
            size = Convert.ToInt32(Console.ReadLine());

            if (size < MIN_VALUE || size > MAX_VALUE)
            {
                Console.WriteLine("Необходимо ввести число в интервале [{0}, {1}]. Повторите попытку", MIN_VALUE, MAX_VALUE);
            }
            else
            {
                break;
            }
        }

        return size;
    }

    /**
     * Возвращает случайный код цвета из Console.ConsoleColor
     */
    static int GetRandomColorCode(Random random)
    {
        const int COLORS_COUNT = 16;
        return random.Next(COLORS_COUNT);
    }

    /**
     * Метод генерирует случайную матрицу, которая симметрична по горизонтали, вертикали и диагонали
     */
    static int[,] MakeKaleidoscope(int halfSize)
    {
        int size = halfSize + halfSize;
        int[,] kaleidoscope = new int[size, size];
        Random random = new Random();

        for (int imain = 0; imain < halfSize; imain++)
        {
            int randomColorCode = GetRandomColorCode(random);
            SetValueForSymmetricalPoints(kaleidoscope, imain, imain, randomColorCode);

            for (int i = imain + 1; i < halfSize; i++)
            {
                randomColorCode = GetRandomColorCode(random);
                SetValueForSymmetricalPoints(kaleidoscope, i, imain, randomColorCode);
                SetValueForSymmetricalPoints(kaleidoscope, imain, i, randomColorCode);
            }
        }

        return kaleidoscope;
    }

    /**
     * Выводит калейдоскоп в консоль в виде цветов
     */
    static void PrintKaleidoscope(int[,] kaleidoscope)
    {
        ConsoleColor currentBackgroundColor = Console.BackgroundColor;
        int rowCount = kaleidoscope.GetLength(0);
        int columnCount = kaleidoscope.GetLength(1);

        for (int i = 0; i < rowCount; i++)
        {
            for (int j = 0; j < columnCount; j++)
            {
                Console.BackgroundColor = (ConsoleColor)kaleidoscope[i, j];
                Console.Write(" ");
            }
            Console.WriteLine();
        }

        Console.BackgroundColor = currentBackgroundColor;
    }

    /**
     * Получая на вход координаты из левой верхней части матрицы, метод устанавливает значение для всех симметричных
     * точек    
     */
    static void SetValueForSymmetricalPoints(int[,] arr, int i, int j, int value)
    {
        int rowCount = arr.GetLength(0);
        int columnCount = arr.GetLength(1);

        // Лево верх
        arr[i, j] = value;
        // Право верх
        arr[i, columnCount - j - 1] = value;
        // Лево низ
        arr[rowCount - i - 1, j] = value;
        // Право низ
        arr[rowCount - i - 1, columnCount - j - 1] = value;
    }
}