#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>


struct CompareSecond
{
    bool operator()(const std::pair<std::string, int>& left, 
        const std::pair<std::string, int>& right) const
    {
        return  right.second > left.second;
    }
};

class Dictionary {
    std::string path;
    std::ifstream file;
    std::ofstream fileOf;
    std::map<std::string, int> dictionary;
    std::vector<std::string> words;
    std::string word;
    int cntWords = 0;
protected:
    void OpenFile(const std::string& path) {
        this->path = path;
        file.open(this->path);

        if (!file) {
            std::cout << "Error: Файла не существет или доступ к нему закрыт\n";
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
            std::cout << "файл пустой\n";
            return;
        }

        file.clear();
        file.seekg(0, std::ios::beg);
        std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::transform(text.begin(),
            text.end(),
            text.begin(),
            [](unsigned char const& c) {
                return ::tolower(c);
            });

        for (int ii = 0; ii < words.size(); ii++) {
            cntWords = 0;
            if(dictionary.insert(make_pair(words[ii], cntWords)).second) {
                for (size_t y{}; y <= text.length() - words[ii].length();) {
                    size_t position = text.find(words[ii], y);
                    if (position == std::string::npos) {
                        break;
                    }
                    ++dictionary[words[ii]];
                    y = position + 1;
                }
            }
        }
        
        std::cout << std::endl;
        std::cout << "Словарь: \n";
        for(auto it : dictionary)
        {
            std::cout << it.first << ":" << it.second << std::endl;
        }
    }

    void FindMostWord() {
        if (dictionary.empty()) {
            std::cout << "Словарь пуст\n" << std::endl;
            return;
        }
        std::pair<std::string, int> max = 
            *max_element(dictionary.begin(), dictionary.end(), CompareSecond());
        std::cout << std::endl;
        std::cout << "Наиболее часто встречающиеся слово: " << max.first << ":" << max.second << std::endl;
    }

    void SaveDictionary() {
        std::string pathOf;
        if (dictionary.empty()) {
            std::cout << "Словарь пуст\n" << std::endl;
            return;
        }

        std::cout << "Введите путь для сохранения словаря: ";
        std::cin >> pathOf;

        if (pathOf == "") {
            std::cout << "путь пуст\n";
            return;
        }

        fileOf.open(pathOf);
        if (!file) {
            std::cout << "Error: Файл не открыт\n";
            return;
        }

        fileOf << "Словарь\n";
        for (auto it : dictionary)
        {
            fileOf << it.first << ":" << it.second<<'\n';
        }
        std::cout << "Файл сохранен\n"<<std::endl;
        fileOf.close();
    }
};

class Menu : public Dictionary {
    std::string path;
    std::string word;
    int choice = 0;
    int count = 0;
public:
    void Show() {
        std::cout << "Введите путь к тексту"<<std::endl;
        std::cin >> path;
        OpenFile(path);
        do {
            std::cout << "------------------------------------\n";
            std::cout << "Выберите необходимое действие:\n"
                << "1. Создать словарь\n"
                << "2. Найти наиболее часто встречающиеся слово\n"
                << "3. Сохранить словарь в файл\n"
                << "4. Выход\n\n"
                << "Выбор -> ";
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


