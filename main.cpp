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
    cout << "\nКвартиры с площадью больше " << minArea << ":" << endl;

    double minAreaFound = 100;
    int flatIndex = -1;

    for (int i = 0; i < flats.size(); i++) {
        if (flats[i].area > minArea) {
            cout << "Номер квартиры: " << flats[i].numberOfFlat << ", Владелец: " << flats[i].owner
                 << ", Площадь: " << flats[i].area << ", Количество комнат: " << flats[i].numberOfRooms << endl;

            if (flats[i].area < minAreaFound) {
                minAreaFound = flats[i].area;
                flatIndex = i;
            }
        }
    }

    if (flatIndex != -1) {
        cout << "\nКвартира с наименьшей площадью среди данных квартир:" << endl;
        cout << "Номер квартиры: " << flats[flatIndex].numberOfFlat << ", Владелец: " << flats[flatIndex].owner
             << ", Площадь: " << flats[flatIndex].area << ", Количество комнат: " << flats[flatIndex].numberOfRooms << endl;
    }
    else {
        cout << "Таких квартир нет." << endl;
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
    cout << "Введите минимальную площадь квартиры: ";
    cin >> minArea;
    printFlats(flats, minArea);

    int roomCount;
    cout << "\nВведите количество комнат для расчета средней площади: ";
    cin >> roomCount;
    double averageArea = calculateAverageAreaForRooms(flats, roomCount);

    if (averageArea > 0) {
        cout << "\nСредняя площадь квартир с заданным количеством комнат: " << averageArea << endl;
    }
    else {
        cout << "\nНет квартир с таким количеством комнат." << endl;
    }
    return 0;
}
