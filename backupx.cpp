#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

// Banner
const string BANNER = R"(
   ______     ______     ______     ______     ______     ______     ______     ______     ______  
  /\  == \   /\  __ \   /\  ___\   /\  __ \   /\  == \   /\  ___\   /\  == \   /\  ___\   /\__  _\ 
  \ \  __<   \ \  __ \  \ \ \____  \ \  __ \  \ \  __<   \ \ \____  \ \  __<   \ \  __\   \/_/\ \/ 
   \ \_\ \_\  \ \_\ \_\  \ \_____\  \ \_\ \_\  \ \_____\  \ \_____\  \ \_\ \_\  \ \_____\    \ \_\ 
    \/_/ /_/   \/_/\/_/   \/_____/   \/_/\/_/   \/_____/   \/_____/   \/_/ /_/   \/_____/     \/_/ 
                                                                                                   
)";

void mainProgram(int argc, char* argv[]) {
    // Argument parsing
    vector<string> extensions;
    string extensionFile, inputListFile, inputFileName, date, numberSeparator, dateSeparator, dateFormat;
    int numberRange = 0;
    bool silent = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-e" && i + 1 < argc) extensionFile = argv[++i];
        else if (arg == "-l" && i + 1 < argc) inputListFile = argv[++i];
        else if (arg == "-i" && i + 1 < argc) inputFileName = argv[++i];
        else if (arg == "-d" && i + 1 < argc) date = argv[++i];
        else if (arg == "-n" && i + 1 < argc) numberRange = stoi(argv[++i]);
        else if (arg == "-ns" && i + 1 < argc) numberSeparator = argv[++i];
        else if (arg == "-ds" && i + 1 < argc) dateSeparator = argv[++i];
        else if (arg == "-df" && i + 1 < argc) dateFormat = argv[++i];
        else if (arg == "-silent") silent = true;
    }

    if (!silent) cout << BANNER << endl;

    // Read extensions from text file
    ifstream extensionFileStream(extensionFile);
    if (!extensionFileStream.is_open()) {
        cout << "Extension file not found." << endl;
        return;
    }
    string line;
    while (getline(extensionFileStream, line)) {
        extensions.push_back(line);
    }
    extensionFileStream.close();

    // Prepare user inputs
    vector<string> userInputs;
    if (!inputListFile.empty()) {
        ifstream inputListFileStream(inputListFile);
        if (inputListFileStream.is_open()) {
            while (getline(inputListFileStream, line)) {
                userInputs.push_back(line);
            }
            inputListFileStream.close();
        } else {
            cout << "Input list file not found." << endl;
            return;
        }
    }
    if (!inputFileName.empty()) {
        userInputs.push_back(inputFileName);
    }

    // Add extensions to user input
    vector<string> outputs;
    if (!date.empty()) {
        int year = stoi(date);
        for (int month = 1; month <= 12; ++month) {
            for (int day = 1; day <= 31; ++day) {
                try {
                    tm dateObj = {};
                    dateObj.tm_year = year - 1900;
                    dateObj.tm_mon = month - 1;
                    dateObj.tm_mday = day;
                    mktime(&dateObj);
                    stringstream formattedDate;
                    if (dateFormat == "year") {
                        formattedDate << dateObj.tm_year + 1900;
                    } else {
                        if (!dateSeparator.empty()) formattedDate << dateSeparator;
                        formattedDate << setw(4) << setfill('0') << dateObj.tm_year + 1900;
                        formattedDate << setw(2) << setfill('0') << dateObj.tm_mon + 1;
                        formattedDate << setw(2) << setfill('0') << dateObj.tm_mday;
                    }
                    for (const string& userInput : userInputs) {
                        for (const string& extension : extensions) {
                            outputs.push_back(userInput + "-" + formattedDate.str() + "." + extension);
                        }
                    }
                } catch (const exception&) {
                }
            }
        }
    } else if (numberRange > 0) {
        for (int num = 1; num <= numberRange; ++num) {
            for (const string& userInput : userInputs) {
                for (const string& extension : extensions) {
                    outputs.push_back(userInput + (numberSeparator.empty() ? "" : numberSeparator) + to_string(num) + "." + extension);
                }
            }
        }
    } else {
        for (const string& userInput : userInputs) {
            for (const string& extension : extensions) {
                outputs.push_back(userInput + "." + extension);
            }
        }
    }

    // Print the outputs
    for (const string& output : outputs) {
        cout << output << endl;
    }
}

int main(int argc, char* argv[]) {
    mainProgram(argc, argv);
    return 0;
}
