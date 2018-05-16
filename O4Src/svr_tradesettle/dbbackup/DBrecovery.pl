#--------------------------------------------------------------------------------------------------
#  program name         DBrecovery.pl
#  version              1.0
#  function             parse interface table config information
#  author               zf
#  release date         16 April, 2014
#--------------------------------------------------------------------------------------------------

use bytes;
use Getopt::Std;
use POSIX;


my(%opt);
getopts("d:u:f:",\%opt);
if ((!defined $opt{d})||(!defined $opt{u})||(!defined $opt{f}))
{
  die "*******************************************************************************
  Function: DBrecovery
  Usage:    DBrecovery.exe -d -u -f
  -d        workdir
  -u:       database user name and password
  -f:       dmp file path
*******************************************************************************\n";
}


my $year_month_day=strftime("%Y%m%d",localtime());

$sqlplus='imp '.$opt{u}.' file='.$opt{f}.' full=y ignore=y buffer=10240000 2>>'.$opt{d}.'log/recoveryError_'.$year_month_day.'.log';

$sysflag = system($sqlplus);

mkdir $opt{d}.'log' if !(-d $opt{d}.'log');

open F,'>',$opt{d}.'log/recoverylog.log' || die "can not open";
if(!($sysflag eq 0))
{	
  print F $sysflag;
}

close F;

exit($sysflag/256);
