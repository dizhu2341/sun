use bytes;
use Getopt::Std;

my(%opt);
getopts("d:c:u:",\%opt);

if ((!defined $opt{d})||(!defined $opt{u})||(!defined $opt{c}))
{
  die "*******************************************************************************
  Function: DBbackup
  Usage:    DBbackup.exe -d -u -f -l -t
  -d:       workdir     
  -u:       database user name
  -c:       database user name and password
*******************************************************************************\n";
}

$sqlarg='sqlplus -L -S '.$opt{c}.' @'.$opt{d}.'checkSession.sql '.'\''.$opt{u}.'\''.' '.$opt{d};

$sysflag=system($sqlarg);

#printf($sysflag);
