#include <fstream>
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
using namespace std;


class Letter
{
private:
    char letter;
    int number;
public:
    Letter(char l) : letter(l), number(0) {}
    char getLetter() { return letter; }
    int getNumber() { return number; }
    void incNumber() { ++number; }
};

// ������� ���������� ������ ����� � ��������
int find_number(char l, string alp)
{
    for (int a = 0; a < alp.length(); ++a)
    {
        if (alp[a] == l)
            return a;
    }
}
// ������� ���������� ������ � ������� � ���� ������ � ���-�� �� ���������� � ������ 
vector<Letter> count_letters(string str)
{
    vector<Letter>letters; //������ �� ����� ���������� ������� � ���-��� �� ����������
    for (int a = 0; a < str.length(); ++a) //�������� �� ���� ������
    {
        if (letters.size() == 0)
            letters.push_back(str[a]); //��������� ������ �����
        else
        {
            int d = 0;
            for (int b = 0; b < letters.size(); ++b) //��������� �� ����� ���������� ����� �������
            {
                if (letters[b].getLetter() == str[a]) //���� ����� ����� ��� ���� � �������, ����������� �� ������� �� 1 � ������� �� �����
                {
                    letters[b].incNumber();
                    d = 1;
                    break;
                }
            }
            if (d == 0) //���� ����� ����� ��� � �������, ��������� ��
                letters.push_back(str[a]);
        }
    }
    return letters;
}
// ������� ���� �������� ������ ����� � ������
char find_letter(string str)
{
    vector<Letter>letters = count_letters(str); //�������� ������ ��� ���������
    char let = '0';
    int c = 0;
    for (int a = 0; a < letters.size(); ++a) //�������� �� ����� ������� � ���������� ����� � ���������� ���������
    {
        if (letters[a].getNumber() > c)
        {
            c = letters[a].getNumber();
            let = letters[a].getLetter();
        }
    }
    return let;
}

//���������� �������� ������ (��� �������������� �������� �����)
double entrophy(string line)
{
    int a = 0;
    vector<Letter>let = count_letters(line); //�������� ������ ��� ���������
    double ent = 0;
    for (int c1 = 0; c1 < let.size(); ++c1) //����������� �������� � (���������� 1-� ����)
    {
        double d = (double)let[c1].getNumber() / line.length();
        if (d != 0)
             ent += (d * log2(d));
    }
    ent = -ent;
    return ent;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // ��������� ����������� ����� �� �����
    ifstream in("D:\\source\\Crypto_lab2\\Text.txt");
    string line, line1;
    if (in.is_open())
    {
        while (getline(in, line1))
            line +=line1;
    }
    else
    {
        cout << "�� ������� ������� ����...\n";
        return 0;
    }
    // ����� ����� R
    cout << "������� ����� ����� �����...\n\n";
    int a = 0, b = 0, counter = 0, max_counter = 0, r = 6, max_r = 6;
    vector<string>main_; //����� ����� �������� ��� ��������� ������, ��������������� ���������� ������
    for (; r < 31; ++r) //��������� ��� ����� ������ �� 6 �� 30 ��������
    {
        cout << "�������� ����� �����: " << r << endl;
        vector<string>fr; // ����� ��������� � ��������� ������ ��� ��������� ����� ��� ���������� �����������
        while (b < r)
        {
            fr.push_back("");
            fr[b] += line[a + b];
            while (a + b + r < line.length())
            {
                if (line[a + b] == line[a + b + r]) //������� ���-�� ������ ������ ������������� ��������
                    ++counter;
                fr[b] += line[a + b + r]; //���������� ����� �� ��������, ����������� �� ���������� r
                a += r;
            }
            a = 0; ++b;
        }
        cout << "���-�� ����������: " << counter << endl << endl;
        if (counter > max_counter) //���� ������� ������������� �������� ������ - ��������� ������
        {
            max_counter = counter; //��������� ������������ ���������� ����������
            max_r = r; //����
            main_ = fr; //� ����������������� �����
        }
        counter = 0;
        b = 0;
    }
    cout << "_____________________________________________\n\n";
    cout << "���������� ����� �����: " << max_r << endl;
    cout << "_____________________________________________\n\n";

    // ����������� ������
    string alphabet = "��������������������������������";
    int main_letters[3] = {14, 5, 0}; //������� ����� ��������������� ���� �������� �����: � (14), � (5), � (0)
    string en_text; //����� ����� �������� �������������� �����
    for (int c1 = 0; c1 < max_r; ++c1) //�������� �� ���� ����������
    {
        char l1 = find_letter(main_[c1]); //������� ����� ������ ����� �� ���������
        int num = find_number(l1, alphabet); //���������� �� ������
        double e_n = 10; string e_str;
        for (int c2 = 0; c2 < 3; ++c2) //��������� ��� 3 ����� (�, �, �)
        {
            int c3 = 0;
            int num1 = -(num - main_letters[c2]); //������� �������������� ���� ������
            string str; //����� ����� �������� �������������� ������
            for (c3 = 0; c3 < main_[c1].length(); ++c3) //�������������� ������ �������������� ������
            {
                int num2 = find_number(main_[c1][c3], alphabet);
                num2 += num1;
                if (num2 >= 32)
                    num2 -= 32;
                else if (num2 < 0)
                    num2 += 32;
                str += alphabet[num2];
            }
            if (c1 == 0) //���� ��� 1-� ������ - ��������� �� � ������ "�" � ��������� � ���������
            {
                en_text += str;
                break;
            }
            double entr = entrophy(en_text + str); //������� �������� ���������� ������ ������ � �������������� �������
            if (entr < e_n) // ������ � ���������� ��������� �������� �������� �������� ����� ������� �������
            {
                e_n = entr;
                e_str = str;
            }
        }
        string txt, txt1;
        int e1 = 0; int e2 = 0;
        for (int c4 = 0; c4 < (en_text + e_str).length(); ++c4) //��������� �������������� ������ � ���������� �������, ����� ���������� ����� �� ���� �����
        {
            if (((c4 + 1) % (c1 + 1)) == 0 && e2 < e_str.length())
            {
                txt += e_str[e2];
                ++e2;
            }
            else
            {
                txt += en_text[e1];
                ++e1;
            }
        }
        en_text = txt;
    }
    cout << "���������� �����: \n";
    cout << en_text << endl << endl;
}
