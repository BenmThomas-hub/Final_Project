#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "Timer.h"


//function to create the Longest proper Prefix / Suffix
void LPS(std::string str, std::vector<int> & lps){
    lps[0] = 0;

    int length = 0;
    int i = 1;

    while(i < str.length()){
        if(str[i] == str[length]){
            length++;
            lps[i] = length;
            i++;
        }
        else {
            if (length == 0){
                lps[i] = 0;
                i++;
            }
            else
                length = lps[length - 1];
        }
    }


}

void KMP(std::string str,std::string txt){
    int txtLength = txt.length();
    int strLength = str.length();
    std::vector<int> lps (strLength);

    //makes an lps array to be compared to the original text

    LPS(str,lps);

    int i = 0, j = 0;


    //using the lps / prefix table, this compares the string and text to find all patterns of the string

    while(i < txtLength){
        if(str[j] == txt[i]){
			i++;
			j++;
		}

        if (j == strLength) {
            std::cout<< i - strLength << ' ';
            j = lps[j - 1];
        }

        else if (i < txtLength && str[j] != txt[i]) {

            if (j == 0){
				i++;
			}

			else {
                j = lps[j - 1];
			}
        }
    }
}


/////////////////////////////////////////////////////////////////////////////

//function that creates an array that gathers all known characters from the string into an array
void badCharRule(std::string str, int lgth, int bad[256]){
    for (int i = 0; i < 256; i++)
        bad[i] = -1;


    for (int i = 0; i < lgth; i++)
        bad[(int) str[i]] = i;
}

void BM(std::string str, std::string txt) {
    int strLength = str.size();
    int txtLength = txt.size();

    int bad[256];

    badCharRule(str, strLength, bad);

    int shift = 0;

    //uses the bad character rule to skip alignments that are known to be mismatched
    while(shift <= (txtLength - strLength))
    {
        int j = strLength - 1;

        while(j >= 0 && str[j] == txt[shift + j])
            j--;

            if (j < 0)
            {
                std::cout << shift << " ";

                shift += (shift + strLength < txtLength)? strLength - bad[txt[shift + strLength]] : 1;
            }
            else
                shift += std::max(1, j - bad[txt[shift + j]]);
    }
}

void terminal(std::string & choice){


    std::cout << std::endl;
    std::cout << "Knuth Morris Pratt and Boyer Moore Algorithms and Benchmarking" << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;
    std::cout << "Please enter an input from the list below:" << std::endl;
    std::cout << "For algorithms:          A" << std::endl;
    std::cout << "For benchmarking:        B" << std::endl;
    std::cout << "To leave the program:    X" << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cin >> choice;

}


int main(){

    std::string text, str, alg;

    std::string choice = "x";

    double duration, duration2;

    while (choice != "x" || choice != "X"){


        terminal(choice);


        if (choice == "a" || choice == "A"){

            std::cout << "Input text:" << std::endl;
            std::cin >> text;

            std::cout << "Input searched string:" << std::endl;
            std::cin >> str;

            std::cout << "Algorithm: (KMP or BM)" << std::endl;
            std::cin >> alg;

            if (alg == "KMP" || alg == "kmp"){

                std::cout << "The string " << str << " occurs at ";

                Timer Timer;
                Timer.start();
                KMP(str, text);
                Timer.stop();
                duration = Timer.getDuration();

                std::cout << "and took " << duration << " nanoseconds to find with KMP" << std::endl;
            }

            else if (alg == "BM" || alg == "bm"){

                std::cout << "The string " << str << " occurs at ";

                Timer Timer;
                Timer.start();
                BM(str, text);
                Timer.stop();
                duration2 = Timer.getDuration();

                std::cout << "and took " << duration2 << " nanoseconds to find with BM" << std::endl;
            }

            else {
                std::cout << "invalid input" << std::endl;
            }

        }


        else if (choice == "b" || choice == "B"){
            std::ofstream outFile ("benchmark.csv");

            if (outFile.is_open()) {
				std::string text = "SUPERCALIFRAGILISTICEXPIALIDOCIOUS";
				std::string pattern[] = {"F","FR","FRA","FRAG","FRAGI","FRAGIL","FRAGILI","FRAGILIS","FRAGILIST","FRAGILISTI"};
				Timer timer;

				outFile << "trip" << ", " << "KMP" << ", " << "BM" << std::endl;

				for (int x = 0; x < 10; x++) {

				    timer.start();
					KMP(text, pattern[x]);
					timer.stop();
					duration = timer.getDuration();


					timer.start();
					BM(text, pattern[x]);
					timer.stop();
					duration2 = timer.getDuration();

					outFile << (x + 1) << ", " << duration << ", " << duration2 << std::endl;
				}

				outFile.close();
            }

            std::cout << std::endl;
			std::cout << "Check benchmark.csv file." << std::endl;
			std::cout << std::endl;
        }


        else if (choice == "x" || choice == "X"){
            std::cout << "Goodbye!" << std::endl;
            return 0;
        }


        else {
            std::cout << "invalid input" << std::endl;
        }

    }


    return 0;
}