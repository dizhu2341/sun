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
getopts("d:u:f:s:",\%opt);
if ((!defined $opt{d})||(!defined $opt{u})||(!defined $opt{f})||(!defined $opt{s}))
{
  die "*******************************************************************************
  Function: DBrecovery
  Usage:    DBrecovery.exe -d -u -f
  -d        workdir
  -u:       database user name and password
  -f:       sql file path
  -s:				system no
*******************************************************************************\n";
}


my $year_month_day=strftime("%Y%m%d",localtime());

$sqlplus='sqlplus -L -S '.$opt{u}.' @'.$opt{d}.$opt{f}.' '.$opt{d}.'Clear_'.$opt{s}.'.sql '.$opt{s}.' 1>>'.$opt{d}.'log/recoveryError_'.$year_month_day.'.log 2>&1';

system($sqlplus);
 
$sqlplus='sqlplus -L -S '.$opt{u}.' @'.$opt{d}.'Clear_'.$opt{s}.'.sql 1>>'.$opt{d}.'log/recoveryError_'.$year_month_day.'.log 2>&1';

system($sqlplus);