#include <iostream>
#include <string>
#include <fstream>

std::uint8_t memory[5000] = {0};
std::string codeSimplified;

void readCode()
{
    //vars
    std::string code;
    std::string codeline;
    std::ifstream codefile("code.txt");
    //get code to 'codeSimplified'
    while (std::getline(codefile, codeline))
    {
        code += codeline + "\n";
    }
    codefile.close();

    for (int i=0; i < code.length(); i++)
    {
        if (code[i] == '<' || code[i] == '>' || code[i] == '[' || code[i] == ']' || code[i] == '+' || code[i] == '-' || code[i] == ',' || code[i] == '.')
        {
            codeSimplified += code[i];
        }
    }
}

void interpreter()
{
    int selectedSlot = 0;
    bool inLoop = false;
    char cinput;
    for (int i=0; i < codeSimplified.length(); i++)
    {
        switch (codeSimplified[i])
        {
        case '<':
            selectedSlot -= 1; //slot left
            break;
        case '>':
            selectedSlot += 1; //slot right
            break;
        case '+':
            memory[selectedSlot] += 1; //increment slot
            break;
        case '-':
            memory[selectedSlot] -= 1; //decrement slot
            break;
        case '.':
            std::cout << memory[selectedSlot]; //print ascii char
            break;
        case ',':
            std::cin >> cinput;
            memory[selectedSlot] = (uint8_t)cinput; //get ascii input
            break;
        case '[':
            //inLoop = true; //enter loop
            break;
        case ']':
            if (memory[selectedSlot] != 0) //if not 0, go to start of loop
            {
                while(codeSimplified[i] != '[')
                {
                    i--;
                }
            }
            break;
        }
    }
    std::cout << "\n";
}

int main()
{
    readCode();
    interpreter();
    std::cout << "\n(press any key to exit...)";
    std::getchar();
}