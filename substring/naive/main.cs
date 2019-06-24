using System;

class Program
{
    public static void Main(string[] args)
    {
        Console.WriteLine(IndexOf("Hello, World", "ld")); // 10
    }

    static int IndexOf(string str, string substr)
    {
        for (int i = 0, n = str.Length - substr.Length + 1; i < n; i++)
        {
            if (IsEqual(str.Substring(i, substr.Length), substr))
            {
                return i;
            }
        }
        return -1;
    }
}
