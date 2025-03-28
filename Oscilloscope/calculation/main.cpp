#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

// ������� ��� ������ ������ �� ����� � ������
std::vector<double> readData(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) 
	{
		throw std::runtime_error("�� ������� ������� ���� " + filename);
	}

	std::vector<double> data;
	double value;
	while (file >> value)
	{
		data.push_back(value);
	}

	return data;
}

// ������� ��� ������� ����������������
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
	// ������ �������� L ��� ������� � ������� ������
	std::vector<double> L_vertical_horizontal = { 10, 20, 30, 40, 50 };
	// ������ �������� L ��� ���������� ����� (Ueff_max.txt)
	std::vector<double> L_max = { 10, 20, 30, 40 };

	// ������ ������ �� ������
	std::vector<double> vertical;
	std::vector<double> horizontal;
	std::vector<double> max_u;

	// ������ ������ �� ������
	vertical = readData("Vertical.txt");
	horizontal = readData("Horizontal.txt");
	max_u = readData("Max.txt");

	// ������ ���������������� ��� ������������ � �������������� ������
	std::vector<double> s_vertical = calculateSensitivity(L_vertical_horizontal, vertical);
	std::vector<double> s_horizontal = calculateSensitivity(L_vertical_horizontal, horizontal);

	// ������ ���������������� ��� ������ �� Ueff_max.txt
	std::vector<double> s_max = calculateSensitivity(L_max, max_u);

	// ����� ����������� ��� ������������ ������
	std::cout << "���������������� ��� ������������ ������:" << std::endl;
	for (size_t i = 0; i < s_vertical.size(); ++i)
	{
		std::cout << "L = " << L_vertical_horizontal[i] << ", S = " << s_vertical[i] << std::endl;
	}

	// ����� ����������� ��� �������������� ������
	std::cout << "\n���������������� ��� �������������� ������:" << std::endl;
	for (size_t i = 0; i < s_horizontal.size(); ++i)
	{
		std::cout << "L = " << L_vertical_horizontal[i] << ", S = " << s_horizontal[i] << std::endl;
	}

	std::ofstream outputFile("output_data.txt");

	outputFile << "���������������� ��� ������ �� Max.txt:" << std::endl;
	for (size_t i = 0; i < s_max.size(); ++i) 
	{
		outputFile << "L = " << L_max[i] << ", S = " << s_max[i] << std::endl;
	}

	outputFile.close();
	std::cout << "���������� �������� � ���� output_max.txt" << std::endl;

	return 0;
}
