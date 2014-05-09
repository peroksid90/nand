#!/usr/bin/env perl
use strict;
use v5.14;

my @tokenzer = <>;
shift @tokenzer;
pop @tokenzer;

Class(\@tokenzer);

sub Class {
	my $token = shift;
	print "<class>\n";
	print shift @{$token};			#class
	print shift @{$token};			#className
	print shift @{$token};			# {
	while(${$token}[0] =~ /static|field/) {	#classVarDec*
		ClassVarDec($token);
	}
	if(${$token}[0] =~ /(constructor|function|method)/ and ${$token}[1] =~ /(void|int|char|boolean|identifier)/) {	#subroutineDec*
		subroutineDec($token);
	} 
	print shift @{$token};			# }
	print "</class>\n";
}

sub ClassVarDec {
	my $token = shift;
	print "<classVarDec>\n";
	print shift @{$token};		#static | field
	print shift @{$token};		#type
	print shift @{$token};		#varName
	while(${$token}[0] =~ /\,/) { 	#(, varName)*
		print shift @{$token};	# ,
		print shift @{$token};	# varName
	}
	print shift @{$token};		# ;
	print "</classVarDec>\n";
}

sub subroutineDec {
	my $token = shift;
	print "<subroutineDec>\n";
	print shift @{$token};		#constructor|function|method
	print shift @{$token};		#void|type
	print shift @{$token};		#subroutineName
	print shift @{$token};		#(
	parameterList($token);	#parameterList
	print shift @{$token};		#)
	subroutineBody($token);	#subroutineBody
	print "</subroutineDec>\n";
}

sub parameterList {
	my $token = shift;
	print "<parameterList>\n";
	if(${$token}[0] =~ /int|char|boolean|identifier/) {
		print shift @{$token};		# type
		print shift @{$token};		# varName
		while(${$token}[0] =~ /\,/) {
			print shift @{$token};	# ,
			print shift @{$token};	# type
			print shift @{$token};	# varName
		}
	}
	print "</parameterList>\n";
}


sub subroutineBody {
	my $token = shift;
	print "<subroutineBody>\n";
	print shift @{$token};		# {
	while(${$token}[0] =~ /var/) { # varDec*
		varDec($token);
	}	
	parseStatement($token);	# statements
	print shift @{$token};		# }
	print "</subroutineBody>\n";
}

sub varDec {
	my $token = shift;
	print "<varDec>\n";
	print shift @{$token};		# var
	print shift @{$token};		# type
	print shift @{$token};		# varName
	while(${$token}[0] =~ /,/) {
		print shift @{$token};	# ,
		print shift @{$token};	# varName
	}
	print shift @{$token};		# ;
	print "</varDec>\n";
}

sub parseStatement {
	my $token = shift;
	while(${$token}[0] =~ /let|if|while|do|return/) {
		print "<statements>\n";
		given(${$token}[0]) {
			when(/let/) {
				letStatement($token);
			}
			when(/if/) {
				ifStatement($token);
			}
			when(/while/) {
				whileStatement($token);
			}
			when(/do/) {
				doStatement($token);
			}
			when(/return/) {
				returnStatement($token);
			}
		}
		print "</statements>\n";
	}
}

sub letStatement {
	my $token = shift;
	print "<letStatement>\n";
	print shift @{$token};				#let
	print shift @{$token};				#varName
		if(${$token}[0] =~ /\[/) {
			print shift @{$token};		# [
			parseExpression($token);
			print shift @{$token};		# ]
		}
	print shift @{$token};				# =
	parseExpression($token);
	print shift @{$token};				# ;
	print "</letStatement>\n";
}

sub ifStatement {
	my $token = shift;
	print "<ifStatement>\n";
	print shift @{$token};				#if
	print shift @{$token};				# (
	parseExpression($token);			# expression
	print shift @{$token};				# )
	print shift @{$token};				# {
	parseStatement($token);			# statements
	print shift;				# }
	if(${$token}[0] =~ /else/) {
		print shift @{$token};			# else
		print shift @{$token};			# {
		parseStatement($token);		# statements
		print shift @{$token};			# }
	}
	print "</ifStatement>\n";
}

sub whileStatement {
	my $token = shift;
	print "<whileStatement>\n";
	print shift @{$token};				#while
	print shift @{$token};				# (
	parseExpression($token);			# expression
	print shift @{$token};				# )
	print shift @{$token};				# {
	parseStatements($token);			# statements
	print shift @{$token};				# }
	print "</whileStatement>\n";
}

sub doStatement {
	my $token = shift;
	print "<doStatement>\n";
	print shift @{$token};				# do
	subroutineCall($token);			# subroutineCall
	print "<doStatement>\n";
}

sub ReturnStatement {
	my $token = shift;
	print "<ReturnStatement>\n";
	print shift @{$token};				# return
	parseExpression($token);			# expression?
	print "</ReturnStatement>\n";
}

sub parseExpression {
	my $token = shift;
	if( (${$token}[0] =~ /integerConstant|stringConstant|true|false|null|this/) or (${$token}[0] =~ /identifier/ and ${$token}[0] =~ /\[/) 
	or (${$token}[0] =~ /identifier/ and ${$token}[1] !~ /\(/) or (${$token}[0] =~ /identifier/ and ${$token}[1] =~ /\(/) 
	or (${$token}[0] =~ /\(/) or (${$token}[0] =~ /\-|\-/) ) {
		print "<expression>\n";
		parseTerm($token);
		while(${$token}[0] =~ /\+|\-|\*|\/|\&|\||\<|\>|\=/) {	#(op term)*
			print shift @{$token} . "!!!!!!!!!!!!!!!\n";				#op
			parseTerm($token);		
		}
		print "</expression>\n";
	}
}

sub expressionList {
	my $token = shift;
	print "<expressionList>\n";
	parseExpression($token);
	while(${$token}[0] =~ /\,/) {
		parseExpression($token);
	}
	print "</expressionList>\n";
}

sub subroutineCall {
	my $token = shift;
	#print "<subroutineCall>\n";
	if(${$token}[0] =~ /identifier/ and ${$token}[1] =~ /\(/ ) {
		print shift @{$token};	#subroutineName
		print shift @{$token};	# (
		expressionList($token);
		print shift @{$token};	# )
	} else {
		print shift @{$token};	#className | varName
		print shift @{$token};	# .
		print shift @{$token};	#subroutineName
		print shift @{$token};	# (
		expressionList($token);
		print shift @{$token};	# )
	}
	#print "</subroutineCall>\n";
}

sub parseTerm {
	my $token = shift;
	print "<term>\n";
	if(${$token}[0] =~ /integerConstant|stringConstant|true|false|null|this/ ) {
		print shift @{$token};
	}
	if(${$token}[0] =~ /identifier/ and ${$token}[1] =~ /\[/) {
		print shift @{$token};		#varName
		print shift @{$token};		# [
		parseExpression($token);	# expression
		print shift @{$token};		# ]
	}
	if(${$token}[0] =~ /identifier/ and ${$token}[1] !~ /\(/) {
		print shift @{$token};		#varName
	}
	if(${$token}[0] =~ /identifier/ and ${$token}[1] =~ /\(/) {
		subroutineCall($token);	
	}
	if(${$token}[0] =~ /\(/) {
		parseExpression($token);	#(expression)
	}
	if(${$token}[0] =~ /\-|\-/) {
		print shift @{$token};		#unaryOp -|-
		parseTerm($token);		#term
	}
	print "</term>\n";
}
