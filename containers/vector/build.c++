#include "vector.h"

bool test_constructor()
{
    try
    {
    int arr[10] = {1, 5, 2, 8, 4, 12, 9, 0, -9, 3};
    
    containers::vector<int> ShinyVector(&arr[0], &arr[9]);
    containers::vector<std::string> ShinyStringVector;
    
    ShinyStringVector.push_back("String inside a vector!");
    ShinyStringVector.push_back("Another string inside a vector!");
    std::cout << "vector<std::string> contents #1";
    for (size_t i = 0; i < ShinyStringVector.size(); ++i)
    {
        std::cout  << "; " << ShinyStringVector[i];
    } std::cout << '\n';

    ShinyStringVector.erase(0);
    std::cout << "vector<std::string> contents #2";
    for (size_t i = 0; i < ShinyStringVector.size(); ++i)
    {
        std::cout  << "; " << ShinyStringVector[i];
    } std::cout << '\n';

    std::cout << "vector<int> " << (ShinyVector.empty() ? "is empty!" : "has something inside...") << '\n';
    }
    catch (std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}

bool test_contents()
{
    try
    {
    int arr[10] = {1, 5, 2, 8, 4, 12, 9, 0, -9, 3};
    containers::vector<int> ShinyVector(&arr[0], &arr[9]);

    std::cout << "vector<int> contents #1";
    for (size_t i = 0; i < ShinyVector.size(); ++i)
    {
        std::cout  << "; " << ShinyVector[i];
    } std::cout << '\n';
    ShinyVector.push_back(14);
    ShinyVector.push_back(33);
    std::cout << "vector<int> contents #2";
    for (size_t i = 0; i < ShinyVector.size(); ++i)
    {
        std::cout  << "; " << ShinyVector[i];
    } std::cout << '\n';
    ShinyVector.push_at(-15, 2);
    std::cout << "vector<int> contents #3";
    for (size_t i = 0; i < ShinyVector.size(); ++i)
    {
        std::cout  << "; " << ShinyVector[i];
    } std::cout << '\n';
    }
    catch (std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}

bool test_errors()
{
    try
    {
    int arr[10] = {1, 5, 2, 8, 4, 12, 9, 0, -9, 3};
    containers::vector<int> ShinyVector(&arr[0], &arr[9]);
    ShinyVector.erase();
    ShinyVector.at(5);
    }
    catch (std::out_of_range& e)
    {
        std::cerr << "exception thrown when intended: at() with invalid index -> ";
        std::cerr << e.what() << '\n';
        return true;
    }
    return false;
}

int main()
{
    auto check = [](bool s){return s ? "passed:\n" : "failed:\n";};
    
    std::cerr << check(test_constructor());
    std::cerr << check(test_contents());
    std::cerr << check(test_errors());

    return EXIT_SUCCESS;
}