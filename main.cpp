/*
 * Copyright (c) 2016 Galen Cochrane
 * Galen Cochrane <galencochrane@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <iostream>
#include "StringAnalyzer.h"
using namespace isu2016sp0;

static const std::string defuaultStrFile = "strings/test0.txt";
std::string queryFileName();

int main(int argc, char ** argv) {
    StringAnalyzer analyzer;
    ReturnValue status = SUCCESS;
    if (argc > 1) {
        status = analyzer.setString(argc, argv);
    } else {
        status = analyzer.setString(queryFileName().c_str());
        while (status == FILE_NOT_FOUND) {
            std::cout << "File not found or unreadable!\n";
            status = analyzer.setString(queryFileName().c_str());
        }
    }
    switch (status) {
        case SUCCESS:
            std::cout << analyzer.getString() << std::endl;
            break;
        case FILE_NOT_FOUND:    // This will only be reached in case of command line arguments
            std::cout << "File not found or unreadable: " << argv[1] << std::endl;
            return status;
        case BAD_ARGUMENTS:
            std::cout << "Bad arguments. Usage: 'StringCount [FILENAME]' OR 'StringCount -s [STRING]'\n";
            return status;
        default:
            return status;
    }
    return 0;
}

std::string queryFileName() {
    printf("Select a file to read (defualt %s): ", defuaultStrFile.c_str());
    std::string input;
    std::cin >> input;
    return input;
}