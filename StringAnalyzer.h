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
#ifndef STRINGCOUNT_STRINGANALYZER_H
#define STRINGCOUNT_STRINGANALYZER_H
#include <string>
#include <unordered_map>
#include <map>
namespace isu2016sp0 {
    /**
     * Only these values will be returned from either of the two 'setString' methods below.
     */
    enum ReturnValue {
        SUCCESS = 0, FILE_NOT_FOUND, BAD_ARGUMENTS
    };
    /**
     * StringAnalyzer encapsulates all that is algorithmically needed to perform our string counting analyses.
     */
    class StringAnalyzer {
        std::string string;
        uint64_t wordCount = 0, charCount = 0;
        std::map<std::string, uint64_t> wordFreq;
        std::unordered_map<char, uint64_t> charFreq;
        void tallyWords();
        void tallyChars();
    public:
        /**
         * Sets the string to be analyzed.
         * @param strFilePath -The file whose contents you wish to analyze
         * @return SUCCESS(0) or FILE_NOT_FOUND(1)
         */
        ReturnValue setString(const char* strFilePath);
        /**
         * Sets the string to be analyzed, in the case that input was given as a CLI argument.
         * @param argc
         * @param argv
         * @return SUCCESS(0), FILE_NOT_FOUND(1), or BAD_ARGUMENTS(2)
         */
        ReturnValue setString(int argc, char ** argv);
        /**
         * returns the string currently being considered for analysis.
         * @return -A copy of current string
         */
        std::string getString();
        /**
         * performs the string counting analyses.
         */
        void analyze();
        /**
         * Produces a string of output detailing the results of the analyses
         * @return -The analyses results in a formatted string
         */
        std::string printResults();
    };
}
#endif //STRINGCOUNT_STRINGANALYZER_H
