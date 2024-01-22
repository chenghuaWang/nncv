
// Generated from ./AutoTenV1Parser.g4 by ANTLR 4.13.0


#include "AutoTenV1ParserListener.h"
#include "AutoTenV1ParserVisitor.h"

#include "AutoTenV1Parser.h"


using namespace antlrcpp;
using namespace antlrcpp;

using namespace antlr4;

namespace {

struct AutoTenV1ParserStaticData final {
  AutoTenV1ParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  AutoTenV1ParserStaticData(const AutoTenV1ParserStaticData&) = delete;
  AutoTenV1ParserStaticData(AutoTenV1ParserStaticData&&) = delete;
  AutoTenV1ParserStaticData& operator=(const AutoTenV1ParserStaticData&) = delete;
  AutoTenV1ParserStaticData& operator=(AutoTenV1ParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag autotenv1parserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
AutoTenV1ParserStaticData *autotenv1parserParserStaticData = nullptr;

void autotenv1parserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (autotenv1parserParserStaticData != nullptr) {
    return;
  }
#else
  assert(autotenv1parserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<AutoTenV1ParserStaticData>(
    std::vector<std::string>{
      "sourceFile", "packageClause", "compileFlags", "declaration", "typeDecl", 
      "typeSpec", "type_", "tensorType", "builtinType", "typeName", "typeLit", 
      "arrayType", "arrayLength", "elementType", "pointerType", "implType", 
      "sliceType", "mapType", "methodSpec", "functionType", "varDecl", "varSpec", 
      "signature", "result", "parameters", "index", "slice_", "typeAssertion", 
      "arguments", "methodExpr", "parameterDecl", "expression", "primaryExpr", 
      "conversion", "nonNamedType", "operand", "expressionList", "identifierList", 
      "literal", "basicLit", "operandName", "qualifiedIdent", "compositeLit", 
      "literalType", "literalValue", "elementList", "keyedElement", "key", 
      "element", "structType", "fieldDecl", "embeddedField", "functionLit", 
      "functionDecl", "block", "statementList", "statement", "simpleStmt", 
      "expressionStmt", "incDecStmt", "assignment", "assign_op", "shortVarDecl", 
      "emptyStmt", "labeledStmt", "returnStmt", "breakStmt", "continueStmt", 
      "gotoStmt", "fallthroughStmt", "ifStmt", "switchStmt", "exprSwitchStmt", 
      "exprCaseClause", "exprSwitchCase", "typeSwitchStmt", "typeSwitchGuard", 
      "typeCaseClause", "typeSwitchCase", "typeList", "forStmt", "pforStmt", 
      "pforClause", "forClause", "whileStmt", "doWhileStmt", "eos"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "'int8'", "'int16'", "'int32'", "'int64'", 
      "'float32'", "'float64'", "'char'", "'bool'", "'string'", "'Tensor'", 
      "'var'", "'false'", "'true'", "'void'", "'nil'", "'break'", "'continue'", 
      "'goto'", "'fallthrough'", "'if'", "'while'", "'for'", "'pfor'", "'else'", 
      "'do'", "'switch'", "'case'", "'default'", "'func'", "'return'", "'struct'", 
      "'type'", "'package'", "'impl'", "'pub'", "'sizeof'", "'('", "')'", 
      "'['", "']'", "'{'", "'}'", "'+'", "'-'", "'*'", "'/'", "", "", "'&'", 
      "'|'", "'~'", "", "'='", "':='", "'<'", "'>'", "'<<'", "'>>'", "'!='", 
      "'=='", "'<='", "'>='", "", "", "'++'", "'--'", "','", "'->'", "':'", 
      "'.'", "'.*'", "'->*'", "'@'", "';'", "'map'", "'...'"
    },
    std::vector<std::string>{
      "", "IntegerLiteral", "CharacterLiteral", "FloatingLiteral", "StringLiteral", 
      "BooleanLiteral", "PointerLiteral", "UserDefinedLiteral", "Int8", 
      "Int16", "Int32", "Int64", "Float32", "Float64", "Char", "Bool", "String", 
      "Tensor", "Var", "False_", "True_", "Void", "Nilptr", "Break", "Continue", 
      "Goto", "Fallthrough", "If", "While", "For", "Pfor", "Else", "Do", 
      "Switch", "Case", "Default", "Function", "Return", "Struct", "Type", 
      "Package", "Impl", "Public", "Sizeof", "LeftParen", "RightParen", 
      "LeftBracket", "RightBracket", "LeftBrace", "RightBrace", "Plus", 
      "Minus", "Star", "Div", "Mod", "Caret", "And", "Or", "Tilde", "Not", 
      "Assign", "DeclareAssign", "Less", "Greater", "LeftShift", "RightShift", 
      "NotEqual", "Equal", "LessEqual", "GreaterEqual", "AndAnd", "OrOr", 
      "PlusPlus", "MinusMinus", "Comma", "ArrowReturnType", "Colon", "Dot", 
      "DotStar", "ArrowStar", "At", "Semi", "Map", "Ellipsis", "Identifier", 
      "DecimalLiteral", "OctalLiteral", "HexadecimalLiteral", "BinaryLiteral", 
      "Integersuffix", "UserDefinedIntegerLiteral", "UserDefinedFloatingLiteral", 
      "UserDefinedStringLiteral", "UserDefinedCharacterLiteral", "Whitespace", 
      "Newline", "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,97,918,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,7,
  	70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,2,75,7,75,2,76,7,76,2,77,7,
  	77,2,78,7,78,2,79,7,79,2,80,7,80,2,81,7,81,2,82,7,82,2,83,7,83,2,84,7,
  	84,2,85,7,85,2,86,7,86,1,0,1,0,1,0,1,0,3,0,179,8,0,1,0,1,0,5,0,183,8,
  	0,10,0,12,0,186,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,5,2,199,
  	8,2,10,2,12,2,202,9,2,1,2,1,2,1,2,1,2,3,2,208,8,2,3,2,210,8,2,1,3,1,3,
  	3,3,214,8,3,1,4,1,4,1,4,1,4,1,4,1,4,5,4,222,8,4,10,4,12,4,225,9,4,1,4,
  	3,4,228,8,4,1,5,1,5,3,5,232,8,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,
  	6,243,8,6,1,7,1,7,1,7,1,7,1,7,5,7,250,8,7,10,7,12,7,253,9,7,1,7,1,7,1,
  	7,1,7,3,7,259,8,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,272,
  	8,8,1,9,1,9,3,9,276,8,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,3,10,285,8,
  	10,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,13,1,13,1,14,1,14,1,14,1,15,1,
  	15,1,15,1,15,1,15,5,15,304,8,15,10,15,12,15,307,9,15,1,15,1,15,1,16,1,
  	16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,
  	18,3,18,327,8,18,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,1,20,5,20,338,
  	8,20,10,20,12,20,341,9,20,1,20,3,20,344,8,20,1,21,1,21,1,21,1,21,3,21,
  	350,8,21,1,21,1,21,3,21,354,8,21,1,22,1,22,1,22,1,22,1,22,3,22,361,8,
  	22,1,23,1,23,3,23,365,8,23,1,24,1,24,1,24,1,24,5,24,371,8,24,10,24,12,
  	24,374,9,24,1,24,3,24,377,8,24,3,24,379,8,24,1,24,1,24,1,25,1,25,1,25,
  	1,25,1,26,1,26,3,26,389,8,26,1,26,1,26,3,26,393,8,26,1,26,3,26,396,8,
  	26,1,26,1,26,1,26,1,26,1,26,1,26,3,26,404,8,26,1,26,1,26,3,26,408,8,26,
  	1,26,1,26,3,26,412,8,26,1,26,3,26,415,8,26,1,26,1,26,1,26,1,26,1,26,1,
  	26,3,26,423,8,26,5,26,425,8,26,10,26,12,26,428,9,26,1,26,1,26,1,27,1,
  	27,1,27,1,27,1,27,1,28,1,28,1,28,1,28,1,28,3,28,442,8,28,3,28,444,8,28,
  	1,28,3,28,447,8,28,1,28,3,28,450,8,28,3,28,452,8,28,1,28,1,28,1,29,1,
  	29,1,29,1,29,1,30,3,30,461,8,30,1,30,3,30,464,8,30,1,30,1,30,1,31,1,31,
  	1,31,1,31,3,31,472,8,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,
  	1,31,1,31,1,31,1,31,1,31,1,31,5,31,489,8,31,10,31,12,31,492,9,31,1,32,
  	1,32,1,32,1,32,3,32,498,8,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,3,32,
  	507,8,32,5,32,509,8,32,10,32,12,32,512,9,32,1,33,1,33,1,33,1,33,3,33,
  	518,8,33,1,33,1,33,1,34,1,34,1,34,1,34,1,34,3,34,527,8,34,1,35,1,35,1,
  	35,1,35,1,35,1,35,3,35,535,8,35,1,36,1,36,1,36,5,36,540,8,36,10,36,12,
  	36,543,9,36,1,37,1,37,1,37,5,37,548,8,37,10,37,12,37,551,9,37,1,38,1,
  	38,1,38,3,38,556,8,38,1,39,1,39,1,40,1,40,1,41,1,41,1,41,1,41,1,42,1,
  	42,1,42,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,3,43,580,
  	8,43,1,44,1,44,1,44,3,44,585,8,44,3,44,587,8,44,1,44,1,44,1,45,1,45,1,
  	45,5,45,594,8,45,10,45,12,45,597,9,45,1,46,1,46,1,46,3,46,602,8,46,1,
  	46,1,46,1,47,1,47,3,47,608,8,47,1,48,1,48,3,48,612,8,48,1,49,1,49,1,49,
  	3,49,617,8,49,1,49,1,49,1,49,5,49,622,8,49,10,49,12,49,625,9,49,1,49,
  	1,49,1,50,1,50,1,50,1,50,3,50,633,8,50,1,50,3,50,636,8,50,1,51,3,51,639,
  	8,51,1,51,1,51,1,52,5,52,644,8,52,10,52,12,52,647,9,52,1,52,1,52,1,52,
  	1,52,1,53,5,53,654,8,53,10,53,12,53,657,9,53,1,53,3,53,660,8,53,1,53,
  	1,53,1,53,1,53,3,53,666,8,53,1,54,1,54,3,54,670,8,54,1,54,1,54,1,55,3,
  	55,675,8,55,1,55,1,55,1,55,4,55,680,8,55,11,55,12,55,681,1,56,1,56,1,
  	56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,3,56,699,
  	8,56,1,57,1,57,1,57,1,57,3,57,705,8,57,1,58,1,58,1,59,1,59,1,59,1,60,
  	1,60,1,60,1,60,1,61,3,61,717,8,61,1,61,1,61,1,62,1,62,1,62,1,62,1,63,
  	1,63,1,64,1,64,1,64,3,64,730,8,64,1,65,1,65,3,65,734,8,65,1,66,1,66,3,
  	66,738,8,66,1,67,1,67,3,67,742,8,67,1,68,1,68,1,68,1,69,1,69,1,70,1,70,
  	1,70,1,70,1,70,1,70,1,70,1,70,1,70,1,70,3,70,759,8,70,1,70,1,70,1,70,
  	1,70,1,70,3,70,766,8,70,3,70,768,8,70,1,71,1,71,3,71,772,8,71,1,72,1,
  	72,1,72,3,72,777,8,72,1,72,3,72,780,8,72,1,72,1,72,3,72,784,8,72,3,72,
  	786,8,72,1,72,1,72,1,72,5,72,791,8,72,10,72,12,72,794,9,72,1,72,1,72,
  	1,73,1,73,1,73,3,73,801,8,73,1,74,1,74,1,74,3,74,806,8,74,1,75,1,75,1,
  	75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,3,75,818,8,75,1,75,1,75,1,75,5,
  	75,823,8,75,10,75,12,75,826,9,75,1,75,1,75,1,76,1,76,3,76,832,8,76,1,
  	76,1,76,1,76,1,76,1,76,1,76,1,77,1,77,1,77,3,77,843,8,77,1,78,1,78,1,
  	78,3,78,848,8,78,1,79,1,79,3,79,852,8,79,1,79,1,79,1,79,3,79,857,8,79,
  	5,79,859,8,79,10,79,12,79,862,9,79,1,80,1,80,1,80,3,80,867,8,80,1,80,
  	3,80,870,8,80,1,80,1,80,1,80,1,81,1,81,1,81,3,81,878,8,81,1,81,3,81,881,
  	8,81,1,81,1,81,1,81,1,82,1,82,1,82,1,82,1,82,1,82,1,83,3,83,893,8,83,
  	1,83,1,83,3,83,897,8,83,1,83,1,83,3,83,901,8,83,1,84,1,84,1,84,1,84,1,
  	84,1,84,1,85,1,85,1,85,1,85,1,85,1,85,1,85,1,86,1,86,1,86,0,2,62,64,87,
  	0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,
  	50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,
  	96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,
  	132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,166,
  	168,170,172,0,8,1,0,10,13,3,0,50,52,55,56,59,59,3,0,52,54,56,56,64,65,
  	3,0,50,51,55,55,57,57,2,0,62,63,66,69,2,0,1,4,22,22,1,0,72,73,2,0,50,
  	57,64,65,986,0,174,1,0,0,0,2,189,1,0,0,0,4,194,1,0,0,0,6,213,1,0,0,0,
  	8,215,1,0,0,0,10,229,1,0,0,0,12,242,1,0,0,0,14,244,1,0,0,0,16,271,1,0,
  	0,0,18,275,1,0,0,0,20,284,1,0,0,0,22,286,1,0,0,0,24,291,1,0,0,0,26,293,
  	1,0,0,0,28,295,1,0,0,0,30,298,1,0,0,0,32,310,1,0,0,0,34,314,1,0,0,0,36,
  	326,1,0,0,0,38,328,1,0,0,0,40,331,1,0,0,0,42,345,1,0,0,0,44,360,1,0,0,
  	0,46,364,1,0,0,0,48,366,1,0,0,0,50,382,1,0,0,0,52,386,1,0,0,0,54,431,
  	1,0,0,0,56,436,1,0,0,0,58,455,1,0,0,0,60,460,1,0,0,0,62,471,1,0,0,0,64,
  	497,1,0,0,0,66,513,1,0,0,0,68,526,1,0,0,0,70,534,1,0,0,0,72,536,1,0,0,
  	0,74,544,1,0,0,0,76,555,1,0,0,0,78,557,1,0,0,0,80,559,1,0,0,0,82,561,
  	1,0,0,0,84,565,1,0,0,0,86,579,1,0,0,0,88,581,1,0,0,0,90,590,1,0,0,0,92,
  	601,1,0,0,0,94,607,1,0,0,0,96,611,1,0,0,0,98,613,1,0,0,0,100,632,1,0,
  	0,0,102,638,1,0,0,0,104,645,1,0,0,0,106,655,1,0,0,0,108,667,1,0,0,0,110,
  	679,1,0,0,0,112,698,1,0,0,0,114,704,1,0,0,0,116,706,1,0,0,0,118,708,1,
  	0,0,0,120,711,1,0,0,0,122,716,1,0,0,0,124,720,1,0,0,0,126,724,1,0,0,0,
  	128,726,1,0,0,0,130,731,1,0,0,0,132,735,1,0,0,0,134,739,1,0,0,0,136,743,
  	1,0,0,0,138,746,1,0,0,0,140,748,1,0,0,0,142,771,1,0,0,0,144,773,1,0,0,
  	0,146,797,1,0,0,0,148,805,1,0,0,0,150,807,1,0,0,0,152,831,1,0,0,0,154,
  	839,1,0,0,0,156,847,1,0,0,0,158,851,1,0,0,0,160,863,1,0,0,0,162,874,1,
  	0,0,0,164,885,1,0,0,0,166,892,1,0,0,0,168,902,1,0,0,0,170,908,1,0,0,0,
  	172,915,1,0,0,0,174,175,3,2,1,0,175,184,3,172,86,0,176,179,3,106,53,0,
  	177,179,3,6,3,0,178,176,1,0,0,0,178,177,1,0,0,0,179,180,1,0,0,0,180,181,
  	3,172,86,0,181,183,1,0,0,0,182,178,1,0,0,0,183,186,1,0,0,0,184,182,1,
  	0,0,0,184,185,1,0,0,0,185,187,1,0,0,0,186,184,1,0,0,0,187,188,5,0,0,1,
  	188,1,1,0,0,0,189,190,5,80,0,0,190,191,5,40,0,0,191,192,5,60,0,0,192,
  	193,5,4,0,0,193,3,1,0,0,0,194,195,5,80,0,0,195,200,5,84,0,0,196,197,9,
  	0,0,0,197,199,5,84,0,0,198,196,1,0,0,0,199,202,1,0,0,0,200,198,1,0,0,
  	0,200,201,1,0,0,0,201,209,1,0,0,0,202,200,1,0,0,0,203,207,5,60,0,0,204,
  	208,5,20,0,0,205,208,5,19,0,0,206,208,3,62,31,0,207,204,1,0,0,0,207,205,
  	1,0,0,0,207,206,1,0,0,0,208,210,1,0,0,0,209,203,1,0,0,0,209,210,1,0,0,
  	0,210,5,1,0,0,0,211,214,3,8,4,0,212,214,3,40,20,0,213,211,1,0,0,0,213,
  	212,1,0,0,0,214,7,1,0,0,0,215,227,5,39,0,0,216,228,3,10,5,0,217,223,5,
  	44,0,0,218,219,3,10,5,0,219,220,3,172,86,0,220,222,1,0,0,0,221,218,1,
  	0,0,0,222,225,1,0,0,0,223,221,1,0,0,0,223,224,1,0,0,0,224,226,1,0,0,0,
  	225,223,1,0,0,0,226,228,5,45,0,0,227,216,1,0,0,0,227,217,1,0,0,0,228,
  	9,1,0,0,0,229,231,5,84,0,0,230,232,5,60,0,0,231,230,1,0,0,0,231,232,1,
  	0,0,0,232,233,1,0,0,0,233,234,3,12,6,0,234,11,1,0,0,0,235,243,3,18,9,
  	0,236,243,3,20,10,0,237,238,5,44,0,0,238,239,3,12,6,0,239,240,5,45,0,
  	0,240,243,1,0,0,0,241,243,3,16,8,0,242,235,1,0,0,0,242,236,1,0,0,0,242,
  	237,1,0,0,0,242,241,1,0,0,0,243,13,1,0,0,0,244,258,5,17,0,0,245,246,5,
  	62,0,0,246,251,3,62,31,0,247,248,5,74,0,0,248,250,3,62,31,0,249,247,1,
  	0,0,0,250,253,1,0,0,0,251,249,1,0,0,0,251,252,1,0,0,0,252,254,1,0,0,0,
  	253,251,1,0,0,0,254,255,5,74,0,0,255,256,7,0,0,0,256,257,5,63,0,0,257,
  	259,1,0,0,0,258,245,1,0,0,0,258,259,1,0,0,0,259,15,1,0,0,0,260,272,5,
  	8,0,0,261,272,5,9,0,0,262,272,5,10,0,0,263,272,5,11,0,0,264,272,5,12,
  	0,0,265,272,5,13,0,0,266,272,5,15,0,0,267,272,5,16,0,0,268,272,5,14,0,
  	0,269,272,3,14,7,0,270,272,5,21,0,0,271,260,1,0,0,0,271,261,1,0,0,0,271,
  	262,1,0,0,0,271,263,1,0,0,0,271,264,1,0,0,0,271,265,1,0,0,0,271,266,1,
  	0,0,0,271,267,1,0,0,0,271,268,1,0,0,0,271,269,1,0,0,0,271,270,1,0,0,0,
  	272,17,1,0,0,0,273,276,3,82,41,0,274,276,5,84,0,0,275,273,1,0,0,0,275,
  	274,1,0,0,0,276,19,1,0,0,0,277,285,3,22,11,0,278,285,3,98,49,0,279,285,
  	3,28,14,0,280,285,3,38,19,0,281,285,3,30,15,0,282,285,3,32,16,0,283,285,
  	3,34,17,0,284,277,1,0,0,0,284,278,1,0,0,0,284,279,1,0,0,0,284,280,1,0,
  	0,0,284,281,1,0,0,0,284,282,1,0,0,0,284,283,1,0,0,0,285,21,1,0,0,0,286,
  	287,5,46,0,0,287,288,3,24,12,0,288,289,5,47,0,0,289,290,3,26,13,0,290,
  	23,1,0,0,0,291,292,3,62,31,0,292,25,1,0,0,0,293,294,3,12,6,0,294,27,1,
  	0,0,0,295,296,5,52,0,0,296,297,3,12,6,0,297,29,1,0,0,0,298,299,5,41,0,
  	0,299,305,5,48,0,0,300,301,3,106,53,0,301,302,5,81,0,0,302,304,1,0,0,
  	0,303,300,1,0,0,0,304,307,1,0,0,0,305,303,1,0,0,0,305,306,1,0,0,0,306,
  	308,1,0,0,0,307,305,1,0,0,0,308,309,5,49,0,0,309,31,1,0,0,0,310,311,5,
  	46,0,0,311,312,5,47,0,0,312,313,3,26,13,0,313,33,1,0,0,0,314,315,5,82,
  	0,0,315,316,5,46,0,0,316,317,3,12,6,0,317,318,5,47,0,0,318,319,3,26,13,
  	0,319,35,1,0,0,0,320,321,5,84,0,0,321,322,3,48,24,0,322,323,3,46,23,0,
  	323,327,1,0,0,0,324,325,5,84,0,0,325,327,3,48,24,0,326,320,1,0,0,0,326,
  	324,1,0,0,0,327,37,1,0,0,0,328,329,5,36,0,0,329,330,3,44,22,0,330,39,
  	1,0,0,0,331,343,5,18,0,0,332,344,3,42,21,0,333,339,5,44,0,0,334,335,3,
  	42,21,0,335,336,3,172,86,0,336,338,1,0,0,0,337,334,1,0,0,0,338,341,1,
  	0,0,0,339,337,1,0,0,0,339,340,1,0,0,0,340,342,1,0,0,0,341,339,1,0,0,0,
  	342,344,5,45,0,0,343,332,1,0,0,0,343,333,1,0,0,0,344,41,1,0,0,0,345,353,
  	3,74,37,0,346,349,3,12,6,0,347,348,5,60,0,0,348,350,3,72,36,0,349,347,
  	1,0,0,0,349,350,1,0,0,0,350,354,1,0,0,0,351,352,5,60,0,0,352,354,3,72,
  	36,0,353,346,1,0,0,0,353,351,1,0,0,0,354,43,1,0,0,0,355,356,3,48,24,0,
  	356,357,5,75,0,0,357,358,3,46,23,0,358,361,1,0,0,0,359,361,3,48,24,0,
  	360,355,1,0,0,0,360,359,1,0,0,0,361,45,1,0,0,0,362,365,3,48,24,0,363,
  	365,3,12,6,0,364,362,1,0,0,0,364,363,1,0,0,0,365,47,1,0,0,0,366,378,5,
  	44,0,0,367,372,3,60,30,0,368,369,5,74,0,0,369,371,3,60,30,0,370,368,1,
  	0,0,0,371,374,1,0,0,0,372,370,1,0,0,0,372,373,1,0,0,0,373,376,1,0,0,0,
  	374,372,1,0,0,0,375,377,5,74,0,0,376,375,1,0,0,0,376,377,1,0,0,0,377,
  	379,1,0,0,0,378,367,1,0,0,0,378,379,1,0,0,0,379,380,1,0,0,0,380,381,5,
  	45,0,0,381,49,1,0,0,0,382,383,5,46,0,0,383,384,3,62,31,0,384,385,5,47,
  	0,0,385,51,1,0,0,0,386,403,5,46,0,0,387,389,3,62,31,0,388,387,1,0,0,0,
  	388,389,1,0,0,0,389,390,1,0,0,0,390,392,5,76,0,0,391,393,3,62,31,0,392,
  	391,1,0,0,0,392,393,1,0,0,0,393,404,1,0,0,0,394,396,3,62,31,0,395,394,
  	1,0,0,0,395,396,1,0,0,0,396,397,1,0,0,0,397,398,5,76,0,0,398,399,3,62,
  	31,0,399,400,5,76,0,0,400,401,3,62,31,0,401,404,1,0,0,0,402,404,3,62,
  	31,0,403,388,1,0,0,0,403,395,1,0,0,0,403,402,1,0,0,0,404,426,1,0,0,0,
  	405,422,5,74,0,0,406,408,3,62,31,0,407,406,1,0,0,0,407,408,1,0,0,0,408,
  	409,1,0,0,0,409,411,5,76,0,0,410,412,3,62,31,0,411,410,1,0,0,0,411,412,
  	1,0,0,0,412,423,1,0,0,0,413,415,3,62,31,0,414,413,1,0,0,0,414,415,1,0,
  	0,0,415,416,1,0,0,0,416,417,5,76,0,0,417,418,3,62,31,0,418,419,5,76,0,
  	0,419,420,3,62,31,0,420,423,1,0,0,0,421,423,3,62,31,0,422,407,1,0,0,0,
  	422,414,1,0,0,0,422,421,1,0,0,0,423,425,1,0,0,0,424,405,1,0,0,0,425,428,
  	1,0,0,0,426,424,1,0,0,0,426,427,1,0,0,0,427,429,1,0,0,0,428,426,1,0,0,
  	0,429,430,5,47,0,0,430,53,1,0,0,0,431,432,5,77,0,0,432,433,5,44,0,0,433,
  	434,3,12,6,0,434,435,5,45,0,0,435,55,1,0,0,0,436,451,5,44,0,0,437,444,
  	3,72,36,0,438,441,3,68,34,0,439,440,5,74,0,0,440,442,3,72,36,0,441,439,
  	1,0,0,0,441,442,1,0,0,0,442,444,1,0,0,0,443,437,1,0,0,0,443,438,1,0,0,
  	0,444,446,1,0,0,0,445,447,5,83,0,0,446,445,1,0,0,0,446,447,1,0,0,0,447,
  	449,1,0,0,0,448,450,5,74,0,0,449,448,1,0,0,0,449,450,1,0,0,0,450,452,
  	1,0,0,0,451,443,1,0,0,0,451,452,1,0,0,0,452,453,1,0,0,0,453,454,5,45,
  	0,0,454,57,1,0,0,0,455,456,3,68,34,0,456,457,5,77,0,0,457,458,5,84,0,
  	0,458,59,1,0,0,0,459,461,3,74,37,0,460,459,1,0,0,0,460,461,1,0,0,0,461,
  	463,1,0,0,0,462,464,5,83,0,0,463,462,1,0,0,0,463,464,1,0,0,0,464,465,
  	1,0,0,0,465,466,3,12,6,0,466,61,1,0,0,0,467,468,6,31,-1,0,468,472,3,64,
  	32,0,469,470,7,1,0,0,470,472,3,62,31,6,471,467,1,0,0,0,471,469,1,0,0,
  	0,472,490,1,0,0,0,473,474,10,5,0,0,474,475,7,2,0,0,475,489,3,62,31,6,
  	476,477,10,4,0,0,477,478,7,3,0,0,478,489,3,62,31,5,479,480,10,3,0,0,480,
  	481,7,4,0,0,481,489,3,62,31,4,482,483,10,2,0,0,483,484,5,70,0,0,484,489,
  	3,62,31,3,485,486,10,1,0,0,486,487,5,71,0,0,487,489,3,62,31,2,488,473,
  	1,0,0,0,488,476,1,0,0,0,488,479,1,0,0,0,488,482,1,0,0,0,488,485,1,0,0,
  	0,489,492,1,0,0,0,490,488,1,0,0,0,490,491,1,0,0,0,491,63,1,0,0,0,492,
  	490,1,0,0,0,493,494,6,32,-1,0,494,498,3,70,35,0,495,498,3,66,33,0,496,
  	498,3,58,29,0,497,493,1,0,0,0,497,495,1,0,0,0,497,496,1,0,0,0,498,510,
  	1,0,0,0,499,506,10,1,0,0,500,501,5,77,0,0,501,507,5,84,0,0,502,507,3,
  	50,25,0,503,507,3,52,26,0,504,507,3,54,27,0,505,507,3,56,28,0,506,500,
  	1,0,0,0,506,502,1,0,0,0,506,503,1,0,0,0,506,504,1,0,0,0,506,505,1,0,0,
  	0,507,509,1,0,0,0,508,499,1,0,0,0,509,512,1,0,0,0,510,508,1,0,0,0,510,
  	511,1,0,0,0,511,65,1,0,0,0,512,510,1,0,0,0,513,514,3,68,34,0,514,515,
  	5,44,0,0,515,517,3,62,31,0,516,518,5,74,0,0,517,516,1,0,0,0,517,518,1,
  	0,0,0,518,519,1,0,0,0,519,520,5,45,0,0,520,67,1,0,0,0,521,527,3,20,10,
  	0,522,523,5,44,0,0,523,524,3,68,34,0,524,525,5,45,0,0,525,527,1,0,0,0,
  	526,521,1,0,0,0,526,522,1,0,0,0,527,69,1,0,0,0,528,535,3,76,38,0,529,
  	535,3,80,40,0,530,531,5,44,0,0,531,532,3,62,31,0,532,533,5,45,0,0,533,
  	535,1,0,0,0,534,528,1,0,0,0,534,529,1,0,0,0,534,530,1,0,0,0,535,71,1,
  	0,0,0,536,541,3,62,31,0,537,538,5,74,0,0,538,540,3,62,31,0,539,537,1,
  	0,0,0,540,543,1,0,0,0,541,539,1,0,0,0,541,542,1,0,0,0,542,73,1,0,0,0,
  	543,541,1,0,0,0,544,549,5,84,0,0,545,546,5,74,0,0,546,548,5,84,0,0,547,
  	545,1,0,0,0,548,551,1,0,0,0,549,547,1,0,0,0,549,550,1,0,0,0,550,75,1,
  	0,0,0,551,549,1,0,0,0,552,556,3,78,39,0,553,556,3,84,42,0,554,556,3,104,
  	52,0,555,552,1,0,0,0,555,553,1,0,0,0,555,554,1,0,0,0,556,77,1,0,0,0,557,
  	558,7,5,0,0,558,79,1,0,0,0,559,560,5,84,0,0,560,81,1,0,0,0,561,562,5,
  	84,0,0,562,563,5,77,0,0,563,564,5,84,0,0,564,83,1,0,0,0,565,566,3,86,
  	43,0,566,567,3,88,44,0,567,85,1,0,0,0,568,580,3,98,49,0,569,580,3,22,
  	11,0,570,571,3,26,13,0,571,572,5,46,0,0,572,573,5,83,0,0,573,574,5,47,
  	0,0,574,580,1,0,0,0,575,580,3,32,16,0,576,580,3,14,7,0,577,580,3,34,17,
  	0,578,580,3,18,9,0,579,568,1,0,0,0,579,569,1,0,0,0,579,570,1,0,0,0,579,
  	575,1,0,0,0,579,576,1,0,0,0,579,577,1,0,0,0,579,578,1,0,0,0,580,87,1,
  	0,0,0,581,586,5,48,0,0,582,584,3,90,45,0,583,585,5,74,0,0,584,583,1,0,
  	0,0,584,585,1,0,0,0,585,587,1,0,0,0,586,582,1,0,0,0,586,587,1,0,0,0,587,
  	588,1,0,0,0,588,589,5,49,0,0,589,89,1,0,0,0,590,595,3,92,46,0,591,592,
  	5,74,0,0,592,594,3,92,46,0,593,591,1,0,0,0,594,597,1,0,0,0,595,593,1,
  	0,0,0,595,596,1,0,0,0,596,91,1,0,0,0,597,595,1,0,0,0,598,599,3,94,47,
  	0,599,600,5,76,0,0,600,602,1,0,0,0,601,598,1,0,0,0,601,602,1,0,0,0,602,
  	603,1,0,0,0,603,604,3,96,48,0,604,93,1,0,0,0,605,608,3,62,31,0,606,608,
  	3,88,44,0,607,605,1,0,0,0,607,606,1,0,0,0,608,95,1,0,0,0,609,612,3,62,
  	31,0,610,612,3,88,44,0,611,609,1,0,0,0,611,610,1,0,0,0,612,97,1,0,0,0,
  	613,614,5,38,0,0,614,623,5,48,0,0,615,617,5,42,0,0,616,615,1,0,0,0,616,
  	617,1,0,0,0,617,618,1,0,0,0,618,619,3,100,50,0,619,620,3,172,86,0,620,
  	622,1,0,0,0,621,616,1,0,0,0,622,625,1,0,0,0,623,621,1,0,0,0,623,624,1,
  	0,0,0,624,626,1,0,0,0,625,623,1,0,0,0,626,627,5,49,0,0,627,99,1,0,0,0,
  	628,629,3,74,37,0,629,630,3,12,6,0,630,633,1,0,0,0,631,633,3,102,51,0,
  	632,628,1,0,0,0,632,631,1,0,0,0,633,635,1,0,0,0,634,636,5,4,0,0,635,634,
  	1,0,0,0,635,636,1,0,0,0,636,101,1,0,0,0,637,639,5,52,0,0,638,637,1,0,
  	0,0,638,639,1,0,0,0,639,640,1,0,0,0,640,641,3,18,9,0,641,103,1,0,0,0,
  	642,644,3,4,2,0,643,642,1,0,0,0,644,647,1,0,0,0,645,643,1,0,0,0,645,646,
  	1,0,0,0,646,648,1,0,0,0,647,645,1,0,0,0,648,649,5,36,0,0,649,650,3,44,
  	22,0,650,651,3,108,54,0,651,105,1,0,0,0,652,654,3,4,2,0,653,652,1,0,0,
  	0,654,657,1,0,0,0,655,653,1,0,0,0,655,656,1,0,0,0,656,659,1,0,0,0,657,
  	655,1,0,0,0,658,660,5,42,0,0,659,658,1,0,0,0,659,660,1,0,0,0,660,661,
  	1,0,0,0,661,662,5,36,0,0,662,663,5,84,0,0,663,665,3,44,22,0,664,666,3,
  	108,54,0,665,664,1,0,0,0,665,666,1,0,0,0,666,107,1,0,0,0,667,669,5,48,
  	0,0,668,670,3,110,55,0,669,668,1,0,0,0,669,670,1,0,0,0,670,671,1,0,0,
  	0,671,672,5,49,0,0,672,109,1,0,0,0,673,675,5,81,0,0,674,673,1,0,0,0,674,
  	675,1,0,0,0,675,676,1,0,0,0,676,677,3,112,56,0,677,678,3,172,86,0,678,
  	680,1,0,0,0,679,674,1,0,0,0,680,681,1,0,0,0,681,679,1,0,0,0,681,682,1,
  	0,0,0,682,111,1,0,0,0,683,699,3,6,3,0,684,699,3,128,64,0,685,699,3,114,
  	57,0,686,699,3,130,65,0,687,699,3,132,66,0,688,699,3,134,67,0,689,699,
  	3,136,68,0,690,699,3,138,69,0,691,699,3,108,54,0,692,699,3,140,70,0,693,
  	699,3,142,71,0,694,699,3,160,80,0,695,699,3,162,81,0,696,699,3,168,84,
  	0,697,699,3,170,85,0,698,683,1,0,0,0,698,684,1,0,0,0,698,685,1,0,0,0,
  	698,686,1,0,0,0,698,687,1,0,0,0,698,688,1,0,0,0,698,689,1,0,0,0,698,690,
  	1,0,0,0,698,691,1,0,0,0,698,692,1,0,0,0,698,693,1,0,0,0,698,694,1,0,0,
  	0,698,695,1,0,0,0,698,696,1,0,0,0,698,697,1,0,0,0,699,113,1,0,0,0,700,
  	705,3,118,59,0,701,705,3,120,60,0,702,705,3,116,58,0,703,705,3,124,62,
  	0,704,700,1,0,0,0,704,701,1,0,0,0,704,702,1,0,0,0,704,703,1,0,0,0,705,
  	115,1,0,0,0,706,707,3,62,31,0,707,117,1,0,0,0,708,709,3,62,31,0,709,710,
  	7,6,0,0,710,119,1,0,0,0,711,712,3,72,36,0,712,713,3,122,61,0,713,714,
  	3,72,36,0,714,121,1,0,0,0,715,717,7,7,0,0,716,715,1,0,0,0,716,717,1,0,
  	0,0,717,718,1,0,0,0,718,719,5,60,0,0,719,123,1,0,0,0,720,721,3,74,37,
  	0,721,722,5,61,0,0,722,723,3,72,36,0,723,125,1,0,0,0,724,725,5,81,0,0,
  	725,127,1,0,0,0,726,727,5,84,0,0,727,729,5,76,0,0,728,730,3,112,56,0,
  	729,728,1,0,0,0,729,730,1,0,0,0,730,129,1,0,0,0,731,733,5,37,0,0,732,
  	734,3,72,36,0,733,732,1,0,0,0,733,734,1,0,0,0,734,131,1,0,0,0,735,737,
  	5,23,0,0,736,738,5,84,0,0,737,736,1,0,0,0,737,738,1,0,0,0,738,133,1,0,
  	0,0,739,741,5,24,0,0,740,742,5,84,0,0,741,740,1,0,0,0,741,742,1,0,0,0,
  	742,135,1,0,0,0,743,744,5,25,0,0,744,745,5,84,0,0,745,137,1,0,0,0,746,
  	747,5,26,0,0,747,139,1,0,0,0,748,749,5,27,0,0,749,758,5,44,0,0,750,759,
  	3,62,31,0,751,752,3,172,86,0,752,753,3,62,31,0,753,759,1,0,0,0,754,755,
  	3,114,57,0,755,756,3,172,86,0,756,757,3,62,31,0,757,759,1,0,0,0,758,750,
  	1,0,0,0,758,751,1,0,0,0,758,754,1,0,0,0,759,760,1,0,0,0,760,761,5,45,
  	0,0,761,767,3,108,54,0,762,765,5,31,0,0,763,766,3,140,70,0,764,766,3,
  	108,54,0,765,763,1,0,0,0,765,764,1,0,0,0,766,768,1,0,0,0,767,762,1,0,
  	0,0,767,768,1,0,0,0,768,141,1,0,0,0,769,772,3,144,72,0,770,772,3,150,
  	75,0,771,769,1,0,0,0,771,770,1,0,0,0,772,143,1,0,0,0,773,774,5,33,0,0,
  	774,785,5,44,0,0,775,777,3,62,31,0,776,775,1,0,0,0,776,777,1,0,0,0,777,
  	786,1,0,0,0,778,780,3,114,57,0,779,778,1,0,0,0,779,780,1,0,0,0,780,781,
  	1,0,0,0,781,783,3,172,86,0,782,784,3,62,31,0,783,782,1,0,0,0,783,784,
  	1,0,0,0,784,786,1,0,0,0,785,776,1,0,0,0,785,779,1,0,0,0,786,787,1,0,0,
  	0,787,788,5,45,0,0,788,792,5,48,0,0,789,791,3,146,73,0,790,789,1,0,0,
  	0,791,794,1,0,0,0,792,790,1,0,0,0,792,793,1,0,0,0,793,795,1,0,0,0,794,
  	792,1,0,0,0,795,796,5,49,0,0,796,145,1,0,0,0,797,798,3,148,74,0,798,800,
  	5,76,0,0,799,801,3,110,55,0,800,799,1,0,0,0,800,801,1,0,0,0,801,147,1,
  	0,0,0,802,803,5,34,0,0,803,806,3,72,36,0,804,806,5,35,0,0,805,802,1,0,
  	0,0,805,804,1,0,0,0,806,149,1,0,0,0,807,808,5,33,0,0,808,817,5,44,0,0,
  	809,818,3,152,76,0,810,811,3,172,86,0,811,812,3,152,76,0,812,818,1,0,
  	0,0,813,814,3,114,57,0,814,815,3,172,86,0,815,816,3,152,76,0,816,818,
  	1,0,0,0,817,809,1,0,0,0,817,810,1,0,0,0,817,813,1,0,0,0,818,819,1,0,0,
  	0,819,820,5,45,0,0,820,824,5,48,0,0,821,823,3,154,77,0,822,821,1,0,0,
  	0,823,826,1,0,0,0,824,822,1,0,0,0,824,825,1,0,0,0,825,827,1,0,0,0,826,
  	824,1,0,0,0,827,828,5,49,0,0,828,151,1,0,0,0,829,830,5,84,0,0,830,832,
  	5,61,0,0,831,829,1,0,0,0,831,832,1,0,0,0,832,833,1,0,0,0,833,834,3,64,
  	32,0,834,835,5,77,0,0,835,836,5,44,0,0,836,837,5,39,0,0,837,838,5,45,
  	0,0,838,153,1,0,0,0,839,840,3,156,78,0,840,842,5,76,0,0,841,843,3,110,
  	55,0,842,841,1,0,0,0,842,843,1,0,0,0,843,155,1,0,0,0,844,845,5,34,0,0,
  	845,848,3,158,79,0,846,848,5,35,0,0,847,844,1,0,0,0,847,846,1,0,0,0,848,
  	157,1,0,0,0,849,852,3,12,6,0,850,852,5,22,0,0,851,849,1,0,0,0,851,850,
  	1,0,0,0,852,860,1,0,0,0,853,856,5,74,0,0,854,857,3,12,6,0,855,857,5,22,
  	0,0,856,854,1,0,0,0,856,855,1,0,0,0,857,859,1,0,0,0,858,853,1,0,0,0,859,
  	862,1,0,0,0,860,858,1,0,0,0,860,861,1,0,0,0,861,159,1,0,0,0,862,860,1,
  	0,0,0,863,864,5,29,0,0,864,869,5,44,0,0,865,867,3,62,31,0,866,865,1,0,
  	0,0,866,867,1,0,0,0,867,870,1,0,0,0,868,870,3,166,83,0,869,866,1,0,0,
  	0,869,868,1,0,0,0,870,871,1,0,0,0,871,872,5,45,0,0,872,873,3,108,54,0,
  	873,161,1,0,0,0,874,875,5,30,0,0,875,880,5,44,0,0,876,878,3,62,31,0,877,
  	876,1,0,0,0,877,878,1,0,0,0,878,881,1,0,0,0,879,881,3,164,82,0,880,877,
  	1,0,0,0,880,879,1,0,0,0,881,882,1,0,0,0,882,883,5,45,0,0,883,884,3,108,
  	54,0,884,163,1,0,0,0,885,886,3,124,62,0,886,887,3,172,86,0,887,888,3,
  	70,35,0,888,889,3,172,86,0,889,890,3,70,35,0,890,165,1,0,0,0,891,893,
  	3,114,57,0,892,891,1,0,0,0,892,893,1,0,0,0,893,894,1,0,0,0,894,896,3,
  	172,86,0,895,897,3,62,31,0,896,895,1,0,0,0,896,897,1,0,0,0,897,898,1,
  	0,0,0,898,900,3,172,86,0,899,901,3,114,57,0,900,899,1,0,0,0,900,901,1,
  	0,0,0,901,167,1,0,0,0,902,903,5,28,0,0,903,904,5,44,0,0,904,905,3,62,
  	31,0,905,906,5,45,0,0,906,907,3,108,54,0,907,169,1,0,0,0,908,909,5,32,
  	0,0,909,910,3,108,54,0,910,911,5,28,0,0,911,912,5,44,0,0,912,913,3,62,
  	31,0,913,914,5,45,0,0,914,171,1,0,0,0,915,916,5,81,0,0,916,173,1,0,0,
  	0,106,178,184,200,207,209,213,223,227,231,242,251,258,271,275,284,305,
  	326,339,343,349,353,360,364,372,376,378,388,392,395,403,407,411,414,422,
  	426,441,443,446,449,451,460,463,471,488,490,497,506,510,517,526,534,541,
  	549,555,579,584,586,595,601,607,611,616,623,632,635,638,645,655,659,665,
  	669,674,681,698,704,716,729,733,737,741,758,765,767,771,776,779,783,785,
  	792,800,805,817,824,831,842,847,851,856,860,866,869,877,880,892,896,900
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  autotenv1parserParserStaticData = staticData.release();
}

}

AutoTenV1Parser::AutoTenV1Parser(TokenStream *input) : AutoTenV1Parser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

AutoTenV1Parser::AutoTenV1Parser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  AutoTenV1Parser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *autotenv1parserParserStaticData->atn, autotenv1parserParserStaticData->decisionToDFA, autotenv1parserParserStaticData->sharedContextCache, options);
}

AutoTenV1Parser::~AutoTenV1Parser() {
  delete _interpreter;
}

const atn::ATN& AutoTenV1Parser::getATN() const {
  return *autotenv1parserParserStaticData->atn;
}

std::string AutoTenV1Parser::getGrammarFileName() const {
  return "AutoTenV1Parser.g4";
}

const std::vector<std::string>& AutoTenV1Parser::getRuleNames() const {
  return autotenv1parserParserStaticData->ruleNames;
}

const dfa::Vocabulary& AutoTenV1Parser::getVocabulary() const {
  return autotenv1parserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView AutoTenV1Parser::getSerializedATN() const {
  return autotenv1parserParserStaticData->serializedATN;
}


//----------------- SourceFileContext ------------------------------------------------------------------

AutoTenV1Parser::SourceFileContext::SourceFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::PackageClauseContext* AutoTenV1Parser::SourceFileContext::packageClause() {
  return getRuleContext<AutoTenV1Parser::PackageClauseContext>(0);
}

std::vector<AutoTenV1Parser::EosContext *> AutoTenV1Parser::SourceFileContext::eos() {
  return getRuleContexts<AutoTenV1Parser::EosContext>();
}

AutoTenV1Parser::EosContext* AutoTenV1Parser::SourceFileContext::eos(size_t i) {
  return getRuleContext<AutoTenV1Parser::EosContext>(i);
}

tree::TerminalNode* AutoTenV1Parser::SourceFileContext::EOF() {
  return getToken(AutoTenV1Parser::EOF, 0);
}

std::vector<AutoTenV1Parser::FunctionDeclContext *> AutoTenV1Parser::SourceFileContext::functionDecl() {
  return getRuleContexts<AutoTenV1Parser::FunctionDeclContext>();
}

AutoTenV1Parser::FunctionDeclContext* AutoTenV1Parser::SourceFileContext::functionDecl(size_t i) {
  return getRuleContext<AutoTenV1Parser::FunctionDeclContext>(i);
}

std::vector<AutoTenV1Parser::DeclarationContext *> AutoTenV1Parser::SourceFileContext::declaration() {
  return getRuleContexts<AutoTenV1Parser::DeclarationContext>();
}

AutoTenV1Parser::DeclarationContext* AutoTenV1Parser::SourceFileContext::declaration(size_t i) {
  return getRuleContext<AutoTenV1Parser::DeclarationContext>(i);
}


size_t AutoTenV1Parser::SourceFileContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleSourceFile;
}

void AutoTenV1Parser::SourceFileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSourceFile(this);
}

void AutoTenV1Parser::SourceFileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSourceFile(this);
}


