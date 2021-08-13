#include <vector>
#include <iostream>
#include <string>

int main()
{
    std::vector<std::string> message {"This", "Message", "is", "from", "WSL", "+", "VS Code!\n"};
    for ( auto word: message)
    {
        std::cout << word << " ";
    }    
    return EXIT_SUCCESS;
}