#!/usr/bin/perl
use strict;

if(!open TXT, "<", "$ARGV[0]") {
	die "Error opening file: $!";
}

my $txt;
for(<TXT>) {
$txt.=$_;
}

close TXT;

$txt=~s/\/\/.*//g;
$txt=~s/ //gg;

if(!open OUT, ">", "out.txt") {
	die "Error opening file: $!";
}

print OUT $txt;
