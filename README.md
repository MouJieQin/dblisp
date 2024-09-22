# dblisp
A json-like lisp

```lisp
("variableName" "aaa" "bbbb")
("set" ("team.showWelcomeMessage" "false")
       ("editor.fontSize" "16")
       ("editor.renderWhitespace" "all")
       ("editor.rulers" "80" "120" "360")
       ("window.zoomLevel" "0")
       ("workbench.colorCustomizations" ("editor.selectionBackground" "#204d68"))
       ("gitlens.advanced.messages" ("suppressLineUncommittedWarning" "true")
                                    ("suppressShowKeyBindingsNotice" "true")
       )
       ("editor.acceptSuggestionOnEnter" "smart")
       ("C_Cpp.clang_format_fallbackStyle" "")
       ("clang-format.language.cpp.fallbackStyle" "Google")
       ("testVariableName" (variableName))
       ("testVariableNamevalue" "first" "test errror")
       (variableName)
       ("[ol (scheme)]" )
)
```