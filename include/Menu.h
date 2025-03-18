#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

class Menu {
public:
    Menu(const std::string& title, const std::vector<std::string>& options);

    void display() const;
    int getUserChoice() const;

    void setTitle(const std::string& newTitle);
    void setOptions(const std::vector<std::string>& newOptions);

private:
    std::string title;
    std::vector<std::string> options;

    void printHeader(const std::string& text) const;
};

#endif // MENU_H
