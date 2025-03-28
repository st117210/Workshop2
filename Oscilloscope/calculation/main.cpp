#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

// Функция для чтения данных из файла в вектор
std::vector<double> readData(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) 
	{
		throw std::runtime_error("Не удалось открыть файл " + filename);
	}

	std::vector<double> data;
	double value;
	while (file >> value)
	{
		data.push_back(value);
	}

	return data;
}

// Функция для расчета чувствительности
std::vector<double> calculateSensitivity(const std::vector<double>& L, const std::vector<double>& U)
{
	std::vector<double> sensitivity;

	for (size_t i = 0; i < L.size(); ++i)
	{
		double S = L[i] / (2 * std::sqrt(2) * U[i]);
		sensitivity.push_back(S);
	}

	return sensitivity;
}

int main()
{

	setlocale(LC_ALL, "Russian");
	// Массив значений L для первого и второго файлов
	std::vector<double> L_vertical_horizontal = { 10, 20, 30, 40, 50 };
	// Массив значений L для последнего файла (Ueff_max.txt)
	std::vector<double> L_max = { 10, 20, 30, 40 };

	// Чтение данных из файлов
	std::vector<double> vertical;
	std::vector<double> horizontal;
	std::vector<double> max_u;

	// Чтение данных из файлов
	vertical = readData("Vertical.txt");
	horizontal = readData("Horizontal.txt");
	max_u = readData("Max.txt");

	// Расчет чувствительности для вертикальных и горизонтальных данных
	std::vector<double> s_vertical = calculateSensitivity(L_vertical_horizontal, vertical);
	std::vector<double> s_horizontal = calculateSensitivity(L_vertical_horizontal, horizontal);

	// Расчет чувствительности для данных из Ueff_max.txt
	std::vector<double> s_max = calculateSensitivity(L_max, max_u);

	// Вывод результатов для вертикальных данных
	std::cout << "Чувствительность для вертикальных данных:" << std::endl;
	for (size_t i = 0; i < s_vertical.size(); ++i)
	{
		std::cout << "L = " << L_vertical_horizontal[i] << ", S = " << s_vertical[i] << std::endl;
	}

	// Вывод результатов для горизонтальных данных
	std::cout << "\nЧувствительность для горизонтальных данных:" << std::endl;
	for (size_t i = 0; i < s_horizontal.size(); ++i)
	{
		std::cout << "L = " << L_vertical_horizontal[i] << ", S = " << s_horizontal[i] << std::endl;
	}

	std::ofstream outputFile("output_data.txt");

	outputFile << "Чувствительность для данных из Max.txt:" << std::endl;
	for (size_t i = 0; i < s_max.size(); ++i) 
	{
		outputFile << "L = " << L_max[i] << ", S = " << s_max[i] << std::endl;
	}

	outputFile.close();
	std::cout << "Результаты записаны в файл output_max.txt" << std::endl;

	return 0;
}
