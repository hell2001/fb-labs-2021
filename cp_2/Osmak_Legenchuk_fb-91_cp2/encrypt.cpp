#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
using namespace std;

//функция возвращает индекс буквы в алфавите
int find_number(char l, string alp)
{
    for (int a = 0; a < alp.length(); ++a)
    {
        if (alp[a] == l)
            return a;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // открываем файл и считываем открытый текст
    ifstream in("D:\\source\\Crypto_lab2_part1\\Text.txt"); 
    string line, line1;
    if (in.is_open())
    {
        while (getline(in, line1))
            line += line1;
    }
    else
    {
        cout << "Не удалось открыть файл...\n";
        return 0;
    }
    cout << "Исходный текст: " << endl << endl;
    cout << line << endl << endl;
    string alphabet = "абвгдежзийклмнопрстуфхцчшщъыьэюя";
    string keys[5] = { "ку", "мда", "слон", "крыса", "попугайвернулся" }; //ключи разной длины
    for (int a = 0; a < 5; ++a) //проходим по всем ключам
    {
        string r_s;
        int len = 0; //переменная запоминает индекс буквы секретного ключа
        cout << "Длина ключа: " << keys[a].length() << endl << endl;
        for (int b = 0; b < line.length(); ++b) //проходим по всей строке
        {
            if (len >= keys[a].length()) //дойдя до конца строки с секретным ключем, начинаем заново
                len = 0;
            int num = find_number(line[b], alphabet) + find_number(keys[a][len], alphabet); //ищем индекс новой буквы
            if (num < 0)
                num += 32;
            if (num > 31)
                num -= 32;
            r_s += alphabet[num]; //формируем шифротекст
            ++len;
        }
        cout << r_s << endl << endl;
    }
}

