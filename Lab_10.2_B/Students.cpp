
#include "Students.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

int ReadInt(const string& prompt, int min, int max)
{
    int value;

    while (true)
    {
        cout << prompt;

        if (cin >> value && value >= min && value <= max)
            return value;

        cout << "Incorrect value. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string ReadSurname(const string& prompt)
{
    string surname;
    cout << prompt;
    cin >> surname;
    return surname;
}

string SpecialtyToString(Specialty specialty)
{
    switch (specialty)
    {
    case COMPUTER_SCIENCE: return "Computer Science";
    case MATH_ECONOMICS: return "Math and Economics";
    case PHYSICS_INFORMATICS: return "Physics and Informatics";
    case INFORMATICS: return "Informatics";
    case LABOR_TRAINING: return "Labor Training";
    default: return "Unknown";
    }
}

int Compare(const Student& a, const Student& b)
{
    if (a.physics < b.physics) return -1;
    if (a.physics > b.physics) return 1;

    string sa = SpecialtyToString(a.specialty);
    string sb = SpecialtyToString(b.specialty);

    if (sa < sb) return -1;
    if (sa > sb) return 1;

    if (a.surname < b.surname) return -1;
    if (a.surname > b.surname) return 1;

    return 0;
}

void Create(Student* students, int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "\nStudent #" << i + 1 << endl;

        students[i].surname = ReadSurname("Surname: ");
        students[i].course = ReadInt("Course (1-6): ", 1, 6);

        cout << "0 - Computer Science\n";
        cout << "1 - Math and Economics\n";
        cout << "2 - Physics and Informatics\n";
        cout << "3 - Informatics\n";
        cout << "4 - Labor Training\n";

        int sp = ReadInt("Specialty (0-4): ", 0, 4);
        students[i].specialty = static_cast<Specialty>(sp);

        students[i].physics = ReadInt("Physics (1-5): ", 1, 5);
        students[i].math = ReadInt("Math (1-5): ", 1, 5);

        switch (students[i].specialty)
        {
        case COMPUTER_SCIENCE:
            students[i].programming =
                ReadInt("Programming (1-5): ", 1, 5);
            break;

        case INFORMATICS:
            students[i].numerical =
                ReadInt("Numerical methods (1-5): ", 1, 5);
            break;

        default:
            students[i].pedagogy =
                ReadInt("Pedagogy (1-5): ", 1, 5);
            break;
        }
    }
}

static void PrintHeader()
{
    cout << string(114, '-') << endl;

    cout << "| " << setw(3) << right << "No"
        << " | " << setw(15) << left << "Surname"
        << " | " << setw(6) << right << "Course"
        << " | " << setw(23) << left << "Specialty"
        << " | " << setw(7) << right << "Physics"
        << " | " << setw(4) << right << "Math"
        << " | " << setw(11) << right << "Programming"
        << " | " << setw(9) << right << "Numerical"
        << " | " << setw(8) << right << "Pedagogy"
        << " |" << endl;

    cout << string(114, '-') << endl;
}

static void PrintRow(const Student& s, int number)
{
    cout << "| " << setw(3) << right << number
        << " | " << setw(15) << left << s.surname
        << " | " << setw(6) << right << s.course
        << " | " << setw(23) << left
        << SpecialtyToString(s.specialty)
        << " | " << setw(7) << right << s.physics
        << " | " << setw(4) << right << s.math
        << " | ";

    if (s.specialty == COMPUTER_SCIENCE)
        cout << setw(11) << right << s.programming;
    else
        cout << setw(11) << right << "";

    cout << " | ";

    if (s.specialty == INFORMATICS)
        cout << setw(9) << right << s.numerical;
    else
        cout << setw(9) << right << "";

    cout << " | ";

    if (s.specialty != COMPUTER_SCIENCE &&
        s.specialty != INFORMATICS)
        cout << setw(8) << right << s.pedagogy;
    else
        cout << setw(8) << right << "";

    cout << " |" << endl;
}

void Print(const Student* students, int N)
{
    cout << "\nSTUDENTS TABLE\n";
    PrintHeader();

    for (int i = 0; i < N; i++)
        PrintRow(students[i], i + 1);

    cout << string(114, '-') << endl;
}

void Sort(Student* students, int N)
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (Compare(students[j], students[j + 1]) > 0)
            {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

int* IndexSort(const Student* students, int N)
{
    int* I = new int[N];

    for (int i = 0; i < N; i++)
        I[i] = i;

    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (Compare(students[I[j]],
                students[I[j + 1]]) > 0)
            {
                int temp = I[j];
                I[j] = I[j + 1];
                I[j + 1] = temp;
            }
        }
    }

    return I;
}

void PrintIndexSorted(
    const Student* students, const int* I, int N)
{
    cout << "\nINDEX SORTED TABLE\n";
    PrintHeader();

    for (int i = 0; i < N; i++)
        PrintRow(students[I[i]], i + 1);

    cout << string(114, '-') << endl;
}

int BinSearch(
    const Student* students, int N,
    const string& surname,
    Specialty specialty, int physics)
{
    Student key = {};
    key.surname = surname;
    key.specialty = specialty;
    key.physics = physics;

    int left = 0;
    int right = N - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int result = Compare(students[mid], key);

        if (result == 0)
            return mid;

        if (result < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

int IndexBinSearch(
    const Student* students, const int* I, int N,
    const string& surname,
    Specialty specialty, int physics)
{
    Student key = {};
    key.surname = surname;
    key.specialty = specialty;
    key.physics = physics;

    int left = 0;
    int right = N - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int result = Compare(students[I[mid]], key);

        if (result == 0)
            return mid;

        if (result < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}
