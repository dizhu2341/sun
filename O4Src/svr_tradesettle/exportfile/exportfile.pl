use bytes;
use Getopt::Std;

my(%opt);
getopts("d:u:e:n:l:",\%opt);

if ((!defined $opt{d})||(!defined $opt{u})||(!defined $opt{e})||(!defined $opt{n})||(!defined $opt{l}))
{
  die "*******************************************************************************
  Function: exportfile
  Usage:    exportfile.exe -d -u -e -n
  -d:       workdir     
  -u:       database user name and password
  -e:	    export file path
  -n:	    filename
  -l:       log filename
*******************************************************************************\n";
}

$sqlarg='sqlplus -L -S '.$opt{u}.' @'.$opt{d}.$opt{n}.'.sql '.$opt{e}.' 1>>'.$opt{d}.'log/'.$opt{l}.'.txt 2>&1';

system($sqlarg);

$sqlarg='rm '.$opt{d}.$opt{n}.'.sql';

system($sqlarg);
