
#include "pch.h"
#include "CppUnitTest.h"
#include "Students.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Lab10_2_B_Tests
{
    TEST_CLASS(StudentTests)
    {
    private:
        Student MakeStudent(
            const string& surname,
            Specialty specialty,
            int physics)
        {
            Student s = {};
            s.surname = surname;
            s.specialty = specialty;
            s.physics = physics;
            s.course = 1;
            s.math = 4;
            s.programming = 5;
            return s;
        }

    public:

        // 1. Порівняння за фізикою
        TEST_METHOD(TestComparePhysics)
        {
            Student a = MakeStudent("A", COMPUTER_SCIENCE, 3);
            Student b = MakeStudent("B", COMPUTER_SCIENCE, 5);

            Assert::AreEqual(-1, Compare(a, b));
        }

        // 2. Порівняння за назвою спеціальності
        TEST_METHOD(TestCompareSpecialty)
        {
            Student a = MakeStudent("A", COMPUTER_SCIENCE, 4);
            Student b = MakeStudent("B", INFORMATICS, 4);

            Assert::AreEqual(-1, Compare(a, b));
        }

        // 3. Порівняння за прізвищем
        TEST_METHOD(TestCompareSurname)
        {
            Student a = MakeStudent("Ivanenko", INFORMATICS, 4);
            Student b = MakeStudent("Petrenko", INFORMATICS, 4);

            Assert::AreEqual(-1, Compare(a, b));
        }

        // 4. Однакові ключі порівняння
        TEST_METHOD(TestCompareEqual)
        {
            Student a = MakeStudent("Ivanenko", INFORMATICS, 5);
            Student b = MakeStudent("Ivanenko", INFORMATICS, 5);

            Assert::AreEqual(0, Compare(a, b));
        }

        // 5. Фізичне сортування
        TEST_METHOD(TestPhysicalSort)
        {
            Student s[3] = {
                MakeStudent("Petrenko", INFORMATICS, 5),
                MakeStudent("Ivanenko", COMPUTER_SCIENCE, 3),
                MakeStudent("Kovalenko", MATH_ECONOMICS, 4)
            };

            Sort(s, 3);

            Assert::AreEqual(string("Ivanenko"), s[0].surname);
            Assert::AreEqual(string("Kovalenko"), s[1].surname);
            Assert::AreEqual(string("Petrenko"), s[2].surname);
        }

        // 6. Індексне сортування
        TEST_METHOD(TestIndexSort)
        {
            Student s[3] = {
                MakeStudent("Petrenko", INFORMATICS, 5),
                MakeStudent("Ivanenko", COMPUTER_SCIENCE, 3),
                MakeStudent("Kovalenko", MATH_ECONOMICS, 4)
            };

            int* I = IndexSort(s, 3);

            Assert::AreEqual(1, I[0]);
            Assert::AreEqual(2, I[1]);
            Assert::AreEqual(0, I[2]);

            // Початковий масив не змінюється
            Assert::AreEqual(string("Petrenko"), s[0].surname);

            delete[] I;
        }

        // 7. Бінарний пошук: студента знайдено
        TEST_METHOD(TestBinarySearchFound)
        {
            Student s[3] = {
                MakeStudent("Ivanenko", COMPUTER_SCIENCE, 3),
                MakeStudent("Kovalenko", MATH_ECONOMICS, 4),
                MakeStudent("Petrenko", INFORMATICS, 5)
            };

            int pos = BinSearch(
                s, 3, "Kovalenko", MATH_ECONOMICS, 4);

            Assert::AreEqual(1, pos);
        }

        // 8. Бінарний пошук: студента немає
        TEST_METHOD(TestBinarySearchNotFound)
        {
            Student s[2] = {
                MakeStudent("Ivanenko", COMPUTER_SCIENCE, 3),
                MakeStudent("Petrenko", INFORMATICS, 5)
            };

            int pos = BinSearch(
                s, 2, "Unknown", INFORMATICS, 5);

            Assert::AreEqual(-1, pos);
        }

        // 9. Індексний бінарний пошук
        TEST_METHOD(TestIndexBinarySearch)
        {
            Student s[3] = {
                MakeStudent("Petrenko", INFORMATICS, 5),
                MakeStudent("Ivanenko", COMPUTER_SCIENCE, 3),
                MakeStudent("Kovalenko", MATH_ECONOMICS, 4)
            };

            int* I = IndexSort(s, 3);

            int pos = IndexBinSearch(
                s, I, 3, "Ivanenko", COMPUTER_SCIENCE, 3);

            Assert::AreEqual(0, pos);

            delete[] I;
        }

        // 10. Перевірка union
        TEST_METHOD(TestUnion)
        {
            Student s = {};

            s.specialty = COMPUTER_SCIENCE;
            s.programming = 4;
            Assert::AreEqual(4, s.programming);

            s.specialty = INFORMATICS;
            s.numerical = 5;
            Assert::AreEqual(5, s.numerical);

            s.specialty = LABOR_TRAINING;
            s.pedagogy = 3;
            Assert::AreEqual(3, s.pedagogy);
        }
    };
}
