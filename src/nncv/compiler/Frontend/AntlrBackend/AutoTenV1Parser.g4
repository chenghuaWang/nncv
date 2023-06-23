parser grammar AutoTenV1Parser;

options {
	tokenVocab = AutoTenV1Lexer;
	language = Cpp;
}

sourceFile:
	packageClause eos ((functionDecl | declaration) eos)* EOF;

packageClause: At Package Assign StringLiteral;

// -- compile ctrl blok --
compileFlags:
	At Identifier (.Identifier)* (
		Assign (True_ | False_ | expression)
	)?;

// -- declaration --
declaration: typeDecl | varDecl;

typeDecl:
	Type (typeSpec | LeftParen (typeSpec eos)* RightParen);

typeSpec: Identifier Assign? type_;

// -- type --
type_:
	typeName
	| typeLit
	| LeftParen type_ RightParen
	| builtinType;

tensorType:
	Tensor (
		Less expression (Comma expression)* Comma (
			Float32
			| Float64
			| Int32
			| Int64
		) Greater
	)?;

builtinType:
	Int8
	| Int16
	| Int32
	| Int64
	| Float32
	| Float64
	| Bool
	| String
	| Char
	| tensorType
	| Void;

typeName: qualifiedIdent | Identifier;

typeLit:
	arrayType
	| structType
	| pointerType
	| functionType
	| implType
	| sliceType
	| mapType;

arrayType: LeftBracket arrayLength RightBracket elementType;

arrayLength: expression;

elementType: type_;

pointerType: Star type_;

implType: Impl LeftBrace (functionDecl Semi)* RightBrace;

sliceType: LeftBracket RightBracket elementType;

mapType: Map LeftBracket type_ RightBracket elementType;

methodSpec:
	Identifier parameters result
	| Identifier parameters;

functionType: Function signature;

varDecl: Var (varSpec | LeftParen (varSpec eos)* RightParen);

varSpec:
	identifierList (
		type_ (Assign expressionList)?
		| Assign expressionList
	);

// -- trivial --
signature: parameters ArrowReturnType result | parameters;

result: parameters | type_;

parameters:
	LeftParen (parameterDecl (Comma parameterDecl)* Comma?)? RightParen;

index: LeftBracket expression RightBracket;

slice_:
	LeftBracket (
		expression? Colon expression?
		| expression? Colon expression Colon expression
		| expression
	) (
		Comma (
			expression? Colon expression?
			| expression? Colon expression Colon expression
			| expression
		)
	)* RightBracket;

typeAssertion: Dot LeftParen type_ RightParen;

arguments:
	LeftParen (
		(expressionList | nonNamedType (Comma expressionList)?) Ellipsis? Comma?
	)? RightParen;

methodExpr: nonNamedType Dot Identifier;

parameterDecl: identifierList? Ellipsis? type_;

// -- expressions --
expression:
	primaryExpr
	| unary_op = (Plus | Minus | Not | Caret | Star | And) expression
	| expression mul_op = (
		Star
		| Div
		| Mod
		| LeftShift
		| RightShift
		| And
	) expression
	| expression add_op = (Plus | Minus | Or | Caret) expression
	| expression rel_op = (
		Equal
		| NotEqual
		| Less
		| LessEqual
		| Greater
		| GreaterEqual
	) expression
	| expression AndAnd expression
	| expression OrOr expression;

primaryExpr:
	operand
	| conversion
	| methodExpr
	| primaryExpr (
		Dot Identifier
		| index
		| slice_
		| typeAssertion
		| arguments
	);

conversion: nonNamedType LeftParen expression Comma? RightParen;

nonNamedType: typeLit | LeftParen nonNamedType RightParen;

operand:
	literal
	| operandName
	| LeftParen expression RightParen;

expressionList: expression (Comma expression)*;

identifierList: Identifier (Comma Identifier)*;

// -- literal --
literal: basicLit | compositeLit | functionLit;

basicLit:
	Nilptr
	| IntegerLiteral
	| StringLiteral
	| FloatingLiteral
	| CharacterLiteral;

operandName: Identifier;

qualifiedIdent: Identifier Dot Identifier;

compositeLit: literalType literalValue;

literalType:
	structType
	| arrayType
	| elementType LeftBracket Ellipsis RightBracket
	| sliceType
	| tensorType
	| mapType
	| typeName;

literalValue: LeftBrace (elementList Comma?)? RightBrace;

elementList: keyedElement (Comma keyedElement)*;

keyedElement: (key Colon)? element;

key: expression | literalValue;

element: expression | literalValue;

// -- Struct / Impl --
structType:
	Struct LeftBrace (Public? fieldDecl eos)* RightBrace;

fieldDecl: (identifierList type_ | embeddedField) tag = StringLiteral?;

embeddedField: Star? typeName;

// -- function --
functionLit: compileFlags* Function signature block;

functionDecl:
	compileFlags* Public? Function Identifier signature block?;

block: LeftBrace statementList? RightBrace;

// -- statement --
statementList: ((Semi?) statement eos)+;

statement:
	declaration
	| labeledStmt
	| simpleStmt
	| returnStmt
	| breakStmt
	| continueStmt
	| gotoStmt
	| fallthroughStmt
	| block
	| ifStmt
	| switchStmt
	| forStmt
	| whileStmt
	| doWhileStmt;

simpleStmt:
	incDecStmt
	| assignment
	| expressionStmt
	| shortVarDecl;

expressionStmt: expression;

incDecStmt: expression (PlusPlus | PlusPlus);

assignment: expressionList assign_op expressionList;

assign_op: (
		Plus
		| Minus
		| Or
		| Caret
		| Star
		| Div
		| Mod
		| LeftShift
		| RightShift
		| And
	)? Assign;

shortVarDecl: identifierList DeclareAssign expressionList;

emptyStmt: Semi;

labeledStmt: Identifier Colon statement?;

returnStmt: Return expressionList?;

breakStmt: Break Identifier?;

continueStmt: Continue Identifier?;

gotoStmt: Goto Identifier;

fallthroughStmt: Fallthrough;

ifStmt:
	If LeftParen (
		expression
		| eos expression
		| simpleStmt eos expression
	) RightParen block (Else (ifStmt | block))?;

switchStmt: exprSwitchStmt | typeSwitchStmt;

exprSwitchStmt:
	Switch LeftParen (expression? | simpleStmt? eos expression?) RightParen LeftBrace exprCaseClause
		* RightBrace;

exprCaseClause: exprSwitchCase Colon statementList?;

exprSwitchCase: Case expressionList | Default;

typeSwitchStmt:
	Switch LeftParen (
		typeSwitchGuard
		| eos typeSwitchGuard
		| simpleStmt eos typeSwitchGuard
	) RightParen LeftBrace typeCaseClause* RightBrace;

typeSwitchGuard: (Identifier DeclareAssign)? primaryExpr Dot LeftParen Type RightParen;

typeCaseClause: typeSwitchCase Colon statementList?;

typeSwitchCase: Case typeList | Default;

typeList: (type_ | Nilptr) (Comma (type_ | Nilptr))*;

forStmt:
	For LeftParen (expression? | forClause) RightParen block;

forClause:
	initStmt = simpleStmt? eos expression? eos postStmt = simpleStmt?;

whileStmt: While LeftParen (expression) RightParen block;

doWhileStmt: Do block While LeftParen (expression) RightParen;

// -- eos(end of sentence) --
eos: Semi;