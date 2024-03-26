#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    // Read the last 5 lines from the file alpha.txt
    std::ifstream file("alpha.txt");
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
        if (lines.size() > 5) {
            lines.erase(lines.begin());
        }
    }

    file.close();

    // Filter lines containing "ee"
    std::vector<std::string> filteredLines;
    for (const std::string& currentLine : lines) {
        if (currentLine.find("ee") != std::string::npos) {
            filteredLines.push_back(currentLine);
        }
    }

    // Sort the filtered lines
    std::sort(filteredLines.begin(), filteredLines.end());

    // Print the sorted output
    for (const std::string& sortedLine : filteredLines) {
        std::cout << sortedLine << std::endl;
    }

    return 0;
}


