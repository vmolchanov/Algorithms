using System;

class Program
{
    public static void Main(string[] args)
    {
        Console.WriteLine(IndexOf("оба обобрали обои обра", "обои")); // 13
    }

    static int[] GetPrefix(string str)
    {
        int[] prefix = new int[str.Length];
        prefix[0] = 0;

        for (int i = 1; i < prefix.Length; i++)
        {
            int prev = prefix[i - 1];

            if (prev == 0)
            {
                prefix[i] = (str[i] == str[0]) ? 1 : 0;
            }
            else
            {
                string str1 = str.Substring(0, prev + 1);
                string str2 = str.Substring(i - prev, prev + 1);
                prefix[i] = IsEqual(str1, str2) ? prev + 1 : 0;
            }
        }

        return prefix;
    }

    static int IndexOf(string str, string substr)
    {
        int[] prefix = GetPrefix(substr);

        for (int i = 0, step = 1; i < str.Length - substr.Length + 1; i += step)
        {
            bool isEqual = true;
            int countOfComparison = 0;

            for (int j = 0; j < substr.Length; j++)
            {
                countOfComparison++;
                if (substr[j] != str[i + j])
                {
                    isEqual = false;
                    break;
                }
            }

            if (isEqual)
            {
                return i;
            }

            int newStep = countOfComparison - prefix[countOfComparison - 1];
            step = newStep;
        }

        return -1;
    }
}