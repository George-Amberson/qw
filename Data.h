#pragma once
#include <QString>
#include <QByteArray>
#include <string>
#include <fstream>


class Data
{
private:
	short Min, Max;
	int width, heigth, deep;
	float x, y, z;
	short* mas;
public:
	Data() :width(0), heigth(0), deep(0), Min(4096), Max(-1000),mas(nullptr),x(0),y(0),z(0) {}
	Data(const std::string& filename)
	{
		readFile(filename);
	}
	~Data()
	{
		if (mas != nullptr)delete[] mas;
	}
	short getMin()
	{
		return Min;
	}
	short getMax()
	{
		return Max;
	}
	int getWidth()
	{
		return width;
	}
	int getHeigth()
	{
		return heigth;
	}
	int getDepth()
	{
		return deep;

	}
	short operator[](int index)
	{
		return mas[index];
	}
	void readFile(const std::string& filename)
	{
		std::ifstream file(filename);
		if (file)
		{
			file.read((char*)&width, sizeof(int));
			file.read((char*)&heigth, sizeof(int));
			file.read((char*)&deep, sizeof(int));
			file.read((char*)&x, sizeof(float));
			file.read((char*)&y, sizeof(float));
			file.read((char*)&z, sizeof(float));
			mas = new short[width*heigth*deep];
			for (int i = 1; i <= width*heigth*deep; i++)
			{
				file.read((char*)(mas + (i - 1)), sizeof(short));
				if (mas[i-1] < Min)Min = mas[i - 1];
				if (mas[i-1] > Max)Max = mas[i - 1];
			}
		}

	}
};

