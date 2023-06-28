#include "Core/Random.h"
#include "Core/FileIO.h"
#include <iostream>

using namespace std;

int main()
{
	cout << Enginuity::getFilePath() << endl;


	Enginuity::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++) 
	{
		cout << Enginuity::random(5, 10) << endl;
	}
	
}