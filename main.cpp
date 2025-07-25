#include "command.hpp"
int main()
{
    char* command = new char[50];
    readfile("show_data", command);
    cout << command << endl;
    return 0;
}