std::any AutoTenV1Parser::SourceFileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitSourceFile(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::SourceFileContext* AutoTenV1Parser::sourceFile() {
  SourceFileContext *_localctx = _tracker.createInstance<SourceFileContext>(_ctx, getState());
  enterRule(_localctx, 0, AutoTenV1Parser::RuleSourceFile);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(174);
    packageClause();
    setState(175);
    eos();
    setState(184);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 18) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 18)) & 4611686018446524417) != 0)) {
      setState(178);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case AutoTenV1Parser::Function:
        case AutoTenV1Parser::Public:
        case AutoTenV1Parser::At: {
          setState(176);
          functionDecl();
          break;
        }

        case AutoTenV1Parser::Var:
        case AutoTenV1Parser::Type: {
          setState(177);
          declaration();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(180);
      eos();
      setState(186);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(187);
    match(AutoTenV1Parser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PackageClauseContext ------------------------------------------------------------------

AutoTenV1Parser::PackageClauseContext::PackageClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::PackageClauseContext::At() {
  return getToken(AutoTenV1Parser::At, 0);
}

tree::TerminalNode* AutoTenV1Parser::PackageClauseContext::Package() {
  return getToken(AutoTenV1Parser::Package, 0);
}

tree::TerminalNode* AutoTenV1Parser::PackageClauseContext::Assign() {
  return getToken(AutoTenV1Parser::Assign, 0);
}

tree::TerminalNode* AutoTenV1Parser::PackageClauseContext::StringLiteral() {
  return getToken(AutoTenV1Parser::StringLiteral, 0);
}


size_t AutoTenV1Parser::PackageClauseContext::getRuleIndex() const {
  return AutoTenV1Parser::RulePackageClause;
}

void AutoTenV1Parser::PackageClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPackageClause(this);
}

void AutoTenV1Parser::PackageClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPackageClause(this);
}


std::any AutoTenV1Parser::PackageClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitPackageClause(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::PackageClauseContext* AutoTenV1Parser::packageClause() {
  PackageClauseContext *_localctx = _tracker.createInstance<PackageClauseContext>(_ctx, getState());
  enterRule(_localctx, 2, AutoTenV1Parser::RulePackageClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(189);
    match(AutoTenV1Parser::At);
    setState(190);
    match(AutoTenV1Parser::Package);
    setState(191);
    match(AutoTenV1Parser::Assign);
    setState(192);
    match(AutoTenV1Parser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompileFlagsContext ------------------------------------------------------------------

AutoTenV1Parser::CompileFlagsContext::CompileFlagsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::CompileFlagsContext::At() {
  return getToken(AutoTenV1Parser::At, 0);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::CompileFlagsContext::Identifier() {
  return getTokens(AutoTenV1Parser::Identifier);
}

tree::TerminalNode* AutoTenV1Parser::CompileFlagsContext::Identifier(size_t i) {
  return getToken(AutoTenV1Parser::Identifier, i);
}

tree::TerminalNode* AutoTenV1Parser::CompileFlagsContext::Assign() {
  return getToken(AutoTenV1Parser::Assign, 0);
}

tree::TerminalNode* AutoTenV1Parser::CompileFlagsContext::True_() {
  return getToken(AutoTenV1Parser::True_, 0);
}

tree::TerminalNode* AutoTenV1Parser::CompileFlagsContext::False_() {
  return getToken(AutoTenV1Parser::False_, 0);
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::CompileFlagsContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}


size_t AutoTenV1Parser::CompileFlagsContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleCompileFlags;
}

void AutoTenV1Parser::CompileFlagsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompileFlags(this);
}

void AutoTenV1Parser::CompileFlagsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompileFlags(this);
}


std::any AutoTenV1Parser::CompileFlagsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitCompileFlags(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::CompileFlagsContext* AutoTenV1Parser::compileFlags() {
  CompileFlagsContext *_localctx = _tracker.createInstance<CompileFlagsContext>(_ctx, getState());
  enterRule(_localctx, 4, AutoTenV1Parser::RuleCompileFlags);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(194);
    match(AutoTenV1Parser::At);
    setState(195);
    match(AutoTenV1Parser::Identifier);
    setState(200);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(196);
        matchWildcard();
        setState(197);
        match(AutoTenV1Parser::Identifier); 
      }
      setState(202);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
    setState(209);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Assign) {
      setState(203);
      match(AutoTenV1Parser::Assign);
      setState(207);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case AutoTenV1Parser::True_: {
          setState(204);
          match(AutoTenV1Parser::True_);
          break;
        }

        case AutoTenV1Parser::False_: {
          setState(205);
          match(AutoTenV1Parser::False_);
          break;
        }

        case AutoTenV1Parser::IntegerLiteral:
        case AutoTenV1Parser::CharacterLiteral:
        case AutoTenV1Parser::FloatingLiteral:
        case AutoTenV1Parser::StringLiteral:
        case AutoTenV1Parser::Int8:
        case AutoTenV1Parser::Int16:
        case AutoTenV1Parser::Int32:
        case AutoTenV1Parser::Int64:
        case AutoTenV1Parser::Float32:
        case AutoTenV1Parser::Float64:
        case AutoTenV1Parser::Char:
        case AutoTenV1Parser::Bool:
        case AutoTenV1Parser::String:
        case AutoTenV1Parser::Tensor:
        case AutoTenV1Parser::Void:
        case AutoTenV1Parser::Nilptr:
        case AutoTenV1Parser::Function:
        case AutoTenV1Parser::Struct:
        case AutoTenV1Parser::Impl:
        case AutoTenV1Parser::LeftParen:
        case AutoTenV1Parser::LeftBracket:
        case AutoTenV1Parser::Plus:
        case AutoTenV1Parser::Minus:
        case AutoTenV1Parser::Star:
        case AutoTenV1Parser::Caret:
        case AutoTenV1Parser::And:
        case AutoTenV1Parser::Not:
        case AutoTenV1Parser::At:
        case AutoTenV1Parser::Map:
        case AutoTenV1Parser::Identifier: {
          setState(206);
          expression(0);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

AutoTenV1Parser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::TypeDeclContext* AutoTenV1Parser::DeclarationContext::typeDecl() {
  return getRuleContext<AutoTenV1Parser::TypeDeclContext>(0);
}

AutoTenV1Parser::VarDeclContext* AutoTenV1Parser::DeclarationContext::varDecl() {
  return getRuleContext<AutoTenV1Parser::VarDeclContext>(0);
}


size_t AutoTenV1Parser::DeclarationContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleDeclaration;
}

void AutoTenV1Parser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void AutoTenV1Parser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}


std::any AutoTenV1Parser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::DeclarationContext* AutoTenV1Parser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 6, AutoTenV1Parser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(213);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Type: {
        enterOuterAlt(_localctx, 1);
        setState(211);
        typeDecl();
        break;
      }

      case AutoTenV1Parser::Var: {
        enterOuterAlt(_localctx, 2);
        setState(212);
        varDecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeDeclContext ------------------------------------------------------------------

AutoTenV1Parser::TypeDeclContext::TypeDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::TypeDeclContext::Type() {
  return getToken(AutoTenV1Parser::Type, 0);
}

std::vector<AutoTenV1Parser::TypeSpecContext *> AutoTenV1Parser::TypeDeclContext::typeSpec() {
  return getRuleContexts<AutoTenV1Parser::TypeSpecContext>();
}

AutoTenV1Parser::TypeSpecContext* AutoTenV1Parser::TypeDeclContext::typeSpec(size_t i) {
  return getRuleContext<AutoTenV1Parser::TypeSpecContext>(i);
}

tree::TerminalNode* AutoTenV1Parser::TypeDeclContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::TypeDeclContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}

std::vector<AutoTenV1Parser::EosContext *> AutoTenV1Parser::TypeDeclContext::eos() {
  return getRuleContexts<AutoTenV1Parser::EosContext>();
}

AutoTenV1Parser::EosContext* AutoTenV1Parser::TypeDeclContext::eos(size_t i) {
  return getRuleContext<AutoTenV1Parser::EosContext>(i);
}


size_t AutoTenV1Parser::TypeDeclContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleTypeDecl;
}

void AutoTenV1Parser::TypeDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeDecl(this);
}

void AutoTenV1Parser::TypeDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeDecl(this);
}


