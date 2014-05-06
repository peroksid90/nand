use strict;

sub Class {
	print "<class>\n";
	print shift;			#class
	my $className = shift;
	print $className;		#className
	print shift;			# {
	$className =~ />(.*)</;
	$className = $1;
	while($_[0] =~ /static|field/) {	#classVarDec*
		ClassVarDec(@_);
	}
	while($_[0] =~ /(constructor|function|method)(void|int|char|boolean|$className)/) {	#subroutineDec*
		subroutineDec(@_);
	} 
	print shift;			# }
	print "</class>\n";q
}

sub ClassVarDec {
	print "<classVarDec>\n"
	print shift;		#static | field
	print shift;		#type
	print shift;		#varName
	while($_[0] =~ /\,/) { 	#(, varName)*
		print shift;	# ,
		print shift;	# varName
	}
	print shift;		# ;
	print "</classVarDec>\n";
}

sub subroutineDec {
	print "<subroutineDec>\n";
	print shift;		#constructor|function|method
	print shift;		#void|type
	print shift;		#subroutineName
	print shift;		#(
	print shift;		#parameterList
	print shift;		#)
	subroutineBody(@_);	#subroutineBody
	print "</subroutineDec>\n";
}

sub varDec {
	print "<varDec>\n";
	print shift;		# var
	print shift;		# type
	print shift;		# varName
	while($_[0] =~ /,/) {
		print shift;	# ,
		print shift;	# varName
	}
	print shift;		# ;
	print "</varDec>\n";
}

sub subroutineBody {
	print shift;		# {
	while($_[0] ~= /var/) { # varDec*
		varDec(@_);
	}	
	parseStetment(@_);	# statements
	print shift;		# }
}

sub parameterList {
	print "<parameterList>\n";
	if($_[0] =~ /int|char|boolean|identifier/) {
		print shift;		# type
		print shift;		# varName
		while($_[0] =~ /,/) {
			print shift;	# ,
			print shift;	# type
			print shift;	# varName
		}
	}
	print "</parameterList>\n";
}

##############!!!!!!!!!!!!!!!!!!!!
sub subroutineBody {
	print "<subroutineBody>\n";
	print shift;			# {
	while($_[0] =~ /var/) {		#varDec*
		print shift;		#var
		print shift;		#type
		print shift;		#varName
		while($_[0] =~ /\,/) {	#(, varName)*
			print shift;	# ,
			print shift;	#varName
		}
		print shift;	# ;
	}
	parseStatement(@_);
	print shift;	# }
	print "</subroutineBody>\n";
}

sub parseStatement {
	print "<statements>\n";
	if($_[0] =~ /let/) {
		letStatement(@_);
	}
	if($_[0] =~ /if/) {
		ifStatement(@_);
	}
	if($_[0] =~ /while/) {
		whileStatement(@_);
	}
	if($_[0] =~ /do/) {
		doStatement(@_);
	}
	if($_[0] =~ /return/) {
		returnStatement(@_);
	}
	print "</statements>\n";
}

sub letStatement {
	print "<letStatement>\n";
	print shift;				#let
	print shift;				#varName
		if($_[0] =~ /\[/) {
			print shift;		# [
			parseExpression(@_);
			print shift;		# ]
		}
	print shift;				# =
	parseExpression(@_);
	print shift;				# ;
	print "</letStatement>\n";
}

sub ifStatement {
	print "<ifStatement>\n";
	print shift;				#if
	print shift;				# (
	parseExpression(@_);			# expression
	print shift;				# )
	print shift;				# {
	parseStatement(@_);			# statements
	print shift;				# }
	if($_[0] =~ /else/) {
		print shift;			# else
		print shift;			# {
		parseStatement(@_);		# statements
		print shift;			# }
	}
	print "</ifStatement>\n";
}

sub whileStatement {
	print "<whileStatement>\n";
	print shift;				#while
	print shift;				# (
	parseExpression(@_);			# expression
	print shift;				# )
	print shift;				# {
	parseExpression(@_);			# expression
	print shift;				# }
	print "</whileStatement>\n";
}

sub doStatement {
	print "<doStatement>\n";
	print shift;				# do
	subroutineCall(@_);			# subroutineCall
	print "<doStatement>\n";
}

sub ReturnStatement {
	print "<ReturnStatement>\n";
	print shift;				# return
	parseExpression(@_);			# expression?
	print "</ReturnStatement>\n";
}

sub parseExpression {
	print "<expression>\n";
	parseTerm(@_);
	while($_[0] =~ /\+|\-|\*|\/|\&|\||\<|\>|\=/) {	#(op term)*
		print shift;				#op
		parseTerm(@_);		
	}
	print "</expression>\n";
}

sub expressionList {
	print "<expressionList>\n";
	parseExpression(@_);
	while($_[0] =~ /\,/) {
		parseExpression(@_);
	}
	print "</expressionList>\n";
}

sub subroutineCall {
	print "<subroutineCall>\n";
	if($_[0] =~ /identifier/ and $_[1] =~ /\(/ ) {
		print shift;	#subroutineName
		print shift;	# (
		expressionList(@_);
		print shift;	# )
	} else {
		print shift;	#className | varName
		print shift;	# .
		print shift;	#subroutineName
		print shift;	# (
		expressionList(@_);
		print shift;	# )
	}
	print "</subroutineCall>\n";
}

sub parseTerm {
	print "<term>\n";
	if($_[0] =~ /integerConstant|stringConstant|true|false|null|this/ ) {
		print shift;
	}
	if($_[0] =~ /identifier/ and $_[1] =~ /\[/) {
		print shift;		#varName
		print shift;		# [
		parseExpression(@_);	# expression
		print shift;		# ]
	}
	if($_[0] =~ /identifier/ and $_[1] !~ /\(/) {
		print shift;		#varName
	}
	if($_[0] =~ /identifier/ and $_[1] =~ /\(/) {
		subroutineCall(@_);	
	}
	if($_[0] =~ /\(/) {
		parseExpression(@_);	#(expression)
	}
	if($_[0] =~ /\-|\-/) {
		print shift;		#unaryOp -|-
		parseTerm(@_);		#term
	}
	print "</term>\n";
}
