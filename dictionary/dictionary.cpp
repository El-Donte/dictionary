#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

class Dictionary {
    std::string path;
    std::ifstream file;
    std::ofstream fileOf;
    std::map<std::string, int> dictionary;
    std::vector<std::string> words;
    std::string word;
protected:
    void OpenFile(const std::string& path) {
        this->path = path;
        file.open(this->path);

        if (!file) {
            std::cout << "Error: ����� �� ��������� ��� ������ � ���� ������\n";
            return;
        }
    }

    void AllWords() {
        dictionary.clear();

        while (file >> word) {
            if (ispunct(static_cast<unsigned char>(word.back())))
                word.erase(word.end() - 1);
            else if (ispunct(static_cast<unsigned char>(word.front())))
                word.erase(word.begin());
            word[0] = std::tolower(word[0]);
            words.push_back(word);
        }

        if (words.empty()) {
            std::cout << "���� ������\n";
            return;
        }


        for (int ii = 0; ii < words.size(); ii++) {
            dictionary[words[ii]]++;
        }
        
        std::cout << std::endl;
        std::cout << "�������: \n";
        for(auto it : dictionary)
        {
            std::cout << it.first << ":" << it.second << std::endl;
        }
    }

    void FindMostWord() {
        if (dictionary.empty()) {
            std::cout << "������� ����\n" << std::endl;
            return;
        }
        auto max =
            std::max_element(dictionary.begin(), dictionary.end(), [](auto& left,
                auto& right) {return left.second < right.second; });
        std::cout << std::endl;
        std::cout << "�������� ����� ������������� �����: " << max->first << ":" << max->second << std::endl;
    }

    void SaveDictionary() {
        std::string pathOf;
        if (dictionary.empty()) {
            std::cout << "������� ����\n" << std::endl;
            return;
        }

        std::cout << "������� ���� ��� ���������� �������: ";
        std::cin >> pathOf;

        if (pathOf == "") {
            std::cout << "���� ����\n";
            return;
        }

        fileOf.open(pathOf);
        if (!file) {
            std::cout << "Error: ���� �� ������\n";
            return;
        }

        fileOf << "�������\n";
        for (auto it : dictionary)
        {
            fileOf << it.first << ":" << it.second<<'\n';
        }
        std::cout << "���� ��������\n"<<std::endl;
        fileOf.close();
    }
};

class Menu : public Dictionary {
    std::string path;
    int choice = 0;  
public:
    void Show() {
        std::cout << "������� ���� � ������"<<std::endl;
        std::cin >> path;
        OpenFile(path);
        do {
            std::cout << "------------------------------------\n";
            std::cout << "�������� ����������� ��������:\n"
                << "1. ������� �������\n"
                << "2. ����� �������� ����� ������������� �����\n"
                << "3. ��������� ������� � ����\n"
                << "4. �����\n\n"
                << "����� -> ";
            std::cin >> choice;
            switch (choice)
            {
            case 1:
                AllWords();
                break;
            case 2:
                FindMostWord();
                break;
            case 3:
                SaveDictionary();
                break;
            case 4:
                exit(0);
                break;
            default:
                break;
            }
        }while (choice != 4);
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    Menu m;
    m.Show();
   
}