std::any AutoTenV1Parser::TypeDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitTypeDecl(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::TypeDeclContext* AutoTenV1Parser::typeDecl() {
  TypeDeclContext *_localctx = _tracker.createInstance<TypeDeclContext>(_ctx, getState());
  enterRule(_localctx, 8, AutoTenV1Parser::RuleTypeDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(215);
    match(AutoTenV1Parser::Type);
    setState(227);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Identifier: {
        setState(216);
        typeSpec();
        break;
      }

      case AutoTenV1Parser::LeftParen: {
        setState(217);
        match(AutoTenV1Parser::LeftParen);
        setState(223);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == AutoTenV1Parser::Identifier) {
          setState(218);
          typeSpec();
          setState(219);
          eos();
          setState(225);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(226);
        match(AutoTenV1Parser::RightParen);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeSpecContext ------------------------------------------------------------------

AutoTenV1Parser::TypeSpecContext::TypeSpecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::TypeSpecContext::Identifier() {
  return getToken(AutoTenV1Parser::Identifier, 0);
}

AutoTenV1Parser::Type_Context* AutoTenV1Parser::TypeSpecContext::type_() {
  return getRuleContext<AutoTenV1Parser::Type_Context>(0);
}

tree::TerminalNode* AutoTenV1Parser::TypeSpecContext::Assign() {
  return getToken(AutoTenV1Parser::Assign, 0);
}


size_t AutoTenV1Parser::TypeSpecContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleTypeSpec;
}

void AutoTenV1Parser::TypeSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeSpec(this);
}

void AutoTenV1Parser::TypeSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeSpec(this);
}


std::any AutoTenV1Parser::TypeSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitTypeSpec(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::TypeSpecContext* AutoTenV1Parser::typeSpec() {
  TypeSpecContext *_localctx = _tracker.createInstance<TypeSpecContext>(_ctx, getState());
  enterRule(_localctx, 10, AutoTenV1Parser::RuleTypeSpec);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(229);
    match(AutoTenV1Parser::Identifier);
    setState(231);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Assign) {
      setState(230);
      match(AutoTenV1Parser::Assign);
    }
    setState(233);
    type_();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Type_Context ------------------------------------------------------------------

AutoTenV1Parser::Type_Context::Type_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::TypeNameContext* AutoTenV1Parser::Type_Context::typeName() {
  return getRuleContext<AutoTenV1Parser::TypeNameContext>(0);
}

AutoTenV1Parser::TypeLitContext* AutoTenV1Parser::Type_Context::typeLit() {
  return getRuleContext<AutoTenV1Parser::TypeLitContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::Type_Context::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

AutoTenV1Parser::Type_Context* AutoTenV1Parser::Type_Context::type_() {
  return getRuleContext<AutoTenV1Parser::Type_Context>(0);
}

tree::TerminalNode* AutoTenV1Parser::Type_Context::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}

AutoTenV1Parser::BuiltinTypeContext* AutoTenV1Parser::Type_Context::builtinType() {
  return getRuleContext<AutoTenV1Parser::BuiltinTypeContext>(0);
}


size_t AutoTenV1Parser::Type_Context::getRuleIndex() const {
  return AutoTenV1Parser::RuleType_;
}

void AutoTenV1Parser::Type_Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType_(this);
}

void AutoTenV1Parser::Type_Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType_(this);
}


std::any AutoTenV1Parser::Type_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitType_(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::Type_Context* AutoTenV1Parser::type_() {
  Type_Context *_localctx = _tracker.createInstance<Type_Context>(_ctx, getState());
  enterRule(_localctx, 12, AutoTenV1Parser::RuleType_);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(242);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(235);
        typeName();
        break;
      }

      case AutoTenV1Parser::Function:
      case AutoTenV1Parser::Struct:
      case AutoTenV1Parser::Impl:
      case AutoTenV1Parser::LeftBracket:
      case AutoTenV1Parser::Star:
      case AutoTenV1Parser::Map: {
        enterOuterAlt(_localctx, 2);
        setState(236);
        typeLit();
        break;
      }

      case AutoTenV1Parser::LeftParen: {
        enterOuterAlt(_localctx, 3);
        setState(237);
        match(AutoTenV1Parser::LeftParen);
        setState(238);
        type_();
        setState(239);
        match(AutoTenV1Parser::RightParen);
        break;
      }

      case AutoTenV1Parser::Int8:
      case AutoTenV1Parser::Int16:
      case AutoTenV1Parser::Int32:
      case AutoTenV1Parser::Int64:
      case AutoTenV1Parser::Float32:
      case AutoTenV1Parser::Float64:
      case AutoTenV1Parser::Char:
      case AutoTenV1Parser::Bool:
      case AutoTenV1Parser::String:
      case AutoTenV1Parser::Tensor:
      case AutoTenV1Parser::Void: {
        enterOuterAlt(_localctx, 4);
        setState(241);
        builtinType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TensorTypeContext ------------------------------------------------------------------

AutoTenV1Parser::TensorTypeContext::TensorTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::TensorTypeContext::Tensor() {
  return getToken(AutoTenV1Parser::Tensor, 0);
}

tree::TerminalNode* AutoTenV1Parser::TensorTypeContext::Less() {
  return getToken(AutoTenV1Parser::Less, 0);
}

std::vector<AutoTenV1Parser::ExpressionContext *> AutoTenV1Parser::TensorTypeContext::expression() {
  return getRuleContexts<AutoTenV1Parser::ExpressionContext>();
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::TensorTypeContext::expression(size_t i) {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::TensorTypeContext::Comma() {
  return getTokens(AutoTenV1Parser::Comma);
}

tree::TerminalNode* AutoTenV1Parser::TensorTypeContext::Comma(size_t i) {
  return getToken(AutoTenV1Parser::Comma, i);
}

tree::TerminalNode* AutoTenV1Parser::TensorTypeContext::Greater() {
  return getToken(AutoTenV1Parser::Greater, 0);
}

tree::TerminalNode* AutoTenV1Parser::TensorTypeContext::Float32() {
  return getToken(AutoTenV1Parser::Float32, 0);
}

tree::TerminalNode* AutoTenV1Parser::TensorTypeContext::Float64() {
  return getToken(AutoTenV1Parser::Float64, 0);
}

tree::TerminalNode* AutoTenV1Parser::TensorTypeContext::Int32() {
  return getToken(AutoTenV1Parser::Int32, 0);
}

tree::TerminalNode* AutoTenV1Parser::TensorTypeContext::Int64() {
  return getToken(AutoTenV1Parser::Int64, 0);
}


size_t AutoTenV1Parser::TensorTypeContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleTensorType;
}

void AutoTenV1Parser::TensorTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTensorType(this);
}

void AutoTenV1Parser::TensorTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTensorType(this);
}


std::any AutoTenV1Parser::TensorTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitTensorType(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::TensorTypeContext* AutoTenV1Parser::tensorType() {
  TensorTypeContext *_localctx = _tracker.createInstance<TensorTypeContext>(_ctx, getState());
  enterRule(_localctx, 14, AutoTenV1Parser::RuleTensorType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(244);
    match(AutoTenV1Parser::Tensor);
    setState(258);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Less) {
      setState(245);
      match(AutoTenV1Parser::Less);
      setState(246);
      expression(0);
      setState(251);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(247);
          match(AutoTenV1Parser::Comma);
          setState(248);
          expression(0); 
        }
        setState(253);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
      }
      setState(254);
      match(AutoTenV1Parser::Comma);
      setState(255);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 15360) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(256);
      match(AutoTenV1Parser::Greater);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BuiltinTypeContext ------------------------------------------------------------------

AutoTenV1Parser::BuiltinTypeContext::BuiltinTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::BuiltinTypeContext::Int8() {
  return getToken(AutoTenV1Parser::Int8, 0);
}

tree::TerminalNode* AutoTenV1Parser::BuiltinTypeContext::Int16() {
  return getToken(AutoTenV1Parser::Int16, 0);
}

tree::TerminalNode* AutoTenV1Parser::BuiltinTypeContext::Int32() {
  return getToken(AutoTenV1Parser::Int32, 0);
}

tree::TerminalNode* AutoTenV1Parser::BuiltinTypeContext::Int64() {
  return getToken(AutoTenV1Parser::Int64, 0);
}

tree::TerminalNode* AutoTenV1Parser::BuiltinTypeContext::Float32() {
  return getToken(AutoTenV1Parser::Float32, 0);
}

tree::TerminalNode* AutoTenV1Parser::BuiltinTypeContext::Float64() {
  return getToken(AutoTenV1Parser::Float64, 0);
}

tree::TerminalNode* AutoTenV1Parser::BuiltinTypeContext::Bool() {
  return getToken(AutoTenV1Parser::Bool, 0);
}

tree::TerminalNode* AutoTenV1Parser::BuiltinTypeContext::String() {
  return getToken(AutoTenV1Parser::String, 0);
}

tree::TerminalNode* AutoTenV1Parser::BuiltinTypeContext::Char() {
  return getToken(AutoTenV1Parser::Char, 0);
}

AutoTenV1Parser::TensorTypeContext* AutoTenV1Parser::BuiltinTypeContext::tensorType() {
  return getRuleContext<AutoTenV1Parser::TensorTypeContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::BuiltinTypeContext::Void() {
  return getToken(AutoTenV1Parser::Void, 0);
}


size_t AutoTenV1Parser::BuiltinTypeContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleBuiltinType;
}

void AutoTenV1Parser::BuiltinTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBuiltinType(this);
}

void AutoTenV1Parser::BuiltinTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBuiltinType(this);
}


std::any AutoTenV1Parser::BuiltinTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitBuiltinType(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::BuiltinTypeContext* AutoTenV1Parser::builtinType() {
  BuiltinTypeContext *_localctx = _tracker.createInstance<BuiltinTypeContext>(_ctx, getState());
  enterRule(_localctx, 16, AutoTenV1Parser::RuleBuiltinType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(271);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Int8: {
        enterOuterAlt(_localctx, 1);
        setState(260);
        match(AutoTenV1Parser::Int8);
        break;
      }

      case AutoTenV1Parser::Int16: {
        enterOuterAlt(_localctx, 2);
        setState(261);
        match(AutoTenV1Parser::Int16);
        break;
      }

      case AutoTenV1Parser::Int32: {
        enterOuterAlt(_localctx, 3);
        setState(262);
        match(AutoTenV1Parser::Int32);
        break;
      }

      case AutoTenV1Parser::Int64: {
        enterOuterAlt(_localctx, 4);
        setState(263);
        match(AutoTenV1Parser::Int64);
        break;
      }

      case AutoTenV1Parser::Float32: {
        enterOuterAlt(_localctx, 5);
        setState(264);
        match(AutoTenV1Parser::Float32);
        break;
      }

      case AutoTenV1Parser::Float64: {
        enterOuterAlt(_localctx, 6);
        setState(265);
        match(AutoTenV1Parser::Float64);
        break;
      }

      case AutoTenV1Parser::Bool: {
        enterOuterAlt(_localctx, 7);
        setState(266);
        match(AutoTenV1Parser::Bool);
        break;
      }

      case AutoTenV1Parser::String: {
        enterOuterAlt(_localctx, 8);
        setState(267);
        match(AutoTenV1Parser::String);
        break;
      }

      case AutoTenV1Parser::Char: {
        enterOuterAlt(_localctx, 9);
        setState(268);
        match(AutoTenV1Parser::Char);
        break;
      }

      case AutoTenV1Parser::Tensor: {
        enterOuterAlt(_localctx, 10);
        setState(269);
        tensorType();
        break;
      }

      case AutoTenV1Parser::Void: {
        enterOuterAlt(_localctx, 11);
        setState(270);
        match(AutoTenV1Parser::Void);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeNameContext ------------------------------------------------------------------

AutoTenV1Parser::TypeNameContext::TypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::QualifiedIdentContext* AutoTenV1Parser::TypeNameContext::qualifiedIdent() {
  return getRuleContext<AutoTenV1Parser::QualifiedIdentContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::TypeNameContext::Identifier() {
  return getToken(AutoTenV1Parser::Identifier, 0);
}


size_t AutoTenV1Parser::TypeNameContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleTypeName;
}

void AutoTenV1Parser::TypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeName(this);
}

void AutoTenV1Parser::TypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeName(this);
}


std::any AutoTenV1Parser::TypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitTypeName(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::TypeNameContext* AutoTenV1Parser::typeName() {
  TypeNameContext *_localctx = _tracker.createInstance<TypeNameContext>(_ctx, getState());
  enterRule(_localctx, 18, AutoTenV1Parser::RuleTypeName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(275);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(273);
      qualifiedIdent();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(274);
      match(AutoTenV1Parser::Identifier);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeLitContext ------------------------------------------------------------------

AutoTenV1Parser::TypeLitContext::TypeLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::ArrayTypeContext* AutoTenV1Parser::TypeLitContext::arrayType() {
  return getRuleContext<AutoTenV1Parser::ArrayTypeContext>(0);
}

AutoTenV1Parser::StructTypeContext* AutoTenV1Parser::TypeLitContext::structType() {
  return getRuleContext<AutoTenV1Parser::StructTypeContext>(0);
}

AutoTenV1Parser::PointerTypeContext* AutoTenV1Parser::TypeLitContext::pointerType() {
  return getRuleContext<AutoTenV1Parser::PointerTypeContext>(0);
}

AutoTenV1Parser::FunctionTypeContext* AutoTenV1Parser::TypeLitContext::functionType() {
  return getRuleContext<AutoTenV1Parser::FunctionTypeContext>(0);
}

AutoTenV1Parser::ImplTypeContext* AutoTenV1Parser::TypeLitContext::implType() {
  return getRuleContext<AutoTenV1Parser::ImplTypeContext>(0);
}

AutoTenV1Parser::SliceTypeContext* AutoTenV1Parser::TypeLitContext::sliceType() {
  return getRuleContext<AutoTenV1Parser::SliceTypeContext>(0);
}

AutoTenV1Parser::MapTypeContext* AutoTenV1Parser::TypeLitContext::mapType() {
  return getRuleContext<AutoTenV1Parser::MapTypeContext>(0);
}


size_t AutoTenV1Parser::TypeLitContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleTypeLit;
}

void AutoTenV1Parser::TypeLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeLit(this);
}

void AutoTenV1Parser::TypeLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeLit(this);
}


std::any AutoTenV1Parser::TypeLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitTypeLit(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::TypeLitContext* AutoTenV1Parser::typeLit() {
  TypeLitContext *_localctx = _tracker.createInstance<TypeLitContext>(_ctx, getState());
  enterRule(_localctx, 20, AutoTenV1Parser::RuleTypeLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(284);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(277);
      arrayType();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(278);
      structType();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(279);
      pointerType();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(280);
      functionType();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(281);
      implType();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(282);
      sliceType();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(283);
      mapType();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayTypeContext ------------------------------------------------------------------

AutoTenV1Parser::ArrayTypeContext::ArrayTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::ArrayTypeContext::LeftBracket() {
  return getToken(AutoTenV1Parser::LeftBracket, 0);
}

AutoTenV1Parser::ArrayLengthContext* AutoTenV1Parser::ArrayTypeContext::arrayLength() {
  return getRuleContext<AutoTenV1Parser::ArrayLengthContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::ArrayTypeContext::RightBracket() {
  return getToken(AutoTenV1Parser::RightBracket, 0);
}

AutoTenV1Parser::ElementTypeContext* AutoTenV1Parser::ArrayTypeContext::elementType() {
  return getRuleContext<AutoTenV1Parser::ElementTypeContext>(0);
}


size_t AutoTenV1Parser::ArrayTypeContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleArrayType;
}

void AutoTenV1Parser::ArrayTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayType(this);
}

void AutoTenV1Parser::ArrayTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayType(this);
}


std::any AutoTenV1Parser::ArrayTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitArrayType(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ArrayTypeContext* AutoTenV1Parser::arrayType() {
  ArrayTypeContext *_localctx = _tracker.createInstance<ArrayTypeContext>(_ctx, getState());
  enterRule(_localctx, 22, AutoTenV1Parser::RuleArrayType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(286);
    match(AutoTenV1Parser::LeftBracket);
    setState(287);
    arrayLength();
    setState(288);
    match(AutoTenV1Parser::RightBracket);
    setState(289);
    elementType();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayLengthContext ------------------------------------------------------------------

AutoTenV1Parser::ArrayLengthContext::ArrayLengthContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::ArrayLengthContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}


size_t AutoTenV1Parser::ArrayLengthContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleArrayLength;
}

void AutoTenV1Parser::ArrayLengthContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayLength(this);
}

void AutoTenV1Parser::ArrayLengthContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayLength(this);
}


std::any AutoTenV1Parser::ArrayLengthContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitArrayLength(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ArrayLengthContext* AutoTenV1Parser::arrayLength() {
  ArrayLengthContext *_localctx = _tracker.createInstance<ArrayLengthContext>(_ctx, getState());
  enterRule(_localctx, 24, AutoTenV1Parser::RuleArrayLength);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(291);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementTypeContext ------------------------------------------------------------------

AutoTenV1Parser::ElementTypeContext::ElementTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::Type_Context* AutoTenV1Parser::ElementTypeContext::type_() {
  return getRuleContext<AutoTenV1Parser::Type_Context>(0);
}


size_t AutoTenV1Parser::ElementTypeContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleElementType;
}

void AutoTenV1Parser::ElementTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementType(this);
}

void AutoTenV1Parser::ElementTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementType(this);
}


std::any AutoTenV1Parser::ElementTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitElementType(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ElementTypeContext* AutoTenV1Parser::elementType() {
  ElementTypeContext *_localctx = _tracker.createInstance<ElementTypeContext>(_ctx, getState());
  enterRule(_localctx, 26, AutoTenV1Parser::RuleElementType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(293);
    type_();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PointerTypeContext ------------------------------------------------------------------

AutoTenV1Parser::PointerTypeContext::PointerTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::PointerTypeContext::Star() {
  return getToken(AutoTenV1Parser::Star, 0);
}

AutoTenV1Parser::Type_Context* AutoTenV1Parser::PointerTypeContext::type_() {
  return getRuleContext<AutoTenV1Parser::Type_Context>(0);
}


size_t AutoTenV1Parser::PointerTypeContext::getRuleIndex() const {
  return AutoTenV1Parser::RulePointerType;
}

void AutoTenV1Parser::PointerTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPointerType(this);
}

void AutoTenV1Parser::PointerTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPointerType(this);
}


std::any AutoTenV1Parser::PointerTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitPointerType(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::PointerTypeContext* AutoTenV1Parser::pointerType() {
  PointerTypeContext *_localctx = _tracker.createInstance<PointerTypeContext>(_ctx, getState());
  enterRule(_localctx, 28, AutoTenV1Parser::RulePointerType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(295);
    match(AutoTenV1Parser::Star);
    setState(296);
    type_();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImplTypeContext ------------------------------------------------------------------

AutoTenV1Parser::ImplTypeContext::ImplTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::ImplTypeContext::Impl() {
  return getToken(AutoTenV1Parser::Impl, 0);
}

tree::TerminalNode* AutoTenV1Parser::ImplTypeContext::LeftBrace() {
  return getToken(AutoTenV1Parser::LeftBrace, 0);
}

tree::TerminalNode* AutoTenV1Parser::ImplTypeContext::RightBrace() {
  return getToken(AutoTenV1Parser::RightBrace, 0);
}

std::vector<AutoTenV1Parser::FunctionDeclContext *> AutoTenV1Parser::ImplTypeContext::functionDecl() {
  return getRuleContexts<AutoTenV1Parser::FunctionDeclContext>();
}

AutoTenV1Parser::FunctionDeclContext* AutoTenV1Parser::ImplTypeContext::functionDecl(size_t i) {
  return getRuleContext<AutoTenV1Parser::FunctionDeclContext>(i);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::ImplTypeContext::Semi() {
  return getTokens(AutoTenV1Parser::Semi);
}

tree::TerminalNode* AutoTenV1Parser::ImplTypeContext::Semi(size_t i) {
  return getToken(AutoTenV1Parser::Semi, i);
}


size_t AutoTenV1Parser::ImplTypeContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleImplType;
}

void AutoTenV1Parser::ImplTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImplType(this);
}

void AutoTenV1Parser::ImplTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImplType(this);
}


std::any AutoTenV1Parser::ImplTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitImplType(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ImplTypeContext* AutoTenV1Parser::implType() {
  ImplTypeContext *_localctx = _tracker.createInstance<ImplTypeContext>(_ctx, getState());
  enterRule(_localctx, 30, AutoTenV1Parser::RuleImplType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(298);
    match(AutoTenV1Parser::Impl);
    setState(299);
    match(AutoTenV1Parser::LeftBrace);
    setState(305);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 36) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 36)) & 17592186044481) != 0)) {
      setState(300);
      functionDecl();
      setState(301);
      match(AutoTenV1Parser::Semi);
      setState(307);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(308);
    match(AutoTenV1Parser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SliceTypeContext ------------------------------------------------------------------

AutoTenV1Parser::SliceTypeContext::SliceTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::SliceTypeContext::LeftBracket() {
  return getToken(AutoTenV1Parser::LeftBracket, 0);
}

tree::TerminalNode* AutoTenV1Parser::SliceTypeContext::RightBracket() {
  return getToken(AutoTenV1Parser::RightBracket, 0);
}

AutoTenV1Parser::ElementTypeContext* AutoTenV1Parser::SliceTypeContext::elementType() {
  return getRuleContext<AutoTenV1Parser::ElementTypeContext>(0);
}


size_t AutoTenV1Parser::SliceTypeContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleSliceType;
}

void AutoTenV1Parser::SliceTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSliceType(this);
}

