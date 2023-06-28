#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include <iostream>

using namespace std;

int main()
{
	int* p = new int;

	delete p;


	cout << Enginuity::getFilePath() << endl;
	Enginuity::setFilePath("Assets");
	cout << Enginuity::getFilePath() << endl;
	size_t size;
	Enginuity::getFileSize("game.txt", size);
	cout << size << endl;

	std::string contents;
	Enginuity::readFile("game.txt", contents);
	cout << contents << endl;

	Enginuity::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++) 
	{
		cout << Enginuity::random(5, 10) << endl;
	}
}