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
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "StringAnalyzer.h"
namespace isu2016sp0 {
    ReturnValue StringAnalyzer::setString(const char* strFilePath) {
        std::ifstream inputFileStream(strFilePath, std::fstream::in);
        if (inputFileStream.fail()) {
            return FILE_NOT_FOUND;
        }
        std::stringstream sstream;
        sstream << inputFileStream.rdbuf();
        string = sstream.str();
        return SUCCESS;
    }
    ReturnValue StringAnalyzer::setString(int argc, char** argv) {
        switch (argc) {
            case 3:
                if (strcmp(argv[1], "-s") == 0) {
                    string = argv[2];
                } else {
                    return BAD_ARGUMENTS;
                }
                break;
            case 2:
                return setString(argv[1]);
            case 1:
                break;
            default:
                return BAD_ARGUMENTS;
        }
        return SUCCESS;
    }
    std::string StringAnalyzer::getString() {
        return string;
    }
    static int isWordChar(int chr) {
        return ( (std::ispunct(chr) && chr != '\'' && chr != '-' && chr != '_') || ! std::isprint(chr) );
    }
    static void splitByDelim(const std::string& str, char delim, std::vector<std::string>& out) {
        std::stringstream stream(str);
        std::string subStr;
        while (std::getline(stream, subStr, delim)) {
            if (subStr.length()) {
                std::string stripped;
                std::remove_copy_if(
                        subStr.begin(), subStr.end(),
                        std::back_inserter(stripped),
                        std::ptr_fun<int, int>(&isWordChar));
                if (stripped.length()) {
                    out.push_back(stripped);
                }
            }
        }
    }
    void StringAnalyzer::tallyWords() {
        std::vector<std::string> lines;
        splitByDelim(string, '\n', lines);
        for (auto line : lines) {
            std::vector<std::string> words;
            splitByDelim(line, ' ', words);
            wordCount += words.size();
            for (uint64_t i = 0; i < words.size(); ++i) {
                wordFreq[words[i]]++;
            }
        }
    }
    void StringAnalyzer::tallyChars() {
        charCount = string.size();
        for (uint64_t i = 0; i < charCount; ++i) {
            charFreq[string[i]]++;
        }
    }
    void StringAnalyzer::analyze() {
        tallyChars();
        tallyWords();
    }
    std::string StringAnalyzer::printResults() {
        std::stringstream out;
        out << "Character count: " << charCount << std::endl;
        out << "Word count: " << wordCount << std::endl;
        out << "Character Frequencies (alphabetically):" << std::endl;
        for (char c = ' '; c <= '~'; ++c) { // only checks visible characters + space
            if (charFreq.count(c)) {
                out << "'" << c << "': " << charFreq.at(c) << std::endl;
            }
        }
        out << "Word Frequencies (alphabetically):" << std::endl;
        for (auto pair : wordFreq) {
            out << "\"" << pair.first << "\": " << pair.second << std::endl;
        }
        return out.str();
    }
}