void AutoTenV1Parser::SliceTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSliceType(this);
}


std::any AutoTenV1Parser::SliceTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitSliceType(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::SliceTypeContext* AutoTenV1Parser::sliceType() {
  SliceTypeContext *_localctx = _tracker.createInstance<SliceTypeContext>(_ctx, getState());
  enterRule(_localctx, 32, AutoTenV1Parser::RuleSliceType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(310);
    match(AutoTenV1Parser::LeftBracket);
    setState(311);
    match(AutoTenV1Parser::RightBracket);
    setState(312);
    elementType();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MapTypeContext ------------------------------------------------------------------

AutoTenV1Parser::MapTypeContext::MapTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::MapTypeContext::Map() {
  return getToken(AutoTenV1Parser::Map, 0);
}

tree::TerminalNode* AutoTenV1Parser::MapTypeContext::LeftBracket() {
  return getToken(AutoTenV1Parser::LeftBracket, 0);
}

AutoTenV1Parser::Type_Context* AutoTenV1Parser::MapTypeContext::type_() {
  return getRuleContext<AutoTenV1Parser::Type_Context>(0);
}

tree::TerminalNode* AutoTenV1Parser::MapTypeContext::RightBracket() {
  return getToken(AutoTenV1Parser::RightBracket, 0);
}

AutoTenV1Parser::ElementTypeContext* AutoTenV1Parser::MapTypeContext::elementType() {
  return getRuleContext<AutoTenV1Parser::ElementTypeContext>(0);
}


size_t AutoTenV1Parser::MapTypeContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleMapType;
}

void AutoTenV1Parser::MapTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMapType(this);
}

void AutoTenV1Parser::MapTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMapType(this);
}


std::any AutoTenV1Parser::MapTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitMapType(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::MapTypeContext* AutoTenV1Parser::mapType() {
  MapTypeContext *_localctx = _tracker.createInstance<MapTypeContext>(_ctx, getState());
  enterRule(_localctx, 34, AutoTenV1Parser::RuleMapType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(314);
    match(AutoTenV1Parser::Map);
    setState(315);
    match(AutoTenV1Parser::LeftBracket);
    setState(316);
    type_();
    setState(317);
    match(AutoTenV1Parser::RightBracket);
    setState(318);
    elementType();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MethodSpecContext ------------------------------------------------------------------

AutoTenV1Parser::MethodSpecContext::MethodSpecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::MethodSpecContext::Identifier() {
  return getToken(AutoTenV1Parser::Identifier, 0);
}

AutoTenV1Parser::ParametersContext* AutoTenV1Parser::MethodSpecContext::parameters() {
  return getRuleContext<AutoTenV1Parser::ParametersContext>(0);
}

AutoTenV1Parser::ResultContext* AutoTenV1Parser::MethodSpecContext::result() {
  return getRuleContext<AutoTenV1Parser::ResultContext>(0);
}


size_t AutoTenV1Parser::MethodSpecContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleMethodSpec;
}

void AutoTenV1Parser::MethodSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMethodSpec(this);
}

void AutoTenV1Parser::MethodSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMethodSpec(this);
}


std::any AutoTenV1Parser::MethodSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitMethodSpec(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::MethodSpecContext* AutoTenV1Parser::methodSpec() {
  MethodSpecContext *_localctx = _tracker.createInstance<MethodSpecContext>(_ctx, getState());
  enterRule(_localctx, 36, AutoTenV1Parser::RuleMethodSpec);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(326);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(320);
      match(AutoTenV1Parser::Identifier);
      setState(321);
      parameters();
      setState(322);
      result();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(324);
      match(AutoTenV1Parser::Identifier);
      setState(325);
      parameters();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionTypeContext ------------------------------------------------------------------

AutoTenV1Parser::FunctionTypeContext::FunctionTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::FunctionTypeContext::Function() {
  return getToken(AutoTenV1Parser::Function, 0);
}

AutoTenV1Parser::SignatureContext* AutoTenV1Parser::FunctionTypeContext::signature() {
  return getRuleContext<AutoTenV1Parser::SignatureContext>(0);
}


size_t AutoTenV1Parser::FunctionTypeContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleFunctionType;
}

void AutoTenV1Parser::FunctionTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionType(this);
}

void AutoTenV1Parser::FunctionTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionType(this);
}


std::any AutoTenV1Parser::FunctionTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitFunctionType(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::FunctionTypeContext* AutoTenV1Parser::functionType() {
  FunctionTypeContext *_localctx = _tracker.createInstance<FunctionTypeContext>(_ctx, getState());
  enterRule(_localctx, 38, AutoTenV1Parser::RuleFunctionType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(328);
    match(AutoTenV1Parser::Function);
    setState(329);
    signature();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

AutoTenV1Parser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::VarDeclContext::Var() {
  return getToken(AutoTenV1Parser::Var, 0);
}

std::vector<AutoTenV1Parser::VarSpecContext *> AutoTenV1Parser::VarDeclContext::varSpec() {
  return getRuleContexts<AutoTenV1Parser::VarSpecContext>();
}

AutoTenV1Parser::VarSpecContext* AutoTenV1Parser::VarDeclContext::varSpec(size_t i) {
  return getRuleContext<AutoTenV1Parser::VarSpecContext>(i);
}

tree::TerminalNode* AutoTenV1Parser::VarDeclContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::VarDeclContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}

std::vector<AutoTenV1Parser::EosContext *> AutoTenV1Parser::VarDeclContext::eos() {
  return getRuleContexts<AutoTenV1Parser::EosContext>();
}

AutoTenV1Parser::EosContext* AutoTenV1Parser::VarDeclContext::eos(size_t i) {
  return getRuleContext<AutoTenV1Parser::EosContext>(i);
}


size_t AutoTenV1Parser::VarDeclContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleVarDecl;
}

void AutoTenV1Parser::VarDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDecl(this);
}

void AutoTenV1Parser::VarDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDecl(this);
}


std::any AutoTenV1Parser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::VarDeclContext* AutoTenV1Parser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 40, AutoTenV1Parser::RuleVarDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(331);
    match(AutoTenV1Parser::Var);
    setState(343);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Identifier: {
        setState(332);
        varSpec();
        break;
      }

      case AutoTenV1Parser::LeftParen: {
        setState(333);
        match(AutoTenV1Parser::LeftParen);
        setState(339);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == AutoTenV1Parser::Identifier) {
          setState(334);
          varSpec();
          setState(335);
          eos();
          setState(341);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(342);
        match(AutoTenV1Parser::RightParen);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarSpecContext ------------------------------------------------------------------

AutoTenV1Parser::VarSpecContext::VarSpecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::IdentifierListContext* AutoTenV1Parser::VarSpecContext::identifierList() {
  return getRuleContext<AutoTenV1Parser::IdentifierListContext>(0);
}

AutoTenV1Parser::Type_Context* AutoTenV1Parser::VarSpecContext::type_() {
  return getRuleContext<AutoTenV1Parser::Type_Context>(0);
}

tree::TerminalNode* AutoTenV1Parser::VarSpecContext::Assign() {
  return getToken(AutoTenV1Parser::Assign, 0);
}

AutoTenV1Parser::ExpressionListContext* AutoTenV1Parser::VarSpecContext::expressionList() {
  return getRuleContext<AutoTenV1Parser::ExpressionListContext>(0);
}


size_t AutoTenV1Parser::VarSpecContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleVarSpec;
}

void AutoTenV1Parser::VarSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarSpec(this);
}

void AutoTenV1Parser::VarSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarSpec(this);
}


std::any AutoTenV1Parser::VarSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitVarSpec(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::VarSpecContext* AutoTenV1Parser::varSpec() {
  VarSpecContext *_localctx = _tracker.createInstance<VarSpecContext>(_ctx, getState());
  enterRule(_localctx, 42, AutoTenV1Parser::RuleVarSpec);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(345);
    identifierList();
    setState(353);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Int8:
      case AutoTenV1Parser::Int16:
      case AutoTenV1Parser::Int32:
      case AutoTenV1Parser::Int64:
      case AutoTenV1Parser::Float32:
      case AutoTenV1Parser::Float64:
      case AutoTenV1Parser::Char:
      case AutoTenV1Parser::Bool:
      case AutoTenV1Parser::String:
      case AutoTenV1Parser::Tensor:
      case AutoTenV1Parser::Void:
      case AutoTenV1Parser::Function:
      case AutoTenV1Parser::Struct:
      case AutoTenV1Parser::Impl:
      case AutoTenV1Parser::LeftParen:
      case AutoTenV1Parser::LeftBracket:
      case AutoTenV1Parser::Star:
      case AutoTenV1Parser::Map:
      case AutoTenV1Parser::Identifier: {
        setState(346);
        type_();
        setState(349);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == AutoTenV1Parser::Assign) {
          setState(347);
          match(AutoTenV1Parser::Assign);
          setState(348);
          expressionList();
        }
        break;
      }

      case AutoTenV1Parser::Assign: {
        setState(351);
        match(AutoTenV1Parser::Assign);
        setState(352);
        expressionList();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SignatureContext ------------------------------------------------------------------

AutoTenV1Parser::SignatureContext::SignatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::ParametersContext* AutoTenV1Parser::SignatureContext::parameters() {
  return getRuleContext<AutoTenV1Parser::ParametersContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::SignatureContext::ArrowReturnType() {
  return getToken(AutoTenV1Parser::ArrowReturnType, 0);
}

AutoTenV1Parser::ResultContext* AutoTenV1Parser::SignatureContext::result() {
  return getRuleContext<AutoTenV1Parser::ResultContext>(0);
}


size_t AutoTenV1Parser::SignatureContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleSignature;
}

void AutoTenV1Parser::SignatureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSignature(this);
}

void AutoTenV1Parser::SignatureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSignature(this);
}


std::any AutoTenV1Parser::SignatureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitSignature(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::SignatureContext* AutoTenV1Parser::signature() {
  SignatureContext *_localctx = _tracker.createInstance<SignatureContext>(_ctx, getState());
  enterRule(_localctx, 44, AutoTenV1Parser::RuleSignature);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(360);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(355);
      parameters();
      setState(356);
      match(AutoTenV1Parser::ArrowReturnType);
      setState(357);
      result();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(359);
      parameters();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ResultContext ------------------------------------------------------------------

AutoTenV1Parser::ResultContext::ResultContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::ParametersContext* AutoTenV1Parser::ResultContext::parameters() {
  return getRuleContext<AutoTenV1Parser::ParametersContext>(0);
}

AutoTenV1Parser::Type_Context* AutoTenV1Parser::ResultContext::type_() {
  return getRuleContext<AutoTenV1Parser::Type_Context>(0);
}


size_t AutoTenV1Parser::ResultContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleResult;
}

void AutoTenV1Parser::ResultContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterResult(this);
}

void AutoTenV1Parser::ResultContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitResult(this);
}


std::any AutoTenV1Parser::ResultContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitResult(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ResultContext* AutoTenV1Parser::result() {
  ResultContext *_localctx = _tracker.createInstance<ResultContext>(_ctx, getState());
  enterRule(_localctx, 46, AutoTenV1Parser::RuleResult);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(364);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(362);
      parameters();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(363);
      type_();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParametersContext ------------------------------------------------------------------

AutoTenV1Parser::ParametersContext::ParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::ParametersContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::ParametersContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}

std::vector<AutoTenV1Parser::ParameterDeclContext *> AutoTenV1Parser::ParametersContext::parameterDecl() {
  return getRuleContexts<AutoTenV1Parser::ParameterDeclContext>();
}

AutoTenV1Parser::ParameterDeclContext* AutoTenV1Parser::ParametersContext::parameterDecl(size_t i) {
  return getRuleContext<AutoTenV1Parser::ParameterDeclContext>(i);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::ParametersContext::Comma() {
  return getTokens(AutoTenV1Parser::Comma);
}

tree::TerminalNode* AutoTenV1Parser::ParametersContext::Comma(size_t i) {
  return getToken(AutoTenV1Parser::Comma, i);
}


size_t AutoTenV1Parser::ParametersContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleParameters;
}

void AutoTenV1Parser::ParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameters(this);
}

void AutoTenV1Parser::ParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameters(this);
}


std::any AutoTenV1Parser::ParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitParameters(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ParametersContext* AutoTenV1Parser::parameters() {
  ParametersContext *_localctx = _tracker.createInstance<ParametersContext>(_ctx, getState());
  enterRule(_localctx, 48, AutoTenV1Parser::RuleParameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(366);
    match(AutoTenV1Parser::LeftParen);
    setState(378);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4594103180590848) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & 7) != 0)) {
      setState(367);
      parameterDecl();
      setState(372);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(368);
          match(AutoTenV1Parser::Comma);
          setState(369);
          parameterDecl(); 
        }
        setState(374);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
      }
      setState(376);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Comma) {
        setState(375);
        match(AutoTenV1Parser::Comma);
      }
    }
    setState(380);
    match(AutoTenV1Parser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IndexContext ------------------------------------------------------------------

AutoTenV1Parser::IndexContext::IndexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::IndexContext::LeftBracket() {
  return getToken(AutoTenV1Parser::LeftBracket, 0);
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::IndexContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::IndexContext::RightBracket() {
  return getToken(AutoTenV1Parser::RightBracket, 0);
}


size_t AutoTenV1Parser::IndexContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleIndex;
}

void AutoTenV1Parser::IndexContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIndex(this);
}

void AutoTenV1Parser::IndexContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIndex(this);
}


std::any AutoTenV1Parser::IndexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitIndex(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::IndexContext* AutoTenV1Parser::index() {
  IndexContext *_localctx = _tracker.createInstance<IndexContext>(_ctx, getState());
  enterRule(_localctx, 50, AutoTenV1Parser::RuleIndex);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(382);
    match(AutoTenV1Parser::LeftBracket);
    setState(383);
    expression(0);
    setState(384);
    match(AutoTenV1Parser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Slice_Context ------------------------------------------------------------------

AutoTenV1Parser::Slice_Context::Slice_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::Slice_Context::LeftBracket() {
  return getToken(AutoTenV1Parser::LeftBracket, 0);
}

tree::TerminalNode* AutoTenV1Parser::Slice_Context::RightBracket() {
  return getToken(AutoTenV1Parser::RightBracket, 0);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::Slice_Context::Colon() {
  return getTokens(AutoTenV1Parser::Colon);
}

tree::TerminalNode* AutoTenV1Parser::Slice_Context::Colon(size_t i) {
  return getToken(AutoTenV1Parser::Colon, i);
}

std::vector<AutoTenV1Parser::ExpressionContext *> AutoTenV1Parser::Slice_Context::expression() {
  return getRuleContexts<AutoTenV1Parser::ExpressionContext>();
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::Slice_Context::expression(size_t i) {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::Slice_Context::Comma() {
  return getTokens(AutoTenV1Parser::Comma);
}

tree::TerminalNode* AutoTenV1Parser::Slice_Context::Comma(size_t i) {
  return getToken(AutoTenV1Parser::Comma, i);
}


size_t AutoTenV1Parser::Slice_Context::getRuleIndex() const {
  return AutoTenV1Parser::RuleSlice_;
}

void AutoTenV1Parser::Slice_Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSlice_(this);
}

void AutoTenV1Parser::Slice_Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSlice_(this);
}


std::any AutoTenV1Parser::Slice_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitSlice_(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::Slice_Context* AutoTenV1Parser::slice_() {
  Slice_Context *_localctx = _tracker.createInstance<Slice_Context>(_ctx, getState());
  enterRule(_localctx, 52, AutoTenV1Parser::RuleSlice_);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(386);
    match(AutoTenV1Parser::LeftBracket);
    setState(403);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      setState(388);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 80)) & 21) != 0)) {
        setState(387);
        expression(0);
      }
      setState(390);
      match(AutoTenV1Parser::Colon);
      setState(392);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 80)) & 21) != 0)) {
        setState(391);
        expression(0);
      }
      break;
    }

    case 2: {
      setState(395);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 80)) & 21) != 0)) {
        setState(394);
        expression(0);
      }
      setState(397);
      match(AutoTenV1Parser::Colon);
      setState(398);
      expression(0);
      setState(399);
      match(AutoTenV1Parser::Colon);
      setState(400);
      expression(0);
      break;
    }

    case 3: {
      setState(402);
      expression(0);
      break;
    }

    default:
      break;
    }
    setState(426);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Comma) {
      setState(405);
      match(AutoTenV1Parser::Comma);
      setState(422);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
      case 1: {
        setState(407);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 80)) & 21) != 0)) {
          setState(406);
          expression(0);
        }
        setState(409);
        match(AutoTenV1Parser::Colon);
        setState(411);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 80)) & 21) != 0)) {
          setState(410);
          expression(0);
        }
        break;
      }

      case 2: {
        setState(414);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 80)) & 21) != 0)) {
          setState(413);
          expression(0);
        }
        setState(416);
        match(AutoTenV1Parser::Colon);
        setState(417);
        expression(0);
        setState(418);
        match(AutoTenV1Parser::Colon);
        setState(419);
        expression(0);
        break;
      }

      case 3: {
        setState(421);
        expression(0);
        break;
      }

      default:
        break;
      }
      setState(428);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(429);
    match(AutoTenV1Parser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeAssertionContext ------------------------------------------------------------------

AutoTenV1Parser::TypeAssertionContext::TypeAssertionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::TypeAssertionContext::Dot() {
  return getToken(AutoTenV1Parser::Dot, 0);
}

tree::TerminalNode* AutoTenV1Parser::TypeAssertionContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

AutoTenV1Parser::Type_Context* AutoTenV1Parser::TypeAssertionContext::type_() {
  return getRuleContext<AutoTenV1Parser::Type_Context>(0);
}

tree::TerminalNode* AutoTenV1Parser::TypeAssertionContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}


size_t AutoTenV1Parser::TypeAssertionContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleTypeAssertion;
}

void AutoTenV1Parser::TypeAssertionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeAssertion(this);
}

void AutoTenV1Parser::TypeAssertionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeAssertion(this);
}


std::any AutoTenV1Parser::TypeAssertionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitTypeAssertion(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::TypeAssertionContext* AutoTenV1Parser::typeAssertion() {
  TypeAssertionContext *_localctx = _tracker.createInstance<TypeAssertionContext>(_ctx, getState());
  enterRule(_localctx, 54, AutoTenV1Parser::RuleTypeAssertion);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(431);
    match(AutoTenV1Parser::Dot);
    setState(432);
    match(AutoTenV1Parser::LeftParen);
    setState(433);
    type_();
    setState(434);
    match(AutoTenV1Parser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

AutoTenV1Parser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::ArgumentsContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::ArgumentsContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}

AutoTenV1Parser::ExpressionListContext* AutoTenV1Parser::ArgumentsContext::expressionList() {
  return getRuleContext<AutoTenV1Parser::ExpressionListContext>(0);
}

AutoTenV1Parser::NonNamedTypeContext* AutoTenV1Parser::ArgumentsContext::nonNamedType() {
  return getRuleContext<AutoTenV1Parser::NonNamedTypeContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::ArgumentsContext::Ellipsis() {
  return getToken(AutoTenV1Parser::Ellipsis, 0);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::ArgumentsContext::Comma() {
  return getTokens(AutoTenV1Parser::Comma);
}

tree::TerminalNode* AutoTenV1Parser::ArgumentsContext::Comma(size_t i) {
  return getToken(AutoTenV1Parser::Comma, i);
}


size_t AutoTenV1Parser::ArgumentsContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleArguments;
}

void AutoTenV1Parser::ArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArguments(this);
}

void AutoTenV1Parser::ArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArguments(this);
}


std::any AutoTenV1Parser::ArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ArgumentsContext* AutoTenV1Parser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 56, AutoTenV1Parser::RuleArguments);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(436);
    match(AutoTenV1Parser::LeftParen);
    setState(451);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 80)) & 21) != 0)) {
      setState(443);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
      case 1: {
        setState(437);
        expressionList();
        break;
      }

      case 2: {
        setState(438);
        nonNamedType();
        setState(441);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
        case 1: {
          setState(439);
          match(AutoTenV1Parser::Comma);
          setState(440);
          expressionList();
          break;
        }

        default:
          break;
        }
        break;
      }

      default:
        break;
      }
      setState(446);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Ellipsis) {
        setState(445);
        match(AutoTenV1Parser::Ellipsis);
      }
      setState(449);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Comma) {
        setState(448);
        match(AutoTenV1Parser::Comma);
      }
    }
    setState(453);
    match(AutoTenV1Parser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MethodExprContext ------------------------------------------------------------------

AutoTenV1Parser::MethodExprContext::MethodExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::NonNamedTypeContext* AutoTenV1Parser::MethodExprContext::nonNamedType() {
  return getRuleContext<AutoTenV1Parser::NonNamedTypeContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::MethodExprContext::Dot() {
  return getToken(AutoTenV1Parser::Dot, 0);
}

tree::TerminalNode* AutoTenV1Parser::MethodExprContext::Identifier() {
  return getToken(AutoTenV1Parser::Identifier, 0);
}


size_t AutoTenV1Parser::MethodExprContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleMethodExpr;
}

void AutoTenV1Parser::MethodExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMethodExpr(this);
}

void AutoTenV1Parser::MethodExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMethodExpr(this);
}


