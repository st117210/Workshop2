#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>  // �������� ��������� ��� ������ � �������

// ������� ���������� ��������
double computeAverage(const std::vector<double>& inputData)
{
    double totalSum = 0.0;
    for (double num : inputData) {
        totalSum += num;
    }
    return totalSum / inputData.size();
}

// ������� ������� ������������ ����������
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

// �������� ������ ��������� ������
void processAndDisplayResults() 
{
    std::vector<double> datasetA = { 0.785674, 0.648722, 0.606092, 0.601793, 0.55942 };
    std::vector<double> datasetB = { 1.17851, 0.83189, 0.774205, 0.700106, 0.667082 };

    double averageA = computeAverage(datasetA);
    double stdDevA = calculateStdDev(datasetA);

    double averageB = computeAverage(datasetB);
    double stdDevB = calculateStdDev(datasetB);

    // ����� � �������
    std::cout << "������� �������� S_y: " << averageA << std::endl;
    std::cout << "����������� ���������� S_y: " << stdDevA << std::endl;
    std::cout << std::endl;
    std::cout << "������� �������� S_x: " << averageB << std::endl;
    std::cout << "����������� ���������� S_x: " << stdDevB << std::endl;

    // ������ � ����
    std::ofstream outFile("output.txt");
    if (outFile.is_open()) 
    {
        outFile << "������� �������� S_y: " << averageA << std::endl;
        outFile << "����������� ���������� S_y: " << stdDevA << std::endl;
        outFile << std::endl;
        outFile << "������� �������� S_x: " << averageB << std::endl;
        outFile << "����������� ���������� S_x: " << stdDevB << std::endl;

        outFile.close();
    }
    else 
    {
        std::cerr << "������ ��� �������� ����� ��� ������!" << std::endl;
    }
}

int main() 
{
    setlocale(LC_ALL, "Russian");

    processAndDisplayResults();
    return 0;
}