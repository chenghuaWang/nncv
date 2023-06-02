lexer grammar AutoTenV1Lexer;

IntegerLiteral:
	DecimalLiteral Integersuffix?
	| OctalLiteral Integersuffix?
	| HexadecimalLiteral Integersuffix?
	| BinaryLiteral Integersuffix?;

CharacterLiteral:
	('u' | 'U' | 'L')? '\'' Cchar+ '\'';

FloatingLiteral:
	Fractionalconstant Exponentpart? Floatingsuffix?
	| Digitsequence Exponentpart Floatingsuffix?;

StringLiteral:
	Encodingprefix?
    (Rawstring
	|'"' Schar* '"');

BooleanLiteral: False_ | True_;

PointerLiteral: Nullptr;

UserDefinedLiteral:
	UserDefinedIntegerLiteral
	| UserDefinedFloatingLiteral
	| UserDefinedStringLiteral
	| UserDefinedCharacterLiteral;

/* Keywords: Types */

Int8: 'int8';

Int16: 'int16';

Int32: 'int32';

Int64: 'int64';

Float32: 'float32';

Float64: 'float64';

Char: 'char';

Bool: 'bool';

String: 'string';

Tensor: 'Tensor';

Var: 'var';

False_: 'false';

True_: 'true';

Void: 'void';

Nilptr: 'nil';

/* Keywords: Control Flow */

Break: 'break';

If: 'if';

While: 'while';

For: 'for';

Else: 'else';

Do: 'do';

Switch: 'switch';

Case: 'case';

Default: 'default';

/* Keywords: Function */

Function: 'func';

Return: 'return';

/* Keywords: structure */

Struct: 'struct';

/* Keywords: impl */

Impl: 'impl';

/* Keywords: Visibility (All members is defualt private.) */

Public: 'pub';

/* Keywords: Build in functions */

Sizeof: 'sizeof';

/* Operators */

LeftParen: '(';

RightParen: ')';

LeftBracket: '[';

RightBracket: ']';

LeftBrace: '{';

RightBrace: '}';

Plus: '+';

Minus: '-';

Star: '*';

Div: '/';

Mod: '%' | 'mod';

Caret: '^' | 'xor';

And: '&';

Or: '|';

Tilde: '~';

Not: '!' | 'not';

Assign: '=';

Less: '<';

Greater: '>';

PlusAssign: '+=';

MinusAssign: '-=';

StarAssign: '*=';

DivAssign: '/=';

ModAssign: '%=';

XorAssign: '^=';

AndAssign: '&=';

OrAssign: '|=';

LeftShiftAssign: '<<=';

RightShiftAssign: '>>=';

Equal: '==';

NotEqual: '!=';

LessEqual: '<=';

GreaterEqual: '>=';

AndAnd: '&&' | 'and';

OrOr: '||' | 'or';

PlusPlus: '++';

MinusMinus: '--';

Comma: ',';

ArrowReturnType: '->';

Colon: ':';

Dot: '.';

fragment NONZERODIGIT: [1-9];

fragment OCTALDIGIT: [0-7];

fragment HEXADECIMALDIGIT: [0-9a-fA-F];

fragment BINARYDIGIT: [01];

Whitespace: [ \t]+ -> skip;

Newline: ('\r' '\n'? | '\n') -> skip;

BlockComment: '#!' .!? '!#' -> skip;

LineComment: '#' ~ [\r\n]! -> skip;