std::any AutoTenV1Parser::MethodExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitMethodExpr(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::MethodExprContext* AutoTenV1Parser::methodExpr() {
  MethodExprContext *_localctx = _tracker.createInstance<MethodExprContext>(_ctx, getState());
  enterRule(_localctx, 58, AutoTenV1Parser::RuleMethodExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(455);
    nonNamedType();
    setState(456);
    match(AutoTenV1Parser::Dot);
    setState(457);
    match(AutoTenV1Parser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterDeclContext ------------------------------------------------------------------

AutoTenV1Parser::ParameterDeclContext::ParameterDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::Type_Context* AutoTenV1Parser::ParameterDeclContext::type_() {
  return getRuleContext<AutoTenV1Parser::Type_Context>(0);
}

AutoTenV1Parser::IdentifierListContext* AutoTenV1Parser::ParameterDeclContext::identifierList() {
  return getRuleContext<AutoTenV1Parser::IdentifierListContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::ParameterDeclContext::Ellipsis() {
  return getToken(AutoTenV1Parser::Ellipsis, 0);
}


size_t AutoTenV1Parser::ParameterDeclContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleParameterDecl;
}

void AutoTenV1Parser::ParameterDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterDecl(this);
}

void AutoTenV1Parser::ParameterDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterDecl(this);
}


std::any AutoTenV1Parser::ParameterDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitParameterDecl(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ParameterDeclContext* AutoTenV1Parser::parameterDecl() {
  ParameterDeclContext *_localctx = _tracker.createInstance<ParameterDeclContext>(_ctx, getState());
  enterRule(_localctx, 60, AutoTenV1Parser::RuleParameterDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(460);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      setState(459);
      identifierList();
      break;
    }

    default:
      break;
    }
    setState(463);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Ellipsis) {
      setState(462);
      match(AutoTenV1Parser::Ellipsis);
    }
    setState(465);
    type_();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

AutoTenV1Parser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::PrimaryExprContext* AutoTenV1Parser::ExpressionContext::primaryExpr() {
  return getRuleContext<AutoTenV1Parser::PrimaryExprContext>(0);
}

std::vector<AutoTenV1Parser::ExpressionContext *> AutoTenV1Parser::ExpressionContext::expression() {
  return getRuleContexts<AutoTenV1Parser::ExpressionContext>();
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::ExpressionContext::expression(size_t i) {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(i);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::Plus() {
  return getToken(AutoTenV1Parser::Plus, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::Minus() {
  return getToken(AutoTenV1Parser::Minus, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::Not() {
  return getToken(AutoTenV1Parser::Not, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::Caret() {
  return getToken(AutoTenV1Parser::Caret, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::Star() {
  return getToken(AutoTenV1Parser::Star, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::And() {
  return getToken(AutoTenV1Parser::And, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::Div() {
  return getToken(AutoTenV1Parser::Div, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::Mod() {
  return getToken(AutoTenV1Parser::Mod, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::LeftShift() {
  return getToken(AutoTenV1Parser::LeftShift, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::RightShift() {
  return getToken(AutoTenV1Parser::RightShift, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::Or() {
  return getToken(AutoTenV1Parser::Or, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::Equal() {
  return getToken(AutoTenV1Parser::Equal, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::NotEqual() {
  return getToken(AutoTenV1Parser::NotEqual, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::Less() {
  return getToken(AutoTenV1Parser::Less, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::LessEqual() {
  return getToken(AutoTenV1Parser::LessEqual, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::Greater() {
  return getToken(AutoTenV1Parser::Greater, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::GreaterEqual() {
  return getToken(AutoTenV1Parser::GreaterEqual, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::AndAnd() {
  return getToken(AutoTenV1Parser::AndAnd, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionContext::OrOr() {
  return getToken(AutoTenV1Parser::OrOr, 0);
}


size_t AutoTenV1Parser::ExpressionContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleExpression;
}

void AutoTenV1Parser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void AutoTenV1Parser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


std::any AutoTenV1Parser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}


AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::expression() {
   return expression(0);
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  AutoTenV1Parser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  AutoTenV1Parser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 62;
  enterRecursionRule(_localctx, 62, AutoTenV1Parser::RuleExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(471);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      setState(468);
      primaryExpr(0);
      break;
    }

    case 2: {
      setState(469);
      antlrcpp::downCast<ExpressionContext *>(_localctx)->unary_op = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 692428442708213760) != 0))) {
        antlrcpp::downCast<ExpressionContext *>(_localctx)->unary_op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(470);
      expression(6);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(490);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(488);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(473);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(474);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->mul_op = _input->LT(1);
          _la = _input->LA(1);
          if (!(((((_la - 52) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 52)) & 12311) != 0))) {
            antlrcpp::downCast<ExpressionContext *>(_localctx)->mul_op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(475);
          expression(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(476);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(477);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->add_op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 183521684815347712) != 0))) {
            antlrcpp::downCast<ExpressionContext *>(_localctx)->add_op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(478);
          expression(5);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(479);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(480);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->rel_op = _input->LT(1);
          _la = _input->LA(1);
          if (!(((((_la - 62) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 62)) & 243) != 0))) {
            antlrcpp::downCast<ExpressionContext *>(_localctx)->rel_op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(481);
          expression(4);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(482);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(483);
          match(AutoTenV1Parser::AndAnd);
          setState(484);
          expression(3);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(485);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(486);
          match(AutoTenV1Parser::OrOr);
          setState(487);
          expression(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(492);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PrimaryExprContext ------------------------------------------------------------------

AutoTenV1Parser::PrimaryExprContext::PrimaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::OperandContext* AutoTenV1Parser::PrimaryExprContext::operand() {
  return getRuleContext<AutoTenV1Parser::OperandContext>(0);
}

AutoTenV1Parser::ConversionContext* AutoTenV1Parser::PrimaryExprContext::conversion() {
  return getRuleContext<AutoTenV1Parser::ConversionContext>(0);
}

AutoTenV1Parser::MethodExprContext* AutoTenV1Parser::PrimaryExprContext::methodExpr() {
  return getRuleContext<AutoTenV1Parser::MethodExprContext>(0);
}

AutoTenV1Parser::PrimaryExprContext* AutoTenV1Parser::PrimaryExprContext::primaryExpr() {
  return getRuleContext<AutoTenV1Parser::PrimaryExprContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::PrimaryExprContext::Dot() {
  return getToken(AutoTenV1Parser::Dot, 0);
}

tree::TerminalNode* AutoTenV1Parser::PrimaryExprContext::Identifier() {
  return getToken(AutoTenV1Parser::Identifier, 0);
}

AutoTenV1Parser::IndexContext* AutoTenV1Parser::PrimaryExprContext::index() {
  return getRuleContext<AutoTenV1Parser::IndexContext>(0);
}

AutoTenV1Parser::Slice_Context* AutoTenV1Parser::PrimaryExprContext::slice_() {
  return getRuleContext<AutoTenV1Parser::Slice_Context>(0);
}

AutoTenV1Parser::TypeAssertionContext* AutoTenV1Parser::PrimaryExprContext::typeAssertion() {
  return getRuleContext<AutoTenV1Parser::TypeAssertionContext>(0);
}

AutoTenV1Parser::ArgumentsContext* AutoTenV1Parser::PrimaryExprContext::arguments() {
  return getRuleContext<AutoTenV1Parser::ArgumentsContext>(0);
}


size_t AutoTenV1Parser::PrimaryExprContext::getRuleIndex() const {
  return AutoTenV1Parser::RulePrimaryExpr;
}

void AutoTenV1Parser::PrimaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpr(this);
}

void AutoTenV1Parser::PrimaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpr(this);
}


std::any AutoTenV1Parser::PrimaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpr(this);
  else
    return visitor->visitChildren(this);
}


AutoTenV1Parser::PrimaryExprContext* AutoTenV1Parser::primaryExpr() {
   return primaryExpr(0);
}

AutoTenV1Parser::PrimaryExprContext* AutoTenV1Parser::primaryExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  AutoTenV1Parser::PrimaryExprContext *_localctx = _tracker.createInstance<PrimaryExprContext>(_ctx, parentState);
  AutoTenV1Parser::PrimaryExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 64;
  enterRecursionRule(_localctx, 64, AutoTenV1Parser::RulePrimaryExpr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(497);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      setState(494);
      operand();
      break;
    }

    case 2: {
      setState(495);
      conversion();
      break;
    }

    case 3: {
      setState(496);
      methodExpr();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(510);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<PrimaryExprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RulePrimaryExpr);
        setState(499);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(506);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
        case 1: {
          setState(500);
          match(AutoTenV1Parser::Dot);
          setState(501);
          match(AutoTenV1Parser::Identifier);
          break;
        }

        case 2: {
          setState(502);
          index();
          break;
        }

        case 3: {
          setState(503);
          slice_();
          break;
        }

        case 4: {
          setState(504);
          typeAssertion();
          break;
        }

        case 5: {
          setState(505);
          arguments();
          break;
        }

        default:
          break;
        } 
      }
      setState(512);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ConversionContext ------------------------------------------------------------------

AutoTenV1Parser::ConversionContext::ConversionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::NonNamedTypeContext* AutoTenV1Parser::ConversionContext::nonNamedType() {
  return getRuleContext<AutoTenV1Parser::NonNamedTypeContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::ConversionContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::ConversionContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::ConversionContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::ConversionContext::Comma() {
  return getToken(AutoTenV1Parser::Comma, 0);
}


size_t AutoTenV1Parser::ConversionContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleConversion;
}

void AutoTenV1Parser::ConversionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConversion(this);
}

void AutoTenV1Parser::ConversionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConversion(this);
}


std::any AutoTenV1Parser::ConversionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitConversion(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ConversionContext* AutoTenV1Parser::conversion() {
  ConversionContext *_localctx = _tracker.createInstance<ConversionContext>(_ctx, getState());
  enterRule(_localctx, 66, AutoTenV1Parser::RuleConversion);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(513);
    nonNamedType();
    setState(514);
    match(AutoTenV1Parser::LeftParen);
    setState(515);
    expression(0);
    setState(517);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Comma) {
      setState(516);
      match(AutoTenV1Parser::Comma);
    }
    setState(519);
    match(AutoTenV1Parser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NonNamedTypeContext ------------------------------------------------------------------

AutoTenV1Parser::NonNamedTypeContext::NonNamedTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::TypeLitContext* AutoTenV1Parser::NonNamedTypeContext::typeLit() {
  return getRuleContext<AutoTenV1Parser::TypeLitContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::NonNamedTypeContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

AutoTenV1Parser::NonNamedTypeContext* AutoTenV1Parser::NonNamedTypeContext::nonNamedType() {
  return getRuleContext<AutoTenV1Parser::NonNamedTypeContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::NonNamedTypeContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}


size_t AutoTenV1Parser::NonNamedTypeContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleNonNamedType;
}

void AutoTenV1Parser::NonNamedTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNonNamedType(this);
}

void AutoTenV1Parser::NonNamedTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNonNamedType(this);
}


std::any AutoTenV1Parser::NonNamedTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitNonNamedType(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::NonNamedTypeContext* AutoTenV1Parser::nonNamedType() {
  NonNamedTypeContext *_localctx = _tracker.createInstance<NonNamedTypeContext>(_ctx, getState());
  enterRule(_localctx, 68, AutoTenV1Parser::RuleNonNamedType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(526);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Function:
      case AutoTenV1Parser::Struct:
      case AutoTenV1Parser::Impl:
      case AutoTenV1Parser::LeftBracket:
      case AutoTenV1Parser::Star:
      case AutoTenV1Parser::Map: {
        enterOuterAlt(_localctx, 1);
        setState(521);
        typeLit();
        break;
      }

      case AutoTenV1Parser::LeftParen: {
        enterOuterAlt(_localctx, 2);
        setState(522);
        match(AutoTenV1Parser::LeftParen);
        setState(523);
        nonNamedType();
        setState(524);
        match(AutoTenV1Parser::RightParen);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperandContext ------------------------------------------------------------------

AutoTenV1Parser::OperandContext::OperandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::LiteralContext* AutoTenV1Parser::OperandContext::literal() {
  return getRuleContext<AutoTenV1Parser::LiteralContext>(0);
}

AutoTenV1Parser::OperandNameContext* AutoTenV1Parser::OperandContext::operandName() {
  return getRuleContext<AutoTenV1Parser::OperandNameContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::OperandContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::OperandContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::OperandContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}


size_t AutoTenV1Parser::OperandContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleOperand;
}

void AutoTenV1Parser::OperandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperand(this);
}

void AutoTenV1Parser::OperandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperand(this);
}


std::any AutoTenV1Parser::OperandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitOperand(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::OperandContext* AutoTenV1Parser::operand() {
  OperandContext *_localctx = _tracker.createInstance<OperandContext>(_ctx, getState());
  enterRule(_localctx, 70, AutoTenV1Parser::RuleOperand);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(534);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(528);
      literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(529);
      operandName();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(530);
      match(AutoTenV1Parser::LeftParen);
      setState(531);
      expression(0);
      setState(532);
      match(AutoTenV1Parser::RightParen);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionListContext ------------------------------------------------------------------

AutoTenV1Parser::ExpressionListContext::ExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<AutoTenV1Parser::ExpressionContext *> AutoTenV1Parser::ExpressionListContext::expression() {
  return getRuleContexts<AutoTenV1Parser::ExpressionContext>();
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::ExpressionListContext::expression(size_t i) {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::ExpressionListContext::Comma() {
  return getTokens(AutoTenV1Parser::Comma);
}

tree::TerminalNode* AutoTenV1Parser::ExpressionListContext::Comma(size_t i) {
  return getToken(AutoTenV1Parser::Comma, i);
}


size_t AutoTenV1Parser::ExpressionListContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleExpressionList;
}

void AutoTenV1Parser::ExpressionListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionList(this);
}

void AutoTenV1Parser::ExpressionListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionList(this);
}


std::any AutoTenV1Parser::ExpressionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitExpressionList(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ExpressionListContext* AutoTenV1Parser::expressionList() {
  ExpressionListContext *_localctx = _tracker.createInstance<ExpressionListContext>(_ctx, getState());
  enterRule(_localctx, 72, AutoTenV1Parser::RuleExpressionList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(536);
    expression(0);
    setState(541);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(537);
        match(AutoTenV1Parser::Comma);
        setState(538);
        expression(0); 
      }
      setState(543);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierListContext ------------------------------------------------------------------

AutoTenV1Parser::IdentifierListContext::IdentifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::IdentifierListContext::Identifier() {
  return getTokens(AutoTenV1Parser::Identifier);
}

tree::TerminalNode* AutoTenV1Parser::IdentifierListContext::Identifier(size_t i) {
  return getToken(AutoTenV1Parser::Identifier, i);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::IdentifierListContext::Comma() {
  return getTokens(AutoTenV1Parser::Comma);
}

tree::TerminalNode* AutoTenV1Parser::IdentifierListContext::Comma(size_t i) {
  return getToken(AutoTenV1Parser::Comma, i);
}


size_t AutoTenV1Parser::IdentifierListContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleIdentifierList;
}

void AutoTenV1Parser::IdentifierListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifierList(this);
}

void AutoTenV1Parser::IdentifierListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifierList(this);
}


std::any AutoTenV1Parser::IdentifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitIdentifierList(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::IdentifierListContext* AutoTenV1Parser::identifierList() {
  IdentifierListContext *_localctx = _tracker.createInstance<IdentifierListContext>(_ctx, getState());
  enterRule(_localctx, 74, AutoTenV1Parser::RuleIdentifierList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(544);
    match(AutoTenV1Parser::Identifier);
    setState(549);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Comma) {
      setState(545);
      match(AutoTenV1Parser::Comma);
      setState(546);
      match(AutoTenV1Parser::Identifier);
      setState(551);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

AutoTenV1Parser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::BasicLitContext* AutoTenV1Parser::LiteralContext::basicLit() {
  return getRuleContext<AutoTenV1Parser::BasicLitContext>(0);
}

AutoTenV1Parser::CompositeLitContext* AutoTenV1Parser::LiteralContext::compositeLit() {
  return getRuleContext<AutoTenV1Parser::CompositeLitContext>(0);
}

AutoTenV1Parser::FunctionLitContext* AutoTenV1Parser::LiteralContext::functionLit() {
  return getRuleContext<AutoTenV1Parser::FunctionLitContext>(0);
}


size_t AutoTenV1Parser::LiteralContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleLiteral;
}

void AutoTenV1Parser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void AutoTenV1Parser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}


std::any AutoTenV1Parser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::LiteralContext* AutoTenV1Parser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 76, AutoTenV1Parser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(555);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(552);
      basicLit();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(553);
      compositeLit();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(554);
      functionLit();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BasicLitContext ------------------------------------------------------------------

AutoTenV1Parser::BasicLitContext::BasicLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::BasicLitContext::Nilptr() {
  return getToken(AutoTenV1Parser::Nilptr, 0);
}

tree::TerminalNode* AutoTenV1Parser::BasicLitContext::IntegerLiteral() {
  return getToken(AutoTenV1Parser::IntegerLiteral, 0);
}

tree::TerminalNode* AutoTenV1Parser::BasicLitContext::StringLiteral() {
  return getToken(AutoTenV1Parser::StringLiteral, 0);
}

tree::TerminalNode* AutoTenV1Parser::BasicLitContext::FloatingLiteral() {
  return getToken(AutoTenV1Parser::FloatingLiteral, 0);
}

tree::TerminalNode* AutoTenV1Parser::BasicLitContext::CharacterLiteral() {
  return getToken(AutoTenV1Parser::CharacterLiteral, 0);
}


size_t AutoTenV1Parser::BasicLitContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleBasicLit;
}

void AutoTenV1Parser::BasicLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBasicLit(this);
}

void AutoTenV1Parser::BasicLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBasicLit(this);
}


std::any AutoTenV1Parser::BasicLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitBasicLit(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::BasicLitContext* AutoTenV1Parser::basicLit() {
  BasicLitContext *_localctx = _tracker.createInstance<BasicLitContext>(_ctx, getState());
  enterRule(_localctx, 78, AutoTenV1Parser::RuleBasicLit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(557);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4194334) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperandNameContext ------------------------------------------------------------------

AutoTenV1Parser::OperandNameContext::OperandNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::OperandNameContext::Identifier() {
  return getToken(AutoTenV1Parser::Identifier, 0);
}


size_t AutoTenV1Parser::OperandNameContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleOperandName;
}

void AutoTenV1Parser::OperandNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperandName(this);
}

void AutoTenV1Parser::OperandNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperandName(this);
}


std::any AutoTenV1Parser::OperandNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitOperandName(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::OperandNameContext* AutoTenV1Parser::operandName() {
  OperandNameContext *_localctx = _tracker.createInstance<OperandNameContext>(_ctx, getState());
  enterRule(_localctx, 80, AutoTenV1Parser::RuleOperandName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(559);
    match(AutoTenV1Parser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QualifiedIdentContext ------------------------------------------------------------------

AutoTenV1Parser::QualifiedIdentContext::QualifiedIdentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::QualifiedIdentContext::Identifier() {
  return getTokens(AutoTenV1Parser::Identifier);
}

tree::TerminalNode* AutoTenV1Parser::QualifiedIdentContext::Identifier(size_t i) {
  return getToken(AutoTenV1Parser::Identifier, i);
}

tree::TerminalNode* AutoTenV1Parser::QualifiedIdentContext::Dot() {
  return getToken(AutoTenV1Parser::Dot, 0);
}


size_t AutoTenV1Parser::QualifiedIdentContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleQualifiedIdent;
}

void AutoTenV1Parser::QualifiedIdentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQualifiedIdent(this);
}

void AutoTenV1Parser::QualifiedIdentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQualifiedIdent(this);
}


std::any AutoTenV1Parser::QualifiedIdentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitQualifiedIdent(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::QualifiedIdentContext* AutoTenV1Parser::qualifiedIdent() {
  QualifiedIdentContext *_localctx = _tracker.createInstance<QualifiedIdentContext>(_ctx, getState());
  enterRule(_localctx, 82, AutoTenV1Parser::RuleQualifiedIdent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(561);
    match(AutoTenV1Parser::Identifier);
    setState(562);
    match(AutoTenV1Parser::Dot);
    setState(563);
    match(AutoTenV1Parser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompositeLitContext ------------------------------------------------------------------

AutoTenV1Parser::CompositeLitContext::CompositeLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::LiteralTypeContext* AutoTenV1Parser::CompositeLitContext::literalType() {
  return getRuleContext<AutoTenV1Parser::LiteralTypeContext>(0);
}

AutoTenV1Parser::LiteralValueContext* AutoTenV1Parser::CompositeLitContext::literalValue() {
  return getRuleContext<AutoTenV1Parser::LiteralValueContext>(0);
}


size_t AutoTenV1Parser::CompositeLitContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleCompositeLit;
}

void AutoTenV1Parser::CompositeLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompositeLit(this);
}

void AutoTenV1Parser::CompositeLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompositeLit(this);
}


std::any AutoTenV1Parser::CompositeLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitCompositeLit(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::CompositeLitContext* AutoTenV1Parser::compositeLit() {
  CompositeLitContext *_localctx = _tracker.createInstance<CompositeLitContext>(_ctx, getState());
  enterRule(_localctx, 84, AutoTenV1Parser::RuleCompositeLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(565);
    literalType();
    setState(566);
    literalValue();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralTypeContext ------------------------------------------------------------------

AutoTenV1Parser::LiteralTypeContext::LiteralTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::StructTypeContext* AutoTenV1Parser::LiteralTypeContext::structType() {
  return getRuleContext<AutoTenV1Parser::StructTypeContext>(0);
}

AutoTenV1Parser::ArrayTypeContext* AutoTenV1Parser::LiteralTypeContext::arrayType() {
  return getRuleContext<AutoTenV1Parser::ArrayTypeContext>(0);
}

AutoTenV1Parser::ElementTypeContext* AutoTenV1Parser::LiteralTypeContext::elementType() {
  return getRuleContext<AutoTenV1Parser::ElementTypeContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::LiteralTypeContext::LeftBracket() {
  return getToken(AutoTenV1Parser::LeftBracket, 0);
}

tree::TerminalNode* AutoTenV1Parser::LiteralTypeContext::Ellipsis() {
  return getToken(AutoTenV1Parser::Ellipsis, 0);
}

tree::TerminalNode* AutoTenV1Parser::LiteralTypeContext::RightBracket() {
  return getToken(AutoTenV1Parser::RightBracket, 0);
}

AutoTenV1Parser::SliceTypeContext* AutoTenV1Parser::LiteralTypeContext::sliceType() {
  return getRuleContext<AutoTenV1Parser::SliceTypeContext>(0);
}

AutoTenV1Parser::TensorTypeContext* AutoTenV1Parser::LiteralTypeContext::tensorType() {
  return getRuleContext<AutoTenV1Parser::TensorTypeContext>(0);
}

AutoTenV1Parser::MapTypeContext* AutoTenV1Parser::LiteralTypeContext::mapType() {
  return getRuleContext<AutoTenV1Parser::MapTypeContext>(0);
}

AutoTenV1Parser::TypeNameContext* AutoTenV1Parser::LiteralTypeContext::typeName() {
  return getRuleContext<AutoTenV1Parser::TypeNameContext>(0);
}


size_t AutoTenV1Parser::LiteralTypeContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleLiteralType;
}

void AutoTenV1Parser::LiteralTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteralType(this);
}

void AutoTenV1Parser::LiteralTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteralType(this);
}


std::any AutoTenV1Parser::LiteralTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitLiteralType(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::LiteralTypeContext* AutoTenV1Parser::literalType() {
  LiteralTypeContext *_localctx = _tracker.createInstance<LiteralTypeContext>(_ctx, getState());
  enterRule(_localctx, 86, AutoTenV1Parser::RuleLiteralType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(579);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(568);
      structType();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(569);
      arrayType();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(570);
      elementType();
      setState(571);
      match(AutoTenV1Parser::LeftBracket);
      setState(572);
      match(AutoTenV1Parser::Ellipsis);
      setState(573);
      match(AutoTenV1Parser::RightBracket);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(575);
      sliceType();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(576);
      tensorType();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(577);
      mapType();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(578);
      typeName();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralValueContext ------------------------------------------------------------------

AutoTenV1Parser::LiteralValueContext::LiteralValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::LiteralValueContext::LeftBrace() {
  return getToken(AutoTenV1Parser::LeftBrace, 0);
}

tree::TerminalNode* AutoTenV1Parser::LiteralValueContext::RightBrace() {
  return getToken(AutoTenV1Parser::RightBrace, 0);
}

AutoTenV1Parser::ElementListContext* AutoTenV1Parser::LiteralValueContext::elementList() {
  return getRuleContext<AutoTenV1Parser::ElementListContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::LiteralValueContext::Comma() {
  return getToken(AutoTenV1Parser::Comma, 0);
}


size_t AutoTenV1Parser::LiteralValueContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleLiteralValue;
}

void AutoTenV1Parser::LiteralValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteralValue(this);
}

void AutoTenV1Parser::LiteralValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteralValue(this);
}


std::any AutoTenV1Parser::LiteralValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitLiteralValue(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::LiteralValueContext* AutoTenV1Parser::literalValue() {
  LiteralValueContext *_localctx = _tracker.createInstance<LiteralValueContext>(_ctx, getState());
  enterRule(_localctx, 88, AutoTenV1Parser::RuleLiteralValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(581);
    match(AutoTenV1Parser::LeftBrace);
    setState(586);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 692800421242339102) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 80)) & 21) != 0)) {
      setState(582);
      elementList();
      setState(584);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Comma) {
        setState(583);
        match(AutoTenV1Parser::Comma);
      }
    }
    setState(588);
    match(AutoTenV1Parser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementListContext ------------------------------------------------------------------

AutoTenV1Parser::ElementListContext::ElementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<AutoTenV1Parser::KeyedElementContext *> AutoTenV1Parser::ElementListContext::keyedElement() {
  return getRuleContexts<AutoTenV1Parser::KeyedElementContext>();
}

AutoTenV1Parser::KeyedElementContext* AutoTenV1Parser::ElementListContext::keyedElement(size_t i) {
  return getRuleContext<AutoTenV1Parser::KeyedElementContext>(i);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::ElementListContext::Comma() {
  return getTokens(AutoTenV1Parser::Comma);
}

tree::TerminalNode* AutoTenV1Parser::ElementListContext::Comma(size_t i) {
  return getToken(AutoTenV1Parser::Comma, i);
}


size_t AutoTenV1Parser::ElementListContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleElementList;
}

void AutoTenV1Parser::ElementListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementList(this);
}

void AutoTenV1Parser::ElementListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementList(this);
}


std::any AutoTenV1Parser::ElementListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitElementList(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ElementListContext* AutoTenV1Parser::elementList() {
  ElementListContext *_localctx = _tracker.createInstance<ElementListContext>(_ctx, getState());
  enterRule(_localctx, 90, AutoTenV1Parser::RuleElementList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(590);
    keyedElement();
    setState(595);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(591);
        match(AutoTenV1Parser::Comma);
        setState(592);
        keyedElement(); 
      }
      setState(597);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeyedElementContext ------------------------------------------------------------------

AutoTenV1Parser::KeyedElementContext::KeyedElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::ElementContext* AutoTenV1Parser::KeyedElementContext::element() {
  return getRuleContext<AutoTenV1Parser::ElementContext>(0);
}

AutoTenV1Parser::KeyContext* AutoTenV1Parser::KeyedElementContext::key() {
  return getRuleContext<AutoTenV1Parser::KeyContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::KeyedElementContext::Colon() {
  return getToken(AutoTenV1Parser::Colon, 0);
}


size_t AutoTenV1Parser::KeyedElementContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleKeyedElement;
}

void AutoTenV1Parser::KeyedElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyedElement(this);
}

void AutoTenV1Parser::KeyedElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyedElement(this);
}


std::any AutoTenV1Parser::KeyedElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitKeyedElement(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::KeyedElementContext* AutoTenV1Parser::keyedElement() {
  KeyedElementContext *_localctx = _tracker.createInstance<KeyedElementContext>(_ctx, getState());
  enterRule(_localctx, 92, AutoTenV1Parser::RuleKeyedElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(601);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      setState(598);
      key();
      setState(599);
      match(AutoTenV1Parser::Colon);
      break;
    }

    default:
      break;
    }
    setState(603);
    element();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeyContext ------------------------------------------------------------------

AutoTenV1Parser::KeyContext::KeyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::KeyContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}

AutoTenV1Parser::LiteralValueContext* AutoTenV1Parser::KeyContext::literalValue() {
  return getRuleContext<AutoTenV1Parser::LiteralValueContext>(0);
}


size_t AutoTenV1Parser::KeyContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleKey;
}

void AutoTenV1Parser::KeyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKey(this);
}

void AutoTenV1Parser::KeyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKey(this);
}


std::any AutoTenV1Parser::KeyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitKey(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::KeyContext* AutoTenV1Parser::key() {
  KeyContext *_localctx = _tracker.createInstance<KeyContext>(_ctx, getState());
  enterRule(_localctx, 94, AutoTenV1Parser::RuleKey);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(607);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::IntegerLiteral:
      case AutoTenV1Parser::CharacterLiteral:
      case AutoTenV1Parser::FloatingLiteral:
      case AutoTenV1Parser::StringLiteral:
      case AutoTenV1Parser::Int8:
      case AutoTenV1Parser::Int16:
      case AutoTenV1Parser::Int32:
      case AutoTenV1Parser::Int64:
      case AutoTenV1Parser::Float32:
      case AutoTenV1Parser::Float64:
      case AutoTenV1Parser::Char:
      case AutoTenV1Parser::Bool:
      case AutoTenV1Parser::String:
      case AutoTenV1Parser::Tensor:
      case AutoTenV1Parser::Void:
      case AutoTenV1Parser::Nilptr:
      case AutoTenV1Parser::Function:
      case AutoTenV1Parser::Struct:
      case AutoTenV1Parser::Impl:
      case AutoTenV1Parser::LeftParen:
      case AutoTenV1Parser::LeftBracket:
      case AutoTenV1Parser::Plus:
      case AutoTenV1Parser::Minus:
      case AutoTenV1Parser::Star:
      case AutoTenV1Parser::Caret:
      case AutoTenV1Parser::And:
      case AutoTenV1Parser::Not:
      case AutoTenV1Parser::At:
      case AutoTenV1Parser::Map:
      case AutoTenV1Parser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(605);
        expression(0);
        break;
      }

      case AutoTenV1Parser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(606);
        literalValue();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementContext ------------------------------------------------------------------

AutoTenV1Parser::ElementContext::ElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::ElementContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}

AutoTenV1Parser::LiteralValueContext* AutoTenV1Parser::ElementContext::literalValue() {
  return getRuleContext<AutoTenV1Parser::LiteralValueContext>(0);
}


size_t AutoTenV1Parser::ElementContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleElement;
}

void AutoTenV1Parser::ElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElement(this);
}

void AutoTenV1Parser::ElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElement(this);
}


std::any AutoTenV1Parser::ElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitElement(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ElementContext* AutoTenV1Parser::element() {
  ElementContext *_localctx = _tracker.createInstance<ElementContext>(_ctx, getState());
  enterRule(_localctx, 96, AutoTenV1Parser::RuleElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(611);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::IntegerLiteral:
      case AutoTenV1Parser::CharacterLiteral:
      case AutoTenV1Parser::FloatingLiteral:
      case AutoTenV1Parser::StringLiteral:
      case AutoTenV1Parser::Int8:
      case AutoTenV1Parser::Int16:
      case AutoTenV1Parser::Int32:
      case AutoTenV1Parser::Int64:
      case AutoTenV1Parser::Float32:
      case AutoTenV1Parser::Float64:
      case AutoTenV1Parser::Char:
      case AutoTenV1Parser::Bool:
      case AutoTenV1Parser::String:
      case AutoTenV1Parser::Tensor:
      case AutoTenV1Parser::Void:
      case AutoTenV1Parser::Nilptr:
      case AutoTenV1Parser::Function:
      case AutoTenV1Parser::Struct:
      case AutoTenV1Parser::Impl:
      case AutoTenV1Parser::LeftParen:
      case AutoTenV1Parser::LeftBracket:
      case AutoTenV1Parser::Plus:
      case AutoTenV1Parser::Minus:
      case AutoTenV1Parser::Star:
      case AutoTenV1Parser::Caret:
      case AutoTenV1Parser::And:
      case AutoTenV1Parser::Not:
      case AutoTenV1Parser::At:
      case AutoTenV1Parser::Map:
      case AutoTenV1Parser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(609);
        expression(0);
        break;
      }

      case AutoTenV1Parser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(610);
        literalValue();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructTypeContext ------------------------------------------------------------------

AutoTenV1Parser::StructTypeContext::StructTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::StructTypeContext::Struct() {
  return getToken(AutoTenV1Parser::Struct, 0);
}

tree::TerminalNode* AutoTenV1Parser::StructTypeContext::LeftBrace() {
  return getToken(AutoTenV1Parser::LeftBrace, 0);
}

tree::TerminalNode* AutoTenV1Parser::StructTypeContext::RightBrace() {
  return getToken(AutoTenV1Parser::RightBrace, 0);
}

std::vector<AutoTenV1Parser::FieldDeclContext *> AutoTenV1Parser::StructTypeContext::fieldDecl() {
  return getRuleContexts<AutoTenV1Parser::FieldDeclContext>();
}

AutoTenV1Parser::FieldDeclContext* AutoTenV1Parser::StructTypeContext::fieldDecl(size_t i) {
  return getRuleContext<AutoTenV1Parser::FieldDeclContext>(i);
}

std::vector<AutoTenV1Parser::EosContext *> AutoTenV1Parser::StructTypeContext::eos() {
  return getRuleContexts<AutoTenV1Parser::EosContext>();
}

AutoTenV1Parser::EosContext* AutoTenV1Parser::StructTypeContext::eos(size_t i) {
  return getRuleContext<AutoTenV1Parser::EosContext>(i);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::StructTypeContext::Public() {
  return getTokens(AutoTenV1Parser::Public);
}

tree::TerminalNode* AutoTenV1Parser::StructTypeContext::Public(size_t i) {
  return getToken(AutoTenV1Parser::Public, i);
}


size_t AutoTenV1Parser::StructTypeContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleStructType;
}

void AutoTenV1Parser::StructTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructType(this);
}

void AutoTenV1Parser::StructTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructType(this);
}


std::any AutoTenV1Parser::StructTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitStructType(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::StructTypeContext* AutoTenV1Parser::structType() {
  StructTypeContext *_localctx = _tracker.createInstance<StructTypeContext>(_ctx, getState());
  enterRule(_localctx, 98, AutoTenV1Parser::RuleStructType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(613);
    match(AutoTenV1Parser::Struct);
    setState(614);
    match(AutoTenV1Parser::LeftBrace);
    setState(623);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 42) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 42)) & 4398046512129) != 0)) {
      setState(616);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Public) {
        setState(615);
        match(AutoTenV1Parser::Public);
      }
      setState(618);
      fieldDecl();
      setState(619);
      eos();
      setState(625);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(626);
    match(AutoTenV1Parser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FieldDeclContext ------------------------------------------------------------------

AutoTenV1Parser::FieldDeclContext::FieldDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::IdentifierListContext* AutoTenV1Parser::FieldDeclContext::identifierList() {
  return getRuleContext<AutoTenV1Parser::IdentifierListContext>(0);
}

AutoTenV1Parser::Type_Context* AutoTenV1Parser::FieldDeclContext::type_() {
  return getRuleContext<AutoTenV1Parser::Type_Context>(0);
}

AutoTenV1Parser::EmbeddedFieldContext* AutoTenV1Parser::FieldDeclContext::embeddedField() {
  return getRuleContext<AutoTenV1Parser::EmbeddedFieldContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::FieldDeclContext::StringLiteral() {
  return getToken(AutoTenV1Parser::StringLiteral, 0);
}


size_t AutoTenV1Parser::FieldDeclContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleFieldDecl;
}

void AutoTenV1Parser::FieldDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFieldDecl(this);
}

void AutoTenV1Parser::FieldDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFieldDecl(this);
}


std::any AutoTenV1Parser::FieldDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitFieldDecl(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::FieldDeclContext* AutoTenV1Parser::fieldDecl() {
  FieldDeclContext *_localctx = _tracker.createInstance<FieldDeclContext>(_ctx, getState());
  enterRule(_localctx, 100, AutoTenV1Parser::RuleFieldDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(632);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      setState(628);
      identifierList();
      setState(629);
      type_();
      break;
    }

    case 2: {
      setState(631);
      embeddedField();
      break;
    }

    default:
      break;
    }
    setState(635);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::StringLiteral) {
      setState(634);
      antlrcpp::downCast<FieldDeclContext *>(_localctx)->tag = match(AutoTenV1Parser::StringLiteral);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EmbeddedFieldContext ------------------------------------------------------------------

AutoTenV1Parser::EmbeddedFieldContext::EmbeddedFieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::TypeNameContext* AutoTenV1Parser::EmbeddedFieldContext::typeName() {
  return getRuleContext<AutoTenV1Parser::TypeNameContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::EmbeddedFieldContext::Star() {
  return getToken(AutoTenV1Parser::Star, 0);
}


size_t AutoTenV1Parser::EmbeddedFieldContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleEmbeddedField;
}

void AutoTenV1Parser::EmbeddedFieldContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEmbeddedField(this);
}

void AutoTenV1Parser::EmbeddedFieldContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEmbeddedField(this);
}


std::any AutoTenV1Parser::EmbeddedFieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitEmbeddedField(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::EmbeddedFieldContext* AutoTenV1Parser::embeddedField() {
  EmbeddedFieldContext *_localctx = _tracker.createInstance<EmbeddedFieldContext>(_ctx, getState());
  enterRule(_localctx, 102, AutoTenV1Parser::RuleEmbeddedField);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(638);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Star) {
      setState(637);
      match(AutoTenV1Parser::Star);
    }
    setState(640);
    typeName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionLitContext ------------------------------------------------------------------

AutoTenV1Parser::FunctionLitContext::FunctionLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::FunctionLitContext::Function() {
  return getToken(AutoTenV1Parser::Function, 0);
}

AutoTenV1Parser::SignatureContext* AutoTenV1Parser::FunctionLitContext::signature() {
  return getRuleContext<AutoTenV1Parser::SignatureContext>(0);
}

AutoTenV1Parser::BlockContext* AutoTenV1Parser::FunctionLitContext::block() {
  return getRuleContext<AutoTenV1Parser::BlockContext>(0);
}

std::vector<AutoTenV1Parser::CompileFlagsContext *> AutoTenV1Parser::FunctionLitContext::compileFlags() {
  return getRuleContexts<AutoTenV1Parser::CompileFlagsContext>();
}

AutoTenV1Parser::CompileFlagsContext* AutoTenV1Parser::FunctionLitContext::compileFlags(size_t i) {
  return getRuleContext<AutoTenV1Parser::CompileFlagsContext>(i);
}


size_t AutoTenV1Parser::FunctionLitContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleFunctionLit;
}

void AutoTenV1Parser::FunctionLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionLit(this);
}

void AutoTenV1Parser::FunctionLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionLit(this);
}


std::any AutoTenV1Parser::FunctionLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitFunctionLit(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::FunctionLitContext* AutoTenV1Parser::functionLit() {
  FunctionLitContext *_localctx = _tracker.createInstance<FunctionLitContext>(_ctx, getState());
  enterRule(_localctx, 104, AutoTenV1Parser::RuleFunctionLit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(645);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::At) {
      setState(642);
      compileFlags();
      setState(647);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(648);
    match(AutoTenV1Parser::Function);
    setState(649);
    signature();
    setState(650);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclContext ------------------------------------------------------------------

AutoTenV1Parser::FunctionDeclContext::FunctionDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::FunctionDeclContext::Function() {
  return getToken(AutoTenV1Parser::Function, 0);
}

tree::TerminalNode* AutoTenV1Parser::FunctionDeclContext::Identifier() {
  return getToken(AutoTenV1Parser::Identifier, 0);
}

AutoTenV1Parser::SignatureContext* AutoTenV1Parser::FunctionDeclContext::signature() {
  return getRuleContext<AutoTenV1Parser::SignatureContext>(0);
}

std::vector<AutoTenV1Parser::CompileFlagsContext *> AutoTenV1Parser::FunctionDeclContext::compileFlags() {
  return getRuleContexts<AutoTenV1Parser::CompileFlagsContext>();
}

AutoTenV1Parser::CompileFlagsContext* AutoTenV1Parser::FunctionDeclContext::compileFlags(size_t i) {
  return getRuleContext<AutoTenV1Parser::CompileFlagsContext>(i);
}

tree::TerminalNode* AutoTenV1Parser::FunctionDeclContext::Public() {
  return getToken(AutoTenV1Parser::Public, 0);
}

AutoTenV1Parser::BlockContext* AutoTenV1Parser::FunctionDeclContext::block() {
  return getRuleContext<AutoTenV1Parser::BlockContext>(0);
}


size_t AutoTenV1Parser::FunctionDeclContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleFunctionDecl;
}

void AutoTenV1Parser::FunctionDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDecl(this);
}

void AutoTenV1Parser::FunctionDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDecl(this);
}


std::any AutoTenV1Parser::FunctionDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitFunctionDecl(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::FunctionDeclContext* AutoTenV1Parser::functionDecl() {
  FunctionDeclContext *_localctx = _tracker.createInstance<FunctionDeclContext>(_ctx, getState());
  enterRule(_localctx, 106, AutoTenV1Parser::RuleFunctionDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(655);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::At) {
      setState(652);
      compileFlags();
      setState(657);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(659);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Public) {
      setState(658);
      match(AutoTenV1Parser::Public);
    }
    setState(661);
    match(AutoTenV1Parser::Function);
    setState(662);
    match(AutoTenV1Parser::Identifier);
    setState(663);
    signature();
    setState(665);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::LeftBrace) {
      setState(664);
      block();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

AutoTenV1Parser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::BlockContext::LeftBrace() {
  return getToken(AutoTenV1Parser::LeftBrace, 0);
}

tree::TerminalNode* AutoTenV1Parser::BlockContext::RightBrace() {
  return getToken(AutoTenV1Parser::RightBrace, 0);
}

AutoTenV1Parser::StatementListContext* AutoTenV1Parser::BlockContext::statementList() {
  return getRuleContext<AutoTenV1Parser::StatementListContext>(0);
}


size_t AutoTenV1Parser::BlockContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleBlock;
}

void AutoTenV1Parser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void AutoTenV1Parser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


std::any AutoTenV1Parser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::BlockContext* AutoTenV1Parser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 108, AutoTenV1Parser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(667);
    match(AutoTenV1Parser::LeftBrace);
    setState(669);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 692801123461365534) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 80)) & 23) != 0)) {
      setState(668);
      statementList();
    }
    setState(671);
    match(AutoTenV1Parser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementListContext ------------------------------------------------------------------

AutoTenV1Parser::StatementListContext::StatementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<AutoTenV1Parser::StatementContext *> AutoTenV1Parser::StatementListContext::statement() {
  return getRuleContexts<AutoTenV1Parser::StatementContext>();
}

AutoTenV1Parser::StatementContext* AutoTenV1Parser::StatementListContext::statement(size_t i) {
  return getRuleContext<AutoTenV1Parser::StatementContext>(i);
}

std::vector<AutoTenV1Parser::EosContext *> AutoTenV1Parser::StatementListContext::eos() {
  return getRuleContexts<AutoTenV1Parser::EosContext>();
}

AutoTenV1Parser::EosContext* AutoTenV1Parser::StatementListContext::eos(size_t i) {
  return getRuleContext<AutoTenV1Parser::EosContext>(i);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::StatementListContext::Semi() {
  return getTokens(AutoTenV1Parser::Semi);
}

tree::TerminalNode* AutoTenV1Parser::StatementListContext::Semi(size_t i) {
  return getToken(AutoTenV1Parser::Semi, i);
}


size_t AutoTenV1Parser::StatementListContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleStatementList;
}

void AutoTenV1Parser::StatementListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementList(this);
}

void AutoTenV1Parser::StatementListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementList(this);
}


std::any AutoTenV1Parser::StatementListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitStatementList(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::StatementListContext* AutoTenV1Parser::statementList() {
  StatementListContext *_localctx = _tracker.createInstance<StatementListContext>(_ctx, getState());
  enterRule(_localctx, 110, AutoTenV1Parser::RuleStatementList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(679); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(674);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Semi) {
        setState(673);
        match(AutoTenV1Parser::Semi);
      }
      setState(676);
      statement();
      setState(677);
      eos();
      setState(681); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 692801123461365534) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 80)) & 23) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

AutoTenV1Parser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::DeclarationContext* AutoTenV1Parser::StatementContext::declaration() {
  return getRuleContext<AutoTenV1Parser::DeclarationContext>(0);
}

AutoTenV1Parser::LabeledStmtContext* AutoTenV1Parser::StatementContext::labeledStmt() {
  return getRuleContext<AutoTenV1Parser::LabeledStmtContext>(0);
}

AutoTenV1Parser::SimpleStmtContext* AutoTenV1Parser::StatementContext::simpleStmt() {
  return getRuleContext<AutoTenV1Parser::SimpleStmtContext>(0);
}

AutoTenV1Parser::ReturnStmtContext* AutoTenV1Parser::StatementContext::returnStmt() {
  return getRuleContext<AutoTenV1Parser::ReturnStmtContext>(0);
}

AutoTenV1Parser::BreakStmtContext* AutoTenV1Parser::StatementContext::breakStmt() {
  return getRuleContext<AutoTenV1Parser::BreakStmtContext>(0);
}

AutoTenV1Parser::ContinueStmtContext* AutoTenV1Parser::StatementContext::continueStmt() {
  return getRuleContext<AutoTenV1Parser::ContinueStmtContext>(0);
}

AutoTenV1Parser::GotoStmtContext* AutoTenV1Parser::StatementContext::gotoStmt() {
  return getRuleContext<AutoTenV1Parser::GotoStmtContext>(0);
}

AutoTenV1Parser::FallthroughStmtContext* AutoTenV1Parser::StatementContext::fallthroughStmt() {
  return getRuleContext<AutoTenV1Parser::FallthroughStmtContext>(0);
}

AutoTenV1Parser::BlockContext* AutoTenV1Parser::StatementContext::block() {
  return getRuleContext<AutoTenV1Parser::BlockContext>(0);
}

AutoTenV1Parser::IfStmtContext* AutoTenV1Parser::StatementContext::ifStmt() {
  return getRuleContext<AutoTenV1Parser::IfStmtContext>(0);
}

AutoTenV1Parser::SwitchStmtContext* AutoTenV1Parser::StatementContext::switchStmt() {
  return getRuleContext<AutoTenV1Parser::SwitchStmtContext>(0);
}

AutoTenV1Parser::ForStmtContext* AutoTenV1Parser::StatementContext::forStmt() {
  return getRuleContext<AutoTenV1Parser::ForStmtContext>(0);
}

AutoTenV1Parser::PforStmtContext* AutoTenV1Parser::StatementContext::pforStmt() {
  return getRuleContext<AutoTenV1Parser::PforStmtContext>(0);
}

AutoTenV1Parser::WhileStmtContext* AutoTenV1Parser::StatementContext::whileStmt() {
  return getRuleContext<AutoTenV1Parser::WhileStmtContext>(0);
}

AutoTenV1Parser::DoWhileStmtContext* AutoTenV1Parser::StatementContext::doWhileStmt() {
  return getRuleContext<AutoTenV1Parser::DoWhileStmtContext>(0);
}


size_t AutoTenV1Parser::StatementContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleStatement;
}

void AutoTenV1Parser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void AutoTenV1Parser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any AutoTenV1Parser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::StatementContext* AutoTenV1Parser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 112, AutoTenV1Parser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(698);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(683);
      declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(684);
      labeledStmt();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(685);
      simpleStmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(686);
      returnStmt();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(687);
      breakStmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(688);
      continueStmt();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(689);
      gotoStmt();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(690);
      fallthroughStmt();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(691);
      block();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(692);
      ifStmt();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(693);
      switchStmt();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(694);
      forStmt();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(695);
      pforStmt();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(696);
      whileStmt();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(697);
      doWhileStmt();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SimpleStmtContext ------------------------------------------------------------------

AutoTenV1Parser::SimpleStmtContext::SimpleStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::IncDecStmtContext* AutoTenV1Parser::SimpleStmtContext::incDecStmt() {
  return getRuleContext<AutoTenV1Parser::IncDecStmtContext>(0);
}

AutoTenV1Parser::AssignmentContext* AutoTenV1Parser::SimpleStmtContext::assignment() {
  return getRuleContext<AutoTenV1Parser::AssignmentContext>(0);
}

AutoTenV1Parser::ExpressionStmtContext* AutoTenV1Parser::SimpleStmtContext::expressionStmt() {
  return getRuleContext<AutoTenV1Parser::ExpressionStmtContext>(0);
}

AutoTenV1Parser::ShortVarDeclContext* AutoTenV1Parser::SimpleStmtContext::shortVarDecl() {
  return getRuleContext<AutoTenV1Parser::ShortVarDeclContext>(0);
}


size_t AutoTenV1Parser::SimpleStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleSimpleStmt;
}

void AutoTenV1Parser::SimpleStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSimpleStmt(this);
}

void AutoTenV1Parser::SimpleStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSimpleStmt(this);
}


std::any AutoTenV1Parser::SimpleStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitSimpleStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::SimpleStmtContext* AutoTenV1Parser::simpleStmt() {
  SimpleStmtContext *_localctx = _tracker.createInstance<SimpleStmtContext>(_ctx, getState());
  enterRule(_localctx, 114, AutoTenV1Parser::RuleSimpleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(704);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(700);
      incDecStmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(701);
      assignment();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(702);
      expressionStmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(703);
      shortVarDecl();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStmtContext ------------------------------------------------------------------

AutoTenV1Parser::ExpressionStmtContext::ExpressionStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::ExpressionStmtContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}


size_t AutoTenV1Parser::ExpressionStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleExpressionStmt;
}

void AutoTenV1Parser::ExpressionStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStmt(this);
}

void AutoTenV1Parser::ExpressionStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStmt(this);
}


std::any AutoTenV1Parser::ExpressionStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitExpressionStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ExpressionStmtContext* AutoTenV1Parser::expressionStmt() {
  ExpressionStmtContext *_localctx = _tracker.createInstance<ExpressionStmtContext>(_ctx, getState());
  enterRule(_localctx, 116, AutoTenV1Parser::RuleExpressionStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(706);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IncDecStmtContext ------------------------------------------------------------------

AutoTenV1Parser::IncDecStmtContext::IncDecStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::IncDecStmtContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::IncDecStmtContext::PlusPlus() {
  return getToken(AutoTenV1Parser::PlusPlus, 0);
}

tree::TerminalNode* AutoTenV1Parser::IncDecStmtContext::MinusMinus() {
  return getToken(AutoTenV1Parser::MinusMinus, 0);
}


size_t AutoTenV1Parser::IncDecStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleIncDecStmt;
}

void AutoTenV1Parser::IncDecStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIncDecStmt(this);
}

void AutoTenV1Parser::IncDecStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIncDecStmt(this);
}


