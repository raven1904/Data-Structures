// Problem Statement: Write a program to manage student attendance records (number of days present).
/* Implement the following:
a. Compute the average attendance of all students.
b.Find the student with the highest and lowest attendance.
c. Count the number of students with zero attendance.
d.Display the most common attendance count (mode).
e. Also, determine the time and space complexity of each operation.*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits> // for INT_MIN, INT_MAX

using namespace std;

class Student
{
private:
  int roll;
  string name;
  int attendance; // number of lectures attended from total conducted

public:
  // Constructor
  Student(int r, const string &n, int a)
      : roll(r), name(n), attendance(a) {}

  // Setters
  void setRoll(int r) { roll = r; }
  void setName(const string &n) { name = n; }
  void setAttendance(int a) { attendance = a; }

  // Getters
  int getRoll() const { return roll; }
  string getName() const { return name; }
  int getAttendance() const { return attendance; }
};

class StudentManager
{
private:
  vector<Student> students; // all operations loop over this vector

public:
  // Add a new student
  void addStudent(const Student &s)
  {
    students.emplace_back(s); // avoids extra copy
  }

  // Compute the average attendance of all students
  float findAvgAttendance() const
  {
    if (students.empty())
      return 0.0; // avoid division by zero

    float sum = 0.0;
    for (const auto &student : students)
    {
      sum += student.getAttendance();
    }
    return sum / students.size();
  }

  // Find the student(s) with highest attendance
  vector<Student> findHighest() const
  {
    vector<Student> highest;
    int high = INT_MIN;

    for (const auto &student : students)
    {
      if (student.getAttendance() > high)
      {
        high = student.getAttendance();
        highest.clear();
        highest.push_back(student);
      }
      else if (student.getAttendance() == high)
      {
        highest.push_back(student);
      }
    }
    return highest;
  }

  // Find the student(s) with lowest attendance
  vector<Student> findLowest() const
  {
    vector<Student> lowest;
    int low = INT_MAX;

    for (const auto &student : students)
    {
      if (student.getAttendance() < low)
      {
        low = student.getAttendance();
        lowest.clear();
        lowest.push_back(student);
      }
      else if (student.getAttendance() == low)
      {
        lowest.push_back(student);
      }
    }
    return lowest;
  }

  // Count the number of students with zero attendance
  int findZero() const
  {
    int zeroCount = 0;
    for (const auto &student : students)
    {
      if (student.getAttendance() == 0)
      {
        zeroCount++;
      }
    }
    return zeroCount;
  }

  // Display the most common attendance count (mode)
  vector<int> findMostCommonCount() const
  {
    unordered_map<int, int> freq; // map attendance -> frequency
    vector<int> modes;

    if (students.empty())
      return {};

    // Count frequencies
    for (const auto &student : students)
    {
      freq[student.getAttendance()]++;
    }

    // Find max frequency
    int maxFreq = 0;
    for (const auto &[attendance, count] : freq)
    {
      maxFreq = max(maxFreq, count);
    }

    // Collect all attendance values with max frequency
    for (const auto &[attendance, count] : freq)
    {
      if (count == maxFreq)
      {
        modes.push_back(attendance);
      }
    }
    return modes;
  }
};

int main()
{
  StudentManager sm;

  // Sample data
  sm.addStudent(Student(1, "Ada", 10));
  sm.addStudent(Student(2, "Bunty", 0));
  sm.addStudent(Student(3, "Chameli", 10));
  sm.addStudent(Student(4, "Drake", 7));

  cout << "Average attendance: " << sm.findAvgAttendance() << endl;

  cout << "Students with highest attendance: ";
  for (const auto &s : sm.findHighest())
  {
    cout << s.getName() << " (" << s.getAttendance() << ") ";
  }
  cout << endl;

  cout << "Students with lowest attendance: ";
  for (const auto &s : sm.findLowest())
  {
    cout << s.getName() << " (" << s.getAttendance() << ") ";
  }
  cout << endl;

  cout << "Zero attendance count: " << sm.findZero() << endl;

  auto modes = sm.findMostCommonCount();
  cout << "Most common attendance count(s): ";
  for (int m : modes)
  {
    cout << m << " ";
  }
  cout << endl;

  return 0;
}
