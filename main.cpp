#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Flat {
    Flat(int _numberOfFlat, string _owner, double _area, int _numberOfRooms):
        numberOfFlat{_numberOfFlat}, owner{_owner}, area{_area}, numberOfRooms{_numberOfRooms} {}

    int numberOfFlat, numberOfRooms;
    double area;
    string owner;
};

void getInformation(vector<Flat>& flats) {
    ifstream file("file.txt");
    if (file.is_open()) {
        int numberOfFlat;
        int numberOfRooms;
        double area;
        string owner;
        while (file >> numberOfFlat >> owner >> area >> numberOfRooms) {
            flats.push_back(Flat{numberOfFlat, owner, area, numberOfRooms});
        }
    }
}

void printFlats(vector<Flat>& flats, double minArea) {
    cout << "\n�������� � �������� ������ " << minArea << ":" << endl;

    double minAreaFound = 100;
    int flatIndex = -1;

    for (int i = 0; i < flats.size(); i++) {
        if (flats[i].area > minArea) {
            cout << "����� ��������: " << flats[i].numberOfFlat << ", ��������: " << flats[i].owner
                 << ", �������: " << flats[i].area << ", ���������� ������: " << flats[i].numberOfRooms << endl;

            if (flats[i].area < minAreaFound) {
                minAreaFound = flats[i].area;
                flatIndex = i;
            }
        }
    }

    if (flatIndex != -1) {
        cout << "\n�������� � ���������� �������� ����� ������ �������:" << endl;
        cout << "����� ��������: " << flats[flatIndex].numberOfFlat << ", ��������: " << flats[flatIndex].owner
             << ", �������: " << flats[flatIndex].area << ", ���������� ������: " << flats[flatIndex].numberOfRooms << endl;
    }
    else {
        cout << "����� ������� ���." << endl;
    }
}

double calculateAverageAreaForRooms(vector<Flat>& flats, int roomCount) {
    double totalArea = 0;
    int countOfRooms = 0;

    for (Flat& f: flats) {
        if (f.numberOfRooms == roomCount) {
            totalArea += f.area;
            countOfRooms++;
        }
    }
    return (totalArea / countOfRooms);
}

int main() {
    setlocale(LC_ALL, "russian");

    vector<Flat> flats;
    getInformation(flats);

    double minArea;
    cout << "������� ����������� ������� ��������: ";
    cin >> minArea;
    printFlats(flats, minArea);

    int roomCount;
    cout << "\n������� ���������� ������ ��� ������� ������� �������: ";
    cin >> roomCount;
    double averageArea = calculateAverageAreaForRooms(flats, roomCount);

    if (averageArea > 0) {
        cout << "\n������� ������� ������� � �������� ����������� ������: " << averageArea << endl;
    }
    else {
        cout << "\n��� ������� � ����� ����������� ������." << endl;
    }
    return 0;
}
