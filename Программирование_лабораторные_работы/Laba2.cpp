#include <iostream>
#include <locale.h>
#include <vector>

#include <string>
#include <math.h>

using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

struct Info 
{
    char fio[64];
    char license[32];
};

struct UAV 
{
    char model[32];
    int year;
    Info info;
    char controlSystem[64]; 
};

const char* FILENAME = "uav.dat";

// Создать файл
void createFile() 
{
    ofstream file(FILENAME, ios::binary | ios::trunc);
    file.close();
    cout << "Файл создан.\n";
}

void addRecord()
 {
    UAV uav;
    cout << "Модель: "; cin.getline(uav.model, 32);
    cout << "Год выпуска: "; cin >> uav.year;
    cout << "ФИО владельца: "; cin >> ws; cin.getline(uav.info.fio, 64);
    cout << "Номер удостоверения: "; cin.getline(uav.info.license, 32);
    cout << "Система управления: "; cin >> ws; cin.getline(uav.controlSystem, 64);

    ofstream file(FILENAME, ios::binary | ios::app);
    file.write(reinterpret_cast<char*>(&uav), sizeof(UAV));
    file.close();
    cout << "Запись добавлена.\n";
}

void viewFile() {
    ifstream file(FILENAME, ios::binary);
    UAV uav;
    int idx = 0;
    while (file.read(reinterpret_cast<char*>(&uav), sizeof(UAV))) {
        cout << "\nЗапись #" << ++idx << endl;
        cout << "Модель: " << uav.model << endl;
        cout << "Год выпуска: " << uav.year << endl;
        cout << "ФИО владельца: " << uav.info.fio << endl;
        cout << "Номер удостоверения: " << uav.info.license << endl;
        cout << "Система управления: " << uav.controlSystem << endl;
    }
    file.close();
    if (idx == 0) cout << "Файл пуст.\n";
}

void deleteRecord() 
{
    cout << "Введите номер записи для удаления: ";
    int delNum; cin >> delNum;
    ifstream file(FILENAME, ios::binary);
    vector<UAV> records;
    UAV uav;
    int idx = 0;
    while (file.read(reinterpret_cast<char*>(&uav), sizeof(UAV))) {
        ++idx;
        if (idx != delNum) records.push_back(uav);
    }
    file.close();
    ofstream out(FILENAME, ios::binary | ios::trunc);
for (size_t i = 0; i < records.size(); ++i)
    out.write(reinterpret_cast<const char*>(&records[i]), sizeof(UAV));
    out.close();
    cout << "Запись удалена (если существовала).\n";
}

void updateRecord() {
    cout << "Введите номер записи для обновления: ";
    int updNum; cin >> updNum;
    fstream file(FILENAME, ios::binary | ios::in | ios::out);
    UAV uav;
    int idx = 0;
    streampos pos;
    while (file.read(reinterpret_cast<char*>(&uav), sizeof(UAV))) {
        ++idx;
        if (idx == updNum) {
            pos = file.tellg();
            cout << "Введите новые данные:\n";
            cout << "Модель: "; cin.getline(uav.model, 32);
            cout << "Год выпуска: "; cin >> uav.year;
            cout << "ФИО владельца: "; cin >> ws; cin.getline(uav.info.fio, 64);
            cout << "Номер удостоверения: "; cin.getline(uav.info.license, 32);
            cout << "Система управления: "; cin >> ws; cin.getline(uav.controlSystem, 64);
            file.seekp(pos - static_cast<streamoff>(sizeof(UAV)));
            file.write(reinterpret_cast<char*>(&uav), sizeof(UAV));
            cout << "Запись обновлена.\n";
            break;
        }
    }
    file.close();
}

void findOwnerBySystem() 
{
    cout << "Введите систему управления БПЛА: ";
    char searchSystem[32];
    cin >> ws; cin.getline(searchSystem, 32);
    ifstream file(FILENAME, ios::binary);
    UAV uav;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&uav), sizeof(UAV)))
	{
        if (strcmp(uav.controlSystem, searchSystem) == 0) 
		{
            cout << "ФИО владельца: " << uav.info.fio << endl;
            found = true;
        }
    }
    file.close();
    if (!found) cout << "БПЛА с такой системой управления не найден.\n";
}


int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Создание файла\n";
        cout << "2. Добавление записи\n";
        cout << "3. Удаление записи\n";
        cout << "4. Просмотр всего файла\n";
        cout << "5. Обновление записи\n";
        cout << "6. Найти ФИО владельца по ситеме управления\n";
        cout << "7. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        switch (choice) {
            case 1: createFile(); break;
            case 2: addRecord(); break;
            case 3: deleteRecord(); break;
            case 4: viewFile(); break;
            case 5: updateRecord(); break;
            case 6: findOwnerBySystem(); break;
            case 7: cout << "Выход.\n"; break;
            default: cout << "Неверный выбор.\n";
        }
    } while (choice != 8);
    return 0;
}
