
#pragma once
#include <string>

enum Specialty
{
    COMPUTER_SCIENCE,
    MATH_ECONOMICS,
    PHYSICS_INFORMATICS,
    INFORMATICS,
    LABOR_TRAINING
};

struct Student
{
    std::string surname;
    int course = 0;
    Specialty specialty = COMPUTER_SCIENCE;
    int physics = 0;
    int math = 0;

    union
    {
        int programming = 0;
        int numerical;
        int pedagogy;
    };
};

int ReadInt(const std::string& prompt, int min, int max);
std::string ReadSurname(const std::string& prompt);
std::string SpecialtyToString(Specialty specialty);

int Compare(const Student& a, const Student& b);

void Create(Student* students, int N);
void Print(const Student* students, int N);

void Sort(Student* students, int N);

int* IndexSort(const Student* students, int N);
void PrintIndexSorted(const Student* students, const int* I, int N);

int BinSearch(const Student* students, int N,
    const std::string& surname,
    Specialty specialty, int physics);

int IndexBinSearch(const Student* students, const int* I, int N,
    const std::string& surname,
    Specialty specialty, int physics);
