#!/usr/bin/perl -w

use strict;
use XML::Parser;
use Jcode;

###### global ############################

my $xml;		# タ゜ト�Д罅Α�・、・�
my %msg = ();	# messages
my %desc = ();	# description
my @inc = ();	# include files
my $msgfile = "hpcmw_msg_table.c";
my $msgnofile = "hpcmw_msgno.h";
my $msgnofile_fortran = "hpcmw_msgno_f.f90";

# XML・ム。シ・ケヘム
my $msg_table = 0;
my $include = 0;
my $table = 0;
my $define = 0;
my $message = 0;
my $description = 0;
my $chars = "";
my $desc_chars = "";
my $prefix = "";
my $name = "";
my $msgno_base = 0;
my $parser;
my $including = 0;

###### main ######################

if($#ARGV+1 != 1) {
	print STDERR "Usage: msg_setup.pl xmlfile\n";
	exit 1;
}
($xml) = @ARGV;
$parser = &init;
$parser->parsefile($xml);
if(@inc) {
	$including = 1;
}
foreach (@inc) {
	$parser->parsefile($_);
}
&create;


###### init ######################
# テヨエケ・ュ。シ・��シ・ノ。「テヨエケク螟ホハクサ������゜ト�Д罅Α�・、・�Ε�、鮠霹タ

sub init {
	# XML::Parser・マ・��ノ・鯊゜ト�
	my $p = new XML::Parser(Handlers => {	Start => \&start_element,
											End	  => \&end_element,
											Char  => \&characters,
										});

	return $p;
}


sub start_element {
	my ($expat, $element, %attr) = @_;
	if($element eq 'msg-table') {
		$msg_table = 1;
		if(!$including) {
			$msgno_base = $attr{"msgno_base"};
			die "Validation Error: atribute 'msgno_base' required in msg-table\n" if(!$msgno_base);
		}
	} elsif($element eq 'include') {
		die "Validation Error\n" if(!$msg_table);
		$include = 1;
		if($attr{"src"} && $including) {
			die "Validation Error: now allow 'src' in include file\n";
		}
		push(@inc, $attr{"src"});
	} elsif($element eq 'table') {
		die "Validation Error\n" if(!$msg_table);
		$table = 1;
		$prefix = $attr{"prefix"};
	} elsif($element eq 'define') {
		die "Validation Error\n" if(!$msg_table || !$table);
		$define = 1;
		$name = $attr{"name"};
	} elsif($element eq 'message') {
		die "Validation Error\n" if(!$msg_table || !$table || !$define);
		$message = 1;
		$chars = "";
	} elsif($element eq 'description') {
		die "Validation Error\n" if(!$msg_table || !$table || !$define || $message);
		$description = 1;
		$desc_chars = "";
	} else {
		die "Unknown element $element\n";
	}
}

sub end_element {
	my ($expat, $element) = @_;
	if($element eq 'msg-table') {
		$msg_table = 0;
	} elsif($element eq 'include') {
		$include = 0;
	} elsif($element eq 'table') {
		$table = 0;
	} elsif($element eq 'define') {
		$define = 0;
		my $msgno; 
		if($prefix) {
			$msgno = $prefix . "-" . $name;
		} else {
			$msgno = $name;
		}
		if($msg{$msgno}) {
			die "Redefinition of '$msgno' in message table\n";
		}
		$msg{$msgno} = $chars;
	} elsif($element eq 'message') {
		$message = 0;
	} elsif($element eq 'description') {
		$description = 0;
		my $msgno; 
		if($prefix) {
			$msgno = $prefix . "-" . $name;
		} else {
			$msgno = $name;
		}
		if($desc{$msgno}) {
			die "Redefinition of '$msgno' in message table\n";
		}
		&Jcode::convert(\$desc_chars, 'euc','utf8');
		$desc{$msgno} = $desc_chars;
	} else {
		die "Unknown element $element\n";
	}
}

sub characters {
	my ($expat, $data) = @_;
	if($message) {
		$chars .= $data;
	} elsif($description) {
		$desc_chars .= $data;
	}
}


###### replace ############################

sub create {
	my $no = $msgno_base+1;
	my $key;
	my $value;
	my $descmsg;

	if(!open MSGFILE, ">$msgfile") {
		print STDERR "ERROR: Fail to open $msgfile\n";
		exit $!;
	}
	if(!open MSGNOFILE, ">$msgnofile") {
		print STDERR "ERROR: Fail to open $msgnofile\n";
		exit $!
	}
	if(!open MSGNOFILEF, ">$msgnofile_fortran") {
		print STDERR "ERROR: Fail to open $msgnofile_fortran\n";
		exit $!
	}

print MSGFILE <<END_OF_MSGFILE_HEADER;
/** \@file $msgfile
 * HPC-MW・皈テ・サ。シ・ク・ニ。シ・ヨ・�
 *
 * \@date
 * \@author
 */
#include <stdio.h>
#include "hpcmw_msg.h"

/**
 * HPC-MW・皈テ・サ。シ・ク・ニ。シ・ヨ・�
 *
 * ・皈テ・サ。シ・クネヨケ讀ネ、ス、�Ε劵張潺���ケ、�рД董Ε機�シ・ク、��ハヌシ、ケ、�
 */
struct hpcmw_msgent hpcmw_msg_table[] = {
END_OF_MSGFILE_HEADER

print MSGNOFILE <<END_OF_MSGNOFILE_HEADER;
/** \@file $msgnofile
 * HPC-MW・皈テ・サ。シ・クネヨケ貽�轡�
 *
 * \@date
 * \@author
 */

#ifndef HPCMW_MSGNO_INCLUDED 
#define HPCMW_MSGNO_INCLUDED

/**
 * ・ル。シ・ケネヨケ�
 *
 * ・皈テ・サ。シ・クネヨケ讀マ。「・ル。シ・ケネヨケ讀隍熙篦遉ュ、、
 */
#define HPCMW_MSGNO_BASE $msgno_base

END_OF_MSGNOFILE_HEADER

print MSGNOFILEF <<END_OF_MSGNOFILEF_HEADER;
module hpcmw_msgno
    use hpcmw_util

END_OF_MSGNOFILEF_HEADER

	foreach $key (sort keys %msg) {
		$value = $msg{$key};
		$descmsg = $desc{$key};
		$_ = $key;
		s/-/_/g;
		print MSGFILE "\t{$_,\"$key\",\"$value\"},\n";
		print MSGNOFILE "/** $descmsg */\n" if $descmsg;
		print MSGNOFILE "#define $_ $no\n";
		print MSGNOFILEF "    integer(kind=kint),parameter :: $_ = $no\n";
		$no++;
	}

print MSGFILE <<END_OF_MSGFILE_FOOTER;
	{-1,NULL,NULL}
};
END_OF_MSGFILE_FOOTER

print MSGNOFILE <<END_OF_MSGNOFILE_FOOTER;

#endif
END_OF_MSGNOFILE_FOOTER

print MSGNOFILEF <<END_OF_MSGNOFILEF_FOOTER;

end module hpcmw_msgno
END_OF_MSGNOFILEF_FOOTER

	close MSGFILE;
	close MSGNOFILE;
	close MSGNOFILEF;
}

