#include "dblisp-parser.h"
#include "gtest/gtest.h"
#include "recursive-tree.h"

using dblisp::DbLispParser;
using dblisp::KeyType;
using dblisp::RecTree;
using dblisp::recursive_map;
using dblisp::ValType;

class TestRecursiveTree : public testing::Test {
 public:
  TestRecursiveTree() {}
  ~TestRecursiveTree(){};
};

TEST_F(TestRecursiveTree, emplace) {
  RecTree rt("key");
  std::cout << "rt key:" << rt.key() << std::endl;
  rt["key1"]["key2"]["key3"]["key4"].pushValue("this is a test");
  rt["key1"]["key5"]["key3"]["key4"].pushValue("this is two test");
  std::cout << "value: " << rt["key1"]["key2"]["key3"]["key4"].getValue()
            << std::endl;
  std::cout << "value: " << rt["key1"]["key5"]["key3"]["key4"].getValue()
            << std::endl;
}

TEST_F(TestRecursiveTree, copy) {
  RecTree rt("key");
  rt["key1"]["key2"]["key3"]["key4"].pushValue("this is a test");
  std::cout << "value: " << rt["key1"]["key2"]["key3"]["key4"][0] << std::endl;
  std::vector<std::string> temp{"9", "8", "7", "6"};
  rt["key1"]["key5"]["key3"]["key4"].assign(temp.begin(), temp.end());
  std::cout << "value: " << rt["key1"]["key5"]["key3"]["key4"][0] << std::endl;
  std::cout << "value: " << rt["key1"]["key5"]["key3"]["key4"][0].asInt()
            << std::endl;
  RecTree rtCopy(rt);
  std::cout << "value: " << rtCopy["key1"]["key2"]["key3"]["key4"][0]
            << std::endl;
  std::cout << "value: " << rtCopy["key1"]["key5"]["key3"]["key4"][0]
            << std::endl;
  std::cout << "value: " << rtCopy["key1"]["key5"]["key3"]["key4"][0].asInt()
            << std::endl;
}

TEST_F(TestRecursiveTree, valueVector) {
  RecTree rt("key");
  rt["key1"]["key2"]["key3"]["key4"].pushValue("this is a test");
  std::cout << "value: " << rt["key1"]["key2"]["key3"]["key4"][0] << std::endl;
  std::vector<std::string> temp{"9", "8", "7", "6"};
  rt["key1"]["key5"]["key3"]["key4"].assign(temp.begin(), temp.end());
  std::cout << "value: " << rt["key1"]["key5"]["key3"]["key4"][0] << std::endl;
  std::cout << "value: " << rt["key1"]["key5"]["key3"]["key4"][0].asInt()
            << std::endl;
  for (const auto &val : rt["key1"]["key5"]["key3"]["key4"].valueVector()) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
  std::vector<std::string> vec;
}

TEST_F(TestRecursiveTree, count) {
  RecTree rtempy;
  EXPECT_EQ(rtempy.count(), 1);
  RecTree rt("key");
  EXPECT_EQ(rt.count(), 1);
  std::vector<std::string> temp{"9", "8", "7", "6"};
  rt["key1"]["key2"]["key3"]["key4"].pushValue("this is a test");
  EXPECT_EQ(rt.count(), 5);
  rt["key1"]["key5"]["key3"]["key4"].assign(temp.begin(), temp.end());
  EXPECT_EQ(rt.count(), 8);
}

TEST_F(TestRecursiveTree, erase) {
  RecTree rtempy;
  EXPECT_EQ(rtempy.count(), 1);
  RecTree rt("key");
  EXPECT_EQ(rt.count(), 1);
  std::vector<std::string> temp{"9", "8", "7", "6"};
  rt["key1"]["key2"]["key3"]["key4"].pushValue("this is a test");
  EXPECT_EQ(rt.count(), 5);
  rt["key1"]["key5"]["key3"]["key4"].assign(temp.begin(), temp.end());
  EXPECT_EQ(rt.count(), 8);
  rt["key1"]["key5"].erase("key3");
  EXPECT_EQ(rt.count(), 6);
  rt["key1"].erase(rt["key1"].begin(), rt["key1"].end());
  EXPECT_EQ(rt.count(), 2);
  rt.erase(rt.begin());
  EXPECT_EQ(rt.count(), 1);
}

