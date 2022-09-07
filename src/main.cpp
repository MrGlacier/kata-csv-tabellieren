// main.cpp für die Kata
// CSV Tabellieren von https://ccd-school.de
//
// ToDos:
// * Über Parameter das Vertzeichniss angeben, wo die CSV liegen ✔
// * Einlesen der CSV ✔
// * Ausgabe der CSV in Tabellenform auf der Konsole
// * Refactoring - Funktionen anlegen und Aufräumen

#include <iostream>
#include <iomanip>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fstream>

void printCenter(int width, std::string text) {
    int halfScreen = width / 2;
    std::cout.width(halfScreen - (text.length() / 2));
    std::cout << std::right << text << std::endl;

}

void printLine(const char fillChar, int width) {
    std::cout << std::setfill(fillChar) << std::cout.width(width) << std::endl;
}

// IEnumerable<string> Tabellieren(IEnumerable<string> CSV_zeilen)
// Das ist die Codezeile aus der Kata.
std::string Tabellieren(std::string CSV_zeilen) {
    const std::string returnText = "Muss noch Implementiert werden!";
    return returnText;
}

// argc - Argument Count - Anzahl der übergebenen Argumente
// argv -  Argument Vector - Zeiger auf Array, welches die übergebenen Argumente hält
int main(int argc, char* argv[]) {
    std::ifstream fileHandler;
    std::string csvLine;
    std::string csvFilePath;

    if (argc >= 2 && strcmp(argv[1], "-csv") == 0) {
        csvFilePath.assign(argv[2]);
    }

    struct winsize currentWinsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &currentWinsize);

    int width = currentWinsize.ws_col;
    int height = currentWinsize.ws_row;

    //std::cout << "Lines:" << currentWinsize.ws_row << ", Columns: " << currentWinsize.ws_col << std::endl;
    std::string headline = "CSV Tabellieren";
    printCenter(width, headline);

    const char fillChar = '-'; 
    printLine(fillChar, width);

    if (!csvFilePath.empty()) {
        fileHandler.open(csvFilePath);
        if (fileHandler.is_open()) {
            while(getline(fileHandler, csvLine)) {
                std::cout << Tabellieren(csvLine) << std::endl;
            }
            fileHandler.close();
        } else {
            std::cout << "Kann die CSV '" << csvFilePath << "' nicht öffnen :-(" << std::endl;
        }
    } else {
        std::cout << "csv Pfad ist leer :-(" << std::endl;
    }

    return 0;
}
