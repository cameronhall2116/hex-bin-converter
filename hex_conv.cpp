#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <time.h>
#include <fstream>

// initialise hexadecimal and binary unorderedmaps

std::unordered_map<std::string, std::string> hex_table = {
        { "0", "0000" }, { "1", "0001" }, { "2", "0010" }, { "3", "0011" }, 
        { "4", "0100" }, { "5", "0101" }, { "6", "0110" }, { "7", "0111" }, 
        { "8", "1000" }, { "9", "1001" }, { "A", "1010" }, { "B", "1011" },
        { "C", "1100" }, { "D", "1101" }, { "E", "1110" }, { "F", "1111" }
    };

std::unordered_map<std::string, std::string> bin_table = {
        { "0000", "0" }, { "0001", "1" }, { "0010", "2" }, { "0011", "3" }, 
        { "0100", "4" }, { "0101", "5" }, { "0110", "6" }, { "0111", "7" }, 
        { "1000", "8" }, { "1001", "9" }, { "1010", "A" }, { "1011", "B" },
        { "1100", "C" }, { "1101", "D" }, { "1110", "E" }, { "1111", "F" }
    };


// function to convert hexadecimal to binary
std::string hexToBin (const std::string& hex)
{
    std::string trimd_hex = hex.substr( 2 , (hex.size()-2) );
    std::string binString;

    for (int i = 0 ; i < trimd_hex.size() ; i++)
    {
        std::string s = trimd_hex.substr( i , 1 );
        std::string binVal = hex_table.at(s);
        binString += binVal;
    }
    return binString;
}

// function to convert binary to hexadecimal
std::string binToHex (std::string& bin)
{
    std::string hexString = "0x";
    int binInt = bin.size();

    if (binInt%4 != 0)
    {
        int zeros = 4 - binInt%4;
        switch (zeros)
        {
            case 3:
            bin = "000" + bin;
            break;
            case 2:
            bin = "00" + bin;
            break;
            case 1:
            bin = "0" + bin;
            break;
        }
    } 

    for (int i = 0 ; i < bin.size() ; i+=4)
    {
        std::string s = bin.substr( i , 4 );
        std::string hexVal = bin_table.at(s);
        hexString += hexVal;
    }
    return hexString;
}

// function to check if a given arguement is a binary string
bool isBinary(std::string str)
{
   for(int i=0 ; i<str.size() ; i++)
   {
       if(str[i]!='1' && str[i]!='0')
       return false;
   }
   return true;
}


/*** function that is called for each arguement
 *   checks whether is hex, bin, or invalid
 *   calls the appropriate conversion function ***/
void checkHexBin(std::string& value, int num)
{
    if (value[1] == 'x')
            {
                const std::string hex = value;
                std::string binString = hexToBin(hex);
                std::cout << "\nValue " 
                            << num+1
                            << " has been converted to binary -> " 
                            << binString << "\n";
            }
            else if (isBinary(value) == true)
            {
                std::string bin = value;
                std::string hexString = binToHex(bin);
                std::cout << "\nValue " 
                            << num+1
                            << " has been converted to hexadecimal -> " 
                            << hexString << "\n";
            }
            else
            {
                std::cout << "\nValue " << num+1 << " is invalid.\n";
            }
}



int main (int argc, char* argv[])
{
    // record start time
    auto t1 = std::chrono::high_resolution_clock::now();

    std::vector<std::string> all_args;

    if (argc > 1) 
    {       
        // add all arguements to string vector 
        std::vector<std::string> all_args(argv + 1, argv + argc);
        int num = 0;
        // loop through each arguement in vector
        for ( int x = 0 ; x < argc-1 ; x++ )
        {   
            std::ifstream file;
            file.open(all_args.at(x));
            std::string line;
            // check if arguement was a text file
            if (file)
            {
                std::cout << "\n Entering file... \n";
                // iterate through every line in file
                while (getline(file, line))
                {
                    checkHexBin(line, num);
                    num++;
                }
            }
            // if it wasn't a file, call conversion function
            else
            {
                checkHexBin(all_args.at(x), num);
                num++;
            }
            file.close();
        
        } 
    }

    // record finish time and print time taken 
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "\nOperation took "
              << std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count()
              << " milliseconds\n";

    return 0;
}
