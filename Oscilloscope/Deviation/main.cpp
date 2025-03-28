#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>  // Добавлен заголовок для работы с файлами

// Функция вычисления среднего
double computeAverage(const std::vector<double>& inputData)
{
    double totalSum = 0.0;
    for (double num : inputData) {
        totalSum += num;
    }
    return totalSum / inputData.size();
}

// Функция расчета стандартного отклонения
double calculateStdDev(const std::vector<double>& dataVector)
{
    double meanValue = computeAverage(dataVector);
    double squaredDiffsTotal = 0.0;

    for (double val : dataVector)
    {
        squaredDiffsTotal += std::pow(val - meanValue, 2);
    }

    return std::sqrt(squaredDiffsTotal / (dataVector.size() * (dataVector.size() - 1)));
}

// Основная логика обработки данных
void processAndDisplayResults() 
{
    std::vector<double> datasetA = { 0.785674, 0.648722, 0.606092, 0.601793, 0.55942 };
    std::vector<double> datasetB = { 1.17851, 0.83189, 0.774205, 0.700106, 0.667082 };

    double averageA = computeAverage(datasetA);
    double stdDevA = calculateStdDev(datasetA);

    double averageB = computeAverage(datasetB);
    double stdDevB = calculateStdDev(datasetB);

    // Вывод в консоль
    std::cout << "Среднее значение S_y: " << averageA << std::endl;
    std::cout << "Стандартное отклонение S_y: " << stdDevA << std::endl;
    std::cout << std::endl;
    std::cout << "Среднее значение S_x: " << averageB << std::endl;
    std::cout << "Стандартное отклонение S_x: " << stdDevB << std::endl;

    // Запись в файл
    std::ofstream outFile("output.txt");
    if (outFile.is_open()) 
    {
        outFile << "Среднее значение S_y: " << averageA << std::endl;
        outFile << "Стандартное отклонение S_y: " << stdDevA << std::endl;
        outFile << std::endl;
        outFile << "Среднее значение S_x: " << averageB << std::endl;
        outFile << "Стандартное отклонение S_x: " << stdDevB << std::endl;

        outFile.close();
    }
    else 
    {
        std::cerr << "Ошибка при открытии файла для записи!" << std::endl;
    }
}

int main() 
{
    setlocale(LC_ALL, "Russian");

    processAndDisplayResults();
    return 0;
}