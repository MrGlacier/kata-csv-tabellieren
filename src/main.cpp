// main.cpp für die Kata
// CSV Tabellieren von https://ccd-school.de

#include <iostream>
#include <iomanip>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

void printCenter(int width, std::string text) {
    int halfScreen = width / 2;
    std::cout.width(halfScreen - (text.length() / 2));
    std::cout << std::right << text << std::endl;

}

void printLine(const char fillChar, int width) {
    std::cout << std::setfill(fillChar) << std::cout.width(width) << std::endl;
}

int main(int argc, char* argv[]) {
    struct winsize currentWinsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &currentWinsize);

    int width = currentWinsize.ws_col;
    int height = currentWinsize.ws_row;

    //std::cout << "Lines:" << currentWinsize.ws_row << ", Columns: " << currentWinsize.ws_col << std::endl;
    std::string headline = "CSV Tabellieren";
    printCenter(width, headline);

    const char fillChar = '-'; 
    printLine(fillChar, width);

    return 0;
}
