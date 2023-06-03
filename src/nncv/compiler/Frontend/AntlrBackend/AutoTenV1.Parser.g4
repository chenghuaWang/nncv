parser grammar AutoTenV1Parser;

options {
	tokenVocab = AutoTenV1Lexer;
}

translationUnit: declarationseq? EOF;

primaryExpression:
	literal+
	| This
	| LeftParen expression RightParen
	| idExpression
	| lambdaExpression;

idExpression: unqualifiedId | qualifiedId;

