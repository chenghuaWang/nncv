
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
      "typeCaseClause", "typeSwitchCase", "typeList", "forStmt", "forClause", 
      "whileStmt", "doWhileStmt", "eos"
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
  	4,1,96,896,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
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
  	84,1,0,1,0,1,0,1,0,3,0,175,8,0,1,0,1,0,5,0,179,8,0,10,0,12,0,182,9,0,
  	1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,5,2,195,8,2,10,2,12,2,198,
  	9,2,1,2,1,2,1,2,1,2,3,2,204,8,2,3,2,206,8,2,1,3,1,3,3,3,210,8,3,1,4,1,
  	4,1,4,1,4,1,4,1,4,5,4,218,8,4,10,4,12,4,221,9,4,1,4,3,4,224,8,4,1,5,1,
  	5,3,5,228,8,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,239,8,6,1,7,1,7,
  	1,7,1,7,1,7,5,7,246,8,7,10,7,12,7,249,9,7,1,7,1,7,1,7,1,7,3,7,255,8,7,
  	1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,268,8,8,1,9,1,9,3,9,272,
  	8,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,3,10,281,8,10,1,11,1,11,1,11,1,
  	11,1,11,1,12,1,12,1,13,1,13,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,5,
  	15,300,8,15,10,15,12,15,303,9,15,1,15,1,15,1,16,1,16,1,16,1,16,1,17,1,
  	17,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,3,18,323,8,18,1,
  	19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,1,20,5,20,334,8,20,10,20,12,20,
  	337,9,20,1,20,3,20,340,8,20,1,21,1,21,1,21,1,21,3,21,346,8,21,1,21,1,
  	21,3,21,350,8,21,1,22,1,22,1,22,1,22,1,22,3,22,357,8,22,1,23,1,23,3,23,
  	361,8,23,1,24,1,24,1,24,1,24,5,24,367,8,24,10,24,12,24,370,9,24,1,24,
  	3,24,373,8,24,3,24,375,8,24,1,24,1,24,1,25,1,25,1,25,1,25,1,26,1,26,3,
  	26,385,8,26,1,26,1,26,3,26,389,8,26,1,26,3,26,392,8,26,1,26,1,26,1,26,
  	1,26,1,26,1,26,3,26,400,8,26,1,26,1,26,3,26,404,8,26,1,26,1,26,3,26,408,
  	8,26,1,26,3,26,411,8,26,1,26,1,26,1,26,1,26,1,26,1,26,3,26,419,8,26,5,
  	26,421,8,26,10,26,12,26,424,9,26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,1,
  	28,1,28,1,28,1,28,1,28,3,28,438,8,28,3,28,440,8,28,1,28,3,28,443,8,28,
  	1,28,3,28,446,8,28,3,28,448,8,28,1,28,1,28,1,29,1,29,1,29,1,29,1,30,3,
  	30,457,8,30,1,30,3,30,460,8,30,1,30,1,30,1,31,1,31,1,31,1,31,3,31,468,
  	8,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,
  	1,31,1,31,5,31,485,8,31,10,31,12,31,488,9,31,1,32,1,32,1,32,1,32,3,32,
  	494,8,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,3,32,503,8,32,5,32,505,8,
  	32,10,32,12,32,508,9,32,1,33,1,33,1,33,1,33,3,33,514,8,33,1,33,1,33,1,
  	34,1,34,1,34,1,34,1,34,3,34,523,8,34,1,35,1,35,1,35,1,35,1,35,1,35,3,
  	35,531,8,35,1,36,1,36,1,36,5,36,536,8,36,10,36,12,36,539,9,36,1,37,1,
  	37,1,37,5,37,544,8,37,10,37,12,37,547,9,37,1,38,1,38,1,38,3,38,552,8,
  	38,1,39,1,39,1,40,1,40,1,41,1,41,1,41,1,41,1,42,1,42,1,42,1,43,1,43,1,
  	43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,3,43,576,8,43,1,44,1,44,1,
  	44,3,44,581,8,44,3,44,583,8,44,1,44,1,44,1,45,1,45,1,45,5,45,590,8,45,
  	10,45,12,45,593,9,45,1,46,1,46,1,46,3,46,598,8,46,1,46,1,46,1,47,1,47,
  	3,47,604,8,47,1,48,1,48,3,48,608,8,48,1,49,1,49,1,49,3,49,613,8,49,1,
  	49,1,49,1,49,5,49,618,8,49,10,49,12,49,621,9,49,1,49,1,49,1,50,1,50,1,
  	50,1,50,3,50,629,8,50,1,50,3,50,632,8,50,1,51,3,51,635,8,51,1,51,1,51,
  	1,52,5,52,640,8,52,10,52,12,52,643,9,52,1,52,1,52,1,52,1,52,1,53,5,53,
  	650,8,53,10,53,12,53,653,9,53,1,53,3,53,656,8,53,1,53,1,53,1,53,1,53,
  	3,53,662,8,53,1,54,1,54,3,54,666,8,54,1,54,1,54,1,55,3,55,671,8,55,1,
  	55,1,55,1,55,4,55,676,8,55,11,55,12,55,677,1,56,1,56,1,56,1,56,1,56,1,
  	56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,3,56,694,8,56,1,57,1,57,1,
  	57,1,57,3,57,700,8,57,1,58,1,58,1,59,1,59,1,59,1,60,1,60,1,60,1,60,1,
  	61,3,61,712,8,61,1,61,1,61,1,62,1,62,1,62,1,62,1,63,1,63,1,64,1,64,1,
  	64,3,64,725,8,64,1,65,1,65,3,65,729,8,65,1,66,1,66,3,66,733,8,66,1,67,
  	1,67,3,67,737,8,67,1,68,1,68,1,68,1,69,1,69,1,70,1,70,1,70,1,70,1,70,
  	1,70,1,70,1,70,1,70,1,70,3,70,754,8,70,1,70,1,70,1,70,1,70,1,70,3,70,
  	761,8,70,3,70,763,8,70,1,71,1,71,3,71,767,8,71,1,72,1,72,1,72,3,72,772,
  	8,72,1,72,3,72,775,8,72,1,72,1,72,3,72,779,8,72,3,72,781,8,72,1,72,1,
  	72,1,72,5,72,786,8,72,10,72,12,72,789,9,72,1,72,1,72,1,73,1,73,1,73,3,
  	73,796,8,73,1,74,1,74,1,74,3,74,801,8,74,1,75,1,75,1,75,1,75,1,75,1,75,
  	1,75,1,75,1,75,1,75,3,75,813,8,75,1,75,1,75,1,75,5,75,818,8,75,10,75,
  	12,75,821,9,75,1,75,1,75,1,76,1,76,3,76,827,8,76,1,76,1,76,1,76,1,76,
  	1,76,1,76,1,77,1,77,1,77,3,77,838,8,77,1,78,1,78,1,78,3,78,843,8,78,1,
  	79,1,79,3,79,847,8,79,1,79,1,79,1,79,3,79,852,8,79,5,79,854,8,79,10,79,
  	12,79,857,9,79,1,80,1,80,1,80,3,80,862,8,80,1,80,3,80,865,8,80,1,80,1,
  	80,1,80,1,81,3,81,871,8,81,1,81,1,81,3,81,875,8,81,1,81,1,81,3,81,879,
  	8,81,1,82,1,82,1,82,1,82,1,82,1,82,1,83,1,83,1,83,1,83,1,83,1,83,1,83,
  	1,84,1,84,1,84,0,2,62,64,85,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,
  	32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,
  	78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,
  	118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,148,150,152,
  	154,156,158,160,162,164,166,168,0,8,1,0,10,13,3,0,49,51,54,55,58,58,3,
  	0,51,53,55,55,63,64,3,0,49,50,54,54,56,56,2,0,61,62,65,68,2,0,1,4,22,
  	22,1,0,71,71,2,0,49,56,63,64,963,0,170,1,0,0,0,2,185,1,0,0,0,4,190,1,
  	0,0,0,6,209,1,0,0,0,8,211,1,0,0,0,10,225,1,0,0,0,12,238,1,0,0,0,14,240,
  	1,0,0,0,16,267,1,0,0,0,18,271,1,0,0,0,20,280,1,0,0,0,22,282,1,0,0,0,24,
  	287,1,0,0,0,26,289,1,0,0,0,28,291,1,0,0,0,30,294,1,0,0,0,32,306,1,0,0,
  	0,34,310,1,0,0,0,36,322,1,0,0,0,38,324,1,0,0,0,40,327,1,0,0,0,42,341,
  	1,0,0,0,44,356,1,0,0,0,46,360,1,0,0,0,48,362,1,0,0,0,50,378,1,0,0,0,52,
  	382,1,0,0,0,54,427,1,0,0,0,56,432,1,0,0,0,58,451,1,0,0,0,60,456,1,0,0,
  	0,62,467,1,0,0,0,64,493,1,0,0,0,66,509,1,0,0,0,68,522,1,0,0,0,70,530,
  	1,0,0,0,72,532,1,0,0,0,74,540,1,0,0,0,76,551,1,0,0,0,78,553,1,0,0,0,80,
  	555,1,0,0,0,82,557,1,0,0,0,84,561,1,0,0,0,86,575,1,0,0,0,88,577,1,0,0,
  	0,90,586,1,0,0,0,92,597,1,0,0,0,94,603,1,0,0,0,96,607,1,0,0,0,98,609,
  	1,0,0,0,100,628,1,0,0,0,102,634,1,0,0,0,104,641,1,0,0,0,106,651,1,0,0,
  	0,108,663,1,0,0,0,110,675,1,0,0,0,112,693,1,0,0,0,114,699,1,0,0,0,116,
  	701,1,0,0,0,118,703,1,0,0,0,120,706,1,0,0,0,122,711,1,0,0,0,124,715,1,
  	0,0,0,126,719,1,0,0,0,128,721,1,0,0,0,130,726,1,0,0,0,132,730,1,0,0,0,
  	134,734,1,0,0,0,136,738,1,0,0,0,138,741,1,0,0,0,140,743,1,0,0,0,142,766,
  	1,0,0,0,144,768,1,0,0,0,146,792,1,0,0,0,148,800,1,0,0,0,150,802,1,0,0,
  	0,152,826,1,0,0,0,154,834,1,0,0,0,156,842,1,0,0,0,158,846,1,0,0,0,160,
  	858,1,0,0,0,162,870,1,0,0,0,164,880,1,0,0,0,166,886,1,0,0,0,168,893,1,
  	0,0,0,170,171,3,2,1,0,171,180,3,168,84,0,172,175,3,106,53,0,173,175,3,
  	6,3,0,174,172,1,0,0,0,174,173,1,0,0,0,175,176,1,0,0,0,176,177,3,168,84,
  	0,177,179,1,0,0,0,178,174,1,0,0,0,179,182,1,0,0,0,180,178,1,0,0,0,180,
  	181,1,0,0,0,181,183,1,0,0,0,182,180,1,0,0,0,183,184,5,0,0,1,184,1,1,0,
  	0,0,185,186,5,79,0,0,186,187,5,39,0,0,187,188,5,59,0,0,188,189,5,4,0,
  	0,189,3,1,0,0,0,190,191,5,79,0,0,191,196,5,83,0,0,192,193,9,0,0,0,193,
  	195,5,83,0,0,194,192,1,0,0,0,195,198,1,0,0,0,196,194,1,0,0,0,196,197,
  	1,0,0,0,197,205,1,0,0,0,198,196,1,0,0,0,199,203,5,59,0,0,200,204,5,20,
  	0,0,201,204,5,19,0,0,202,204,3,62,31,0,203,200,1,0,0,0,203,201,1,0,0,
  	0,203,202,1,0,0,0,204,206,1,0,0,0,205,199,1,0,0,0,205,206,1,0,0,0,206,
  	5,1,0,0,0,207,210,3,8,4,0,208,210,3,40,20,0,209,207,1,0,0,0,209,208,1,
  	0,0,0,210,7,1,0,0,0,211,223,5,38,0,0,212,224,3,10,5,0,213,219,5,43,0,
  	0,214,215,3,10,5,0,215,216,3,168,84,0,216,218,1,0,0,0,217,214,1,0,0,0,
  	218,221,1,0,0,0,219,217,1,0,0,0,219,220,1,0,0,0,220,222,1,0,0,0,221,219,
  	1,0,0,0,222,224,5,44,0,0,223,212,1,0,0,0,223,213,1,0,0,0,224,9,1,0,0,
  	0,225,227,5,83,0,0,226,228,5,59,0,0,227,226,1,0,0,0,227,228,1,0,0,0,228,
  	229,1,0,0,0,229,230,3,12,6,0,230,11,1,0,0,0,231,239,3,18,9,0,232,239,
  	3,20,10,0,233,234,5,43,0,0,234,235,3,12,6,0,235,236,5,44,0,0,236,239,
  	1,0,0,0,237,239,3,16,8,0,238,231,1,0,0,0,238,232,1,0,0,0,238,233,1,0,
  	0,0,238,237,1,0,0,0,239,13,1,0,0,0,240,254,5,17,0,0,241,242,5,61,0,0,
  	242,247,3,62,31,0,243,244,5,73,0,0,244,246,3,62,31,0,245,243,1,0,0,0,
  	246,249,1,0,0,0,247,245,1,0,0,0,247,248,1,0,0,0,248,250,1,0,0,0,249,247,
  	1,0,0,0,250,251,5,73,0,0,251,252,7,0,0,0,252,253,5,62,0,0,253,255,1,0,
  	0,0,254,241,1,0,0,0,254,255,1,0,0,0,255,15,1,0,0,0,256,268,5,8,0,0,257,
  	268,5,9,0,0,258,268,5,10,0,0,259,268,5,11,0,0,260,268,5,12,0,0,261,268,
  	5,13,0,0,262,268,5,15,0,0,263,268,5,16,0,0,264,268,5,14,0,0,265,268,3,
  	14,7,0,266,268,5,21,0,0,267,256,1,0,0,0,267,257,1,0,0,0,267,258,1,0,0,
  	0,267,259,1,0,0,0,267,260,1,0,0,0,267,261,1,0,0,0,267,262,1,0,0,0,267,
  	263,1,0,0,0,267,264,1,0,0,0,267,265,1,0,0,0,267,266,1,0,0,0,268,17,1,
  	0,0,0,269,272,3,82,41,0,270,272,5,83,0,0,271,269,1,0,0,0,271,270,1,0,
  	0,0,272,19,1,0,0,0,273,281,3,22,11,0,274,281,3,98,49,0,275,281,3,28,14,
  	0,276,281,3,38,19,0,277,281,3,30,15,0,278,281,3,32,16,0,279,281,3,34,
  	17,0,280,273,1,0,0,0,280,274,1,0,0,0,280,275,1,0,0,0,280,276,1,0,0,0,
  	280,277,1,0,0,0,280,278,1,0,0,0,280,279,1,0,0,0,281,21,1,0,0,0,282,283,
  	5,45,0,0,283,284,3,24,12,0,284,285,5,46,0,0,285,286,3,26,13,0,286,23,
  	1,0,0,0,287,288,3,62,31,0,288,25,1,0,0,0,289,290,3,12,6,0,290,27,1,0,
  	0,0,291,292,5,51,0,0,292,293,3,12,6,0,293,29,1,0,0,0,294,295,5,40,0,0,
  	295,301,5,47,0,0,296,297,3,106,53,0,297,298,5,80,0,0,298,300,1,0,0,0,
  	299,296,1,0,0,0,300,303,1,0,0,0,301,299,1,0,0,0,301,302,1,0,0,0,302,304,
  	1,0,0,0,303,301,1,0,0,0,304,305,5,48,0,0,305,31,1,0,0,0,306,307,5,45,
  	0,0,307,308,5,46,0,0,308,309,3,26,13,0,309,33,1,0,0,0,310,311,5,81,0,
  	0,311,312,5,45,0,0,312,313,3,12,6,0,313,314,5,46,0,0,314,315,3,26,13,
  	0,315,35,1,0,0,0,316,317,5,83,0,0,317,318,3,48,24,0,318,319,3,46,23,0,
  	319,323,1,0,0,0,320,321,5,83,0,0,321,323,3,48,24,0,322,316,1,0,0,0,322,
  	320,1,0,0,0,323,37,1,0,0,0,324,325,5,35,0,0,325,326,3,44,22,0,326,39,
  	1,0,0,0,327,339,5,18,0,0,328,340,3,42,21,0,329,335,5,43,0,0,330,331,3,
  	42,21,0,331,332,3,168,84,0,332,334,1,0,0,0,333,330,1,0,0,0,334,337,1,
  	0,0,0,335,333,1,0,0,0,335,336,1,0,0,0,336,338,1,0,0,0,337,335,1,0,0,0,
  	338,340,5,44,0,0,339,328,1,0,0,0,339,329,1,0,0,0,340,41,1,0,0,0,341,349,
  	3,74,37,0,342,345,3,12,6,0,343,344,5,59,0,0,344,346,3,72,36,0,345,343,
  	1,0,0,0,345,346,1,0,0,0,346,350,1,0,0,0,347,348,5,59,0,0,348,350,3,72,
  	36,0,349,342,1,0,0,0,349,347,1,0,0,0,350,43,1,0,0,0,351,352,3,48,24,0,
  	352,353,5,74,0,0,353,354,3,46,23,0,354,357,1,0,0,0,355,357,3,48,24,0,
  	356,351,1,0,0,0,356,355,1,0,0,0,357,45,1,0,0,0,358,361,3,48,24,0,359,
  	361,3,12,6,0,360,358,1,0,0,0,360,359,1,0,0,0,361,47,1,0,0,0,362,374,5,
  	43,0,0,363,368,3,60,30,0,364,365,5,73,0,0,365,367,3,60,30,0,366,364,1,
  	0,0,0,367,370,1,0,0,0,368,366,1,0,0,0,368,369,1,0,0,0,369,372,1,0,0,0,
  	370,368,1,0,0,0,371,373,5,73,0,0,372,371,1,0,0,0,372,373,1,0,0,0,373,
  	375,1,0,0,0,374,363,1,0,0,0,374,375,1,0,0,0,375,376,1,0,0,0,376,377,5,
  	44,0,0,377,49,1,0,0,0,378,379,5,45,0,0,379,380,3,62,31,0,380,381,5,46,
  	0,0,381,51,1,0,0,0,382,399,5,45,0,0,383,385,3,62,31,0,384,383,1,0,0,0,
  	384,385,1,0,0,0,385,386,1,0,0,0,386,388,5,75,0,0,387,389,3,62,31,0,388,
  	387,1,0,0,0,388,389,1,0,0,0,389,400,1,0,0,0,390,392,3,62,31,0,391,390,
  	1,0,0,0,391,392,1,0,0,0,392,393,1,0,0,0,393,394,5,75,0,0,394,395,3,62,
  	31,0,395,396,5,75,0,0,396,397,3,62,31,0,397,400,1,0,0,0,398,400,3,62,
  	31,0,399,384,1,0,0,0,399,391,1,0,0,0,399,398,1,0,0,0,400,422,1,0,0,0,
  	401,418,5,73,0,0,402,404,3,62,31,0,403,402,1,0,0,0,403,404,1,0,0,0,404,
  	405,1,0,0,0,405,407,5,75,0,0,406,408,3,62,31,0,407,406,1,0,0,0,407,408,
  	1,0,0,0,408,419,1,0,0,0,409,411,3,62,31,0,410,409,1,0,0,0,410,411,1,0,
  	0,0,411,412,1,0,0,0,412,413,5,75,0,0,413,414,3,62,31,0,414,415,5,75,0,
  	0,415,416,3,62,31,0,416,419,1,0,0,0,417,419,3,62,31,0,418,403,1,0,0,0,
  	418,410,1,0,0,0,418,417,1,0,0,0,419,421,1,0,0,0,420,401,1,0,0,0,421,424,
  	1,0,0,0,422,420,1,0,0,0,422,423,1,0,0,0,423,425,1,0,0,0,424,422,1,0,0,
  	0,425,426,5,46,0,0,426,53,1,0,0,0,427,428,5,76,0,0,428,429,5,43,0,0,429,
  	430,3,12,6,0,430,431,5,44,0,0,431,55,1,0,0,0,432,447,5,43,0,0,433,440,
  	3,72,36,0,434,437,3,68,34,0,435,436,5,73,0,0,436,438,3,72,36,0,437,435,
  	1,0,0,0,437,438,1,0,0,0,438,440,1,0,0,0,439,433,1,0,0,0,439,434,1,0,0,
  	0,440,442,1,0,0,0,441,443,5,82,0,0,442,441,1,0,0,0,442,443,1,0,0,0,443,
  	445,1,0,0,0,444,446,5,73,0,0,445,444,1,0,0,0,445,446,1,0,0,0,446,448,
  	1,0,0,0,447,439,1,0,0,0,447,448,1,0,0,0,448,449,1,0,0,0,449,450,5,44,
  	0,0,450,57,1,0,0,0,451,452,3,68,34,0,452,453,5,76,0,0,453,454,5,83,0,
  	0,454,59,1,0,0,0,455,457,3,74,37,0,456,455,1,0,0,0,456,457,1,0,0,0,457,
  	459,1,0,0,0,458,460,5,82,0,0,459,458,1,0,0,0,459,460,1,0,0,0,460,461,
  	1,0,0,0,461,462,3,12,6,0,462,61,1,0,0,0,463,464,6,31,-1,0,464,468,3,64,
  	32,0,465,466,7,1,0,0,466,468,3,62,31,6,467,463,1,0,0,0,467,465,1,0,0,
  	0,468,486,1,0,0,0,469,470,10,5,0,0,470,471,7,2,0,0,471,485,3,62,31,6,
  	472,473,10,4,0,0,473,474,7,3,0,0,474,485,3,62,31,5,475,476,10,3,0,0,476,
  	477,7,4,0,0,477,485,3,62,31,4,478,479,10,2,0,0,479,480,5,69,0,0,480,485,
  	3,62,31,3,481,482,10,1,0,0,482,483,5,70,0,0,483,485,3,62,31,2,484,469,
  	1,0,0,0,484,472,1,0,0,0,484,475,1,0,0,0,484,478,1,0,0,0,484,481,1,0,0,
  	0,485,488,1,0,0,0,486,484,1,0,0,0,486,487,1,0,0,0,487,63,1,0,0,0,488,
  	486,1,0,0,0,489,490,6,32,-1,0,490,494,3,70,35,0,491,494,3,66,33,0,492,
  	494,3,58,29,0,493,489,1,0,0,0,493,491,1,0,0,0,493,492,1,0,0,0,494,506,
  	1,0,0,0,495,502,10,1,0,0,496,497,5,76,0,0,497,503,5,83,0,0,498,503,3,
  	50,25,0,499,503,3,52,26,0,500,503,3,54,27,0,501,503,3,56,28,0,502,496,
  	1,0,0,0,502,498,1,0,0,0,502,499,1,0,0,0,502,500,1,0,0,0,502,501,1,0,0,
  	0,503,505,1,0,0,0,504,495,1,0,0,0,505,508,1,0,0,0,506,504,1,0,0,0,506,
  	507,1,0,0,0,507,65,1,0,0,0,508,506,1,0,0,0,509,510,3,68,34,0,510,511,
  	5,43,0,0,511,513,3,62,31,0,512,514,5,73,0,0,513,512,1,0,0,0,513,514,1,
  	0,0,0,514,515,1,0,0,0,515,516,5,44,0,0,516,67,1,0,0,0,517,523,3,20,10,
  	0,518,519,5,43,0,0,519,520,3,68,34,0,520,521,5,44,0,0,521,523,1,0,0,0,
  	522,517,1,0,0,0,522,518,1,0,0,0,523,69,1,0,0,0,524,531,3,76,38,0,525,
  	531,3,80,40,0,526,527,5,43,0,0,527,528,3,62,31,0,528,529,5,44,0,0,529,
  	531,1,0,0,0,530,524,1,0,0,0,530,525,1,0,0,0,530,526,1,0,0,0,531,71,1,
  	0,0,0,532,537,3,62,31,0,533,534,5,73,0,0,534,536,3,62,31,0,535,533,1,
  	0,0,0,536,539,1,0,0,0,537,535,1,0,0,0,537,538,1,0,0,0,538,73,1,0,0,0,
  	539,537,1,0,0,0,540,545,5,83,0,0,541,542,5,73,0,0,542,544,5,83,0,0,543,
  	541,1,0,0,0,544,547,1,0,0,0,545,543,1,0,0,0,545,546,1,0,0,0,546,75,1,
  	0,0,0,547,545,1,0,0,0,548,552,3,78,39,0,549,552,3,84,42,0,550,552,3,104,
  	52,0,551,548,1,0,0,0,551,549,1,0,0,0,551,550,1,0,0,0,552,77,1,0,0,0,553,
  	554,7,5,0,0,554,79,1,0,0,0,555,556,5,83,0,0,556,81,1,0,0,0,557,558,5,
  	83,0,0,558,559,5,76,0,0,559,560,5,83,0,0,560,83,1,0,0,0,561,562,3,86,
  	43,0,562,563,3,88,44,0,563,85,1,0,0,0,564,576,3,98,49,0,565,576,3,22,
  	11,0,566,567,3,26,13,0,567,568,5,45,0,0,568,569,5,82,0,0,569,570,5,46,
  	0,0,570,576,1,0,0,0,571,576,3,32,16,0,572,576,3,14,7,0,573,576,3,34,17,
  	0,574,576,3,18,9,0,575,564,1,0,0,0,575,565,1,0,0,0,575,566,1,0,0,0,575,
  	571,1,0,0,0,575,572,1,0,0,0,575,573,1,0,0,0,575,574,1,0,0,0,576,87,1,
  	0,0,0,577,582,5,47,0,0,578,580,3,90,45,0,579,581,5,73,0,0,580,579,1,0,
  	0,0,580,581,1,0,0,0,581,583,1,0,0,0,582,578,1,0,0,0,582,583,1,0,0,0,583,
  	584,1,0,0,0,584,585,5,48,0,0,585,89,1,0,0,0,586,591,3,92,46,0,587,588,
  	5,73,0,0,588,590,3,92,46,0,589,587,1,0,0,0,590,593,1,0,0,0,591,589,1,
  	0,0,0,591,592,1,0,0,0,592,91,1,0,0,0,593,591,1,0,0,0,594,595,3,94,47,
  	0,595,596,5,75,0,0,596,598,1,0,0,0,597,594,1,0,0,0,597,598,1,0,0,0,598,
  	599,1,0,0,0,599,600,3,96,48,0,600,93,1,0,0,0,601,604,3,62,31,0,602,604,
  	3,88,44,0,603,601,1,0,0,0,603,602,1,0,0,0,604,95,1,0,0,0,605,608,3,62,
  	31,0,606,608,3,88,44,0,607,605,1,0,0,0,607,606,1,0,0,0,608,97,1,0,0,0,
  	609,610,5,37,0,0,610,619,5,47,0,0,611,613,5,41,0,0,612,611,1,0,0,0,612,
  	613,1,0,0,0,613,614,1,0,0,0,614,615,3,100,50,0,615,616,3,168,84,0,616,
  	618,1,0,0,0,617,612,1,0,0,0,618,621,1,0,0,0,619,617,1,0,0,0,619,620,1,
  	0,0,0,620,622,1,0,0,0,621,619,1,0,0,0,622,623,5,48,0,0,623,99,1,0,0,0,
  	624,625,3,74,37,0,625,626,3,12,6,0,626,629,1,0,0,0,627,629,3,102,51,0,
  	628,624,1,0,0,0,628,627,1,0,0,0,629,631,1,0,0,0,630,632,5,4,0,0,631,630,
  	1,0,0,0,631,632,1,0,0,0,632,101,1,0,0,0,633,635,5,51,0,0,634,633,1,0,
  	0,0,634,635,1,0,0,0,635,636,1,0,0,0,636,637,3,18,9,0,637,103,1,0,0,0,
  	638,640,3,4,2,0,639,638,1,0,0,0,640,643,1,0,0,0,641,639,1,0,0,0,641,642,
  	1,0,0,0,642,644,1,0,0,0,643,641,1,0,0,0,644,645,5,35,0,0,645,646,3,44,
  	22,0,646,647,3,108,54,0,647,105,1,0,0,0,648,650,3,4,2,0,649,648,1,0,0,
  	0,650,653,1,0,0,0,651,649,1,0,0,0,651,652,1,0,0,0,652,655,1,0,0,0,653,
  	651,1,0,0,0,654,656,5,41,0,0,655,654,1,0,0,0,655,656,1,0,0,0,656,657,
  	1,0,0,0,657,658,5,35,0,0,658,659,5,83,0,0,659,661,3,44,22,0,660,662,3,
  	108,54,0,661,660,1,0,0,0,661,662,1,0,0,0,662,107,1,0,0,0,663,665,5,47,
  	0,0,664,666,3,110,55,0,665,664,1,0,0,0,665,666,1,0,0,0,666,667,1,0,0,
  	0,667,668,5,48,0,0,668,109,1,0,0,0,669,671,5,80,0,0,670,669,1,0,0,0,670,
  	671,1,0,0,0,671,672,1,0,0,0,672,673,3,112,56,0,673,674,3,168,84,0,674,
  	676,1,0,0,0,675,670,1,0,0,0,676,677,1,0,0,0,677,675,1,0,0,0,677,678,1,
  	0,0,0,678,111,1,0,0,0,679,694,3,6,3,0,680,694,3,128,64,0,681,694,3,114,
  	57,0,682,694,3,130,65,0,683,694,3,132,66,0,684,694,3,134,67,0,685,694,
  	3,136,68,0,686,694,3,138,69,0,687,694,3,108,54,0,688,694,3,140,70,0,689,
  	694,3,142,71,0,690,694,3,160,80,0,691,694,3,164,82,0,692,694,3,166,83,
  	0,693,679,1,0,0,0,693,680,1,0,0,0,693,681,1,0,0,0,693,682,1,0,0,0,693,
  	683,1,0,0,0,693,684,1,0,0,0,693,685,1,0,0,0,693,686,1,0,0,0,693,687,1,
  	0,0,0,693,688,1,0,0,0,693,689,1,0,0,0,693,690,1,0,0,0,693,691,1,0,0,0,
  	693,692,1,0,0,0,694,113,1,0,0,0,695,700,3,118,59,0,696,700,3,120,60,0,
  	697,700,3,116,58,0,698,700,3,124,62,0,699,695,1,0,0,0,699,696,1,0,0,0,
  	699,697,1,0,0,0,699,698,1,0,0,0,700,115,1,0,0,0,701,702,3,62,31,0,702,
  	117,1,0,0,0,703,704,3,62,31,0,704,705,7,6,0,0,705,119,1,0,0,0,706,707,
  	3,72,36,0,707,708,3,122,61,0,708,709,3,72,36,0,709,121,1,0,0,0,710,712,
  	7,7,0,0,711,710,1,0,0,0,711,712,1,0,0,0,712,713,1,0,0,0,713,714,5,59,
  	0,0,714,123,1,0,0,0,715,716,3,74,37,0,716,717,5,60,0,0,717,718,3,72,36,
  	0,718,125,1,0,0,0,719,720,5,80,0,0,720,127,1,0,0,0,721,722,5,83,0,0,722,
  	724,5,75,0,0,723,725,3,112,56,0,724,723,1,0,0,0,724,725,1,0,0,0,725,129,
  	1,0,0,0,726,728,5,36,0,0,727,729,3,72,36,0,728,727,1,0,0,0,728,729,1,
  	0,0,0,729,131,1,0,0,0,730,732,5,23,0,0,731,733,5,83,0,0,732,731,1,0,0,
  	0,732,733,1,0,0,0,733,133,1,0,0,0,734,736,5,24,0,0,735,737,5,83,0,0,736,
  	735,1,0,0,0,736,737,1,0,0,0,737,135,1,0,0,0,738,739,5,25,0,0,739,740,
  	5,83,0,0,740,137,1,0,0,0,741,742,5,26,0,0,742,139,1,0,0,0,743,744,5,27,
  	0,0,744,753,5,43,0,0,745,754,3,62,31,0,746,747,3,168,84,0,747,748,3,62,
  	31,0,748,754,1,0,0,0,749,750,3,114,57,0,750,751,3,168,84,0,751,752,3,
  	62,31,0,752,754,1,0,0,0,753,745,1,0,0,0,753,746,1,0,0,0,753,749,1,0,0,
  	0,754,755,1,0,0,0,755,756,5,44,0,0,756,762,3,108,54,0,757,760,5,30,0,
  	0,758,761,3,140,70,0,759,761,3,108,54,0,760,758,1,0,0,0,760,759,1,0,0,
  	0,761,763,1,0,0,0,762,757,1,0,0,0,762,763,1,0,0,0,763,141,1,0,0,0,764,
  	767,3,144,72,0,765,767,3,150,75,0,766,764,1,0,0,0,766,765,1,0,0,0,767,
  	143,1,0,0,0,768,769,5,32,0,0,769,780,5,43,0,0,770,772,3,62,31,0,771,770,
  	1,0,0,0,771,772,1,0,0,0,772,781,1,0,0,0,773,775,3,114,57,0,774,773,1,
  	0,0,0,774,775,1,0,0,0,775,776,1,0,0,0,776,778,3,168,84,0,777,779,3,62,
  	31,0,778,777,1,0,0,0,778,779,1,0,0,0,779,781,1,0,0,0,780,771,1,0,0,0,
  	780,774,1,0,0,0,781,782,1,0,0,0,782,783,5,44,0,0,783,787,5,47,0,0,784,
  	786,3,146,73,0,785,784,1,0,0,0,786,789,1,0,0,0,787,785,1,0,0,0,787,788,
  	1,0,0,0,788,790,1,0,0,0,789,787,1,0,0,0,790,791,5,48,0,0,791,145,1,0,
  	0,0,792,793,3,148,74,0,793,795,5,75,0,0,794,796,3,110,55,0,795,794,1,
  	0,0,0,795,796,1,0,0,0,796,147,1,0,0,0,797,798,5,33,0,0,798,801,3,72,36,
  	0,799,801,5,34,0,0,800,797,1,0,0,0,800,799,1,0,0,0,801,149,1,0,0,0,802,
  	803,5,32,0,0,803,812,5,43,0,0,804,813,3,152,76,0,805,806,3,168,84,0,806,
  	807,3,152,76,0,807,813,1,0,0,0,808,809,3,114,57,0,809,810,3,168,84,0,
  	810,811,3,152,76,0,811,813,1,0,0,0,812,804,1,0,0,0,812,805,1,0,0,0,812,
  	808,1,0,0,0,813,814,1,0,0,0,814,815,5,44,0,0,815,819,5,47,0,0,816,818,
  	3,154,77,0,817,816,1,0,0,0,818,821,1,0,0,0,819,817,1,0,0,0,819,820,1,
  	0,0,0,820,822,1,0,0,0,821,819,1,0,0,0,822,823,5,48,0,0,823,151,1,0,0,
  	0,824,825,5,83,0,0,825,827,5,60,0,0,826,824,1,0,0,0,826,827,1,0,0,0,827,
  	828,1,0,0,0,828,829,3,64,32,0,829,830,5,76,0,0,830,831,5,43,0,0,831,832,
  	5,38,0,0,832,833,5,44,0,0,833,153,1,0,0,0,834,835,3,156,78,0,835,837,
  	5,75,0,0,836,838,3,110,55,0,837,836,1,0,0,0,837,838,1,0,0,0,838,155,1,
  	0,0,0,839,840,5,33,0,0,840,843,3,158,79,0,841,843,5,34,0,0,842,839,1,
  	0,0,0,842,841,1,0,0,0,843,157,1,0,0,0,844,847,3,12,6,0,845,847,5,22,0,
  	0,846,844,1,0,0,0,846,845,1,0,0,0,847,855,1,0,0,0,848,851,5,73,0,0,849,
  	852,3,12,6,0,850,852,5,22,0,0,851,849,1,0,0,0,851,850,1,0,0,0,852,854,
  	1,0,0,0,853,848,1,0,0,0,854,857,1,0,0,0,855,853,1,0,0,0,855,856,1,0,0,
  	0,856,159,1,0,0,0,857,855,1,0,0,0,858,859,5,29,0,0,859,864,5,43,0,0,860,
  	862,3,62,31,0,861,860,1,0,0,0,861,862,1,0,0,0,862,865,1,0,0,0,863,865,
  	3,162,81,0,864,861,1,0,0,0,864,863,1,0,0,0,865,866,1,0,0,0,866,867,5,
  	44,0,0,867,868,3,108,54,0,868,161,1,0,0,0,869,871,3,114,57,0,870,869,
  	1,0,0,0,870,871,1,0,0,0,871,872,1,0,0,0,872,874,3,168,84,0,873,875,3,
  	62,31,0,874,873,1,0,0,0,874,875,1,0,0,0,875,876,1,0,0,0,876,878,3,168,
  	84,0,877,879,3,114,57,0,878,877,1,0,0,0,878,879,1,0,0,0,879,163,1,0,0,
  	0,880,881,5,28,0,0,881,882,5,43,0,0,882,883,3,62,31,0,883,884,5,44,0,
  	0,884,885,3,108,54,0,885,165,1,0,0,0,886,887,5,31,0,0,887,888,3,108,54,
  	0,888,889,5,28,0,0,889,890,5,43,0,0,890,891,3,62,31,0,891,892,5,44,0,
  	0,892,167,1,0,0,0,893,894,5,80,0,0,894,169,1,0,0,0,104,174,180,196,203,
  	205,209,219,223,227,238,247,254,267,271,280,301,322,335,339,345,349,356,
  	360,368,372,374,384,388,391,399,403,407,410,418,422,437,439,442,445,447,
  	456,459,467,484,486,493,502,506,513,522,530,537,545,551,575,580,582,591,
  	597,603,607,612,619,628,631,634,641,651,655,661,665,670,677,693,699,711,
  	724,728,732,736,753,760,762,766,771,774,778,780,787,795,800,812,819,826,
  	837,842,846,851,855,861,864,870,874,878
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
    setState(170);
    packageClause();
    setState(171);
    eos();
    setState(180);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 18) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 18)) & 2305843009223262209) != 0)) {
      setState(174);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case AutoTenV1Parser::Function:
        case AutoTenV1Parser::Public:
        case AutoTenV1Parser::At: {
          setState(172);
          functionDecl();
          break;
        }

        case AutoTenV1Parser::Var:
        case AutoTenV1Parser::Type: {
          setState(173);
          declaration();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(176);
      eos();
      setState(182);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(183);
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
    setState(185);
    match(AutoTenV1Parser::At);
    setState(186);
    match(AutoTenV1Parser::Package);
    setState(187);
    match(AutoTenV1Parser::Assign);
    setState(188);
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
    setState(190);
    match(AutoTenV1Parser::At);
    setState(191);
    match(AutoTenV1Parser::Identifier);
    setState(196);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(192);
        matchWildcard();
        setState(193);
        match(AutoTenV1Parser::Identifier); 
      }
      setState(198);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
    setState(205);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Assign) {
      setState(199);
      match(AutoTenV1Parser::Assign);
      setState(203);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case AutoTenV1Parser::True_: {
          setState(200);
          match(AutoTenV1Parser::True_);
          break;
        }

        case AutoTenV1Parser::False_: {
          setState(201);
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
          setState(202);
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
    setState(209);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Type: {
        enterOuterAlt(_localctx, 1);
        setState(207);
        typeDecl();
        break;
      }

      case AutoTenV1Parser::Var: {
        enterOuterAlt(_localctx, 2);
        setState(208);
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
    setState(211);
    match(AutoTenV1Parser::Type);
    setState(223);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Identifier: {
        setState(212);
        typeSpec();
        break;
      }

      case AutoTenV1Parser::LeftParen: {
        setState(213);
        match(AutoTenV1Parser::LeftParen);
        setState(219);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == AutoTenV1Parser::Identifier) {
          setState(214);
          typeSpec();
          setState(215);
          eos();
          setState(221);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(222);
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
    setState(225);
    match(AutoTenV1Parser::Identifier);
    setState(227);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Assign) {
      setState(226);
      match(AutoTenV1Parser::Assign);
    }
    setState(229);
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
    setState(238);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(231);
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
        setState(232);
        typeLit();
        break;
      }

      case AutoTenV1Parser::LeftParen: {
        enterOuterAlt(_localctx, 3);
        setState(233);
        match(AutoTenV1Parser::LeftParen);
        setState(234);
        type_();
        setState(235);
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
        setState(237);
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
    setState(240);
    match(AutoTenV1Parser::Tensor);
    setState(254);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Less) {
      setState(241);
      match(AutoTenV1Parser::Less);
      setState(242);
      expression(0);
      setState(247);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(243);
          match(AutoTenV1Parser::Comma);
          setState(244);
          expression(0); 
        }
        setState(249);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
      }
      setState(250);
      match(AutoTenV1Parser::Comma);
      setState(251);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 15360) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(252);
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
    setState(267);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Int8: {
        enterOuterAlt(_localctx, 1);
        setState(256);
        match(AutoTenV1Parser::Int8);
        break;
      }

      case AutoTenV1Parser::Int16: {
        enterOuterAlt(_localctx, 2);
        setState(257);
        match(AutoTenV1Parser::Int16);
        break;
      }

      case AutoTenV1Parser::Int32: {
        enterOuterAlt(_localctx, 3);
        setState(258);
        match(AutoTenV1Parser::Int32);
        break;
      }

      case AutoTenV1Parser::Int64: {
        enterOuterAlt(_localctx, 4);
        setState(259);
        match(AutoTenV1Parser::Int64);
        break;
      }

      case AutoTenV1Parser::Float32: {
        enterOuterAlt(_localctx, 5);
        setState(260);
        match(AutoTenV1Parser::Float32);
        break;
      }

      case AutoTenV1Parser::Float64: {
        enterOuterAlt(_localctx, 6);
        setState(261);
        match(AutoTenV1Parser::Float64);
        break;
      }

      case AutoTenV1Parser::Bool: {
        enterOuterAlt(_localctx, 7);
        setState(262);
        match(AutoTenV1Parser::Bool);
        break;
      }

      case AutoTenV1Parser::String: {
        enterOuterAlt(_localctx, 8);
        setState(263);
        match(AutoTenV1Parser::String);
        break;
      }

      case AutoTenV1Parser::Char: {
        enterOuterAlt(_localctx, 9);
        setState(264);
        match(AutoTenV1Parser::Char);
        break;
      }

      case AutoTenV1Parser::Tensor: {
        enterOuterAlt(_localctx, 10);
        setState(265);
        tensorType();
        break;
      }

      case AutoTenV1Parser::Void: {
        enterOuterAlt(_localctx, 11);
        setState(266);
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
    setState(271);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(269);
      qualifiedIdent();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(270);
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
    setState(280);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(273);
      arrayType();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(274);
      structType();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(275);
      pointerType();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(276);
      functionType();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(277);
      implType();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(278);
      sliceType();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(279);
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
    setState(282);
    match(AutoTenV1Parser::LeftBracket);
    setState(283);
    arrayLength();
    setState(284);
    match(AutoTenV1Parser::RightBracket);
    setState(285);
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
    setState(287);
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
    setState(289);
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
    setState(291);
    match(AutoTenV1Parser::Star);
    setState(292);
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
    setState(294);
    match(AutoTenV1Parser::Impl);
    setState(295);
    match(AutoTenV1Parser::LeftBrace);
    setState(301);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 35) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 35)) & 17592186044481) != 0)) {
      setState(296);
      functionDecl();
      setState(297);
      match(AutoTenV1Parser::Semi);
      setState(303);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(304);
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
    setState(306);
    match(AutoTenV1Parser::LeftBracket);
    setState(307);
    match(AutoTenV1Parser::RightBracket);
    setState(308);
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
    setState(310);
    match(AutoTenV1Parser::Map);
    setState(311);
    match(AutoTenV1Parser::LeftBracket);
    setState(312);
    type_();
    setState(313);
    match(AutoTenV1Parser::RightBracket);
    setState(314);
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
    setState(322);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(316);
      match(AutoTenV1Parser::Identifier);
      setState(317);
      parameters();
      setState(318);
      result();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(320);
      match(AutoTenV1Parser::Identifier);
      setState(321);
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
    setState(324);
    match(AutoTenV1Parser::Function);
    setState(325);
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
    setState(327);
    match(AutoTenV1Parser::Var);
    setState(339);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Identifier: {
        setState(328);
        varSpec();
        break;
      }

      case AutoTenV1Parser::LeftParen: {
        setState(329);
        match(AutoTenV1Parser::LeftParen);
        setState(335);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == AutoTenV1Parser::Identifier) {
          setState(330);
          varSpec();
          setState(331);
          eos();
          setState(337);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(338);
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
    setState(341);
    identifierList();
    setState(349);
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
        setState(342);
        type_();
        setState(345);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == AutoTenV1Parser::Assign) {
          setState(343);
          match(AutoTenV1Parser::Assign);
          setState(344);
          expressionList();
        }
        break;
      }

      case AutoTenV1Parser::Assign: {
        setState(347);
        match(AutoTenV1Parser::Assign);
        setState(348);
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
    setState(356);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(351);
      parameters();
      setState(352);
      match(AutoTenV1Parser::ArrowReturnType);
      setState(353);
      result();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(355);
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
    setState(360);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(358);
      parameters();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(359);
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
    setState(362);
    match(AutoTenV1Parser::LeftParen);
    setState(374);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2297051591474944) != 0) || ((((_la - 81) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 81)) & 7) != 0)) {
      setState(363);
      parameterDecl();
      setState(368);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(364);
          match(AutoTenV1Parser::Comma);
          setState(365);
          parameterDecl(); 
        }
        setState(370);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
      }
      setState(372);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Comma) {
        setState(371);
        match(AutoTenV1Parser::Comma);
      }
    }
    setState(376);
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
    setState(378);
    match(AutoTenV1Parser::LeftBracket);
    setState(379);
    expression(0);
    setState(380);
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
    setState(382);
    match(AutoTenV1Parser::LeftBracket);
    setState(399);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      setState(384);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 79)) & 21) != 0)) {
        setState(383);
        expression(0);
      }
      setState(386);
      match(AutoTenV1Parser::Colon);
      setState(388);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 79)) & 21) != 0)) {
        setState(387);
        expression(0);
      }
      break;
    }

    case 2: {
      setState(391);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 79)) & 21) != 0)) {
        setState(390);
        expression(0);
      }
      setState(393);
      match(AutoTenV1Parser::Colon);
      setState(394);
      expression(0);
      setState(395);
      match(AutoTenV1Parser::Colon);
      setState(396);
      expression(0);
      break;
    }

    case 3: {
      setState(398);
      expression(0);
      break;
    }

    default:
      break;
    }
    setState(422);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Comma) {
      setState(401);
      match(AutoTenV1Parser::Comma);
      setState(418);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
      case 1: {
        setState(403);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 79)) & 21) != 0)) {
          setState(402);
          expression(0);
        }
        setState(405);
        match(AutoTenV1Parser::Colon);
        setState(407);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 79)) & 21) != 0)) {
          setState(406);
          expression(0);
        }
        break;
      }

      case 2: {
        setState(410);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 79)) & 21) != 0)) {
          setState(409);
          expression(0);
        }
        setState(412);
        match(AutoTenV1Parser::Colon);
        setState(413);
        expression(0);
        setState(414);
        match(AutoTenV1Parser::Colon);
        setState(415);
        expression(0);
        break;
      }

      case 3: {
        setState(417);
        expression(0);
        break;
      }

      default:
        break;
      }
      setState(424);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(425);
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
    setState(427);
    match(AutoTenV1Parser::Dot);
    setState(428);
    match(AutoTenV1Parser::LeftParen);
    setState(429);
    type_();
    setState(430);
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
    setState(432);
    match(AutoTenV1Parser::LeftParen);
    setState(447);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 21) != 0)) {
      setState(439);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
      case 1: {
        setState(433);
        expressionList();
        break;
      }

      case 2: {
        setState(434);
        nonNamedType();
        setState(437);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
        case 1: {
          setState(435);
          match(AutoTenV1Parser::Comma);
          setState(436);
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
      setState(442);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Ellipsis) {
        setState(441);
        match(AutoTenV1Parser::Ellipsis);
      }
      setState(445);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Comma) {
        setState(444);
        match(AutoTenV1Parser::Comma);
      }
    }
    setState(449);
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
    setState(451);
    nonNamedType();
    setState(452);
    match(AutoTenV1Parser::Dot);
    setState(453);
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
    setState(456);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      setState(455);
      identifierList();
      break;
    }

    default:
      break;
    }
    setState(459);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Ellipsis) {
      setState(458);
      match(AutoTenV1Parser::Ellipsis);
    }
    setState(461);
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
    setState(467);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      setState(464);
      primaryExpr(0);
      break;
    }

    case 2: {
      setState(465);
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
      setState(466);
      expression(6);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(486);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(484);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(469);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(470);
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
          setState(471);
          expression(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(472);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(473);
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
          setState(474);
          expression(5);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(475);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(476);
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
          setState(477);
          expression(4);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(478);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(479);
          match(AutoTenV1Parser::AndAnd);
          setState(480);
          expression(3);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(481);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(482);
          match(AutoTenV1Parser::OrOr);
          setState(483);
          expression(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(488);
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
    setState(493);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      setState(490);
      operand();
      break;
    }

    case 2: {
      setState(491);
      conversion();
      break;
    }

    case 3: {
      setState(492);
      methodExpr();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(506);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<PrimaryExprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RulePrimaryExpr);
        setState(495);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(502);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
        case 1: {
          setState(496);
          match(AutoTenV1Parser::Dot);
          setState(497);
          match(AutoTenV1Parser::Identifier);
          break;
        }

        case 2: {
          setState(498);
          index();
          break;
        }

        case 3: {
          setState(499);
          slice_();
          break;
        }

        case 4: {
          setState(500);
          typeAssertion();
          break;
        }

        case 5: {
          setState(501);
          arguments();
          break;
        }

        default:
          break;
        } 
      }
      setState(508);
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
    setState(509);
    nonNamedType();
    setState(510);
    match(AutoTenV1Parser::LeftParen);
    setState(511);
    expression(0);
    setState(513);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Comma) {
      setState(512);
      match(AutoTenV1Parser::Comma);
    }
    setState(515);
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
    setState(522);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Function:
      case AutoTenV1Parser::Struct:
      case AutoTenV1Parser::Impl:
      case AutoTenV1Parser::LeftBracket:
      case AutoTenV1Parser::Star:
      case AutoTenV1Parser::Map: {
        enterOuterAlt(_localctx, 1);
        setState(517);
        typeLit();
        break;
      }

      case AutoTenV1Parser::LeftParen: {
        enterOuterAlt(_localctx, 2);
        setState(518);
        match(AutoTenV1Parser::LeftParen);
        setState(519);
        nonNamedType();
        setState(520);
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
    setState(530);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(524);
      literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(525);
      operandName();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(526);
      match(AutoTenV1Parser::LeftParen);
      setState(527);
      expression(0);
      setState(528);
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
    setState(532);
    expression(0);
    setState(537);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(533);
        match(AutoTenV1Parser::Comma);
        setState(534);
        expression(0); 
      }
      setState(539);
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
    setState(540);
    match(AutoTenV1Parser::Identifier);
    setState(545);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Comma) {
      setState(541);
      match(AutoTenV1Parser::Comma);
      setState(542);
      match(AutoTenV1Parser::Identifier);
      setState(547);
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
    setState(551);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(548);
      basicLit();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(549);
      compositeLit();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(550);
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
    setState(553);
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
    setState(555);
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
    setState(557);
    match(AutoTenV1Parser::Identifier);
    setState(558);
    match(AutoTenV1Parser::Dot);
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
    setState(561);
    literalType();
    setState(562);
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
    setState(575);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(564);
      structType();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(565);
      arrayType();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(566);
      elementType();
      setState(567);
      match(AutoTenV1Parser::LeftBracket);
      setState(568);
      match(AutoTenV1Parser::Ellipsis);
      setState(569);
      match(AutoTenV1Parser::RightBracket);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(571);
      sliceType();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(572);
      tensorType();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(573);
      mapType();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(574);
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
    setState(577);
    match(AutoTenV1Parser::LeftBrace);
    setState(582);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346400210624446238) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 21) != 0)) {
      setState(578);
      elementList();
      setState(580);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Comma) {
        setState(579);
        match(AutoTenV1Parser::Comma);
      }
    }
    setState(584);
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
    setState(586);
    keyedElement();
    setState(591);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(587);
        match(AutoTenV1Parser::Comma);
        setState(588);
        keyedElement(); 
      }
      setState(593);
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
    setState(597);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      setState(594);
      key();
      setState(595);
      match(AutoTenV1Parser::Colon);
      break;
    }

    default:
      break;
    }
    setState(599);
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
    setState(603);
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
        setState(601);
        expression(0);
        break;
      }

      case AutoTenV1Parser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(602);
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
    setState(609);
    match(AutoTenV1Parser::Struct);
    setState(610);
    match(AutoTenV1Parser::LeftBrace);
    setState(619);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 41) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 41)) & 4398046512129) != 0)) {
      setState(612);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Public) {
        setState(611);
        match(AutoTenV1Parser::Public);
      }
      setState(614);
      fieldDecl();
      setState(615);
      eos();
      setState(621);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(622);
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
    setState(628);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      setState(624);
      identifierList();
      setState(625);
      type_();
      break;
    }

    case 2: {
      setState(627);
      embeddedField();
      break;
    }

    default:
      break;
    }
    setState(631);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::StringLiteral) {
      setState(630);
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
    setState(634);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Star) {
      setState(633);
      match(AutoTenV1Parser::Star);
    }
    setState(636);
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
    setState(641);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::At) {
      setState(638);
      compileFlags();
      setState(643);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(644);
    match(AutoTenV1Parser::Function);
    setState(645);
    signature();
    setState(646);
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
    setState(651);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::At) {
      setState(648);
      compileFlags();
      setState(653);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(655);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Public) {
      setState(654);
      match(AutoTenV1Parser::Public);
    }
    setState(657);
    match(AutoTenV1Parser::Function);
    setState(658);
    match(AutoTenV1Parser::Identifier);
    setState(659);
    signature();
    setState(661);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::LeftBrace) {
      setState(660);
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
    setState(663);
    match(AutoTenV1Parser::LeftBrace);
    setState(665);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346400561729896222) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 23) != 0)) {
      setState(664);
      statementList();
    }
    setState(667);
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
    setState(675); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(670);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AutoTenV1Parser::Semi) {
        setState(669);
        match(AutoTenV1Parser::Semi);
      }
      setState(672);
      statement();
      setState(673);
      eos();
      setState(677); 
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
  enterRule(_localctx, 112, AutoTenV1Parser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(693);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(679);
      declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(680);
      labeledStmt();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(681);
      simpleStmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(682);
      returnStmt();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(683);
      breakStmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(684);
      continueStmt();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(685);
      gotoStmt();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(686);
      fallthroughStmt();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(687);
      block();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(688);
      ifStmt();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(689);
      switchStmt();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(690);
      forStmt();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(691);
      whileStmt();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(692);
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
    setState(699);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(695);
      incDecStmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(696);
      assignment();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(697);
      expressionStmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(698);
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
    setState(701);
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
    setState(703);
    expression(0);
    setState(704);
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
    setState(706);
    expressionList();
    setState(707);
    assign_op();
    setState(708);
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
    setState(711);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 49) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 49)) & 49407) != 0)) {
      setState(710);
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
    setState(713);
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
    setState(715);
    identifierList();
    setState(716);
    match(AutoTenV1Parser::DeclareAssign);
    setState(717);
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
    setState(719);
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
    setState(721);
    match(AutoTenV1Parser::Identifier);
    setState(722);
    match(AutoTenV1Parser::Colon);
    setState(724);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346400561729896222) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 21) != 0)) {
      setState(723);
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
    setState(726);
    match(AutoTenV1Parser::Return);
    setState(728);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 21) != 0)) {
      setState(727);
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
    setState(730);
    match(AutoTenV1Parser::Break);
    setState(732);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Identifier) {
      setState(731);
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
    setState(734);
    match(AutoTenV1Parser::Continue);
    setState(736);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Identifier) {
      setState(735);
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
    setState(738);
    match(AutoTenV1Parser::Goto);
    setState(739);
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
    setState(741);
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
    setState(743);
    match(AutoTenV1Parser::If);
    setState(744);
    match(AutoTenV1Parser::LeftParen);
    setState(753);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 80, _ctx)) {
    case 1: {
      setState(745);
      expression(0);
      break;
    }

    case 2: {
      setState(746);
      eos();
      setState(747);
      expression(0);
      break;
    }

    case 3: {
      setState(749);
      simpleStmt();
      setState(750);
      eos();
      setState(751);
      expression(0);
      break;
    }

    default:
      break;
    }
    setState(755);
    match(AutoTenV1Parser::RightParen);
    setState(756);
    block();
    setState(762);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AutoTenV1Parser::Else) {
      setState(757);
      match(AutoTenV1Parser::Else);
      setState(760);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case AutoTenV1Parser::If: {
          setState(758);
          ifStmt();
          break;
        }

        case AutoTenV1Parser::LeftBrace: {
          setState(759);
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
    setState(766);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 83, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(764);
      exprSwitchStmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(765);
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
    setState(768);
    match(AutoTenV1Parser::Switch);
    setState(769);
    match(AutoTenV1Parser::LeftParen);
    setState(780);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 87, _ctx)) {
    case 1: {
      setState(771);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 79)) & 21) != 0)) {
        setState(770);
        expression(0);
      }
      break;
    }

    case 2: {
      setState(774);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 79)) & 21) != 0)) {
        setState(773);
        simpleStmt();
      }
      setState(776);
      eos();
      setState(778);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 79)) & 21) != 0)) {
        setState(777);
        expression(0);
      }
      break;
    }

    default:
      break;
    }
    setState(782);
    match(AutoTenV1Parser::RightParen);
    setState(783);
    match(AutoTenV1Parser::LeftBrace);
    setState(787);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Case

    || _la == AutoTenV1Parser::Default) {
      setState(784);
      exprCaseClause();
      setState(789);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(790);
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
    setState(792);
    exprSwitchCase();
    setState(793);
    match(AutoTenV1Parser::Colon);
    setState(795);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346400561729896222) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 23) != 0)) {
      setState(794);
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
    setState(800);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Case: {
        enterOuterAlt(_localctx, 1);
        setState(797);
        match(AutoTenV1Parser::Case);
        setState(798);
        expressionList();
        break;
      }

      case AutoTenV1Parser::Default: {
        enterOuterAlt(_localctx, 2);
        setState(799);
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
    setState(802);
    match(AutoTenV1Parser::Switch);
    setState(803);
    match(AutoTenV1Parser::LeftParen);
    setState(812);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 91, _ctx)) {
    case 1: {
      setState(804);
      typeSwitchGuard();
      break;
    }

    case 2: {
      setState(805);
      eos();
      setState(806);
      typeSwitchGuard();
      break;
    }

    case 3: {
      setState(808);
      simpleStmt();
      setState(809);
      eos();
      setState(810);
      typeSwitchGuard();
      break;
    }

    default:
      break;
    }
    setState(814);
    match(AutoTenV1Parser::RightParen);
    setState(815);
    match(AutoTenV1Parser::LeftBrace);
    setState(819);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Case

    || _la == AutoTenV1Parser::Default) {
      setState(816);
      typeCaseClause();
      setState(821);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(822);
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
    setState(826);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 93, _ctx)) {
    case 1: {
      setState(824);
      match(AutoTenV1Parser::Identifier);
      setState(825);
      match(AutoTenV1Parser::DeclareAssign);
      break;
    }

    default:
      break;
    }
    setState(828);
    primaryExpr(0);
    setState(829);
    match(AutoTenV1Parser::Dot);
    setState(830);
    match(AutoTenV1Parser::LeftParen);
    setState(831);
    match(AutoTenV1Parser::Type);
    setState(832);
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
    setState(834);
    typeSwitchCase();
    setState(835);
    match(AutoTenV1Parser::Colon);
    setState(837);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346400561729896222) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 23) != 0)) {
      setState(836);
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
    setState(842);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AutoTenV1Parser::Case: {
        enterOuterAlt(_localctx, 1);
        setState(839);
        match(AutoTenV1Parser::Case);
        setState(840);
        typeList();
        break;
      }

      case AutoTenV1Parser::Default: {
        enterOuterAlt(_localctx, 2);
        setState(841);
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
    setState(846);
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
        setState(844);
        type_();
        break;
      }

      case AutoTenV1Parser::Nilptr: {
        setState(845);
        match(AutoTenV1Parser::Nilptr);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(855);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AutoTenV1Parser::Comma) {
      setState(848);
      match(AutoTenV1Parser::Comma);
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
      setState(857);
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
    setState(858);
    match(AutoTenV1Parser::For);
    setState(859);
    match(AutoTenV1Parser::LeftParen);
    setState(864);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 100, _ctx)) {
    case 1: {
      setState(861);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 79)) & 21) != 0)) {
        setState(860);
        expression(0);
      }
      break;
    }

    case 2: {
      setState(863);
      forClause();
      break;
    }

    default:
      break;
    }
    setState(866);
    match(AutoTenV1Parser::RightParen);
    setState(867);
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
  enterRule(_localctx, 162, AutoTenV1Parser::RuleForClause);
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
    setState(870);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 21) != 0)) {
      setState(869);
      antlrcpp::downCast<ForClauseContext *>(_localctx)->initStmt = simpleStmt();
    }
    setState(872);
    eos();
    setState(874);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 21) != 0)) {
      setState(873);
      expression(0);
    }
    setState(876);
    eos();
    setState(878);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 346259473136090910) != 0) || ((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & 21) != 0)) {
      setState(877);
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
  enterRule(_localctx, 164, AutoTenV1Parser::RuleWhileStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(880);
    match(AutoTenV1Parser::While);
    setState(881);
    match(AutoTenV1Parser::LeftParen);

    setState(882);
    expression(0);
    setState(883);
    match(AutoTenV1Parser::RightParen);
    setState(884);
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
  enterRule(_localctx, 166, AutoTenV1Parser::RuleDoWhileStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(886);
    match(AutoTenV1Parser::Do);
    setState(887);
    block();
    setState(888);
    match(AutoTenV1Parser::While);
    setState(889);
    match(AutoTenV1Parser::LeftParen);

    setState(890);
    expression(0);
    setState(891);
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
  enterRule(_localctx, 168, AutoTenV1Parser::RuleEos);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(893);
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
