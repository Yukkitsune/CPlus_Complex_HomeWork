#pragma once
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <map>
#include <vector>


class Student {
	std::map<std::string, std::vector<double>> grades; // Объявляем поля класса
	std::string fio;
	std::string id;
	std::string email;
public:
	Student();
	Student(const std::string& fio,const std::string& id, const std::string& email); // Конструктор класса
	Student(const Student& other); // Копирование
	Student(const std::string& fio, const std::string& id,const std::string& email, const std::map<std::string, std::vector<double>>& grades); // Конструктор с оценками
	~Student(); // Деструктор
	void add_grade(const std::string& subject, double grade); // Добавление оценок студенту
	double get_avg_grade() const; // Средняя оценка
	double get_grade_by_subject(const std::string& subject) const; // Средняя оценка по предмету
	bool operator<(const Student& other) const; // Перегрузка оператора срвнения
	std::string get_id() const; // Геттеры
	std::string get_fio() const;
	std::string get_email() const;
	std::map<std::string, std::vector<double>> get_grades() const; // Получение всех оценок
	void print() const; // Вывод на печать
	friend std::ostream& operator<<(std::ostream& stream, const Student& student); // Перегрузка оператора вывода в стандартный поток
	
};
