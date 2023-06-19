
// Generated from ../AutoTenV1Parser.g4 by ANTLR 4.13.0


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
      "typeSpec", "type_", "builtinType", "typeName", "typeLit", "arrayType", 
      "arrayLength", "elementType", "pointerType", "implType", "sliceType", 
      "mapType", "methodSpec", "functionType", "varDecl", "varSpec", "signature", 
      "result", "parameters", "index", "slice_", "typeAssertion", "arguments", 
      "methodExpr", "parameterDecl", "expression", "primaryExpr", "conversion", 
      "nonNamedType", "operand", "expressionList", "identifierList", "literal", 
      "basicLit", "operandName", "qualifiedIdent", "compositeLit", "literalType", 
      "literalValue", "elementList", "keyedElement", "key", "element", "structType", 
      "fieldDecl", "embeddedField", "functionLit", "functionDecl", "block", 
      "statementList", "statement", "simpleStmt", "expressionStmt", "incDecStmt", 
      "assignment", "assign_op", "shortVarDecl", "emptyStmt", "labeledStmt", 
      "returnStmt", "breakStmt", "continueStmt", "gotoStmt", "fallthroughStmt", 
      "ifStmt", "switchStmt", "exprSwitchStmt", "exprCaseClause", "exprSwitchCase", 
      "typeSwitchStmt", "typeSwitchGuard", "typeCaseClause", "typeSwitchCase", 
      "typeList", "forStmt", "forClause", "whileStmt", "doWhileStmt", "eos"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "'int8'", "'int16'", "'int32'", "'int64'", 
      "'float32'", "'float64'", "'char'", "'bool'", "'string'", "'Tensor'", 
      "'var'", "'false'", "'true'", "'void'", "'nil'", "'break'", "'continue'", 
      "'goto'", "'fallthrough'", "'if'", "'while'", "'for'", "'else'", "'do'", 
      "'switch'", "'case'", "'default'", "'func'", "'return'", "'struct'", 
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
      "Goto", "Fallthrough", "If", "While", "For", "Else", "Do", "Switch", 
      "Case", "Default", "Function", "Return", "Struct", "Type", "Package", 
      "Impl", "Public", "Sizeof", "LeftParen", "RightParen", "LeftBracket", 
      "RightBracket", "LeftBrace", "RightBrace", "Plus", "Minus", "Star", 
      "Div", "Mod", "Caret", "And", "Or", "Tilde", "Not", "Assign", "DeclareAssign", 
      "Less", "Greater", "LeftShift", "RightShift", "NotEqual", "Equal", 
      "LessEqual", "GreaterEqual", "AndAnd", "OrOr", "PlusPlus", "MinusMinus", 
      "Comma", "ArrowReturnType", "Colon", "Dot", "DotStar", "ArrowStar", 
      "At", "Semi", "Map", "Ellipsis", "Identifier", "DecimalLiteral", "OctalLiteral", 
      "HexadecimalLiteral", "BinaryLiteral", "Integersuffix", "UserDefinedIntegerLiteral", 
      "UserDefinedFloatingLiteral", "UserDefinedStringLiteral", "UserDefinedCharacterLiteral", 
      "Whitespace", "Newline", "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,96,830,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
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
  	77,2,78,7,78,2,79,7,79,2,80,7,80,2,81,7,81,2,82,7,82,2,83,7,83,1,0,1,
  	0,1,0,1,0,3,0,173,8,0,1,0,1,0,5,0,177,8,0,10,0,12,0,180,9,0,1,0,1,0,1,
  	1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,5,2,193,8,2,10,2,12,2,196,9,2,1,2,1,
  	2,1,2,1,2,3,2,202,8,2,1,2,1,2,1,3,1,3,3,3,208,8,3,1,4,1,4,1,4,1,4,1,4,
  	1,4,5,4,216,8,4,10,4,12,4,219,9,4,1,4,3,4,222,8,4,1,5,1,5,3,5,226,8,5,
  	1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,237,8,6,1,7,1,7,1,8,1,8,3,8,243,
  	8,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,252,8,9,1,10,1,10,1,10,1,10,1,10,
  	1,11,1,11,1,12,1,12,1,13,1,13,1,13,1,14,1,14,1,14,3,14,269,8,14,1,14,
  	5,14,272,8,14,10,14,12,14,275,9,14,1,14,1,14,1,15,1,15,1,15,1,15,1,16,
  	1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,3,17,295,8,17,
  	1,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,19,5,19,306,8,19,10,19,12,19,
  	309,9,19,1,19,3,19,312,8,19,1,20,1,20,1,20,1,20,3,20,318,8,20,1,20,1,
  	20,3,20,322,8,20,1,21,1,21,1,21,1,21,1,21,3,21,329,8,21,1,22,1,22,3,22,
  	333,8,22,1,23,1,23,1,23,1,23,5,23,339,8,23,10,23,12,23,342,9,23,1,23,
  	3,23,345,8,23,3,23,347,8,23,1,23,1,23,1,24,1,24,1,24,1,24,1,25,1,25,3,
  	25,357,8,25,1,25,1,25,3,25,361,8,25,1,25,3,25,364,8,25,1,25,1,25,1,25,
  	1,25,1,25,3,25,371,8,25,1,25,1,25,1,26,1,26,1,26,1,26,1,26,1,27,1,27,
  	1,27,1,27,1,27,3,27,385,8,27,3,27,387,8,27,1,27,3,27,390,8,27,1,27,3,
  	27,393,8,27,3,27,395,8,27,1,27,1,27,1,28,1,28,1,28,1,28,1,29,3,29,404,
  	8,29,1,29,3,29,407,8,29,1,29,1,29,1,30,1,30,1,30,1,30,3,30,415,8,30,1,
  	30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,
  	30,5,30,432,8,30,10,30,12,30,435,9,30,1,31,1,31,1,31,1,31,3,31,441,8,
  	31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,3,31,450,8,31,5,31,452,8,31,10,
  	31,12,31,455,9,31,1,32,1,32,1,32,1,32,3,32,461,8,32,1,32,1,32,1,33,1,
  	33,1,33,1,33,1,33,3,33,470,8,33,1,34,1,34,1,34,1,34,1,34,1,34,3,34,478,
  	8,34,1,35,1,35,1,35,5,35,483,8,35,10,35,12,35,486,9,35,1,36,1,36,1,36,
  	5,36,491,8,36,10,36,12,36,494,9,36,1,37,1,37,1,37,3,37,499,8,37,1,38,
  	1,38,1,39,1,39,1,40,1,40,1,40,1,40,1,41,1,41,1,41,1,42,1,42,1,42,1,42,
  	1,42,1,42,1,42,1,42,1,42,1,42,3,42,522,8,42,1,43,1,43,1,43,3,43,527,8,
  	43,3,43,529,8,43,1,43,1,43,1,44,1,44,1,44,5,44,536,8,44,10,44,12,44,539,
  	9,44,1,45,1,45,1,45,3,45,544,8,45,1,45,1,45,1,46,1,46,3,46,550,8,46,1,
  	47,1,47,3,47,554,8,47,1,48,1,48,1,48,1,48,1,48,5,48,561,8,48,10,48,12,
  	48,564,9,48,1,48,1,48,1,49,1,49,1,49,1,49,3,49,572,8,49,1,49,3,49,575,
  	8,49,1,50,3,50,578,8,50,1,50,1,50,1,51,5,51,583,8,51,10,51,12,51,586,
  	9,51,1,51,1,51,1,51,1,51,1,52,1,52,1,52,1,52,3,52,596,8,52,1,53,1,53,
  	3,53,600,8,53,1,53,1,53,1,54,3,54,605,8,54,1,54,1,54,1,54,4,54,610,8,
  	54,11,54,12,54,611,1,55,1,55,1,55,1,55,1,55,1,55,1,55,1,55,1,55,1,55,
  	1,55,1,55,1,55,1,55,3,55,628,8,55,1,56,1,56,1,56,1,56,3,56,634,8,56,1,
  	57,1,57,1,58,1,58,1,58,1,59,1,59,1,59,1,59,1,60,3,60,646,8,60,1,60,1,
  	60,1,61,1,61,1,61,1,61,1,62,1,62,1,63,1,63,1,63,3,63,659,8,63,1,64,1,
  	64,3,64,663,8,64,1,65,1,65,3,65,667,8,65,1,66,1,66,3,66,671,8,66,1,67,
  	1,67,1,67,1,68,1,68,1,69,1,69,1,69,1,69,1,69,1,69,1,69,1,69,1,69,1,69,
  	3,69,688,8,69,1,69,1,69,1,69,1,69,1,69,3,69,695,8,69,3,69,697,8,69,1,
  	70,1,70,3,70,701,8,70,1,71,1,71,1,71,3,71,706,8,71,1,71,3,71,709,8,71,
  	1,71,1,71,3,71,713,8,71,3,71,715,8,71,1,71,1,71,1,71,5,71,720,8,71,10,
  	71,12,71,723,9,71,1,71,1,71,1,72,1,72,1,72,3,72,730,8,72,1,73,1,73,1,
  	73,3,73,735,8,73,1,74,1,74,1,74,1,74,1,74,1,74,1,74,1,74,1,74,1,74,3,
  	74,747,8,74,1,74,1,74,1,74,5,74,752,8,74,10,74,12,74,755,9,74,1,74,1,
  	74,1,75,1,75,3,75,761,8,75,1,75,1,75,1,75,1,75,1,75,1,75,1,76,1,76,1,
  	76,3,76,772,8,76,1,77,1,77,1,77,3,77,777,8,77,1,78,1,78,3,78,781,8,78,
  	1,78,1,78,1,78,3,78,786,8,78,5,78,788,8,78,10,78,12,78,791,9,78,1,79,
  	1,79,1,79,3,79,796,8,79,1,79,3,79,799,8,79,1,79,1,79,1,79,1,80,3,80,805,
  	8,80,1,80,1,80,3,80,809,8,80,1,80,1,80,3,80,813,8,80,1,81,1,81,1,81,1,
  	81,1,81,1,81,1,82,1,82,1,82,1,82,1,82,1,82,1,82,1,83,1,83,1,83,0,2,60,
  	62,84,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,
  	46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,
  	92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,
  	130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,
  	166,0,8,2,0,8,17,21,21,3,0,49,51,54,55,58,58,3,0,51,53,55,55,63,64,3,
  	0,49,50,54,54,56,56,2,0,61,62,65,68,2,0,1,4,22,22,1,0,71,71,2,0,49,56,
  	63,64,876,0,168,1,0,0,0,2,183,1,0,0,0,4,188,1,0,0,0,6,207,1,0,0,0,8,209,
  	1,0,0,0,10,223,1,0,0,0,12,236,1,0,0,0,14,238,1,0,0,0,16,242,1,0,0,0,18,
  	251,1,0,0,0,20,253,1,0,0,0,22,258,1,0,0,0,24,260,1,0,0,0,26,262,1,0,0,
  	0,28,265,1,0,0,0,30,278,1,0,0,0,32,282,1,0,0,0,34,294,1,0,0,0,36,296,
  	1,0,0,0,38,299,1,0,0,0,40,313,1,0,0,0,42,328,1,0,0,0,44,332,1,0,0,0,46,
  	334,1,0,0,0,48,350,1,0,0,0,50,354,1,0,0,0,52,374,1,0,0,0,54,379,1,0,0,
  	0,56,398,1,0,0,0,58,403,1,0,0,0,60,414,1,0,0,0,62,440,1,0,0,0,64,456,
  	1,0,0,0,66,469,1,0,0,0,68,477,1,0,0,0,70,479,1,0,0,0,72,487,1,0,0,0,74,
  	498,1,0,0,0,76,500,1,0,0,0,78,502,1,0,0,0,80,504,1,0,0,0,82,508,1,0,0,
  	0,84,521,1,0,0,0,86,523,1,0,0,0,88,532,1,0,0,0,90,543,1,0,0,0,92,549,
  	1,0,0,0,94,553,1,0,0,0,96,555,1,0,0,0,98,571,1,0,0,0,100,577,1,0,0,0,
  	102,584,1,0,0,0,104,591,1,0,0,0,106,597,1,0,0,0,108,609,1,0,0,0,110,627,
  	1,0,0,0,112,633,1,0,0,0,114,635,1,0,0,0,116,637,1,0,0,0,118,640,1,0,0,
  	0,120,645,1,0,0,0,122,649,1,0,0,0,124,653,1,0,0,0,126,655,1,0,0,0,128,
  	660,1,0,0,0,130,664,1,0,0,0,132,668,1,0,0,0,134,672,1,0,0,0,136,675,1,
  	0,0,0,138,677,1,0,0,0,140,700,1,0,0,0,142,702,1,0,0,0,144,726,1,0,0,0,
  	146,734,1,0,0,0,148,736,1,0,0,0,150,760,1,0,0,0,152,768,1,0,0,0,154,776,
  	1,0,0,0,156,780,1,0,0,0,158,792,1,0,0,0,160,804,1,0,0,0,162,814,1,0,0,
  	0,164,820,1,0,0,0,166,827,1,0,0,0,168,169,3,2,1,0,169,178,3,166,83,0,
  	170,173,3,104,52,0,171,173,3,6,3,0,172,170,1,0,0,0,172,171,1,0,0,0,173,
  	174,1,0,0,0,174,175,3,166,83,0,175,177,1,0,0,0,176,172,1,0,0,0,177,180,
  	1,0,0,0,178,176,1,0,0,0,178,179,1,0,0,0,179,181,1,0,0,0,180,178,1,0,0,
  	0,181,182,5,0,0,1,182,1,1,0,0,0,183,184,5,79,0,0,184,185,5,39,0,0,185,
  	186,5,59,0,0,186,187,5,4,0,0,187,3,1,0,0,0,188,189,5,79,0,0,189,194,5,
  	83,0,0,190,191,9,0,0,0,191,193,5,83,0,0,192,190,1,0,0,0,193,196,1,0,0,
  	0,194,192,1,0,0,0,194,195,1,0,0,0,195,201,1,0,0,0,196,194,1,0,0,0,197,
  	198,5,59,0,0,198,202,5,20,0,0,199,202,5,19,0,0,200,202,5,4,0,0,201,197,
  	1,0,0,0,201,199,1,0,0,0,201,200,1,0,0,0,201,202,1,0,0,0,202,203,1,0,0,
  	0,203,204,5,80,0,0,204,5,1,0,0,0,205,208,3,8,4,0,206,208,3,38,19,0,207,
  	205,1,0,0,0,207,206,1,0,0,0,208,7,1,0,0,0,209,221,5,38,0,0,210,222,3,
  	10,5,0,211,217,5,43,0,0,212,213,3,10,5,0,213,214,3,166,83,0,214,216,1,
  	0,0,0,215,212,1,0,0,0,216,219,1,0,0,0,217,215,1,0,0,0,217,218,1,0,0,0,
  	218,220,1,0,0,0,219,217,1,0,0,0,220,222,5,44,0,0,221,210,1,0,0,0,221,
  	211,1,0,0,0,222,9,1,0,0,0,223,225,5,83,0,0,224,226,5,59,0,0,225,224,1,
  	0,0,0,225,226,1,0,0,0,226,227,1,0,0,0,227,228,3,12,6,0,228,11,1,0,0,0,
  	229,237,3,16,8,0,230,237,3,18,9,0,231,232,5,43,0,0,232,233,3,12,6,0,233,
  	234,5,44,0,0,234,237,1,0,0,0,235,237,3,14,7,0,236,229,1,0,0,0,236,230,
  	1,0,0,0,236,231,1,0,0,0,236,235,1,0,0,0,237,13,1,0,0,0,238,239,7,0,0,
  	0,239,15,1,0,0,0,240,243,3,80,40,0,241,243,5,83,0,0,242,240,1,0,0,0,242,
  	241,1,0,0,0,243,17,1,0,0,0,244,252,3,20,10,0,245,252,3,96,48,0,246,252,
  	3,26,13,0,247,252,3,36,18,0,248,252,3,28,14,0,249,252,3,30,15,0,250,252,
  	3,32,16,0,251,244,1,0,0,0,251,245,1,0,0,0,251,246,1,0,0,0,251,247,1,0,
  	0,0,251,248,1,0,0,0,251,249,1,0,0,0,251,250,1,0,0,0,252,19,1,0,0,0,253,
  	254,5,45,0,0,254,255,3,22,11,0,255,256,5,46,0,0,256,257,3,24,12,0,257,
  	21,1,0,0,0,258,259,3,60,30,0,259,23,1,0,0,0,260,261,3,12,6,0,261,25,1,
  	0,0,0,262,263,5,51,0,0,263,264,3,12,6,0,264,27,1,0,0,0,265,266,5,40,0,
  	0,266,273,5,47,0,0,267,269,5,41,0,0,268,267,1,0,0,0,268,269,1,0,0,0,269,
  	270,1,0,0,0,270,272,3,102,51,0,271,268,1,0,0,0,272,275,1,0,0,0,273,271,
  	1,0,0,0,273,274,1,0,0,0,274,276,1,0,0,0,275,273,1,0,0,0,276,277,5,48,
  	0,0,277,29,1,0,0,0,278,279,5,45,0,0,279,280,5,46,0,0,280,281,3,24,12,
  	0,281,31,1,0,0,0,282,283,5,81,0,0,283,284,5,45,0,0,284,285,3,12,6,0,285,
  	286,5,46,0,0,286,287,3,24,12,0,287,33,1,0,0,0,288,289,5,83,0,0,289,290,
  	3,46,23,0,290,291,3,44,22,0,291,295,1,0,0,0,292,293,5,83,0,0,293,295,
  	3,46,23,0,294,288,1,0,0,0,294,292,1,0,0,0,295,35,1,0,0,0,296,297,5,35,
  	0,0,297,298,3,42,21,0,298,37,1,0,0,0,299,311,5,18,0,0,300,312,3,40,20,
  	0,301,307,5,43,0,0,302,303,3,40,20,0,303,304,3,166,83,0,304,306,1,0,0,
  	0,305,302,1,0,0,0,306,309,1,0,0,0,307,305,1,0,0,0,307,308,1,0,0,0,308,
  	310,1,0,0,0,309,307,1,0,0,0,310,312,5,44,0,0,311,300,1,0,0,0,311,301,
  	1,0,0,0,312,39,1,0,0,0,313,321,3,72,36,0,314,317,3,12,6,0,315,316,5,59,
  	0,0,316,318,3,70,35,0,317,315,1,0,0,0,317,318,1,0,0,0,318,322,1,0,0,0,
  	319,320,5,59,0,0,320,322,3,70,35,0,321,314,1,0,0,0,321,319,1,0,0,0,322,
  	41,1,0,0,0,323,324,3,46,23,0,324,325,5,74,0,0,325,326,3,44,22,0,326,329,
  	1,0,0,0,327,329,3,46,23,0,328,323,1,0,0,0,328,327,1,0,0,0,329,43,1,0,
  	0,0,330,333,3,46,23,0,331,333,3,12,6,0,332,330,1,0,0,0,332,331,1,0,0,
  	0,333,45,1,0,0,0,334,346,5,43,0,0,335,340,3,58,29,0,336,337,5,73,0,0,
  	337,339,3,58,29,0,338,336,1,0,0,0,339,342,1,0,0,0,340,338,1,0,0,0,340,
  	341,1,0,0,0,341,344,1,0,0,0,342,340,1,0,0,0,343,345,5,73,0,0,344,343,
  	1,0,0,0,344,345,1,0,0,0,345,347,1,0,0,0,346,335,1,0,0,0,346,347,1,0,0,
  	0,347,348,1,0,0,0,348,349,5,44,0,0,349,47,1,0,0,0,350,351,5,45,0,0,351,
  	352,3,60,30,0,352,353,5,46,0,0,353,49,1,0,0,0,354,370,5,45,0,0,355,357,
  	3,60,30,0,356,355,1,0,0,0,356,357,1,0,0,0,357,358,1,0,0,0,358,360,5,75,
  	0,0,359,361,3,60,30,0,360,359,1,0,0,0,360,361,1,0,0,0,361,371,1,0,0,0,
  	362,364,3,60,30,0,363,362,1,0,0,0,363,364,1,0,0,0,364,365,1,0,0,0,365,
  	366,5,75,0,0,366,367,3,60,30,0,367,368,5,75,0,0,368,369,3,60,30,0,369,
  	371,1,0,0,0,370,356,1,0,0,0,370,363,1,0,0,0,371,372,1,0,0,0,372,373,5,
  	46,0,0,373,51,1,0,0,0,374,375,5,76,0,0,375,376,5,43,0,0,376,377,3,12,
  	6,0,377,378,5,44,0,0,378,53,1,0,0,0,379,394,5,43,0,0,380,387,3,70,35,
  	0,381,384,3,66,33,0,382,383,5,73,0,0,383,385,3,70,35,0,384,382,1,0,0,
  	0,384,385,1,0,0,0,385,387,1,0,0,0,386,380,1,0,0,0,386,381,1,0,0,0,387,
  	389,1,0,0,0,388,390,5,82,0,0,389,388,1,0,0,0,389,390,1,0,0,0,390,392,
  	1,0,0,0,391,393,5,73,0,0,392,391,1,0,0,0,392,393,1,0,0,0,393,395,1,0,
  	0,0,394,386,1,0,0,0,394,395,1,0,0,0,395,396,1,0,0,0,396,397,5,44,0,0,
  	397,55,1,0,0,0,398,399,3,66,33,0,399,400,5,76,0,0,400,401,5,83,0,0,401,
  	57,1,0,0,0,402,404,3,72,36,0,403,402,1,0,0,0,403,404,1,0,0,0,404,406,
  	1,0,0,0,405,407,5,82,0,0,406,405,1,0,0,0,406,407,1,0,0,0,407,408,1,0,
  	0,0,408,409,3,12,6,0,409,59,1,0,0,0,410,411,6,30,-1,0,411,415,3,62,31,
  	0,412,413,7,1,0,0,413,415,3,60,30,6,414,410,1,0,0,0,414,412,1,0,0,0,415,
  	433,1,0,0,0,416,417,10,5,0,0,417,418,7,2,0,0,418,432,3,60,30,6,419,420,
  	10,4,0,0,420,421,7,3,0,0,421,432,3,60,30,5,422,423,10,3,0,0,423,424,7,
  	4,0,0,424,432,3,60,30,4,425,426,10,2,0,0,426,427,5,69,0,0,427,432,3,60,
  	30,3,428,429,10,1,0,0,429,430,5,70,0,0,430,432,3,60,30,2,431,416,1,0,
  	0,0,431,419,1,0,0,0,431,422,1,0,0,0,431,425,1,0,0,0,431,428,1,0,0,0,432,
  	435,1,0,0,0,433,431,1,0,0,0,433,434,1,0,0,0,434,61,1,0,0,0,435,433,1,
  	0,0,0,436,437,6,31,-1,0,437,441,3,68,34,0,438,441,3,64,32,0,439,441,3,
  	56,28,0,440,436,1,0,0,0,440,438,1,0,0,0,440,439,1,0,0,0,441,453,1,0,0,
  	0,442,449,10,1,0,0,443,444,5,76,0,0,444,450,5,83,0,0,445,450,3,48,24,
  	0,446,450,3,50,25,0,447,450,3,52,26,0,448,450,3,54,27,0,449,443,1,0,0,
  	0,449,445,1,0,0,0,449,446,1,0,0,0,449,447,1,0,0,0,449,448,1,0,0,0,450,
  	452,1,0,0,0,451,442,1,0,0,0,452,455,1,0,0,0,453,451,1,0,0,0,453,454,1,
  	0,0,0,454,63,1,0,0,0,455,453,1,0,0,0,456,457,3,66,33,0,457,458,5,43,0,
  	0,458,460,3,60,30,0,459,461,5,73,0,0,460,459,1,0,0,0,460,461,1,0,0,0,
  	461,462,1,0,0,0,462,463,5,44,0,0,463,65,1,0,0,0,464,470,3,18,9,0,465,
  	466,5,43,0,0,466,467,3,66,33,0,467,468,5,44,0,0,468,470,1,0,0,0,469,464,
  	1,0,0,0,469,465,1,0,0,0,470,67,1,0,0,0,471,478,3,74,37,0,472,478,3,78,
  	39,0,473,474,5,43,0,0,474,475,3,60,30,0,475,476,5,44,0,0,476,478,1,0,
  	0,0,477,471,1,0,0,0,477,472,1,0,0,0,477,473,1,0,0,0,478,69,1,0,0,0,479,
  	484,3,60,30,0,480,481,5,73,0,0,481,483,3,60,30,0,482,480,1,0,0,0,483,
  	486,1,0,0,0,484,482,1,0,0,0,484,485,1,0,0,0,485,71,1,0,0,0,486,484,1,
  	0,0,0,487,492,5,83,0,0,488,489,5,73,0,0,489,491,5,83,0,0,490,488,1,0,
  	0,0,491,494,1,0,0,0,492,490,1,0,0,0,492,493,1,0,0,0,493,73,1,0,0,0,494,
  	492,1,0,0,0,495,499,3,76,38,0,496,499,3,82,41,0,497,499,3,102,51,0,498,
  	495,1,0,0,0,498,496,1,0,0,0,498,497,1,0,0,0,499,75,1,0,0,0,500,501,7,
  	5,0,0,501,77,1,0,0,0,502,503,5,83,0,0,503,79,1,0,0,0,504,505,5,83,0,0,
  	505,506,5,76,0,0,506,507,5,83,0,0,507,81,1,0,0,0,508,509,3,84,42,0,509,
  	510,3,86,43,0,510,83,1,0,0,0,511,522,3,96,48,0,512,522,3,20,10,0,513,
  	514,3,24,12,0,514,515,5,45,0,0,515,516,5,82,0,0,516,517,5,46,0,0,517,
  	522,1,0,0,0,518,522,3,30,15,0,519,522,3,32,16,0,520,522,3,16,8,0,521,
  	511,1,0,0,0,521,512,1,0,0,0,521,513,1,0,0,0,521,518,1,0,0,0,521,519,1,
  	0,0,0,521,520,1,0,0,0,522,85,1,0,0,0,523,528,5,47,0,0,524,526,3,88,44,
  	0,525,527,5,73,0,0,526,525,1,0,0,0,526,527,1,0,0,0,527,529,1,0,0,0,528,
  	524,1,0,0,0,528,529,1,0,0,0,529,530,1,0,0,0,530,531,5,48,0,0,531,87,1,
  	0,0,0,532,537,3,90,45,0,533,534,5,73,0,0,534,536,3,90,45,0,535,533,1,
  	0,0,0,536,539,1,0,0,0,537,535,1,0,0,0,537,538,1,0,0,0,538,89,1,0,0,0,
  	539,537,1,0,0,0,540,541,3,92,46,0,541,542,5,75,0,0,542,544,1,0,0,0,543,
  	540,1,0,0,0,543,544,1,0,0,0,544,545,1,0,0,0,545,546,3,94,47,0,546,91,
  	1,0,0,0,547,550,3,60,30,0,548,550,3,86,43,0,549,547,1,0,0,0,549,548,1,
  	0,0,0,550,93,1,0,0,0,551,554,3,60,30,0,552,554,3,86,43,0,553,551,1,0,
  	0,0,553,552,1,0,0,0,554,95,1,0,0,0,555,556,5,37,0,0,556,562,5,47,0,0,
  	557,558,3,98,49,0,558,559,3,166,83,0,559,561,1,0,0,0,560,557,1,0,0,0,
  	561,564,1,0,0,0,562,560,1,0,0,0,562,563,1,0,0,0,563,565,1,0,0,0,564,562,
  	1,0,0,0,565,566,5,48,0,0,566,97,1,0,0,0,567,568,3,72,36,0,568,569,3,12,
  	6,0,569,572,1,0,0,0,570,572,3,100,50,0,571,567,1,0,0,0,571,570,1,0,0,
  	0,572,574,1,0,0,0,573,575,5,4,0,0,574,573,1,0,0,0,574,575,1,0,0,0,575,
  	99,1,0,0,0,576,578,5,51,0,0,577,576,1,0,0,0,577,578,1,0,0,0,578,579,1,
  	0,0,0,579,580,3,16,8,0,580,101,1,0,0,0,581,583,3,4,2,0,582,581,1,0,0,
  	0,583,586,1,0,0,0,584,582,1,0,0,0,584,585,1,0,0,0,585,587,1,0,0,0,586,
  	584,1,0,0,0,587,588,5,35,0,0,588,589,3,42,21,0,589,590,3,106,53,0,590,
  	103,1,0,0,0,591,592,5,35,0,0,592,593,5,83,0,0,593,595,3,42,21,0,594,596,
  	3,106,53,0,595,594,1,0,0,0,595,596,1,0,0,0,596,105,1,0,0,0,597,599,5,
  	47,0,0,598,600,3,108,54,0,599,598,1,0,0,0,599,600,1,0,0,0,600,601,1,0,
  	0,0,601,602,5,48,0,0,602,107,1,0,0,0,603,605,5,80,0,0,604,603,1,0,0,0,
  	604,605,1,0,0,0,605,606,1,0,0,0,606,607,3,110,55,0,607,608,3,166,83,0,
  	608,610,1,0,0,0,609,604,1,0,0,0,610,611,1,0,0,0,611,609,1,0,0,0,611,612,
  	1,0,0,0,612,109,1,0,0,0,613,628,3,6,3,0,614,628,3,126,63,0,615,628,3,
  	112,56,0,616,628,3,128,64,0,617,628,3,130,65,0,618,628,3,132,66,0,619,
  	628,3,134,67,0,620,628,3,136,68,0,621,628,3,106,53,0,622,628,3,138,69,
  	0,623,628,3,140,70,0,624,628,3,158,79,0,625,628,3,162,81,0,626,628,3,
  	164,82,0,627,613,1,0,0,0,627,614,1,0,0,0,627,615,1,0,0,0,627,616,1,0,
  	0,0,627,617,1,0,0,0,627,618,1,0,0,0,627,619,1,0,0,0,627,620,1,0,0,0,627,
  	621,1,0,0,0,627,622,1,0,0,0,627,623,1,0,0,0,627,624,1,0,0,0,627,625,1,
  	0,0,0,627,626,1,0,0,0,628,111,1,0,0,0,629,634,3,116,58,0,630,634,3,118,
  	59,0,631,634,3,114,57,0,632,634,3,122,61,0,633,629,1,0,0,0,633,630,1,
  	0,0,0,633,631,1,0,0,0,633,632,1,0,0,0,634,113,1,0,0,0,635,636,3,60,30,
  	0,636,115,1,0,0,0,637,638,3,60,30,0,638,639,7,6,0,0,639,117,1,0,0,0,640,
  	641,3,70,35,0,641,642,3,120,60,0,642,643,3,70,35,0,643,119,1,0,0,0,644,
  	646,7,7,0,0,645,644,1,0,0,0,645,646,1,0,0,0,646,647,1,0,0,0,647,648,5,
  	66,0,0,648,121,1,0,0,0,649,650,3,72,36,0,650,651,5,60,0,0,651,652,3,70,
  	35,0,652,123,1,0,0,0,653,654,5,80,0,0,654,125,1,0,0,0,655,656,5,83,0,
  	0,656,658,5,75,0,0,657,659,3,110,55,0,658,657,1,0,0,0,658,659,1,0,0,0,
  	659,127,1,0,0,0,660,662,5,36,0,0,661,663,3,70,35,0,662,661,1,0,0,0,662,
  	663,1,0,0,0,663,129,1,0,0,0,664,666,5,23,0,0,665,667,5,83,0,0,666,665,
  	1,0,0,0,666,667,1,0,0,0,667,131,1,0,0,0,668,670,5,24,0,0,669,671,5,83,
  	0,0,670,669,1,0,0,0,670,671,1,0,0,0,671,133,1,0,0,0,672,673,5,25,0,0,
  	673,674,5,83,0,0,674,135,1,0,0,0,675,676,5,26,0,0,676,137,1,0,0,0,677,
  	678,5,27,0,0,678,687,5,43,0,0,679,688,3,60,30,0,680,681,3,166,83,0,681,
  	682,3,60,30,0,682,688,1,0,0,0,683,684,3,112,56,0,684,685,3,166,83,0,685,
  	686,3,60,30,0,686,688,1,0,0,0,687,679,1,0,0,0,687,680,1,0,0,0,687,683,
  	1,0,0,0,688,689,1,0,0,0,689,690,5,44,0,0,690,696,3,106,53,0,691,694,5,
  	30,0,0,692,695,3,138,69,0,693,695,3,106,53,0,694,692,1,0,0,0,694,693,
  	1,0,0,0,695,697,1,0,0,0,696,691,1,0,0,0,696,697,1,0,0,0,697,139,1,0,0,
  	0,698,701,3,142,71,0,699,701,3,148,74,0,700,698,1,0,0,0,700,699,1,0,0,
  	0,701,141,1,0,0,0,702,703,5,32,0,0,703,714,5,43,0,0,704,706,3,60,30,0,
  	705,704,1,0,0,0,705,706,1,0,0,0,706,715,1,0,0,0,707,709,3,112,56,0,708,
  	707,1,0,0,0,708,709,1,0,0,0,709,710,1,0,0,0,710,712,3,166,83,0,711,713,
  	3,60,30,0,712,711,1,0,0,0,712,713,1,0,0,0,713,715,1,0,0,0,714,705,1,0,
  	0,0,714,708,1,0,0,0,715,716,1,0,0,0,716,717,5,44,0,0,717,721,5,47,0,0,
  	718,720,3,144,72,0,719,718,1,0,0,0,720,723,1,0,0,0,721,719,1,0,0,0,721,
  	722,1,0,0,0,722,724,1,0,0,0,723,721,1,0,0,0,724,725,5,48,0,0,725,143,
  	1,0,0,0,726,727,3,146,73,0,727,729,5,75,0,0,728,730,3,108,54,0,729,728,
  	1,0,0,0,729,730,1,0,0,0,730,145,1,0,0,0,731,732,5,33,0,0,732,735,3,70,
  	35,0,733,735,5,34,0,0,734,731,1,0,0,0,734,733,1,0,0,0,735,147,1,0,0,0,
  	736,737,5,32,0,0,737,746,5,43,0,0,738,747,3,150,75,0,739,740,3,166,83,
  	0,740,741,3,150,75,0,741,747,1,0,0,0,742,743,3,112,56,0,743,744,3,166,
  	83,0,744,745,3,150,75,0,745,747,1,0,0,0,746,738,1,0,0,0,746,739,1,0,0,
  	0,746,742,1,0,0,0,747,748,1,0,0,0,748,749,5,44,0,0,749,753,5,47,0,0,750,
  	752,3,152,76,0,751,750,1,0,0,0,752,755,1,0,0,0,753,751,1,0,0,0,753,754,
  	1,0,0,0,754,756,1,0,0,0,755,753,1,0,0,0,756,757,5,48,0,0,757,149,1,0,
  	0,0,758,759,5,83,0,0,759,761,5,60,0,0,760,758,1,0,0,0,760,761,1,0,0,0,
  	761,762,1,0,0,0,762,763,3,62,31,0,763,764,5,76,0,0,764,765,5,43,0,0,765,
  	766,5,38,0,0,766,767,5,44,0,0,767,151,1,0,0,0,768,769,3,154,77,0,769,
  	771,5,75,0,0,770,772,3,108,54,0,771,770,1,0,0,0,771,772,1,0,0,0,772,153,
  	1,0,0,0,773,774,5,33,0,0,774,777,3,156,78,0,775,777,5,34,0,0,776,773,
  	1,0,0,0,776,775,1,0,0,0,777,155,1,0,0,0,778,781,3,12,6,0,779,781,5,22,
  	0,0,780,778,1,0,0,0,780,779,1,0,0,0,781,789,1,0,0,0,782,785,5,73,0,0,
  	783,786,3,12,6,0,784,786,5,22,0,0,785,783,1,0,0,0,785,784,1,0,0,0,786,
  	788,1,0,0,0,787,782,1,0,0,0,788,791,1,0,0,0,789,787,1,0,0,0,789,790,1,
  	0,0,0,790,157,1,0,0,0,791,789,1,0,0,0,792,793,5,29,0,0,793,798,5,43,0,
  	0,794,796,3,60,30,0,795,794,1,0,0,0,795,796,1,0,0,0,796,799,1,0,0,0,797,
  	799,3,160,80,0,798,795,1,0,0,0,798,797,1,0,0,0,799,800,1,0,0,0,800,801,
  	5,44,0,0,801,802,3,106,53,0,802,159,1,0,0,0,803,805,3,112,56,0,804,803,
  	1,0,0,0,804,805,1,0,0,0,805,806,1,0,0,0,806,808,3,166,83,0,807,809,3,
  	60,30,0,808,807,1,0,0,0,808,809,1,0,0,0,809,810,1,0,0,0,810,812,3,166,
  	83,0,811,813,3,112,56,0,812,811,1,0,0,0,812,813,1,0,0,0,813,161,1,0,0,
  	0,814,815,5,28,0,0,815,816,5,43,0,0,816,817,3,60,30,0,817,818,5,44,0,
  	0,818,819,3,106,53,0,819,163,1,0,0,0,820,821,5,31,0,0,821,822,3,106,53,
  	0,822,823,5,28,0,0,823,824,5,43,0,0,824,825,3,60,30,0,825,826,5,44,0,
  	0,826,165,1,0,0,0,827,828,5,80,0,0,828,167,1,0,0,0,93,172,178,194,201,
  	207,217,221,225,236,242,251,268,273,294,307,311,317,321,328,332,340,344,
  	346,356,360,363,370,384,386,389,392,394,403,406,414,431,433,440,449,453,
  	460,469,477,484,492,498,521,526,528,537,543,549,553,562,571,574,577,584,
  	595,599,604,611,627,633,645,658,662,666,670,687,694,696,700,705,708,712,
  	714,721,729,734,746,753,760,771,776,780,785,789,795,798,804,808,812
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
    setState(168);
    packageClause();
    setState(169);
    eos();
    setState(178);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 309237907456) != 0)) {
      setState(172);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case AutoTenV1Parser::Function: {
          setState(170);
          functionDecl();
          break;
        }

        case AutoTenV1Parser::Var:
        case AutoTenV1Parser::Type: {
          setState(171);
          declaration();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(174);
      eos();
      setState(180);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(181);
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
    setState(183);
    match(AutoTenV1Parser::At);
    setState(184);
    match(AutoTenV1Parser::Package);
    setState(185);
    match(AutoTenV1Parser::Assign);
    setState(186);
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

tree::TerminalNode* AutoTenV1Parser::CompileFlagsContext::Semi() {
  return getToken(AutoTenV1Parser::Semi, 0);
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

tree::TerminalNode* AutoTenV1Parser::CompileFlagsContext::StringLiteral() {
  return getToken(AutoTenV1Parser::StringLiteral, 0);
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
    setState(188);
    match(AutoTenV1Parser::At);
    setState(189);
    match(AutoTenV1Parser::Identifier);
    setState(194);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(190);
        matchWildcard();
        setState(191);
        match(AutoTenV1Parser::Identifier); 
      }
      setState(196);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
    setState(201);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Assign: {
        setState(197);
        match(AutoTenV1Parser::Assign);
        setState(198);
        match(AutoTenV1Parser::True_);
        break;
      }

      case AutoTenV1Parser::False_: {
        setState(199);
        match(AutoTenV1Parser::False_);
        break;
      }

      case AutoTenV1Parser::StringLiteral: {
        setState(200);
        match(AutoTenV1Parser::StringLiteral);
        break;
      }

      case AutoTenV1Parser::Semi: {
        break;
      }

    default:
      break;
    }
    setState(203);
    match(AutoTenV1Parser::Semi);
   
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
    setState(207);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Type: {
        enterOuterAlt(_localctx, 1);
        setState(205);
        typeDecl();
        break;
      }

      case AutoTenV1Parser::Var: {
        enterOuterAlt(_localctx, 2);
        setState(206);
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
    setState(209);
    match(AutoTenV1Parser::Type);
    setState(221);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Identifier: {
        setState(210);
        typeSpec();
        break;
      }

      case AutoTenV1Parser::LeftParen: {
        setState(211);
        match(AutoTenV1Parser::LeftParen);
        setState(217);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == AutoTenV1Parser::Identifier) {
          setState(212);
          typeSpec();
          setState(213);
          eos();
          setState(219);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(220);
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
    setState(223);
    match(AutoTenV1Parser::Identifier);
    setState(225);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Assign) {
      setState(224);
      match(AutoTenV1Parser::Assign);
    }
    setState(227);
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
    setState(236);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(229);
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
        setState(230);
        typeLit();
        break;
      }

      case AutoTenV1Parser::LeftParen: {
        enterOuterAlt(_localctx, 3);
        setState(231);
        match(AutoTenV1Parser::LeftParen);
        setState(232);
        type_();
        setState(233);
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
        setState(235);
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

tree::TerminalNode* AutoTenV1Parser::BuiltinTypeContext::Tensor() {
  return getToken(AutoTenV1Parser::Tensor, 0);
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
  enterRule(_localctx, 14, AutoTenV1Parser::RuleBuiltinType);
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
    setState(238);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2359040) != 0))) {
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
  enterRule(_localctx, 16, AutoTenV1Parser::RuleTypeName);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(240);
      qualifiedIdent();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(241);
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
  enterRule(_localctx, 18, AutoTenV1Parser::RuleTypeLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(251);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(244);
      arrayType();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(245);
      structType();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(246);
      pointerType();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(247);
      functionType();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(248);
      implType();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(249);
      sliceType();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(250);
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
  enterRule(_localctx, 20, AutoTenV1Parser::RuleArrayType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(253);
    match(AutoTenV1Parser::LeftBracket);
    setState(254);
    arrayLength();
    setState(255);
    match(AutoTenV1Parser::RightBracket);
    setState(256);
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
  enterRule(_localctx, 22, AutoTenV1Parser::RuleArrayLength);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(258);
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
  enterRule(_localctx, 24, AutoTenV1Parser::RuleElementType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(260);
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
  enterRule(_localctx, 26, AutoTenV1Parser::RulePointerType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(262);
    match(AutoTenV1Parser::Star);
    setState(263);
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

std::vector<AutoTenV1Parser::FunctionLitContext *> AutoTenV1Parser::ImplTypeContext::functionLit() {
  return getRuleContexts<AutoTenV1Parser::FunctionLitContext>();
}

AutoTenV1Parser::FunctionLitContext* AutoTenV1Parser::ImplTypeContext::functionLit(size_t i) {
  return getRuleContext<AutoTenV1Parser::FunctionLitContext>(i);
}

std::vector<tree::TerminalNode *> AutoTenV1Parser::ImplTypeContext::Public() {
  return getTokens(AutoTenV1Parser::Public);
}

tree::TerminalNode* AutoTenV1Parser::ImplTypeContext::Public(size_t i) {
  return getToken(AutoTenV1Parser::Public, i);
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
  enterRule(_localctx, 28, AutoTenV1Parser::RuleImplType);
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
    setState(265);
    match(AutoTenV1Parser::Impl);
    setState(266);
    match(AutoTenV1Parser::LeftBrace);
    setState(273);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 35) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 35)) & 17592186044481) != 0)) {
      setState(268);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Public) {
        setState(267);
        match(AutoTenV1Parser::Public);
      }
      setState(270);
      functionLit();
      setState(275);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(276);
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
  enterRule(_localctx, 30, AutoTenV1Parser::RuleSliceType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(278);
    match(AutoTenV1Parser::LeftBracket);
    setState(279);
    match(AutoTenV1Parser::RightBracket);
    setState(280);
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
  enterRule(_localctx, 32, AutoTenV1Parser::RuleMapType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(282);
    match(AutoTenV1Parser::Map);
    setState(283);
    match(AutoTenV1Parser::LeftBracket);
    setState(284);
    type_();
    setState(285);
    match(AutoTenV1Parser::RightBracket);
    setState(286);
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
  enterRule(_localctx, 34, AutoTenV1Parser::RuleMethodSpec);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(294);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(288);
      match(AutoTenV1Parser::Identifier);
      setState(289);
      parameters();
      setState(290);
      result();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(292);
      match(AutoTenV1Parser::Identifier);
      setState(293);
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
  enterRule(_localctx, 36, AutoTenV1Parser::RuleFunctionType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(296);
    match(AutoTenV1Parser::Function);
    setState(297);
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
  enterRule(_localctx, 38, AutoTenV1Parser::RuleVarDecl);
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
    setState(299);
    match(AutoTenV1Parser::Var);
    setState(311);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Identifier: {
        setState(300);
        varSpec();
        break;
      }

      case AutoTenV1Parser::LeftParen: {
        setState(301);
        match(AutoTenV1Parser::LeftParen);
        setState(307);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == AutoTenV1Parser::Identifier) {
          setState(302);
          varSpec();
          setState(303);
          eos();
          setState(309);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(310);
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
  enterRule(_localctx, 40, AutoTenV1Parser::RuleVarSpec);
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
    setState(313);
    identifierList();
    setState(321);
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
        setState(314);
        type_();
        setState(317);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == AutoTenV1Parser::Assign) {
          setState(315);
          match(AutoTenV1Parser::Assign);
          setState(316);
          expressionList();
        }
        break;
      }

      case AutoTenV1Parser::Assign: {
        setState(319);
        match(AutoTenV1Parser::Assign);
        setState(320);
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
  enterRule(_localctx, 42, AutoTenV1Parser::RuleSignature);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(328);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(323);
      parameters();
      setState(324);
      match(AutoTenV1Parser::ArrowReturnType);
      setState(325);
      result();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(327);
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
  enterRule(_localctx, 44, AutoTenV1Parser::RuleResult);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(332);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(330);
      parameters();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(331);
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
  enterRule(_localctx, 46, AutoTenV1Parser::RuleParameters);
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
    setState(334);
    match(AutoTenV1Parser::LeftParen);
    setState(346);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2297051591474944) != 0) || ((((_la - 81) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 81)) & 7) != 0)) {
      setState(335);
      parameterDecl();
      setState(340);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(336);
          match(AutoTenV1Parser::Comma);
          setState(337);
          parameterDecl(); 
        }
        setState(342);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
      }
      setState(344);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Comma) {
        setState(343);
        match(AutoTenV1Parser::Comma);
      }
    }
    setState(348);
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
  enterRule(_localctx, 48, AutoTenV1Parser::RuleIndex);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(350);
    match(AutoTenV1Parser::LeftBracket);
    setState(351);
    expression(0);
    setState(352);
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
  enterRule(_localctx, 50, AutoTenV1Parser::RuleSlice_);
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
    setState(354);
    match(AutoTenV1Parser::LeftBracket);
    setState(370);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      setState(356);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 79)) & 21) != 0)) {
        setState(355);
        expression(0);
      }
      setState(358);
      match(AutoTenV1Parser::Colon);
      setState(360);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 79)) & 21) != 0)) {
        setState(359);
        expression(0);
      }
      break;
    }

    case 2: {
      setState(363);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 79)) & 21) != 0)) {
        setState(362);
        expression(0);
      }
      setState(365);
      match(AutoTenV1Parser::Colon);
      setState(366);
      expression(0);
      setState(367);
      match(AutoTenV1Parser::Colon);
      setState(368);
      expression(0);
      break;
    }

    default:
      break;
    }
    setState(372);
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
  enterRule(_localctx, 52, AutoTenV1Parser::RuleTypeAssertion);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(374);
    match(AutoTenV1Parser::Dot);
    setState(375);
    match(AutoTenV1Parser::LeftParen);
    setState(376);
    type_();
    setState(377);
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
  enterRule(_localctx, 54, AutoTenV1Parser::RuleArguments);
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
    setState(379);
    match(AutoTenV1Parser::LeftParen);
    setState(394);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 21) != 0)) {
      setState(386);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
      case 1: {
        setState(380);
        expressionList();
        break;
      }

      case 2: {
        setState(381);
        nonNamedType();
        setState(384);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
        case 1: {
          setState(382);
          match(AutoTenV1Parser::Comma);
          setState(383);
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
      setState(389);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Ellipsis) {
        setState(388);
        match(AutoTenV1Parser::Ellipsis);
      }
      setState(392);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Comma) {
        setState(391);
        match(AutoTenV1Parser::Comma);
      }
    }
    setState(396);
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
  enterRule(_localctx, 56, AutoTenV1Parser::RuleMethodExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(398);
    nonNamedType();
    setState(399);
    match(AutoTenV1Parser::Dot);
    setState(400);
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
  enterRule(_localctx, 58, AutoTenV1Parser::RuleParameterDecl);
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
    setState(403);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      setState(402);
      identifierList();
      break;
    }

    default:
      break;
    }
    setState(406);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Ellipsis) {
      setState(405);
      match(AutoTenV1Parser::Ellipsis);
    }
    setState(408);
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
  size_t startState = 60;
  enterRecursionRule(_localctx, 60, AutoTenV1Parser::RuleExpression, precedence);

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
    setState(414);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      setState(411);
      primaryExpr(0);
      break;
    }

    case 2: {
      setState(412);
      antlrcpp::downCast<ExpressionContext *>(_localctx)->unary_op = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346214221354106880) != 0))) {
        antlrcpp::downCast<ExpressionContext *>(_localctx)->unary_op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(413);
      expression(6);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(433);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(431);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(416);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(417);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->mul_op = _input->LT(1);
          _la = _input->LA(1);
          if (!(((((_la - 51) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 51)) & 12311) != 0))) {
            antlrcpp::downCast<ExpressionContext *>(_localctx)->mul_op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(418);
          expression(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(419);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(420);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->add_op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 91760842407673856) != 0))) {
            antlrcpp::downCast<ExpressionContext *>(_localctx)->add_op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(421);
          expression(5);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(422);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(423);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->rel_op = _input->LT(1);
          _la = _input->LA(1);
          if (!(((((_la - 61) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 61)) & 243) != 0))) {
            antlrcpp::downCast<ExpressionContext *>(_localctx)->rel_op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(424);
          expression(4);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(425);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(426);
          match(AutoTenV1Parser::AndAnd);
          setState(427);
          expression(3);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(428);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(429);
          match(AutoTenV1Parser::OrOr);
          setState(430);
          expression(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(435);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
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
  size_t startState = 62;
  enterRecursionRule(_localctx, 62, AutoTenV1Parser::RulePrimaryExpr, precedence);

    

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
    setState(440);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      setState(437);
      operand();
      break;
    }

    case 2: {
      setState(438);
      conversion();
      break;
    }

    case 3: {
      setState(439);
      methodExpr();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(453);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<PrimaryExprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RulePrimaryExpr);
        setState(442);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(449);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
        case 1: {
          setState(443);
          match(AutoTenV1Parser::Dot);
          setState(444);
          match(AutoTenV1Parser::Identifier);
          break;
        }

        case 2: {
          setState(445);
          index();
          break;
        }

        case 3: {
          setState(446);
          slice_();
          break;
        }

        case 4: {
          setState(447);
          typeAssertion();
          break;
        }

        case 5: {
          setState(448);
          arguments();
          break;
        }

        default:
          break;
        } 
      }
      setState(455);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
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
  enterRule(_localctx, 64, AutoTenV1Parser::RuleConversion);
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
    setState(456);
    nonNamedType();
    setState(457);
    match(AutoTenV1Parser::LeftParen);
    setState(458);
    expression(0);
    setState(460);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Comma) {
      setState(459);
      match(AutoTenV1Parser::Comma);
    }
    setState(462);
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
  enterRule(_localctx, 66, AutoTenV1Parser::RuleNonNamedType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(469);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Function:
      case AutoTenV1Parser::Struct:
      case AutoTenV1Parser::Impl:
      case AutoTenV1Parser::LeftBracket:
      case AutoTenV1Parser::Star:
      case AutoTenV1Parser::Map: {
        enterOuterAlt(_localctx, 1);
        setState(464);
        typeLit();
        break;
      }

      case AutoTenV1Parser::LeftParen: {
        enterOuterAlt(_localctx, 2);
        setState(465);
        match(AutoTenV1Parser::LeftParen);
        setState(466);
        nonNamedType();
        setState(467);
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
  enterRule(_localctx, 68, AutoTenV1Parser::RuleOperand);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(477);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(471);
      literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(472);
      operandName();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(473);
      match(AutoTenV1Parser::LeftParen);
      setState(474);
      expression(0);
      setState(475);
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
  enterRule(_localctx, 70, AutoTenV1Parser::RuleExpressionList);

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
    setState(479);
    expression(0);
    setState(484);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(480);
        match(AutoTenV1Parser::Comma);
        setState(481);
        expression(0); 
      }
      setState(486);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
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
  enterRule(_localctx, 72, AutoTenV1Parser::RuleIdentifierList);
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
    setState(487);
    match(AutoTenV1Parser::Identifier);
    setState(492);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Comma) {
      setState(488);
      match(AutoTenV1Parser::Comma);
      setState(489);
      match(AutoTenV1Parser::Identifier);
      setState(494);
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
  enterRule(_localctx, 74, AutoTenV1Parser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(498);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(495);
      basicLit();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(496);
      compositeLit();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(497);
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
  enterRule(_localctx, 76, AutoTenV1Parser::RuleBasicLit);
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
    setState(500);
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
  enterRule(_localctx, 78, AutoTenV1Parser::RuleOperandName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(502);
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
  enterRule(_localctx, 80, AutoTenV1Parser::RuleQualifiedIdent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(504);
    match(AutoTenV1Parser::Identifier);
    setState(505);
    match(AutoTenV1Parser::Dot);
    setState(506);
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
  enterRule(_localctx, 82, AutoTenV1Parser::RuleCompositeLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(508);
    literalType();
    setState(509);
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
  enterRule(_localctx, 84, AutoTenV1Parser::RuleLiteralType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(521);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(511);
      structType();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(512);
      arrayType();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(513);
      elementType();
      setState(514);
      match(AutoTenV1Parser::LeftBracket);
      setState(515);
      match(AutoTenV1Parser::Ellipsis);
      setState(516);
      match(AutoTenV1Parser::RightBracket);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(518);
      sliceType();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(519);
      mapType();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(520);
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
  enterRule(_localctx, 86, AutoTenV1Parser::RuleLiteralValue);
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
    setState(523);
    match(AutoTenV1Parser::LeftBrace);
    setState(528);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346400210624446238) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 21) != 0)) {
      setState(524);
      elementList();
      setState(526);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Comma) {
        setState(525);
        match(AutoTenV1Parser::Comma);
      }
    }
    setState(530);
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
  enterRule(_localctx, 88, AutoTenV1Parser::RuleElementList);

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
    setState(532);
    keyedElement();
    setState(537);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(533);
        match(AutoTenV1Parser::Comma);
        setState(534);
        keyedElement(); 
      }
      setState(539);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
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
  enterRule(_localctx, 90, AutoTenV1Parser::RuleKeyedElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(543);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      setState(540);
      key();
      setState(541);
      match(AutoTenV1Parser::Colon);
      break;
    }

    default:
      break;
    }
    setState(545);
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
  enterRule(_localctx, 92, AutoTenV1Parser::RuleKey);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(549);
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
        setState(547);
        expression(0);
        break;
      }

      case AutoTenV1Parser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(548);
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
  enterRule(_localctx, 94, AutoTenV1Parser::RuleElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(553);
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
        setState(551);
        expression(0);
        break;
      }

      case AutoTenV1Parser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(552);
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
  enterRule(_localctx, 96, AutoTenV1Parser::RuleStructType);
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
    setState(555);
    match(AutoTenV1Parser::Struct);
    setState(556);
    match(AutoTenV1Parser::LeftBrace);
    setState(562);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Star

    || _la == AutoTenV1Parser::Identifier) {
      setState(557);
      fieldDecl();
      setState(558);
      eos();
      setState(564);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(565);
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
  enterRule(_localctx, 98, AutoTenV1Parser::RuleFieldDecl);
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
    setState(571);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      setState(567);
      identifierList();
      setState(568);
      type_();
      break;
    }

    case 2: {
      setState(570);
      embeddedField();
      break;
    }

    default:
      break;
    }
    setState(574);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::StringLiteral) {
      setState(573);
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
  enterRule(_localctx, 100, AutoTenV1Parser::RuleEmbeddedField);
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
    setState(577);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Star) {
      setState(576);
      match(AutoTenV1Parser::Star);
    }
    setState(579);
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
  enterRule(_localctx, 102, AutoTenV1Parser::RuleFunctionLit);
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
    setState(584);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::At) {
      setState(581);
      compileFlags();
      setState(586);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(587);
    match(AutoTenV1Parser::Function);
    setState(588);
    signature();
    setState(589);
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
  enterRule(_localctx, 104, AutoTenV1Parser::RuleFunctionDecl);
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
    setState(591);
    match(AutoTenV1Parser::Function);
    setState(592);
    match(AutoTenV1Parser::Identifier);
    setState(593);
    signature();
    setState(595);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::LeftBrace) {
      setState(594);
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
  enterRule(_localctx, 106, AutoTenV1Parser::RuleBlock);
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
    setState(597);
    match(AutoTenV1Parser::LeftBrace);
    setState(599);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346400561729896222) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 23) != 0)) {
      setState(598);
      statementList();
    }
    setState(601);
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
  enterRule(_localctx, 108, AutoTenV1Parser::RuleStatementList);
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
    setState(609); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(604);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Semi) {
        setState(603);
        match(AutoTenV1Parser::Semi);
      }
      setState(606);
      statement();
      setState(607);
      eos();
      setState(611); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346400561729896222) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 23) != 0));
   
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
  enterRule(_localctx, 110, AutoTenV1Parser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(627);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(613);
      declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(614);
      labeledStmt();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(615);
      simpleStmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(616);
      returnStmt();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(617);
      breakStmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(618);
      continueStmt();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(619);
      gotoStmt();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(620);
      fallthroughStmt();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(621);
      block();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(622);
      ifStmt();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(623);
      switchStmt();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(624);
      forStmt();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(625);
      whileStmt();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(626);
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
  enterRule(_localctx, 112, AutoTenV1Parser::RuleSimpleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(633);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(629);
      incDecStmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(630);
      assignment();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(631);
      expressionStmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(632);
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
  enterRule(_localctx, 114, AutoTenV1Parser::RuleExpressionStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(635);
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
  enterRule(_localctx, 116, AutoTenV1Parser::RuleIncDecStmt);
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
    setState(637);
    expression(0);
    setState(638);
    _la = _input->LA(1);
    if (!(_la == AutoTenV1Parser::PlusPlus)) {
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
  enterRule(_localctx, 118, AutoTenV1Parser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(640);
    expressionList();
    setState(641);
    assign_op();
    setState(642);
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

tree::TerminalNode* AutoTenV1Parser::Assign_opContext::Equal() {
  return getToken(AutoTenV1Parser::Equal, 0);
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
  enterRule(_localctx, 120, AutoTenV1Parser::RuleAssign_op);
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
    if (((((_la - 49) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 49)) & 49407) != 0)) {
      setState(644);
      _la = _input->LA(1);
      if (!(((((_la - 49) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 49)) & 49407) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(647);
    match(AutoTenV1Parser::Equal);
   
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
  enterRule(_localctx, 122, AutoTenV1Parser::RuleShortVarDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(649);
    identifierList();
    setState(650);
    match(AutoTenV1Parser::DeclareAssign);
    setState(651);
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
  enterRule(_localctx, 124, AutoTenV1Parser::RuleEmptyStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(653);
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
  enterRule(_localctx, 126, AutoTenV1Parser::RuleLabeledStmt);
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
    match(AutoTenV1Parser::Identifier);
    setState(656);
    match(AutoTenV1Parser::Colon);
    setState(658);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346400561729896222) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 21) != 0)) {
      setState(657);
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
  enterRule(_localctx, 128, AutoTenV1Parser::RuleReturnStmt);
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
    setState(660);
    match(AutoTenV1Parser::Return);
    setState(662);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 21) != 0)) {
      setState(661);
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
  enterRule(_localctx, 130, AutoTenV1Parser::RuleBreakStmt);
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
    setState(664);
    match(AutoTenV1Parser::Break);
    setState(666);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Identifier) {
      setState(665);
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
  enterRule(_localctx, 132, AutoTenV1Parser::RuleContinueStmt);
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
    setState(668);
    match(AutoTenV1Parser::Continue);
    setState(670);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Identifier) {
      setState(669);
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
  enterRule(_localctx, 134, AutoTenV1Parser::RuleGotoStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(672);
    match(AutoTenV1Parser::Goto);
    setState(673);
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
  enterRule(_localctx, 136, AutoTenV1Parser::RuleFallthroughStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(675);
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
  enterRule(_localctx, 138, AutoTenV1Parser::RuleIfStmt);
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
    setState(677);
    match(AutoTenV1Parser::If);
    setState(678);
    match(AutoTenV1Parser::LeftParen);
    setState(687);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
    case 1: {
      setState(679);
      expression(0);
      break;
    }

    case 2: {
      setState(680);
      eos();
      setState(681);
      expression(0);
      break;
    }

    case 3: {
      setState(683);
      simpleStmt();
      setState(684);
      eos();
      setState(685);
      expression(0);
      break;
    }

    default:
      break;
    }
    setState(689);
    match(AutoTenV1Parser::RightParen);
    setState(690);
    block();
    setState(696);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Else) {
      setState(691);
      match(AutoTenV1Parser::Else);
      setState(694);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case AutoTenV1Parser::If: {
          setState(692);
          ifStmt();
          break;
        }

        case AutoTenV1Parser::LeftBrace: {
          setState(693);
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
  enterRule(_localctx, 140, AutoTenV1Parser::RuleSwitchStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(700);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(698);
      exprSwitchStmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(699);
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
  enterRule(_localctx, 142, AutoTenV1Parser::RuleExprSwitchStmt);
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
    setState(702);
    match(AutoTenV1Parser::Switch);
    setState(703);
    match(AutoTenV1Parser::LeftParen);
    setState(714);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx)) {
    case 1: {
      setState(705);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 79)) & 21) != 0)) {
        setState(704);
        expression(0);
      }
      break;
    }

    case 2: {
      setState(708);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 79)) & 21) != 0)) {
        setState(707);
        simpleStmt();
      }
      setState(710);
      eos();
      setState(712);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 79)) & 21) != 0)) {
        setState(711);
        expression(0);
      }
      break;
    }

    default:
      break;
    }
    setState(716);
    match(AutoTenV1Parser::RightParen);
    setState(717);
    match(AutoTenV1Parser::LeftBrace);
    setState(721);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Case

    || _la == AutoTenV1Parser::Default) {
      setState(718);
      exprCaseClause();
      setState(723);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(724);
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
  enterRule(_localctx, 144, AutoTenV1Parser::RuleExprCaseClause);
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
    exprSwitchCase();
    setState(727);
    match(AutoTenV1Parser::Colon);
    setState(729);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346400561729896222) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 23) != 0)) {
      setState(728);
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
  enterRule(_localctx, 146, AutoTenV1Parser::RuleExprSwitchCase);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(734);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Case: {
        enterOuterAlt(_localctx, 1);
        setState(731);
        match(AutoTenV1Parser::Case);
        setState(732);
        expressionList();
        break;
      }

      case AutoTenV1Parser::Default: {
        enterOuterAlt(_localctx, 2);
        setState(733);
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
  enterRule(_localctx, 148, AutoTenV1Parser::RuleTypeSwitchStmt);
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
    setState(736);
    match(AutoTenV1Parser::Switch);
    setState(737);
    match(AutoTenV1Parser::LeftParen);
    setState(746);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 80, _ctx)) {
    case 1: {
      setState(738);
      typeSwitchGuard();
      break;
    }

    case 2: {
      setState(739);
      eos();
      setState(740);
      typeSwitchGuard();
      break;
    }

    case 3: {
      setState(742);
      simpleStmt();
      setState(743);
      eos();
      setState(744);
      typeSwitchGuard();
      break;
    }

    default:
      break;
    }
    setState(748);
    match(AutoTenV1Parser::RightParen);
    setState(749);
    match(AutoTenV1Parser::LeftBrace);
    setState(753);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Case

    || _la == AutoTenV1Parser::Default) {
      setState(750);
      typeCaseClause();
      setState(755);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(756);
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
  enterRule(_localctx, 150, AutoTenV1Parser::RuleTypeSwitchGuard);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(760);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx)) {
    case 1: {
      setState(758);
      match(AutoTenV1Parser::Identifier);
      setState(759);
      match(AutoTenV1Parser::DeclareAssign);
      break;
    }

    default:
      break;
    }
    setState(762);
    primaryExpr(0);
    setState(763);
    match(AutoTenV1Parser::Dot);
    setState(764);
    match(AutoTenV1Parser::LeftParen);
    setState(765);
    match(AutoTenV1Parser::Type);
    setState(766);
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
  enterRule(_localctx, 152, AutoTenV1Parser::RuleTypeCaseClause);
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
    setState(768);
    typeSwitchCase();
    setState(769);
    match(AutoTenV1Parser::Colon);
    setState(771);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346400561729896222) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 23) != 0)) {
      setState(770);
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
  enterRule(_localctx, 154, AutoTenV1Parser::RuleTypeSwitchCase);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(776);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Case: {
        enterOuterAlt(_localctx, 1);
        setState(773);
        match(AutoTenV1Parser::Case);
        setState(774);
        typeList();
        break;
      }

      case AutoTenV1Parser::Default: {
        enterOuterAlt(_localctx, 2);
        setState(775);
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
  enterRule(_localctx, 156, AutoTenV1Parser::RuleTypeList);
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
    setState(780);
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
        setState(778);
        type_();
        break;
      }

      case AutoTenV1Parser::Nilptr: {
        setState(779);
        match(AutoTenV1Parser::Nilptr);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(789);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Comma) {
      setState(782);
      match(AutoTenV1Parser::Comma);
      setState(785);
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
          setState(783);
          type_();
          break;
        }

        case AutoTenV1Parser::Nilptr: {
          setState(784);
          match(AutoTenV1Parser::Nilptr);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(791);
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
  enterRule(_localctx, 158, AutoTenV1Parser::RuleForStmt);
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
    setState(792);
    match(AutoTenV1Parser::For);
    setState(793);
    match(AutoTenV1Parser::LeftParen);
    setState(798);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 89, _ctx)) {
    case 1: {
      setState(795);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 79)) & 21) != 0)) {
        setState(794);
        expression(0);
      }
      break;
    }

    case 2: {
      setState(797);
      forClause();
      break;
    }

    default:
      break;
    }
    setState(800);
    match(AutoTenV1Parser::RightParen);
    setState(801);
    block();
   
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
  enterRule(_localctx, 160, AutoTenV1Parser::RuleForClause);
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
    setState(804);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 21) != 0)) {
      setState(803);
      antlrcpp::downCast<ForClauseContext *>(_localctx)->initStmt = simpleStmt();
    }
    setState(806);
    eos();
    setState(808);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 21) != 0)) {
      setState(807);
      expression(0);
    }
    setState(810);
    eos();
    setState(812);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 21) != 0)) {
      setState(811);
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
  enterRule(_localctx, 162, AutoTenV1Parser::RuleWhileStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(814);
    match(AutoTenV1Parser::While);
    setState(815);
    match(AutoTenV1Parser::LeftParen);

    setState(816);
    expression(0);
    setState(817);
    match(AutoTenV1Parser::RightParen);
    setState(818);
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
  enterRule(_localctx, 164, AutoTenV1Parser::RuleDoWhileStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(820);
    match(AutoTenV1Parser::Do);
    setState(821);
    block();
    setState(822);
    match(AutoTenV1Parser::While);
    setState(823);
    match(AutoTenV1Parser::LeftParen);

    setState(824);
    expression(0);
    setState(825);
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
  enterRule(_localctx, 166, AutoTenV1Parser::RuleEos);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(827);
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
    case 30: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);
    case 31: return primaryExprSempred(antlrcpp::downCast<PrimaryExprContext *>(context), predicateIndex);

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
