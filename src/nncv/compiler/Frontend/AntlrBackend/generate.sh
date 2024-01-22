# created 2024.
# This file is used to generate source file from the aten-lang's antlr script

java -jar ../../../../../third_party/antlr/antlr-4.13.0-complete.jar -Dlanguage=Cpp -listener -visitor -o . -package antlrcpp ./AutoTenV1Lexer.g4 ./AutoTenV1Parser.g4