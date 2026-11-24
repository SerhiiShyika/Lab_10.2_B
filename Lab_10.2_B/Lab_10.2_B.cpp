
// Lab_10.2_B.cpp
// Шийка Сергій Іванович
// Лабораторна робота № 10.2 Б
// Варіант 31

#include <iostream>
#include "Students.h"

using namespace std;

int main()
{
    int N = ReadInt("Enter number of students (1-100): ", 1, 100);

    Student* students = new Student[N];
    int* I = nullptr;

    bool sorted = false;
    bool filled = false;
    int menuItem;

    do
    {
        cout << "\nChoose an action:\n";
        cout << "[1] Enter students\n";
        cout << "[2] Print table\n";
        cout << "[3] Physical sort\n";
        cout << "[4] Index sort\n";
        cout << "[5] Binary search\n";
        cout << "[6] Index binary search\n";
        cout << "[0] Exit\n\n";

        menuItem = ReadInt("Enter value: ", 0, 6);

        switch (menuItem)
        {
        case 1:
            Create(students, N);
            filled = true;
            sorted = false;

            delete[] I;
            I = nullptr;
            break;

        case 2:
            if (filled)
                Print(students, N);
            else
                cout << "Enter students first.\n";
            break;

        case 3:
            if (!filled)
            {
                cout << "Enter students first.\n";
                break;
            }

            Sort(students, N);
            sorted = true;

            delete[] I;
            I = nullptr;

            cout << "Array is physically sorted.\n";
            Print(students, N);
            break;

        case 4:
            if (!filled)
            {
                cout << "Enter students first.\n";
                break;
            }

            delete[] I;
            I = IndexSort(students, N);

            PrintIndexSorted(students, I, N);
            break;

        case 5:
        case 6:
        {
            if (!filled)
            {
                cout << "Enter students first.\n";
                break;
            }

            if (menuItem == 5 && !sorted)
            {
                cout << "Use physical sort [3] first.\n";
                break;
            }

            if (menuItem == 6 && I == nullptr)
            {
                cout << "Use index sort [4] first.\n";
                break;
            }

            string surname = ReadSurname("Enter surname: ");

            cout << "0 - Computer Science\n";
            cout << "1 - Math and Economics\n";
            cout << "2 - Physics and Informatics\n";
            cout << "3 - Informatics\n";
            cout << "4 - Labor Training\n";

            int sp = ReadInt("Specialty (0-4): ", 0, 4);
            int physics = ReadInt("Physics (1-5): ", 1, 5);

            int pos;

            if (menuItem == 5)
            {
                pos = BinSearch(
                    students, N, surname,
                    static_cast<Specialty>(sp), physics);
            }
            else
            {
                pos = IndexBinSearch(
                    students, I, N, surname,
                    static_cast<Specialty>(sp), physics);
            }

            if (pos == -1)
                cout << "Student NOT found.\n";
            else
                cout << "Student found at sorted row #"
                << pos + 1 << endl;

            break;
        }
        }

    } while (menuItem != 0);

    delete[] I;
    delete[] students;

    return 0;
}