std::any AutoTenV1Parser::IncDecStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitIncDecStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::IncDecStmtContext* AutoTenV1Parser::incDecStmt() {
  IncDecStmtContext *_localctx = _tracker.createInstance<IncDecStmtContext>(_ctx, getState());
  enterRule(_localctx, 118, AutoTenV1Parser::RuleIncDecStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(708);
    expression(0);
    setState(709);
    _la = _input->LA(1);
    if (!(_la == AutoTenV1Parser::PlusPlus

    || _la == AutoTenV1Parser::MinusMinus)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

AutoTenV1Parser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<AutoTenV1Parser::ExpressionListContext *> AutoTenV1Parser::AssignmentContext::expressionList() {
  return getRuleContexts<AutoTenV1Parser::ExpressionListContext>();
}

AutoTenV1Parser::ExpressionListContext* AutoTenV1Parser::AssignmentContext::expressionList(size_t i) {
  return getRuleContext<AutoTenV1Parser::ExpressionListContext>(i);
}

AutoTenV1Parser::Assign_opContext* AutoTenV1Parser::AssignmentContext::assign_op() {
  return getRuleContext<AutoTenV1Parser::Assign_opContext>(0);
}


size_t AutoTenV1Parser::AssignmentContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleAssignment;
}

void AutoTenV1Parser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void AutoTenV1Parser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}


std::any AutoTenV1Parser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::AssignmentContext* AutoTenV1Parser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 120, AutoTenV1Parser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(711);
    expressionList();
    setState(712);
    assign_op();
    setState(713);
    expressionList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Assign_opContext ------------------------------------------------------------------

AutoTenV1Parser::Assign_opContext::Assign_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::Assign_opContext::Assign() {
  return getToken(AutoTenV1Parser::Assign, 0);
}

tree::TerminalNode* AutoTenV1Parser::Assign_opContext::Plus() {
  return getToken(AutoTenV1Parser::Plus, 0);
}

tree::TerminalNode* AutoTenV1Parser::Assign_opContext::Minus() {
  return getToken(AutoTenV1Parser::Minus, 0);
}

tree::TerminalNode* AutoTenV1Parser::Assign_opContext::Or() {
  return getToken(AutoTenV1Parser::Or, 0);
}

tree::TerminalNode* AutoTenV1Parser::Assign_opContext::Caret() {
  return getToken(AutoTenV1Parser::Caret, 0);
}

tree::TerminalNode* AutoTenV1Parser::Assign_opContext::Star() {
  return getToken(AutoTenV1Parser::Star, 0);
}

tree::TerminalNode* AutoTenV1Parser::Assign_opContext::Div() {
  return getToken(AutoTenV1Parser::Div, 0);
}

tree::TerminalNode* AutoTenV1Parser::Assign_opContext::Mod() {
  return getToken(AutoTenV1Parser::Mod, 0);
}

tree::TerminalNode* AutoTenV1Parser::Assign_opContext::LeftShift() {
  return getToken(AutoTenV1Parser::LeftShift, 0);
}

tree::TerminalNode* AutoTenV1Parser::Assign_opContext::RightShift() {
  return getToken(AutoTenV1Parser::RightShift, 0);
}

tree::TerminalNode* AutoTenV1Parser::Assign_opContext::And() {
  return getToken(AutoTenV1Parser::And, 0);
}


size_t AutoTenV1Parser::Assign_opContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleAssign_op;
}

