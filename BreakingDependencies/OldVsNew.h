#include <functional>

// class Command
//{
// public:
//     virtual void operator()(int) const = 0;
//     //    ...
// };

// class PrintCommand : public Command
//{
//     void operator()(int) const {};
// };
// class SearchCommand : public Command
//{
//     void operator()(int) const {};
// };
// class ExecuteCommand : public Command
//{
//     void operator()(int) const {};
// };

// void f(Command* command);

class PrintCommand
{
    void operator()(int) const {};
};
class SearchCommand
{
    void operator()(int) const {};
};
class ExecuteCommand
{
    void operator()(int) const {};
};

void f(std::function<void(int)> command);