TEST_F(TestRecursiveTree, insert) {
  RecTree rt("key");
  rt["key1"]["key2"]["key3"]["key4"].pushValue("this is a test");
  std::cout << "value: " << rt["key1"]["key2"]["key3"]["key4"][0] << std::endl;
  std::vector<std::string> temp{"9", "8", "7", "6"};
  rt["key1"]["key5"]["key3"]["key4"].assign(temp.begin(), temp.end());
  std::cout << "value: " << rt["key1"]["key5"]["key3"]["key4"][0] << std::endl;
  RecTree tempTree1(rt), tempTree2(rt);
  RecTree mergeTree("mt");
  mergeTree.insert({rt, tempTree1, tempTree2});
  EXPECT_EQ(rt.count(), 8);
  EXPECT_EQ(mergeTree.count(), 9);
  std::cout << "value: " << mergeTree["key"]["key1"]["key5"]["key3"]["key4"][0]
            << std::endl;
  //   for (const auto &val :
  //        mergeTree["key1"]["key5"]["key3"]["key4"].valueVector()) {
  //     std::cout << val << " ";
  //   }
  //   std::cout << std::endl;
}

TEST_F(TestRecursiveTree, pushValue) {
  RecTree rt("key");
  rt["key1"]["key2"]["key3"]["key4"].pushValue("this is a test");
  rt["key1"]["key5"]["key3"]["key4"].pushValue("9");
  rt["key1"]["key5"]["key3"]["key4"].pushValue("8");
  rt["key1"]["key5"]["key3"]["key4"].pushValue("7");
  rt["key1"]["key5"]["key3"]["key4"].pushValue("6");
  EXPECT_EQ(rt["key1"]["key5"]["key3"]["key4"][2].asString(), "7");
}

TEST_F(TestRecursiveTree, formatLisp) {
  recursive_map setRt("set");
  setRt["team.showWelcomeMessage"].pushValue("false");
  setRt["editor.fontSize"].pushValue("16");
  setRt["editor.rulers"].pushValue("80");
  setRt["editor.rulers"].pushValue("120");
  setRt["editor.rulers"].pushValue("360");
  setRt["window.zoomLevel"].pushValue("0");
  setRt["workbench.colorCustomizations"]["editor.selectionBackground"]
      .pushValue("#204d68");
  setRt["gitlens.advanced.messages"]["suppressLineUncommittedWarning"]
      .pushValue("true");
  setRt["gitlens.advanced.messages"]["suppressShowKeyBindingsNotice"]
      .pushValue(  // test comment
          "true");
  setRt["editor.renderWhitespace"].pushValue("all");
  setRt["editor.acceptSuggestionOnEnter"].pushValue("smart");
  setRt["C_Cpp.clang_format_fallbackStyle"].pushValue("");
  setRt["clang-format.language.cpp.fallbackStyle"].pushValue("Google");
  setRt["testVariableName"].pushValue("this is a \nmulti line\ntest");
  setRt["[ol (scheme)]"];
  setRt.formatLisp(std::cout) << std::endl;
  RecTree rt("key");
  rt["key1"]["key2"]["key3"]["key4"].pushValue("this is a test");
  std::vector<std::string> temp{"9", "8", "7", "6"};
  rt["key1"]["key5"]["key3"]["key4"].assign(temp.begin(), temp.end());
  rt["key1"]["key5"].formatLisp(std::cout) << std::endl;
  rt["key1"].formatLisp(std::cout) << std::endl;
  RecTree tempTree1(rt), tempTree2(rt);
  RecTree mergeTree("mt");
  mergeTree.insert({rt, tempTree1, tempTree2});
  EXPECT_EQ(rt.count(), 8);
  EXPECT_EQ(mergeTree.count(), 9);
  std::cout << "value: " << mergeTree["key"]["key1"]["key5"]["key3"]["key4"][0]
            << std::endl;
  rt.formatLisp(std::cout) << std::endl;
  mergeTree.formatLisp(std::cout) << std::endl;
}

class TestDbLispParser : public testing::Test {
 public:
  TestDbLispParser() {}
  ~TestDbLispParser(){};
};

TEST_F(TestDbLispParser, parser) {
  DbLispParser parser;
  recursive_map rmap;
  EXPECT_TRUE(parser.lispToRecMap("parser.scm", rmap));
}