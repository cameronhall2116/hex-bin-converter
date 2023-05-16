#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main(int argc, char* argv[])
{
    std::ofstream binFile("binFile1.txt");
    int num;
    int random;
    srand(time(0));
    for (int x = 0 ; x < 1000 ; x++)
    {
        for (int i = 0 ; i < 16 ; i++)
        {
	        random = (rand() % 10) + 1;
            if (random <= 5)
            {
                num = 0;
            }
            else 
            {
                num = 1;
            }
            binFile << num;
        }
        
        binFile << "\n";
    }

    binFile.close();
}