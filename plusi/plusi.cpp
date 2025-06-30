// plusi.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Student {
public:
    string name;
    string specialnost;
    string gruppa;
    string ball;

    Student(string n, string r, string m, string s): name(n), specialnost(r), gruppa(m), ball(s){}

    static void writeToFile(const vector<Student>& students, const string& filename) {
        ofstream file(filename);
        for (const auto& student : students) {
            file << student.name << "," << student.specialnost << "," << student.gruppa << "," << student.ball << endl;
        }
        file.close();

 }
    static vector<Student> readFromFile(const string& filename) {
        vector<Student> students;
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            size_t pos = 0;
            vector<string> tokens;

            // Разбиваем строку по запятым
            while ((pos = line.find(',')) != string::npos) {
                string token = line.substr(0, pos);
                tokens.push_back(token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);  // Добавляем оставшуюся часть строки

            // Проверяем, что получили 4 поля (ФИО, специальность, группа, балл)
            if (tokens.size() == 4) {
                students.emplace_back(tokens[0], tokens[1], tokens[2], tokens[3]);
            }
        }

        file.close();
        return students;
    }

    static bool compareByNameAsc(const Student& a, const Student& b) {
        return a.name < b.name;
    }

    static bool compareByNameDesc(const Student& a, const Student& b) {
        return a.name > b.name;
    }
};

void addStudent(vector<Student>& students) {
    string name, specialnost, gruppa, ball;
    cout << "Введите ФИО: ";
    cin >> name;
    cout << "Введите наименование специальности: ";
    cin >> specialnost;
    cout << "Введите номер группы: ";
    cin >> gruppa;
    cout << "Введите средний бал: ";
    cin >> ball;
    students.emplace_back(name, specialnost, gruppa, ball);
}

int main()
{
    setlocale(LC_ALL, "RU");
    vector<Student> students;
    string filename = "students.txt";
    int choice;
    bool running = true;

    while (running) {
        cout << "1. Добавьте студента\n2. Отсортируйте по названию (asc)\n3. Отсортируйте по названию (desc)\n4. Сохраните в файл\n5. Загрузите из файла\n6. Завершите работу\n";
        cin >> choice;
        switch (choice) {
        case 1:
            addStudent(students);
            break;
        case 2:
            sort(students.begin(), students.end(), Student::compareByNameAsc);
            break;
        case 3:
            sort(students.begin(), students.end(), Student::compareByNameDesc);
            break;
        case 4:
            Student::writeToFile(students, filename);
            break;
        case 5:
            students = Student::readFromFile(filename);
            break;
        case 6:
            running = false;
            break;
        }
    }
    return 0;
}

