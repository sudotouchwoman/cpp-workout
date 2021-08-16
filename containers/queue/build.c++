#include "queue.h"

int main()
{
    containers::queue<std::string> ShinyQueue;
    auto check = [](bool s){return s ? "empty" : "filled";};
    std::cout << "queue is: " << check(ShinyQueue.empty()) << '\n';
    try
    {
        const std::string popped = ShinyQueue.pop_front();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    const std::string sentense[5] = {"so my", "templated", "queue", "works", "great!"};
    for (auto item : sentense)
        ShinyQueue.push_back(item);
    ShinyQueue.print();
    std::cout << "queue size: " << ShinyQueue.size() << '\n';
    ShinyQueue.pop_front();
    ShinyQueue.pop_front();
    ShinyQueue.print();
    std::cout << "queue size: " << ShinyQueue.size() << '\n';
    std::cout << "queue is: " << check(ShinyQueue.empty()) << '\n';
    return EXIT_SUCCESS;
}