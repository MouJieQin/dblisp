#ifndef _DBLISP_DBLISP_PARSER_H_
#define _DBLISP_DBLISP_PARSER_H_
#include <fstream>
#include <iostream>

#include "recursive-tree.h"

namespace dblisp {

enum WordType { LEFT_PARENTHESIS, RIGHT_PARENTHESIS, STRING_VALUE, VARIABLE };

class DbLispWord {
  friend std::ostream& operator<<(std::ostream& outStream,
                                  const DbLispWord& word);

 public:
  DbLispWord(std::string&& value, WordType wordType)
      : value_(std::move(value)), wordType_(wordType) {}

 private:
  std::string value_;
  WordType wordType_;
};

std::ostream& operator<<(std::ostream& outStream, const DbLispWord& word) {
  outStream << word.value_;
  return outStream;
}

class DbLispParser {
 public:
  bool lispToRecMap(const std::string& lispFile, recursive_map& rmap) {
    lispFile_ = lispFile;
    std::vector<std::string> lispFileVec;
    if (!copyToFile(lispFile, lispFileVec)) {
      return false;
    }
    return lispToRecMap(lispFileVec, rmap);
  }

 private:
  bool lispToRecMap(std::vector<std::string>& lispFileVec,
                    recursive_map& rmap) {
    std::vector<DbLispWord> wordVec;
    if (!lispWords(lispFileVec, wordVec)) {
      return false;
    }
    std::cout << "--------------start------------------------\n";
    for (const auto& word : wordVec) {
      std::cout << word << " ";
    }
    std::cout << "\n----------------end----------------------\n";
    return true;
  }

  bool lispWords(const std::vector<std::string>& lispFileVec,
                 std::vector<DbLispWord>& wordVec) {
    size_t lineIndex = 0, index = 0;
    size_t openLineIndex = 0, openIndex = 0, closeIndex = 0;
    bool quotClose = true;
    std::string strValue;
    std::vector<DbLispWord> wordVecTemp;
    for (;;) {
      //   std::cout << "--------------start------------------------\n";
      //   for (const auto& word : wordVecTemp) {
      //     std::cout << word << " ";
      //   }
      //   std::cout << "\n----------------end----------------------\n";
      if (lineIndex >= lispFileVec.size()) {
        if (!quotClose) {
          return errorIndexLog(openLineIndex, openIndex, "`\" not close");
        }
        wordVec.swap(wordVecTemp);
        return true;
      }
      if (index >= lispFileVec[lineIndex].size()) {
        index = 0;
        lineIndex += 1;
      } else {
        if (!quotClose) {
          strValue.push_back('\n');
          if (lispFileVec[lineIndex][index] == '"') {
            quotClose = true;
            wordVecTemp.emplace_back(std::move(strValue), STRING_VALUE);
            strValue.clear();
            index += 1;
          } else {
            closeIndex = index + 1;
            for (; closeIndex != lispFileVec[lineIndex].size(); ++closeIndex) {
              if (lispFileVec[lineIndex][closeIndex] == '"' &&
                  lispFileVec[lineIndex][closeIndex - 1] != '\\') {
                quotClose = true;
                strValue.append(lispFileVec[lineIndex].substr(0, closeIndex));
                wordVecTemp.emplace_back(std::move(strValue), STRING_VALUE);
                strValue.clear();
                break;
              }
            }
            index = closeIndex + 1;
            if (!quotClose) {
              strValue.append(lispFileVec[lineIndex]);
            }
          }
        } else {
          const char c = lispFileVec[lineIndex][index];
          switch (c) {
            case '(':
              wordVecTemp.emplace_back("(", LEFT_PARENTHESIS);
              index += 1;
              break;
            case ')':
              wordVecTemp.emplace_back(")", RIGHT_PARENTHESIS);
              index += 1;
              break;
            case ';':
              lineIndex += 1;
              index = 0;
              break;
            case '"':
              quotClose = false;
              openLineIndex = lineIndex;
              openIndex = index;
              closeIndex = index + 1;
              for (; closeIndex != lispFileVec[lineIndex].size();
                   ++closeIndex) {
                if (lispFileVec[lineIndex][closeIndex] == '"' &&
                    lispFileVec[lineIndex][closeIndex - 1] != '\\') {
                  quotClose = true;
                  wordVecTemp.emplace_back(
                      lispFileVec[lineIndex].substr(
                          openIndex + 1, closeIndex - (openIndex + 1)),
                      STRING_VALUE);
                  break;
                }
              }
              index = closeIndex + 1;
              if (!quotClose) {
                strValue = lispFileVec[lineIndex].substr(openIndex + 1);
              }
              break;
            default:
              if (!isspace(c)) {
              }
              index += 1;
              break;
          }
        }
      }
    }
    return true;
  }

 private:
  bool copyToFile(const std::string& inputFile,
                  std::vector<std::string>& lispFileVec) {
    std::ifstream inf(inputFile);
    if (!inf.is_open()) return openErrorLog(inputFile);
    std::string buf;
    buf.reserve(100);
    std::vector<std::string> lispFileVecImple;
    for (; getline(inf, buf);) {
      lispFileVecImple.emplace_back(std::move(buf));
    }
    lispFileVec.swap(lispFileVecImple);
    return true;
  }

 private:
  std::ostream& errorLog(std::ostream& ostream) const {
    ostream << "dblisp: parser: ";
    return ostream;
  }

  bool errorLog(const std::string& logInfo) const {
    errorLog(std::cerr) << logInfo << std::endl;
    return false;
  }

  bool errorIndexLog(const size_t lineIndex, const size_t index,
                     const std::string& logInfo) {
    errorLog(std::cerr) << lispFile_ << ":" << lineIndex << ":" << index << ':'
                        << logInfo << std::endl;
    return false;
  }

  bool openErrorLog(const std::string& fileName) const {
    errorLog(std::cerr) << "open error: " << fileName << std::endl;
    return false;
  }

 private:
  std::string lispFile_;
};

}  // namespace dblisp

#endif