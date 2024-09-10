#pragma once
#include "student.h"
#include <set>
#include <mutex>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>

class Group {
private:
    std::set<Student> students; // Поля класса группы
    mutable std::mutex mtx;
    std::string group_name;

public:
    Group() = default; // Пустой конструктор
    Group(const Group& group_2); // Конструктор копирования
    Group(const std::string& name); // Конструктор с именем группы
    ~Group(); // Деструктор
    void set_group_name(const std::string& name); // Сеттер названия группы
    std::string get_group_name() const; // Геттер названия группы
    void add_student(const Student& student); // Добавление студента
    bool find_student_by_ID(const std::string& id, Student& student); // Поиск студента по id
    void edit_student(const std::string& id, const Student& new_student); // Изменение параметров студента
    void remove_student(const std::string& id); // Удаление студента
    void save_to_file(const std::string& file); // Сохранение в файл
    void load_from_file(const std::string& file); // Чтение из файла
    void sort_print_by_field(const std::string& field); // Сортировка и вывод студентов по значению поля
    void print_students() const; // Печать всех студентов

    Group operator +(const Student& student) const; // Перегрузка оператора сложения для добавления студента в группу
    Group operator+(const Group& other) const; // Перегрузка оператора сложения для сложания двух групп
    void add_students_to_group(const std::vector<Student>& students, Group& group);
    friend std::ostream& operator<<(std::ostream& stream,  Group& group); // Перегрузка оператора вывода в стандартный поток
};
