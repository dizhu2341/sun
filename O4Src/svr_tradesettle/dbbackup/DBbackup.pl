#--------------------------------------------------------------------------------------------------
#  program name         DBbackup.pl
#  version              1.0
#  function             parse interface table config information
#  author               zf
#  release date         16 April, 2014
#--------------------------------------------------------------------------------------------------

use bytes;
use Getopt::Std;
my(%opt);
getopts("d:u:f:l:t:e:",\%opt);
if ((!defined $opt{d})||(!defined $opt{u})||(!defined $opt{f})||(!defined $opt{l})||(!defined $opt{t})||(!defined $opt{e}))
{
  die "*******************************************************************************
  Function: DBbackup
  Usage:    DBbackup.exe -d -u -f -l -t
  -d:       workdir     
  -u:       database user name and password
  -f:       dmp file path
  -l:       log file path
  -t:       backup table
  -e:       backup error log
*******************************************************************************\n";
}

open IN, "<", $opt{t} or die;
my $tableinfo = <IN>;
close IN;

$sqlplus='exp '.$opt{u}.' file='.$opt{f}.' log='.$opt{l}.' '.$tableinfo.' buffer=10240000 2>>'.$opt{d}.'log/'.$opt{e};

$sysflag = system($sqlplus);

mkdir $opt{d}.'log' if !(-d $opt{d}.'log');
open F,'>',$opt{d}.'log/backuplog.log' || die "can not open";
if(!($sysflag eq 0))
{	
  print F $sysflag;	
}

close F;

exit($sysflag/256);