void AutoTenV1Parser::Assign_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssign_op(this);
}

void AutoTenV1Parser::Assign_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssign_op(this);
}


std::any AutoTenV1Parser::Assign_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitAssign_op(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::Assign_opContext* AutoTenV1Parser::assign_op() {
  Assign_opContext *_localctx = _tracker.createInstance<Assign_opContext>(_ctx, getState());
  enterRule(_localctx, 122, AutoTenV1Parser::RuleAssign_op);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(716);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 50) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 50)) & 49407) != 0)) {
      setState(715);
      _la = _input->LA(1);
      if (!(((((_la - 50) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 50)) & 49407) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(718);
    match(AutoTenV1Parser::Assign);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ShortVarDeclContext ------------------------------------------------------------------

AutoTenV1Parser::ShortVarDeclContext::ShortVarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::IdentifierListContext* AutoTenV1Parser::ShortVarDeclContext::identifierList() {
  return getRuleContext<AutoTenV1Parser::IdentifierListContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::ShortVarDeclContext::DeclareAssign() {
  return getToken(AutoTenV1Parser::DeclareAssign, 0);
}

AutoTenV1Parser::ExpressionListContext* AutoTenV1Parser::ShortVarDeclContext::expressionList() {
  return getRuleContext<AutoTenV1Parser::ExpressionListContext>(0);
}


size_t AutoTenV1Parser::ShortVarDeclContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleShortVarDecl;
}

void AutoTenV1Parser::ShortVarDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShortVarDecl(this);
}

void AutoTenV1Parser::ShortVarDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShortVarDecl(this);
}


std::any AutoTenV1Parser::ShortVarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitShortVarDecl(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ShortVarDeclContext* AutoTenV1Parser::shortVarDecl() {
  ShortVarDeclContext *_localctx = _tracker.createInstance<ShortVarDeclContext>(_ctx, getState());
  enterRule(_localctx, 124, AutoTenV1Parser::RuleShortVarDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(720);
    identifierList();
    setState(721);
    match(AutoTenV1Parser::DeclareAssign);
    setState(722);
    expressionList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EmptyStmtContext ------------------------------------------------------------------

AutoTenV1Parser::EmptyStmtContext::EmptyStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::EmptyStmtContext::Semi() {
  return getToken(AutoTenV1Parser::Semi, 0);
}


size_t AutoTenV1Parser::EmptyStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleEmptyStmt;
}

void AutoTenV1Parser::EmptyStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEmptyStmt(this);
}

void AutoTenV1Parser::EmptyStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEmptyStmt(this);
}


std::any AutoTenV1Parser::EmptyStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitEmptyStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::EmptyStmtContext* AutoTenV1Parser::emptyStmt() {
  EmptyStmtContext *_localctx = _tracker.createInstance<EmptyStmtContext>(_ctx, getState());
  enterRule(_localctx, 126, AutoTenV1Parser::RuleEmptyStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(724);
    match(AutoTenV1Parser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabeledStmtContext ------------------------------------------------------------------

AutoTenV1Parser::LabeledStmtContext::LabeledStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::LabeledStmtContext::Identifier() {
  return getToken(AutoTenV1Parser::Identifier, 0);
}

tree::TerminalNode* AutoTenV1Parser::LabeledStmtContext::Colon() {
  return getToken(AutoTenV1Parser::Colon, 0);
}

AutoTenV1Parser::StatementContext* AutoTenV1Parser::LabeledStmtContext::statement() {
  return getRuleContext<AutoTenV1Parser::StatementContext>(0);
}


size_t AutoTenV1Parser::LabeledStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleLabeledStmt;
}

void AutoTenV1Parser::LabeledStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLabeledStmt(this);
}

void AutoTenV1Parser::LabeledStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLabeledStmt(this);
}


std::any AutoTenV1Parser::LabeledStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitLabeledStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::LabeledStmtContext* AutoTenV1Parser::labeledStmt() {
  LabeledStmtContext *_localctx = _tracker.createInstance<LabeledStmtContext>(_ctx, getState());
  enterRule(_localctx, 128, AutoTenV1Parser::RuleLabeledStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(726);
    match(AutoTenV1Parser::Identifier);
    setState(727);
    match(AutoTenV1Parser::Colon);
    setState(729);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 692801123461365534) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 80)) & 21) != 0)) {
      setState(728);
      statement();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStmtContext ------------------------------------------------------------------

AutoTenV1Parser::ReturnStmtContext::ReturnStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::ReturnStmtContext::Return() {
  return getToken(AutoTenV1Parser::Return, 0);
}

AutoTenV1Parser::ExpressionListContext* AutoTenV1Parser::ReturnStmtContext::expressionList() {
  return getRuleContext<AutoTenV1Parser::ExpressionListContext>(0);
}


size_t AutoTenV1Parser::ReturnStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleReturnStmt;
}

void AutoTenV1Parser::ReturnStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStmt(this);
}

void AutoTenV1Parser::ReturnStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStmt(this);
}


std::any AutoTenV1Parser::ReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitReturnStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ReturnStmtContext* AutoTenV1Parser::returnStmt() {
  ReturnStmtContext *_localctx = _tracker.createInstance<ReturnStmtContext>(_ctx, getState());
  enterRule(_localctx, 130, AutoTenV1Parser::RuleReturnStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(731);
    match(AutoTenV1Parser::Return);
    setState(733);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 80)) & 21) != 0)) {
      setState(732);
      expressionList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakStmtContext ------------------------------------------------------------------

AutoTenV1Parser::BreakStmtContext::BreakStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::BreakStmtContext::Break() {
  return getToken(AutoTenV1Parser::Break, 0);
}

tree::TerminalNode* AutoTenV1Parser::BreakStmtContext::Identifier() {
  return getToken(AutoTenV1Parser::Identifier, 0);
}


size_t AutoTenV1Parser::BreakStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleBreakStmt;
}

void AutoTenV1Parser::BreakStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStmt(this);
}

void AutoTenV1Parser::BreakStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStmt(this);
}


std::any AutoTenV1Parser::BreakStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitBreakStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::BreakStmtContext* AutoTenV1Parser::breakStmt() {
  BreakStmtContext *_localctx = _tracker.createInstance<BreakStmtContext>(_ctx, getState());
  enterRule(_localctx, 132, AutoTenV1Parser::RuleBreakStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(735);
    match(AutoTenV1Parser::Break);
    setState(737);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Identifier) {
      setState(736);
      match(AutoTenV1Parser::Identifier);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContinueStmtContext ------------------------------------------------------------------

AutoTenV1Parser::ContinueStmtContext::ContinueStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::ContinueStmtContext::Continue() {
  return getToken(AutoTenV1Parser::Continue, 0);
}

tree::TerminalNode* AutoTenV1Parser::ContinueStmtContext::Identifier() {
  return getToken(AutoTenV1Parser::Identifier, 0);
}


size_t AutoTenV1Parser::ContinueStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleContinueStmt;
}

void AutoTenV1Parser::ContinueStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinueStmt(this);
}

void AutoTenV1Parser::ContinueStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinueStmt(this);
}


std::any AutoTenV1Parser::ContinueStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitContinueStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ContinueStmtContext* AutoTenV1Parser::continueStmt() {
  ContinueStmtContext *_localctx = _tracker.createInstance<ContinueStmtContext>(_ctx, getState());
  enterRule(_localctx, 134, AutoTenV1Parser::RuleContinueStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(739);
    match(AutoTenV1Parser::Continue);
    setState(741);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Identifier) {
      setState(740);
      match(AutoTenV1Parser::Identifier);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GotoStmtContext ------------------------------------------------------------------

AutoTenV1Parser::GotoStmtContext::GotoStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::GotoStmtContext::Goto() {
  return getToken(AutoTenV1Parser::Goto, 0);
}

tree::TerminalNode* AutoTenV1Parser::GotoStmtContext::Identifier() {
  return getToken(AutoTenV1Parser::Identifier, 0);
}


size_t AutoTenV1Parser::GotoStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleGotoStmt;
}

void AutoTenV1Parser::GotoStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGotoStmt(this);
}

void AutoTenV1Parser::GotoStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGotoStmt(this);
}


std::any AutoTenV1Parser::GotoStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitGotoStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::GotoStmtContext* AutoTenV1Parser::gotoStmt() {
  GotoStmtContext *_localctx = _tracker.createInstance<GotoStmtContext>(_ctx, getState());
  enterRule(_localctx, 136, AutoTenV1Parser::RuleGotoStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(743);
    match(AutoTenV1Parser::Goto);
    setState(744);
    match(AutoTenV1Parser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FallthroughStmtContext ------------------------------------------------------------------

AutoTenV1Parser::FallthroughStmtContext::FallthroughStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::FallthroughStmtContext::Fallthrough() {
  return getToken(AutoTenV1Parser::Fallthrough, 0);
}


size_t AutoTenV1Parser::FallthroughStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleFallthroughStmt;
}

void AutoTenV1Parser::FallthroughStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFallthroughStmt(this);
}

void AutoTenV1Parser::FallthroughStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFallthroughStmt(this);
}


std::any AutoTenV1Parser::FallthroughStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitFallthroughStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::FallthroughStmtContext* AutoTenV1Parser::fallthroughStmt() {
  FallthroughStmtContext *_localctx = _tracker.createInstance<FallthroughStmtContext>(_ctx, getState());
  enterRule(_localctx, 138, AutoTenV1Parser::RuleFallthroughStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(746);
    match(AutoTenV1Parser::Fallthrough);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStmtContext ------------------------------------------------------------------

AutoTenV1Parser::IfStmtContext::IfStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::IfStmtContext::If() {
  return getToken(AutoTenV1Parser::If, 0);
}

tree::TerminalNode* AutoTenV1Parser::IfStmtContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::IfStmtContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}

std::vector<AutoTenV1Parser::BlockContext *> AutoTenV1Parser::IfStmtContext::block() {
  return getRuleContexts<AutoTenV1Parser::BlockContext>();
}

AutoTenV1Parser::BlockContext* AutoTenV1Parser::IfStmtContext::block(size_t i) {
  return getRuleContext<AutoTenV1Parser::BlockContext>(i);
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::IfStmtContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}

AutoTenV1Parser::EosContext* AutoTenV1Parser::IfStmtContext::eos() {
  return getRuleContext<AutoTenV1Parser::EosContext>(0);
}

AutoTenV1Parser::SimpleStmtContext* AutoTenV1Parser::IfStmtContext::simpleStmt() {
  return getRuleContext<AutoTenV1Parser::SimpleStmtContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::IfStmtContext::Else() {
  return getToken(AutoTenV1Parser::Else, 0);
}

AutoTenV1Parser::IfStmtContext* AutoTenV1Parser::IfStmtContext::ifStmt() {
  return getRuleContext<AutoTenV1Parser::IfStmtContext>(0);
}


size_t AutoTenV1Parser::IfStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleIfStmt;
}

void AutoTenV1Parser::IfStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStmt(this);
}

void AutoTenV1Parser::IfStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStmt(this);
}


std::any AutoTenV1Parser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::IfStmtContext* AutoTenV1Parser::ifStmt() {
  IfStmtContext *_localctx = _tracker.createInstance<IfStmtContext>(_ctx, getState());
  enterRule(_localctx, 140, AutoTenV1Parser::RuleIfStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(748);
    match(AutoTenV1Parser::If);
    setState(749);
    match(AutoTenV1Parser::LeftParen);
    setState(758);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 80, _ctx)) {
    case 1: {
      setState(750);
      expression(0);
      break;
    }

    case 2: {
      setState(751);
      eos();
      setState(752);
      expression(0);
      break;
    }

    case 3: {
      setState(754);
      simpleStmt();
      setState(755);
      eos();
      setState(756);
      expression(0);
      break;
    }

    default:
      break;
    }
    setState(760);
    match(AutoTenV1Parser::RightParen);
    setState(761);
    block();
    setState(767);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Else) {
      setState(762);
      match(AutoTenV1Parser::Else);
      setState(765);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case AutoTenV1Parser::If: {
          setState(763);
          ifStmt();
          break;
        }

        case AutoTenV1Parser::LeftBrace: {
          setState(764);
          block();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SwitchStmtContext ------------------------------------------------------------------

AutoTenV1Parser::SwitchStmtContext::SwitchStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::ExprSwitchStmtContext* AutoTenV1Parser::SwitchStmtContext::exprSwitchStmt() {
  return getRuleContext<AutoTenV1Parser::ExprSwitchStmtContext>(0);
}

AutoTenV1Parser::TypeSwitchStmtContext* AutoTenV1Parser::SwitchStmtContext::typeSwitchStmt() {
  return getRuleContext<AutoTenV1Parser::TypeSwitchStmtContext>(0);
}


size_t AutoTenV1Parser::SwitchStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleSwitchStmt;
}

void AutoTenV1Parser::SwitchStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSwitchStmt(this);
}

void AutoTenV1Parser::SwitchStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSwitchStmt(this);
}


std::any AutoTenV1Parser::SwitchStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitSwitchStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::SwitchStmtContext* AutoTenV1Parser::switchStmt() {
  SwitchStmtContext *_localctx = _tracker.createInstance<SwitchStmtContext>(_ctx, getState());
  enterRule(_localctx, 142, AutoTenV1Parser::RuleSwitchStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(771);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 83, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(769);
      exprSwitchStmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(770);
      typeSwitchStmt();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprSwitchStmtContext ------------------------------------------------------------------

AutoTenV1Parser::ExprSwitchStmtContext::ExprSwitchStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::ExprSwitchStmtContext::Switch() {
  return getToken(AutoTenV1Parser::Switch, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExprSwitchStmtContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExprSwitchStmtContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExprSwitchStmtContext::LeftBrace() {
  return getToken(AutoTenV1Parser::LeftBrace, 0);
}

tree::TerminalNode* AutoTenV1Parser::ExprSwitchStmtContext::RightBrace() {
  return getToken(AutoTenV1Parser::RightBrace, 0);
}

AutoTenV1Parser::EosContext* AutoTenV1Parser::ExprSwitchStmtContext::eos() {
  return getRuleContext<AutoTenV1Parser::EosContext>(0);
}

std::vector<AutoTenV1Parser::ExprCaseClauseContext *> AutoTenV1Parser::ExprSwitchStmtContext::exprCaseClause() {
  return getRuleContexts<AutoTenV1Parser::ExprCaseClauseContext>();
}

AutoTenV1Parser::ExprCaseClauseContext* AutoTenV1Parser::ExprSwitchStmtContext::exprCaseClause(size_t i) {
  return getRuleContext<AutoTenV1Parser::ExprCaseClauseContext>(i);
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::ExprSwitchStmtContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}

AutoTenV1Parser::SimpleStmtContext* AutoTenV1Parser::ExprSwitchStmtContext::simpleStmt() {
  return getRuleContext<AutoTenV1Parser::SimpleStmtContext>(0);
}


size_t AutoTenV1Parser::ExprSwitchStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleExprSwitchStmt;
}

void AutoTenV1Parser::ExprSwitchStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprSwitchStmt(this);
}

void AutoTenV1Parser::ExprSwitchStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprSwitchStmt(this);
}


std::any AutoTenV1Parser::ExprSwitchStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitExprSwitchStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ExprSwitchStmtContext* AutoTenV1Parser::exprSwitchStmt() {
  ExprSwitchStmtContext *_localctx = _tracker.createInstance<ExprSwitchStmtContext>(_ctx, getState());
  enterRule(_localctx, 144, AutoTenV1Parser::RuleExprSwitchStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(773);
    match(AutoTenV1Parser::Switch);
    setState(774);
    match(AutoTenV1Parser::LeftParen);
    setState(785);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 87, _ctx)) {
    case 1: {
      setState(776);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 80)) & 21) != 0)) {
        setState(775);
        expression(0);
      }
      break;
    }

    case 2: {
      setState(779);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 80)) & 21) != 0)) {
        setState(778);
        simpleStmt();
      }
      setState(781);
      eos();
      setState(783);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 80)) & 21) != 0)) {
        setState(782);
        expression(0);
      }
      break;
    }

    default:
      break;
    }
    setState(787);
    match(AutoTenV1Parser::RightParen);
    setState(788);
    match(AutoTenV1Parser::LeftBrace);
    setState(792);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Case

    || _la == AutoTenV1Parser::Default) {
      setState(789);
      exprCaseClause();
      setState(794);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(795);
    match(AutoTenV1Parser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprCaseClauseContext ------------------------------------------------------------------

AutoTenV1Parser::ExprCaseClauseContext::ExprCaseClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::ExprSwitchCaseContext* AutoTenV1Parser::ExprCaseClauseContext::exprSwitchCase() {
  return getRuleContext<AutoTenV1Parser::ExprSwitchCaseContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::ExprCaseClauseContext::Colon() {
  return getToken(AutoTenV1Parser::Colon, 0);
}

AutoTenV1Parser::StatementListContext* AutoTenV1Parser::ExprCaseClauseContext::statementList() {
  return getRuleContext<AutoTenV1Parser::StatementListContext>(0);
}


size_t AutoTenV1Parser::ExprCaseClauseContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleExprCaseClause;
}

void AutoTenV1Parser::ExprCaseClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprCaseClause(this);
}

void AutoTenV1Parser::ExprCaseClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprCaseClause(this);
}


std::any AutoTenV1Parser::ExprCaseClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitExprCaseClause(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ExprCaseClauseContext* AutoTenV1Parser::exprCaseClause() {
  ExprCaseClauseContext *_localctx = _tracker.createInstance<ExprCaseClauseContext>(_ctx, getState());
  enterRule(_localctx, 146, AutoTenV1Parser::RuleExprCaseClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(797);
    exprSwitchCase();
    setState(798);
    match(AutoTenV1Parser::Colon);
    setState(800);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 692801123461365534) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 80)) & 23) != 0)) {
      setState(799);
      statementList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprSwitchCaseContext ------------------------------------------------------------------

AutoTenV1Parser::ExprSwitchCaseContext::ExprSwitchCaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::ExprSwitchCaseContext::Case() {
  return getToken(AutoTenV1Parser::Case, 0);
}

AutoTenV1Parser::ExpressionListContext* AutoTenV1Parser::ExprSwitchCaseContext::expressionList() {
  return getRuleContext<AutoTenV1Parser::ExpressionListContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::ExprSwitchCaseContext::Default() {
  return getToken(AutoTenV1Parser::Default, 0);
}


size_t AutoTenV1Parser::ExprSwitchCaseContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleExprSwitchCase;
}

void AutoTenV1Parser::ExprSwitchCaseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprSwitchCase(this);
}

void AutoTenV1Parser::ExprSwitchCaseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprSwitchCase(this);
}


