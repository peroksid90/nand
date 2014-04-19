use strict;
my @result;

for(<>) {
s#//.*|/\*+.*\*/|^\s+\*.*|/\*\*\n?.*|\*/##;
push @result, /(\{|\}|\(|\)|\[|\]|\.|\,|\;|\+|\-|\*|\/|\&|\||\<|\>|\=|\~|
  class|constructor|function|method|field|static|var|\bint\b|char|boolean|void|true|false|null|this|let|do|if|else|while|return|
  ".*"|[a-zA-Z_]+[0-9]*|(?<![0-9])\d+)/gx;
}

sub escape {
        my $arg = shift;
        $arg =~ s/</&lt;/;
        $arg =~ s/>/&gt;/;
        $arg =~ s/&(?!g|l)/&amp;/;
        return $arg;
}

my $symbol = '(\{|\}|\(|\)|\[|\]|\.|\,|\;|\+|\-|\*|\/|\&|\||\<|\>|\=|\~)';
my $keyword = '(class|constructor|function|method|field|static|var|\bint\b|char|boolean|void|true|false|null|this|let|do|if|else|while|return)';
my $string = '("(.*)")';
my $identifier = '([a-zA-Z_][a-zA-Z_0-9]*)';
my $int = '(\d+)';

print "<tokens>\n";
for(@result) {
        if( /$symbol/ ) { print "<symbol> " . escape($1) . " </symbol>" . "\n"; next; }
        if( /$keyword/ ) { print "<keyword> " . $1 . " </keyword>" . "\n"; next; }
        if( /$string/ ) { print "<stringConstant> " . $2 . " </stringConstant>" . "\n"; next; }
        if( /$identifier/ ) { print "<identifier> " . $1 . " </identifier>" . "\n"; next; }
        if( /$int/ ) { print "<integerConstant> " . $1 . " </integerConstant>" . "\n"; next; }
}
print "</tokens>\n";
1;
