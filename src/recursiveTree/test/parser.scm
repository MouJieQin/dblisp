;;test comment
;;test comment
;; ("key0")
;; ("key1" "value")
;; ("key2" ("key1" ("key2" ("key3" ("key4")))))
;; ("key3" ("key4")
;;         ("key5")
;; )

;; ("key" ("key1" ("key2" ("key3" ("key4" "this is a test")
;;                                ("key6" "val1 val2 val3")
;;                        ))))

;; ("key" ("key1" ("key2" ("key3" ("key4" "this is a test")
;;                                ("key6" "val1 val2 val3")
;;                        )
;;                )
;;                ("key5" ("key3" ("key4" "9" "8" "7" "6")
;;                        )
;;                )
;;        )
;; )

("set" ("C_Cpp.clang_format_fallbackStyle" "")
       ("[ol (scheme)]")
       ("clang-format.language.cpp.fallbackStyle" "Google")
       ("editor.acceptSuggestionOnEnter" "smart")
       ("editor.fontSize" "16")
       ("editor.renderWhitespace" "all")
       ("editor.rulers" "80" "120" "360");this is comment test
       ;; test comment
       ("gitlens.advanced.messages" ("suppressLineUncommittedWarning" "true")
                                    ("suppressShowKeyBindingsNotice" "true")
;;test comment
       )
       ("team.showWelcomeMessage" "false")
       ("testVariableName" "this is a")
;; multi line
;; test")
       ("window.zoomLevel" "0")
       ("workbench.colorCustomizations" ("editor.selectionBackground" "#204d68"))
)

;; test comment
;; ("variableName" "aaa" "bbbb")
;; ("variable2" "second" "three" "fefsf" "est")

;; ("set" ("team.showWelcomeMessage" "false")
;;        ("editor.fontSize" "16")
;;        ("editor.renderWhitespace" "all")
;;        ("editor.rulers" "80" "120" "360")
;;        ("window.zoomLevel" "0")
;;        ("workbench.colorCustomizations" ("editor.selectionBackground" "#204d68"))
;;        ("gitlens.advanced.messages" ("suppressLineUncommittedWarning" "true")
;;                                     ("suppressShowKeyBindingsNotice" "true")
;;        )
;;        ("editor.acceptSuggestionOnEnter" "smart")
;;        ("C_Cpp.clang_format_fallbackStyle" "")
;;        ("clang-format.language.cpp.fallbackStyle" "Google")
;;        ("testVariableName" (variableName))
;;        ("testVariableNamevalue" "first" variable2 "test errror")
;;        (variableName)
;;        ("[ol (scheme)]" )
;; )


