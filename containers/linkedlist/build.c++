#include "linkedlist.h"

int main()
{
    containers::linkedlist<std::string> Shinylinkedlist;
    auto check = [](bool s){return s ? "empty" : "filled";};
    std::cout << "linkedlist is: " << check(Shinylinkedlist.empty()) << '\n';
    try
    {
        const std::string removed = Shinylinkedlist.remove(3);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception occured: " << e.what() << '\n';
    }
    const std::string sentense[10] = {"Linked", "list", "is", "a data", "structure", "which", "can be", "used", "to add/remove", "elements"};
    for (auto item : sentense)
        Shinylinkedlist.append(item);
    Shinylinkedlist.print();
    std::cout << "List elements: ";
    for (size_t i=0; i < Shinylinkedlist.size(); ++i)
        std::cout << Shinylinkedlist[i] << ' ';
    std::cout << '\n';
    std::cout << "linkedlist size: " << Shinylinkedlist.size() << '\n';
    Shinylinkedlist.remove(0);
    Shinylinkedlist.remove(2);
    Shinylinkedlist.print();
    std::cout << "linkedlist size: " << Shinylinkedlist.size() << '\n';
    std::cout << "linkedlist is: " << check(Shinylinkedlist.empty()) << '\n';
    return EXIT_SUCCESS;
}