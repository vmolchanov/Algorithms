using System;

class Program
{
    public static void Main(string[] args)
    {
        Console.WriteLine(IndexOf("Hello, World", "ld")); // 10
    }

    static int IndexOf(string str, string substr)
    {
        int substrHash = GetHash(substr);

        string currentSubstring = str.Substring(0, substr.Length);
        int hash = GetHash(currentSubstring);

        if (substrHash == hash)
        {
            if (IsEqual(currentSubstring, substr))
            {
                return 0;
            }
        }

        for (int i = 1, n = str.Length - substr.Length + 1; i < n; i++)
        {
            currentSubstring = currentSubstring.Substring(1) + str[i + substr.Length - 1];
            hash -= GetHash(str[i - 1].ToString());
            hash += GetHash(str[i + substr.Length - 1].ToString());

            if (substrHash == hash)
            {
                if (IsEqual(currentSubstring, substr))
                {
                    return i;
                }
            }
        }

        return -1;
    }

    static int GetHash(string str)
    {
        int hash = 0;
        foreach (char c in str)
        {
            hash += c;
        }
        return hash;
    }

    static bool IsEqual(string a, string b)
    {
        if (a.Length != b.Length)
        {
            return false;
        }

        for (int i = 0; i < a.Length; i++)
        {
            if (a[i] != b[i])
            {
                return false;
            }
        }

        return true;
    }
}