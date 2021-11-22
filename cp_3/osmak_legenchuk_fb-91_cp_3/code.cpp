#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Bigram
{
private:
    string bigram;
    int number;
public:
    Bigram(string b) : bigram(b), number(0) {}
    string getLetter() { return bigram; }
    int getNumber() { return number; }
    void incNumber() { ++number; }
};

int find_number(char l, string& alp)
{
    for (int a = 0; a < alp.length(); ++a)
    {
        if (alp[a] == l)
            return a;
    }
}

vector<Bigram> count_letters(string str)
{
    vector<Bigram>bigrams;
    for (int a = 0; a + 1 < str.length(); a += 2)
    {
        if (bigrams.size() == 0)
        {
            string b = "  "; b[0] = str[a]; b[1] = str[a + 1];
            bigrams.push_back(b);
        }
        else
        {
            int d = 0;
            string b1 = "  ";
            for (int b = 0; b < bigrams.size(); ++b)
            {
                b1[0] = str[a]; b1[1] = str[a + 1];
                if (bigrams[b].getLetter() == b1)
                {
                    bigrams[b].incNumber();
                    d = 1;
                    break;
                }
            }
            if (d == 0)
                bigrams.push_back(b1);
        }
    }
    return bigrams;
}

void find_letter(string str, string bigrs[5])
{
    vector<Bigram>letters = count_letters(str);
    int c = 0;
    for (int a = 0; a < letters.size(); ++a)
    {
        if (letters[a].getNumber() > c)
        {
            bigrs[4] = bigrs[3];
            bigrs[3] = bigrs[2];
            bigrs[2] = bigrs[1];
            bigrs[1] = bigrs[0];
            c = letters[a].getNumber();
            bigrs[0] = letters[a].getLetter();
        }
    }
}

int wide_euklid(int a, int b, int& x, int& y)
{
    if (a == 0)
    {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int d = wide_euklid(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

bool language_recognition(string line)
{
    int c = 0;
    for (int a = 0; a < line.length(); ++a)
    {
        if ((line[a] == 'а' || line[a] == 'о' || line[a] == 'у' || line[a] == 'и' || line[a] == 'я' || line[a] == 'ю' || line[a] == 'э')
            && (line[a + 1] == 'ь'))
            ++c;
        if (c == 2)
            return false;
    }
    return true;
}

int linear_compare(int yi, int xi, int n, vector<int>& solutions)
{
    int _x = 0, _y = 0;
    int d = wide_euklid(yi, n, _x, _y);
    if (d == 1)
    {
        int a = _x * xi;
        for (; a >= n; a -= n) {}
        for (; a < 0; a += n) {}
        wide_euklid(a, n, _x, _y);
        return _x;
    }
    else if (d > 1 && xi % d == 0)
    {
        int x = linear_compare(yi / d, xi / d, n / d, solutions);
        for (int c = 0; c < d; c += (n / d))
            solutions.push_back(x + c);
        return 0;
    }
    else
        return -1;
}

int search_text(int a, int sb[5], int open_bigrams[5], int& st3, int& st1, string& alphabet, string& line)
{
    int b = sb[st3] - a * open_bigrams[st1];
    for (; b >= 961; b -= 961) {}
    for (; b < 0; b += 961) {}
    string open_text;
    for (int count = 0; count < line.length(); count += 2)
    {
        int x_i = (find_number(line[count], alphabet) * 31 + find_number(line[count + 1], alphabet)) - b;
        for (; x_i >= 961; x_i -= 961) {}
        for (; x_i < 0; x_i += 961) {}
        int x11 = 0, y11 = 0;
        wide_euklid(a, 961, x11, y11);
        int xx = x11 * x_i;
        for (; xx < 0; xx += 961) {}
        for (; xx >= 961; xx -= 961) {}
        int sec = xx % 31;
        int fir = (xx - sec) / 31;
        open_text += alphabet[fir];
        open_text += alphabet[sec];
    }
    if (language_recognition(open_text) == true)
    {
        cout << "ТЕКСТ РАСПОЗНАНО\nКЛЮЧ: a = " << a << ", b = " << b << endl << endl;
        cout << open_text << endl;
        system("pause");
        return 0;
    }
    else
        return 1;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string alphabet = "абвгдежзийклмнопрстуфхцчшщыьэюя";
    ifstream in("D:\\source\\Crypto_3\\11.txt");
    string line, line1;
    if (in.is_open())
    {
        while (getline(in, line1))
            line += line1;
    }
    else
        return 0;
    string bigrs[5] = { "0", "0", "0", "0", "0" };
    int open_bigrams[5] = { 545, 417, 572, 403, 168 };
    find_letter(line, bigrs);
    int sb[5] = { 0, 0, 0, 0, 0 };
    for (int a = 0; a < 5; ++a)
    {
        sb[a] = find_number(bigrs[a][0], alphabet) * 31 + find_number(bigrs[a][1], alphabet);
        for (; sb[a] > 961; sb[a] -= 961) {}
    }
    int ctr = 0;
    for (int st1 = 0; st1 < 5; ++st1)
    {
        int x_ = open_bigrams[st1];
        for (int st2 = 0; st2 < 5; ++st2)
        {
            if (st2 != st1)
            {
                int y_ = open_bigrams[st2];
                int xi = x_ - y_;
                if (xi < 0)
                    xi += 961;
                for (int st3 = 0; st3 < 5; ++st3)
                {
                    int x__ = sb[st3];
                    for (int st4 = 0; st4 < 5; ++st4)
                    {
                        if (st4 != st3)
                        {
                            int yi = x__ - sb[st4];
                            if (yi < 0)
                                yi += 961;
                            vector<int> solutions;
                            int a = linear_compare(yi, xi, 961, solutions);

                            
                            if (a < 0)
                                a += 961;


                            if (a != 0)
                                search_text(a, sb, open_bigrams, st3, st1, alphabet, line);
                            else
                            {
                                for (int crt = 0; ctr < solutions.size(); ++ctr)
                                {
                                    search_text(solutions[ctr], sb, open_bigrams, st3, st1, alphabet, line);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
