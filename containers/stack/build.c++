#include "stack.h"

int main()
{
    containers::stack<std::string> ShinyStack;
    auto check = [](bool s){return s ? "empty" : "filled";};
    std::cout << "stack is: " << check(ShinyStack.empty()) << '\n';
    try
    {
        const std::string popped = ShinyStack.pop();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    ShinyStack.push("great!");
    ShinyStack.push("works");
    ShinyStack.push("stack");
    ShinyStack.push("templated");
    ShinyStack.push("so my");
    ShinyStack.print();
    std::cout << "stack size: " << ShinyStack.size() << '\n';
    ShinyStack.pop();
    ShinyStack.pop();
    ShinyStack.print();
    std::cout << "stack size: " << ShinyStack.size() << '\n';
    std::cout << "stack is: " << check(ShinyStack.empty()) << '\n';
    return EXIT_SUCCESS;
}