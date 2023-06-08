parser grammar AutoTenV1Parser;

options {
	tokenVocab = AutoTenV1Lexer;
	language = Cpp;
}

// translationUnit: declarationseq? EOF;

// primaryExpression: literal+ | This | LeftParen expression RightParen | idExpression |
// lambdaExpression;

// idExpression: unqualifiedId | qualifiedId;

//===----------------------------------------------------------------------===//
// Statements collection And Expressions.

unaryExpression:
	(PlusPlus | MinusMinus | unaryOperator | Sizeof) unaryExpression
	| Sizeof (LeftParen theTypeId RightParen);

unaryOperator: Or | Star | And | Plus | Tilde | Minus | Not;

castExpression:
	unaryExpression
	| LeftParen theTypeId RightParen castExpression;

pointerMemberExpression:
	castExpression ((DotStar | ArrowStar) castExpression)*;

multiplicativeExpression:
	pointerMemberExpression (
		(Star | Div | Mod) pointerMemberExpression
	)*;

additiveExpression:
	multiplicativeExpression (
		(Plus | Minus) multiplicativeExpression
	)*;

shiftExpression:
	additiveExpression (shiftOperator additiveExpression)*;

shiftOperator: Greater Greater | Less Less;

relationalExpression:
	shiftExpression (
		(Less | Greater | LessEqual | GreaterEqual) shiftExpression
	)*;

equalityExpression:
	relationalExpression (
		(Equal | NotEqual) relationalExpression
	)*;

andExpression: equalityExpression (And equalityExpression)*;

exclusiveOrExpression: andExpression (Caret andExpression)*;

inclusiveOrExpression:
	exclusiveOrExpression (Or exclusiveOrExpression)*;

logicalAndExpression:
	inclusiveOrExpression (AndAnd inclusiveOrExpression)*;

logicalOrExpression:
	logicalAndExpression (OrOr logicalAndExpression)*;

assignmentExpression:
	logicalOrExpression assignmentOperator initializerClause;

assignmentOperator:
	Assign
	| StarAssign
	| DivAssign
	| ModAssign
	| PlusAssign
	| MinusAssign
	| RightShiftAssign
	| LeftShiftAssign
	| AndAssign
	| XorAssign
	| OrAssign;

expression: assignmentExpression (Comma assignmentExpression)*;

expressionStatement: expression? Semi;

statement:;

initializerClause:;

//===----------------------------------------------------------------------===//
// The function body

compoundStatement: LeftBrace statementSeq? RightBrace;

statementSeq: statement+;

functionBody: compoundStatement;

//===----------------------------------------------------------------------===//
// Identifier

theTypeId:;

//===----------------------------------------------------------------------===//
// Attribute Declaration

//===----------------------------------------------------------------------===//
// The Lexer Part

theOperator:
	Plus
	| Minus
	| Star
	| Div
	| Mod
	| Caret
	| And
	| Or
	| Tilde
	| Not
	| Assign
	| Greater
	| Less
	| GreaterEqual
	| PlusAssign
	| MinusAssign
	| StarAssign
	| ModAssign
	| XorAssign
	| AndAssign
	| OrAssign
	| Less Less
	| Greater Greater
	| RightShiftAssign
	| LeftShiftAssign
	| Equal
	| NotEqual
	| LessEqual
	| AndAnd
	| OrOr
	| PlusPlus
	| MinusMinus
	| Comma
	| LeftParen RightParen
	| LeftBracket RightBracket;

literal:
	IntegerLiteral
	| CharacterLiteral
	| FloatingLiteral
	| StringLiteral
	| BooleanLiteral
	| PointerLiteral
	| UserDefinedLiteral;
