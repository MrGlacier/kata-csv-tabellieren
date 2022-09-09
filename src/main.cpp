// main.cpp für die Kata
// CSV Tabellieren von https://ccd-school.de
// './csv-kata -csv csv/test-1.csv'
// 
// ToDos:
// * Über Parameter das Vertzeichniss angeben, wo die CSV liegen ✔
// * Einlesen der CSV ✔
// * Ausgabe der CSV in Tabellenform auf der Konsole ✔
// * Refactoring - Funktionen anlegen und Aufräumen ✔

#include <iostream>
#include <iomanip>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <vector>


// Gibt den 'text' in der mitte der Konsole aus.
void printTextCentered(int width, std::string text) {
    int halfScreen = width / 2;
    std::cout.width(halfScreen - (text.length() / 2));
    std::cout << std::right << text << std::endl;
}

// Klassische 'trim'funktion
std::string trim(std::string& str, const char trimSign)
{
    str.erase(str.find_last_not_of(trimSign)+1);         //suffixing spaces
    str.erase(0, str.find_first_not_of(trimSign));       //prefixing spaces
    return str;
}

// "Zeichnet" eine Linie anhand 'fillChar' über die ganze Breite der Konsole.
void printLine(const char fillChar, int width) {
    std::cout << std::setfill(fillChar) << std::cout.width(width) << std::endl << std::endl;
}

// Wandelt die CSV_zeile in ein vector um, und gibt die Einträge des Vectors inkl. Linie wieder auf der Console aus.
void printFieldValues(std::string csvLine) {
    std::string fieldDelimiter = ";";
    std::vector<std::string> stringVector;
    size_t pos = 0;

    while((pos = csvLine.find(fieldDelimiter)) != std::string::npos) {
        std::string currField = csvLine.substr(0, pos);
        currField = trim(currField, '"');
        stringVector.push_back(currField);
        csvLine.erase(0, pos + fieldDelimiter.length());
    }

    // Ausgabe Text
    for(unsigned int currField = 0; currField < stringVector.size(); ++currField) {
        unsigned int fieldWidth = 15;
        if (currField == 0 || currField == 2 || currField > 4) continue;
        
        std::cout << std::left << std::setfill(' ') << std::setw(fieldWidth) << stringVector.at(currField) << "|";
    }
    std::cout << std::endl;

    // Ausgabe Linie
    for(unsigned int currField = 0; currField < stringVector.size(); ++currField) {
        unsigned int fieldWidth = 16;
        if (currField == 0 || currField == 2 || currField > 4) continue;
        
        std::cout << std::right << std::setfill('-') << std::setw(fieldWidth) << "+";
    }
    std::cout << std::endl;
}

// Gibt eine 'Überschrift' in der Konsole aus.
void printMainHeadline(std::string headline, const unsigned int width) {
    printTextCentered(width, headline);

    const char fillChar = '-'; 
    printLine(fillChar, width);
}

// IEnumerable<string> Tabellieren(IEnumerable<string> CSV_zeilen)
// Das ist die Codezeile aus der Kata.
void Tabellieren(const std::string CSV_zeilen, const unsigned int lineCounter) {
    printFieldValues(CSV_zeilen);
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

    const unsigned int width = currentWinsize.ws_col;
    const unsigned int height = currentWinsize.ws_row;

    const std::string headline = "CSV Tabellieren";
    printMainHeadline(headline, width);

    if (!csvFilePath.empty()) {
        fileHandler.open(csvFilePath);
        if (fileHandler.is_open()) {
            unsigned int lineCounter = 0;
            while(getline(fileHandler, csvLine)) {
                ++lineCounter;
                Tabellieren(csvLine, lineCounter);
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
