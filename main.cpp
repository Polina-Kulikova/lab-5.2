//Вариант 6
//Дан файл, содержащий русский текст, размер текста не превышает 10 К байт.
//Найти в тексте N (N ≤ 100) слов, содержащих наибольшее количество сочетаний из двух согласных.
//Записать найденные слова в текстовый файл в порядке не возрастания количества сочетаний.
//Для каждого слова вывести также количество сочетаний из двух согласных. Все найденные слова должны быть разными. Число N вводить из файла.
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

bool IsConsonants (char x)
{
    bool flag = false;
    if ((66 <= int(x) && int(x) < 69) || (70 <= int(x) && int(x) < 73) || (74 <= int(x) && int(x) < 79) || (80 <= int(x) && int(x)< 85) || (87 <= int(x) && int(x) < 91)||
        (98 <= int(x) && int(x) < 101) || (102 <= int(x) && int(x) < 105) || (106 <= int(x) && int(x) < 111) || (112 <= int(x) && (int(x) < 117) || (119 <= int(x) && int(x) < 123)))
    {
        flag = true;
    }
    return flag;
}
int main()
{
    std::ifstream in("test.txt");
    if(!in.is_open())   //проверка открытия файла
    {
        std::cout << "File good!!" << std::endl;
        return -1;
    }
    std::ofstream out("output.txt", std::ios::out);
    std::string outwords[1000];
    int n;
    in >> n;
    //std::cout << n << std::endl;
    //std::string words[100];
    int k = 0;
    int score[1000];
    int p = 0;
    while (!in.eof())
    {
        std::string a;
        in >> a;
        //std::cout << a << " " << a.length() <<  std::endl;
        for (int i = 1; i < a.length(); i++)
        {
            //std::cout << a.length() << " " << i+1 << std::endl;
            if (IsConsonants(a[i-1]) && IsConsonants(a[i]))
                k += 1;
        }

        if (k >= 1)
        {
            for (int i = 0; i < a.length(); i++)
                if (a[i] == '.' || a[i] == '!' || a[i] == ',' || a[i] == '?')
                {
                    a.erase(i, 1);//удаление знаков препинания
                    i--;
                }

            bool consists = false;
            for (int i = 0; i < p; i++)
                if (outwords[i] == a)
                {
                    consists = true;//избавляемся от повторов
                    break;
                }

            if (!consists)
            {
                outwords[p] = a;
                score[p] = k;
                p += 1;
            }
            //std::cout << outwords[1000]<<" "<<p<<std::endl;
        }
        //std::cout<<k<<std::endl;
        k = 0;
    }

    //cортировка и вывод в файл
    for (int i = 0; i < p; i++)
    {
        //std::cout << outwords[i] << " " << score[i] <<" ";
    }
    for (int k = 0; k < outwords[1000].size() - 1; k++)
        for (int j = k + 1; j < outwords[1000].size(); j++)
        {
            if ((score[k] < score[j]) || (score[k] == score[j] && outwords[k].size() < outwords[j].size()))
            {
                std::swap(score[k], score[j]);
                std::swap(outwords[k], outwords[j]);
            }
        }

    for (int i=0; i<n; i++)
        out<<outwords[i]<<" "<<score[i]<<std::endl;

  return 0;
}