std::any AutoTenV1Parser::ExprSwitchCaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitExprSwitchCase(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ExprSwitchCaseContext* AutoTenV1Parser::exprSwitchCase() {
  ExprSwitchCaseContext *_localctx = _tracker.createInstance<ExprSwitchCaseContext>(_ctx, getState());
  enterRule(_localctx, 148, AutoTenV1Parser::RuleExprSwitchCase);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(805);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Case: {
        enterOuterAlt(_localctx, 1);
        setState(802);
        match(AutoTenV1Parser::Case);
        setState(803);
        expressionList();
        break;
      }

      case AutoTenV1Parser::Default: {
        enterOuterAlt(_localctx, 2);
        setState(804);
        match(AutoTenV1Parser::Default);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeSwitchStmtContext ------------------------------------------------------------------

AutoTenV1Parser::TypeSwitchStmtContext::TypeSwitchStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::TypeSwitchStmtContext::Switch() {
  return getToken(AutoTenV1Parser::Switch, 0);
}

tree::TerminalNode* AutoTenV1Parser::TypeSwitchStmtContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::TypeSwitchStmtContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::TypeSwitchStmtContext::LeftBrace() {
  return getToken(AutoTenV1Parser::LeftBrace, 0);
}

tree::TerminalNode* AutoTenV1Parser::TypeSwitchStmtContext::RightBrace() {
  return getToken(AutoTenV1Parser::RightBrace, 0);
}

AutoTenV1Parser::TypeSwitchGuardContext* AutoTenV1Parser::TypeSwitchStmtContext::typeSwitchGuard() {
  return getRuleContext<AutoTenV1Parser::TypeSwitchGuardContext>(0);
}

AutoTenV1Parser::EosContext* AutoTenV1Parser::TypeSwitchStmtContext::eos() {
  return getRuleContext<AutoTenV1Parser::EosContext>(0);
}

AutoTenV1Parser::SimpleStmtContext* AutoTenV1Parser::TypeSwitchStmtContext::simpleStmt() {
  return getRuleContext<AutoTenV1Parser::SimpleStmtContext>(0);
}

std::vector<AutoTenV1Parser::TypeCaseClauseContext *> AutoTenV1Parser::TypeSwitchStmtContext::typeCaseClause() {
  return getRuleContexts<AutoTenV1Parser::TypeCaseClauseContext>();
}

AutoTenV1Parser::TypeCaseClauseContext* AutoTenV1Parser::TypeSwitchStmtContext::typeCaseClause(size_t i) {
  return getRuleContext<AutoTenV1Parser::TypeCaseClauseContext>(i);
}


size_t AutoTenV1Parser::TypeSwitchStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleTypeSwitchStmt;
}

void AutoTenV1Parser::TypeSwitchStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeSwitchStmt(this);
}

void AutoTenV1Parser::TypeSwitchStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeSwitchStmt(this);
}


std::any AutoTenV1Parser::TypeSwitchStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitTypeSwitchStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::TypeSwitchStmtContext* AutoTenV1Parser::typeSwitchStmt() {
  TypeSwitchStmtContext *_localctx = _tracker.createInstance<TypeSwitchStmtContext>(_ctx, getState());
  enterRule(_localctx, 150, AutoTenV1Parser::RuleTypeSwitchStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(807);
    match(AutoTenV1Parser::Switch);
    setState(808);
    match(AutoTenV1Parser::LeftParen);
    setState(817);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 91, _ctx)) {
    case 1: {
      setState(809);
      typeSwitchGuard();
      break;
    }

    case 2: {
      setState(810);
      eos();
      setState(811);
      typeSwitchGuard();
      break;
    }

    case 3: {
      setState(813);
      simpleStmt();
      setState(814);
      eos();
      setState(815);
      typeSwitchGuard();
      break;
    }

    default:
      break;
    }
    setState(819);
    match(AutoTenV1Parser::RightParen);
    setState(820);
    match(AutoTenV1Parser::LeftBrace);
    setState(824);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Case

    || _la == AutoTenV1Parser::Default) {
      setState(821);
      typeCaseClause();
      setState(826);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(827);
    match(AutoTenV1Parser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeSwitchGuardContext ------------------------------------------------------------------

AutoTenV1Parser::TypeSwitchGuardContext::TypeSwitchGuardContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::PrimaryExprContext* AutoTenV1Parser::TypeSwitchGuardContext::primaryExpr() {
  return getRuleContext<AutoTenV1Parser::PrimaryExprContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::TypeSwitchGuardContext::Dot() {
  return getToken(AutoTenV1Parser::Dot, 0);
}

tree::TerminalNode* AutoTenV1Parser::TypeSwitchGuardContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::TypeSwitchGuardContext::Type() {
  return getToken(AutoTenV1Parser::Type, 0);
}

tree::TerminalNode* AutoTenV1Parser::TypeSwitchGuardContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::TypeSwitchGuardContext::Identifier() {
  return getToken(AutoTenV1Parser::Identifier, 0);
}

tree::TerminalNode* AutoTenV1Parser::TypeSwitchGuardContext::DeclareAssign() {
  return getToken(AutoTenV1Parser::DeclareAssign, 0);
}


size_t AutoTenV1Parser::TypeSwitchGuardContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleTypeSwitchGuard;
}

void AutoTenV1Parser::TypeSwitchGuardContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeSwitchGuard(this);
}

void AutoTenV1Parser::TypeSwitchGuardContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeSwitchGuard(this);
}


std::any AutoTenV1Parser::TypeSwitchGuardContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitTypeSwitchGuard(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::TypeSwitchGuardContext* AutoTenV1Parser::typeSwitchGuard() {
  TypeSwitchGuardContext *_localctx = _tracker.createInstance<TypeSwitchGuardContext>(_ctx, getState());
  enterRule(_localctx, 152, AutoTenV1Parser::RuleTypeSwitchGuard);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(831);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 93, _ctx)) {
    case 1: {
      setState(829);
      match(AutoTenV1Parser::Identifier);
      setState(830);
      match(AutoTenV1Parser::DeclareAssign);
      break;
    }

    default:
      break;
    }
    setState(833);
    primaryExpr(0);
    setState(834);
    match(AutoTenV1Parser::Dot);
    setState(835);
    match(AutoTenV1Parser::LeftParen);
    setState(836);
    match(AutoTenV1Parser::Type);
    setState(837);
    match(AutoTenV1Parser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeCaseClauseContext ------------------------------------------------------------------

AutoTenV1Parser::TypeCaseClauseContext::TypeCaseClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::TypeSwitchCaseContext* AutoTenV1Parser::TypeCaseClauseContext::typeSwitchCase() {
  return getRuleContext<AutoTenV1Parser::TypeSwitchCaseContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::TypeCaseClauseContext::Colon() {
  return getToken(AutoTenV1Parser::Colon, 0);
}

AutoTenV1Parser::StatementListContext* AutoTenV1Parser::TypeCaseClauseContext::statementList() {
  return getRuleContext<AutoTenV1Parser::StatementListContext>(0);
}


size_t AutoTenV1Parser::TypeCaseClauseContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleTypeCaseClause;
}

void AutoTenV1Parser::TypeCaseClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeCaseClause(this);
}

void AutoTenV1Parser::TypeCaseClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeCaseClause(this);
}


std::any AutoTenV1Parser::TypeCaseClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitTypeCaseClause(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::TypeCaseClauseContext* AutoTenV1Parser::typeCaseClause() {
  TypeCaseClauseContext *_localctx = _tracker.createInstance<TypeCaseClauseContext>(_ctx, getState());
  enterRule(_localctx, 154, AutoTenV1Parser::RuleTypeCaseClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(839);
    typeSwitchCase();
    setState(840);
    match(AutoTenV1Parser::Colon);
    setState(842);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 692801123461365534) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 80)) & 23) != 0)) {
      setState(841);
      statementList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeSwitchCaseContext ------------------------------------------------------------------

AutoTenV1Parser::TypeSwitchCaseContext::TypeSwitchCaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::TypeSwitchCaseContext::Case() {
  return getToken(AutoTenV1Parser::Case, 0);
}

AutoTenV1Parser::TypeListContext* AutoTenV1Parser::TypeSwitchCaseContext::typeList() {
  return getRuleContext<AutoTenV1Parser::TypeListContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::TypeSwitchCaseContext::Default() {
  return getToken(AutoTenV1Parser::Default, 0);
}


size_t AutoTenV1Parser::TypeSwitchCaseContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleTypeSwitchCase;
}

void AutoTenV1Parser::TypeSwitchCaseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeSwitchCase(this);
}

void AutoTenV1Parser::TypeSwitchCaseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeSwitchCase(this);
}


std::any AutoTenV1Parser::TypeSwitchCaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitTypeSwitchCase(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::TypeSwitchCaseContext* AutoTenV1Parser::typeSwitchCase() {
  TypeSwitchCaseContext *_localctx = _tracker.createInstance<TypeSwitchCaseContext>(_ctx, getState());
  enterRule(_localctx, 156, AutoTenV1Parser::RuleTypeSwitchCase);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(847);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Case: {
        enterOuterAlt(_localctx, 1);
        setState(844);
        match(AutoTenV1Parser::Case);
        setState(845);
        typeList();
        break;
      }

      case AutoTenV1Parser::Default: {
        enterOuterAlt(_localctx, 2);
        setState(846);
        match(AutoTenV1Parser::Default);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeListContext ------------------------------------------------------------------

AutoTenV1Parser::TypeListContext::TypeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<AutoTenV1Parser::Type_Context *> AutoTenV1Parser::TypeListContext::type_() {
  return getRuleContexts<AutoTenV1Parser::Type_Context>();
}

AutoTenV1Parser::Type_Context* AutoTenV1Parser::TypeListContext::type_(size_t i) {
  return getRuleContext<AutoTenV1Parser::Type_Context>(i);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::TypeListContext::Nilptr() {
  return getTokens(AutoTenV1Parser::Nilptr);
}

tree::TerminalNode* AutoTenV1Parser::TypeListContext::Nilptr(size_t i) {
  return getToken(AutoTenV1Parser::Nilptr, i);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::TypeListContext::Comma() {
  return getTokens(AutoTenV1Parser::Comma);
}

tree::TerminalNode* AutoTenV1Parser::TypeListContext::Comma(size_t i) {
  return getToken(AutoTenV1Parser::Comma, i);
}


size_t AutoTenV1Parser::TypeListContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleTypeList;
}

void AutoTenV1Parser::TypeListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeList(this);
}

void AutoTenV1Parser::TypeListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeList(this);
}


std::any AutoTenV1Parser::TypeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitTypeList(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::TypeListContext* AutoTenV1Parser::typeList() {
  TypeListContext *_localctx = _tracker.createInstance<TypeListContext>(_ctx, getState());
  enterRule(_localctx, 158, AutoTenV1Parser::RuleTypeList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(851);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Int8:
      case AutoTenV1Parser::Int16:
      case AutoTenV1Parser::Int32:
      case AutoTenV1Parser::Int64:
      case AutoTenV1Parser::Float32:
      case AutoTenV1Parser::Float64:
      case AutoTenV1Parser::Char:
      case AutoTenV1Parser::Bool:
      case AutoTenV1Parser::String:
      case AutoTenV1Parser::Tensor:
      case AutoTenV1Parser::Void:
      case AutoTenV1Parser::Function:
      case AutoTenV1Parser::Struct:
      case AutoTenV1Parser::Impl:
      case AutoTenV1Parser::LeftParen:
      case AutoTenV1Parser::LeftBracket:
      case AutoTenV1Parser::Star:
      case AutoTenV1Parser::Map:
      case AutoTenV1Parser::Identifier: {
        setState(849);
        type_();
        break;
      }

      case AutoTenV1Parser::Nilptr: {
        setState(850);
        match(AutoTenV1Parser::Nilptr);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(860);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Comma) {
      setState(853);
      match(AutoTenV1Parser::Comma);
      setState(856);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case AutoTenV1Parser::Int8:
        case AutoTenV1Parser::Int16:
        case AutoTenV1Parser::Int32:
        case AutoTenV1Parser::Int64:
        case AutoTenV1Parser::Float32:
        case AutoTenV1Parser::Float64:
        case AutoTenV1Parser::Char:
        case AutoTenV1Parser::Bool:
        case AutoTenV1Parser::String:
        case AutoTenV1Parser::Tensor:
        case AutoTenV1Parser::Void:
        case AutoTenV1Parser::Function:
        case AutoTenV1Parser::Struct:
        case AutoTenV1Parser::Impl:
        case AutoTenV1Parser::LeftParen:
        case AutoTenV1Parser::LeftBracket:
        case AutoTenV1Parser::Star:
        case AutoTenV1Parser::Map:
        case AutoTenV1Parser::Identifier: {
          setState(854);
          type_();
          break;
        }

        case AutoTenV1Parser::Nilptr: {
          setState(855);
          match(AutoTenV1Parser::Nilptr);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(862);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForStmtContext ------------------------------------------------------------------

AutoTenV1Parser::ForStmtContext::ForStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::ForStmtContext::For() {
  return getToken(AutoTenV1Parser::For, 0);
}

tree::TerminalNode* AutoTenV1Parser::ForStmtContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::ForStmtContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}

AutoTenV1Parser::BlockContext* AutoTenV1Parser::ForStmtContext::block() {
  return getRuleContext<AutoTenV1Parser::BlockContext>(0);
}

AutoTenV1Parser::ForClauseContext* AutoTenV1Parser::ForStmtContext::forClause() {
  return getRuleContext<AutoTenV1Parser::ForClauseContext>(0);
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::ForStmtContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}


size_t AutoTenV1Parser::ForStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleForStmt;
}

void AutoTenV1Parser::ForStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForStmt(this);
}

void AutoTenV1Parser::ForStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForStmt(this);
}


std::any AutoTenV1Parser::ForStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitForStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ForStmtContext* AutoTenV1Parser::forStmt() {
  ForStmtContext *_localctx = _tracker.createInstance<ForStmtContext>(_ctx, getState());
  enterRule(_localctx, 160, AutoTenV1Parser::RuleForStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(863);
    match(AutoTenV1Parser::For);
    setState(864);
    match(AutoTenV1Parser::LeftParen);
    setState(869);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 100, _ctx)) {
    case 1: {
      setState(866);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 80)) & 21) != 0)) {
        setState(865);
        expression(0);
      }
      break;
    }

    case 2: {
      setState(868);
      forClause();
      break;
    }

    default:
      break;
    }
    setState(871);
    match(AutoTenV1Parser::RightParen);
    setState(872);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PforStmtContext ------------------------------------------------------------------

AutoTenV1Parser::PforStmtContext::PforStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::PforStmtContext::Pfor() {
  return getToken(AutoTenV1Parser::Pfor, 0);
}

tree::TerminalNode* AutoTenV1Parser::PforStmtContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::PforStmtContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}

AutoTenV1Parser::BlockContext* AutoTenV1Parser::PforStmtContext::block() {
  return getRuleContext<AutoTenV1Parser::BlockContext>(0);
}

AutoTenV1Parser::PforClauseContext* AutoTenV1Parser::PforStmtContext::pforClause() {
  return getRuleContext<AutoTenV1Parser::PforClauseContext>(0);
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::PforStmtContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}


size_t AutoTenV1Parser::PforStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RulePforStmt;
}

void AutoTenV1Parser::PforStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPforStmt(this);
}

void AutoTenV1Parser::PforStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPforStmt(this);
}


std::any AutoTenV1Parser::PforStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitPforStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::PforStmtContext* AutoTenV1Parser::pforStmt() {
  PforStmtContext *_localctx = _tracker.createInstance<PforStmtContext>(_ctx, getState());
  enterRule(_localctx, 162, AutoTenV1Parser::RulePforStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(874);
    match(AutoTenV1Parser::Pfor);
    setState(875);
    match(AutoTenV1Parser::LeftParen);
    setState(880);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 102, _ctx)) {
    case 1: {
      setState(877);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 80)) & 21) != 0)) {
        setState(876);
        expression(0);
      }
      break;
    }

    case 2: {
      setState(879);
      pforClause();
      break;
    }

    default:
      break;
    }
    setState(882);
    match(AutoTenV1Parser::RightParen);
    setState(883);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PforClauseContext ------------------------------------------------------------------

AutoTenV1Parser::PforClauseContext::PforClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AutoTenV1Parser::ShortVarDeclContext* AutoTenV1Parser::PforClauseContext::shortVarDecl() {
  return getRuleContext<AutoTenV1Parser::ShortVarDeclContext>(0);
}

std::vector<AutoTenV1Parser::EosContext *> AutoTenV1Parser::PforClauseContext::eos() {
  return getRuleContexts<AutoTenV1Parser::EosContext>();
}

AutoTenV1Parser::EosContext* AutoTenV1Parser::PforClauseContext::eos(size_t i) {
  return getRuleContext<AutoTenV1Parser::EosContext>(i);
}

std::vector<AutoTenV1Parser::OperandContext *> AutoTenV1Parser::PforClauseContext::operand() {
  return getRuleContexts<AutoTenV1Parser::OperandContext>();
}

AutoTenV1Parser::OperandContext* AutoTenV1Parser::PforClauseContext::operand(size_t i) {
  return getRuleContext<AutoTenV1Parser::OperandContext>(i);
}


size_t AutoTenV1Parser::PforClauseContext::getRuleIndex() const {
  return AutoTenV1Parser::RulePforClause;
}

void AutoTenV1Parser::PforClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPforClause(this);
}

void AutoTenV1Parser::PforClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPforClause(this);
}


std::any AutoTenV1Parser::PforClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitPforClause(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::PforClauseContext* AutoTenV1Parser::pforClause() {
  PforClauseContext *_localctx = _tracker.createInstance<PforClauseContext>(_ctx, getState());
  enterRule(_localctx, 164, AutoTenV1Parser::RulePforClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(885);
    shortVarDecl();
    setState(886);
    eos();
    setState(887);
    operand();
    setState(888);
    eos();
    setState(889);
    operand();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForClauseContext ------------------------------------------------------------------

AutoTenV1Parser::ForClauseContext::ForClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<AutoTenV1Parser::EosContext *> AutoTenV1Parser::ForClauseContext::eos() {
  return getRuleContexts<AutoTenV1Parser::EosContext>();
}

AutoTenV1Parser::EosContext* AutoTenV1Parser::ForClauseContext::eos(size_t i) {
  return getRuleContext<AutoTenV1Parser::EosContext>(i);
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::ForClauseContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}

std::vector<AutoTenV1Parser::SimpleStmtContext *> AutoTenV1Parser::ForClauseContext::simpleStmt() {
  return getRuleContexts<AutoTenV1Parser::SimpleStmtContext>();
}

AutoTenV1Parser::SimpleStmtContext* AutoTenV1Parser::ForClauseContext::simpleStmt(size_t i) {
  return getRuleContext<AutoTenV1Parser::SimpleStmtContext>(i);
}


size_t AutoTenV1Parser::ForClauseContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleForClause;
}

void AutoTenV1Parser::ForClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForClause(this);
}

void AutoTenV1Parser::ForClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForClause(this);
}


std::any AutoTenV1Parser::ForClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitForClause(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::ForClauseContext* AutoTenV1Parser::forClause() {
  ForClauseContext *_localctx = _tracker.createInstance<ForClauseContext>(_ctx, getState());
  enterRule(_localctx, 166, AutoTenV1Parser::RuleForClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(892);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 80)) & 21) != 0)) {
      setState(891);
      antlrcpp::downCast<ForClauseContext *>(_localctx)->initStmt = simpleStmt();
    }
    setState(894);
    eos();
    setState(896);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 80)) & 21) != 0)) {
      setState(895);
      expression(0);
    }
    setState(898);
    eos();
    setState(900);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 692518946265628446) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 80)) & 21) != 0)) {
      setState(899);
      antlrcpp::downCast<ForClauseContext *>(_localctx)->postStmt = simpleStmt();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStmtContext ------------------------------------------------------------------

AutoTenV1Parser::WhileStmtContext::WhileStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::WhileStmtContext::While() {
  return getToken(AutoTenV1Parser::While, 0);
}

tree::TerminalNode* AutoTenV1Parser::WhileStmtContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::WhileStmtContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}

AutoTenV1Parser::BlockContext* AutoTenV1Parser::WhileStmtContext::block() {
  return getRuleContext<AutoTenV1Parser::BlockContext>(0);
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::WhileStmtContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}


size_t AutoTenV1Parser::WhileStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleWhileStmt;
}

void AutoTenV1Parser::WhileStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhileStmt(this);
}

void AutoTenV1Parser::WhileStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhileStmt(this);
}


std::any AutoTenV1Parser::WhileStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitWhileStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::WhileStmtContext* AutoTenV1Parser::whileStmt() {
  WhileStmtContext *_localctx = _tracker.createInstance<WhileStmtContext>(_ctx, getState());
  enterRule(_localctx, 168, AutoTenV1Parser::RuleWhileStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(902);
    match(AutoTenV1Parser::While);
    setState(903);
    match(AutoTenV1Parser::LeftParen);

    setState(904);
    expression(0);
    setState(905);
    match(AutoTenV1Parser::RightParen);
    setState(906);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DoWhileStmtContext ------------------------------------------------------------------

AutoTenV1Parser::DoWhileStmtContext::DoWhileStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::DoWhileStmtContext::Do() {
  return getToken(AutoTenV1Parser::Do, 0);
}

AutoTenV1Parser::BlockContext* AutoTenV1Parser::DoWhileStmtContext::block() {
  return getRuleContext<AutoTenV1Parser::BlockContext>(0);
}

tree::TerminalNode* AutoTenV1Parser::DoWhileStmtContext::While() {
  return getToken(AutoTenV1Parser::While, 0);
}

tree::TerminalNode* AutoTenV1Parser::DoWhileStmtContext::LeftParen() {
  return getToken(AutoTenV1Parser::LeftParen, 0);
}

tree::TerminalNode* AutoTenV1Parser::DoWhileStmtContext::RightParen() {
  return getToken(AutoTenV1Parser::RightParen, 0);
}

AutoTenV1Parser::ExpressionContext* AutoTenV1Parser::DoWhileStmtContext::expression() {
  return getRuleContext<AutoTenV1Parser::ExpressionContext>(0);
}


size_t AutoTenV1Parser::DoWhileStmtContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleDoWhileStmt;
}

void AutoTenV1Parser::DoWhileStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDoWhileStmt(this);
}

void AutoTenV1Parser::DoWhileStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDoWhileStmt(this);
}


std::any AutoTenV1Parser::DoWhileStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitDoWhileStmt(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::DoWhileStmtContext* AutoTenV1Parser::doWhileStmt() {
  DoWhileStmtContext *_localctx = _tracker.createInstance<DoWhileStmtContext>(_ctx, getState());
  enterRule(_localctx, 170, AutoTenV1Parser::RuleDoWhileStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(908);
    match(AutoTenV1Parser::Do);
    setState(909);
    block();
    setState(910);
    match(AutoTenV1Parser::While);
    setState(911);
    match(AutoTenV1Parser::LeftParen);

    setState(912);
    expression(0);
    setState(913);
    match(AutoTenV1Parser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EosContext ------------------------------------------------------------------

AutoTenV1Parser::EosContext::EosContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AutoTenV1Parser::EosContext::Semi() {
  return getToken(AutoTenV1Parser::Semi, 0);
}


size_t AutoTenV1Parser::EosContext::getRuleIndex() const {
  return AutoTenV1Parser::RuleEos;
}

void AutoTenV1Parser::EosContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEos(this);
}

void AutoTenV1Parser::EosContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AutoTenV1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEos(this);
}


std::any AutoTenV1Parser::EosContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AutoTenV1ParserVisitor*>(visitor))
    return parserVisitor->visitEos(this);
  else
    return visitor->visitChildren(this);
}

AutoTenV1Parser::EosContext* AutoTenV1Parser::eos() {
  EosContext *_localctx = _tracker.createInstance<EosContext>(_ctx, getState());
  enterRule(_localctx, 172, AutoTenV1Parser::RuleEos);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(915);
    match(AutoTenV1Parser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool AutoTenV1Parser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 31: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);
    case 32: return primaryExprSempred(antlrcpp::downCast<PrimaryExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool AutoTenV1Parser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 5);
    case 1: return precpred(_ctx, 4);
    case 2: return precpred(_ctx, 3);
    case 3: return precpred(_ctx, 2);
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool AutoTenV1Parser::primaryExprSempred(PrimaryExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void AutoTenV1Parser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  autotenv1parserParserInitialize();
#else
  ::antlr4::internal::call_once(autotenv1parserParserOnceFlag, autotenv1parserParserInitialize);
#endif
}
