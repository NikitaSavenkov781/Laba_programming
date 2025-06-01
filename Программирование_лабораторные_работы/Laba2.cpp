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

// ������� ����
void createFile() 
{
    ofstream file(FILENAME, ios::binary | ios::trunc);
    file.close();
    cout << "���� ������.\n";
}

void addRecord()
 {
    UAV uav;
    cout << "������: "; cin.getline(uav.model, 32);
    cout << "��� �������: "; cin >> uav.year;
    cout << "��� ���������: "; cin >> ws; cin.getline(uav.info.fio, 64);
    cout << "����� �������������: "; cin.getline(uav.info.license, 32);
    cout << "������� ����������: "; cin >> ws; cin.getline(uav.controlSystem, 64);

    ofstream file(FILENAME, ios::binary | ios::app);
    file.write(reinterpret_cast<char*>(&uav), sizeof(UAV));
    file.close();
    cout << "������ ���������.\n";
}

void viewFile() {
    ifstream file(FILENAME, ios::binary);
    UAV uav;
    int idx = 0;
    while (file.read(reinterpret_cast<char*>(&uav), sizeof(UAV))) {
        cout << "\n������ #" << ++idx << endl;
        cout << "������: " << uav.model << endl;
        cout << "��� �������: " << uav.year << endl;
        cout << "��� ���������: " << uav.info.fio << endl;
        cout << "����� �������������: " << uav.info.license << endl;
        cout << "������� ����������: " << uav.controlSystem << endl;
    }
    file.close();
    if (idx == 0) cout << "���� ����.\n";
}

void deleteRecord() 
{
    cout << "������� ����� ������ ��� ��������: ";
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
    cout << "������ ������� (���� ������������).\n";
}

void updateRecord() {
    cout << "������� ����� ������ ��� ����������: ";
    int updNum; cin >> updNum;
    fstream file(FILENAME, ios::binary | ios::in | ios::out);
    UAV uav;
    int idx = 0;
    streampos pos;
    while (file.read(reinterpret_cast<char*>(&uav), sizeof(UAV))) {
        ++idx;
        if (idx == updNum) {
            pos = file.tellg();
            cout << "������� ����� ������:\n";
            cout << "������: "; cin.getline(uav.model, 32);
            cout << "��� �������: "; cin >> uav.year;
            cout << "��� ���������: "; cin >> ws; cin.getline(uav.info.fio, 64);
            cout << "����� �������������: "; cin.getline(uav.info.license, 32);
            cout << "������� ����������: "; cin >> ws; cin.getline(uav.controlSystem, 64);
            file.seekp(pos - static_cast<streamoff>(sizeof(UAV)));
            file.write(reinterpret_cast<char*>(&uav), sizeof(UAV));
            cout << "������ ���������.\n";
            break;
        }
    }
    file.close();
}

void findOwnerBySystem() 
{
    cout << "������� ������� ���������� ����: ";
    char searchSystem[32];
    cin >> ws; cin.getline(searchSystem, 32);
    ifstream file(FILENAME, ios::binary);
    UAV uav;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&uav), sizeof(UAV)))
	{
        if (strcmp(uav.controlSystem, searchSystem) == 0) 
		{
            cout << "��� ���������: " << uav.info.fio << endl;
            found = true;
        }
    }
    file.close();
    if (!found) cout << "���� � ����� �������� ���������� �� ������.\n";
}


int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    do {
        cout << "\n����:\n";
        cout << "1. �������� �����\n";
        cout << "2. ���������� ������\n";
        cout << "3. �������� ������\n";
        cout << "4. �������� ����� �����\n";
        cout << "5. ���������� ������\n";
        cout << "6. ����� ��� ��������� �� ������ ����������\n";
        cout << "7. �����\n";
        cout << "�������� ��������: ";
        cin >> choice;
        switch (choice) {
            case 1: createFile(); break;
            case 2: addRecord(); break;
            case 3: deleteRecord(); break;
            case 4: viewFile(); break;
            case 5: updateRecord(); break;
            case 6: findOwnerBySystem(); break;
            case 7: cout << "�����.\n"; break;
            default: cout << "�������� �����.\n";
        }
    } while (choice != 8);
    return 0;
}
