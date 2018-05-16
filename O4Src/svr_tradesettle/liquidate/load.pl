#--------------------------------------------------------------------------------------------------
#  program name         load.pl
#  version              1.404
#  function             parse interface table config information and load data into the database
#  author               Zhuyz
#  release date         23 April, 2015
#--------------------------------------------------------------------------------------------------

use bytes;
use Getopt::Std;
my(%opt);
getopts("o:d:s:u:m:",\%opt);
if ((!defined $opt{o}) || (!defined $opt{d}) || (!defined $opt{s}) || (!defined $opt{u}))
{
  die "***********************************************************************************
  Function: main procedure of hundsun clear system
  Usage:    perl load.pl -o operator -d cleardate -s sourcedir -u dbuser/dbpassword
  -o:       operator
  -d:       cleardate
  -s:       sourcedir
  -u:       database user name and password
  -m:       clearmode (optional, 'f' or 'b', default 'f')
***********************************************************************************\n";
}

my $mypwd =`pwd`;
$mypwd=~s/\n|\r//g;
my $currentpath=$0;
if ($currentpath=~m/^\.\.\/hsqsload\/liquidate\//)
{
	$mypwd=~s/\/$//;
	$mypwd=~s/[^\/]+$//;
	$currentpath=~s/^\.+//g;
	$currentpath=~s/^\///;
	$currentpath=~s/load\.pl$//;
}
else
{
	print '程序路径必须是../hsqsload/liquidate/load.pl',"\n";
	close FILEOU;
	exit;
}
$prgpath=$mypwd.$currentpath;
$prgpath=~s/\/+$//;
$prgpath=$prgpath.'/';
my $ostype  = ($prgpath=~m/\\/io) ? 'win' : 'unix';
my $qslogfile=$prgpath.'o4qs.log';
open FILEOU,">$qslogfile";

my $prgfile=$prgpath.'dbf2txt';
if ((-f $prgfile) and (-x $prgfile) and  (-r $prgfile)){}
else
{
	print FILEOU '1008 程序'.$prgfile.'不存在, 或者没有读取和执行权限',"\n";
	close FILEOU;
	exit;
}
my $prgfile=$prgpath.'proc_hsqs';
if ((-f $prgfile) and (-x $prgfile) and  (-r $prgfile)){}
else
{
	print FILEOU '1009 文件'.$prgfile.'不存在, 或者没有读取和执行权限',"\n";
	close FILEOU;
	exit;
}
my $prgfile=$prgpath.'proc_qh';
if ((-f $prgfile) and (-x $prgfile) and  (-r $prgfile)){}
else
{
	print FILEOU '1010 期货程序文件'.$prgfile.'不存在, 或者没有读取和执行权限',"\n";
	close FILEOU;
	exit;
}

if (length($opt{o})>10)
{
	print FILEOU '1001 操作员编号长度不能超过10字节',"\n";
	close FILEOU;
	exit;
}
if ($opt{d}!~/^\d{8}$/o)
{
	print FILEOU '1002 日期参数必须是8个数字',"\n";
	close FILEOU;
	exit;
}
if (($prgpath=~m/\s/o) or ($opt{s}!~m/^\//o) or ($opt{s}=~m/\s/o) or (length($prgpath)>500) or (length($opt{s})>500))
{
	print FILEOU '1003 程序目录/数据源目录含有空格, 或者目录长度超过500字节, 或者数据源目录不是绝对路径',"\n";
	close FILEOU;
	exit;
}
$opt{u}=~m/^([^\/\@]+)\/([^\/\@]+)\@*([^\/\@]*)$/go;
$dbuser=$1;
$dbpass=$2;
$dbconn=$3;
if ($dbuser eq '' or $dbpass eq '' or length($dbuser)>30 or length($dbpass)>30 or length($dbconn)>30)
{
	print FILEOU '1006 数据库用户名, 密码和连接名(可选)不完整, 或者用户名,密码和连接名之一超过30字节',"\n";
	close FILEOU;
	exit;
}
if (($opt{m} ne 'f') and ($opt{m} ne 'b'))
{
	print FILEOU '1007 清算模式(load.pl的-m参数)必须是f(full)或者b(branch), 或者不传入-m参数, 默认是f',"\n";
	close FILEOU;
	exit;
}
my $fullprocess=(lc($opt{m}) eq lc('b')) ? lc('branch') : lc('full');

my $workdir,$f_provider,$f_nametype,$files;
my @filelist,@nametype_list,@dirfile_list;
my %hash_all_parsetype,%hash_tablename,%hash_all_lenlist,%hash_all_loadgroup,%hash_prov_nametype;


$workdir=$opt{s};
$workdir=~s/\/$|\\$//g;
if ($ostype eq 'win')
{
	$workdir=~s/\/|\\/\\/go;
	$workdir=$workdir.'\\';
}
else
{
	$workdir=~s/\/|\\/\//go;
	$workdir=$workdir.'/';
}
if (!(-d $workdir))
{
	print FILEOU '1004 数据源目录',$workdir,'不存在',"\n";
	close FILEOU;
	exit;
}


if (lc($fullprocess) ne lc('full'))
{
	&readconfigbranch($prgpath);
	$sqlplus='sqlplus '.$opt{u}.' @'.$prgpath.'readconfig.sql';
	system($sqlplus);
}
if (lc($fullprocess) eq lc('full'))
{
opendir(DIR,$workdir.'bad');
@filelist=readdir(DIR);
closedir(DIR);
foreach $ele(@filelist){unlink $workdir.'bad/'.$ele if (-f $workdir.'bad/'.$ele);}
undef @filelist;
opendir(DIR,$workdir.'ctl');
@filelist=readdir(DIR);
closedir(DIR);
foreach $ele(@filelist){unlink $workdir.'ctl/'.$ele if (-f $workdir.'ctl/'.$ele);}
opendir(DIR,$workdir.'log');
@filelist=readdir(DIR);
closedir(DIR);
foreach $ele(@filelist){unlink $workdir.'log/'.$ele if (-f $workdir.'log/'.$ele);}
opendir(DIR,$workdir.'txt');
@filelist=readdir(DIR);
closedir(DIR);
foreach $ele(@filelist){unlink $workdir.'txt/'.$ele if (-f $workdir.'txt/'.$ele);}

undef @filelist;
mkdir $workdir.'bad' if !(-d $workdir.'bad');
mkdir $workdir.'ctl' if !(-d $workdir.'ctl');
mkdir $workdir.'log' if !(-d $workdir.'log');
mkdir $workdir.'txt' if !(-d $workdir.'txt');


if (!(-d $workdir.'source') or !(-r $workdir.'source'))
{
	print FILEOU '1005 数据源目录下没有source子目录, 或者source目录没有可读权限';
	close FILEOU;
	exit;
}
my $qhdir=$workdir.'source/QH/';
opendir(DIR,$qhdir);
@qhfilelist=readdir(DIR);
foreach $ele(@qhfilelist)
{
	if ($ele=~/^[0-9].*Trade\.dbf$/io)
	{
		my $ghdbfname=$qhdir.$ele;
		my $newghdbfname=$qhdir.'trade'.$ele;
		unlink $newghdbfname if (-f $newghdbfname);
		system("mv $ghdbfname $newghdbfname");
	}
	if ($ele=~/^[0-9].*Delivery\.dbf$/io)
	{
		my $ghdbfname=$qhdir.$ele;
		my $newghdbfname=$qhdir.'Delivery'.$ele;
		unlink $newghdbfname if (-f $newghdbfname);
		system("mv $ghdbfname $newghdbfname");
	}
	if ($ele=~/^[0-9].*SettlementDetail\.dbf$/io)
	{
		my $ghdbfname=$qhdir.$ele;
		my $newghdbfname=$qhdir.'SettlementDetail'.$ele;
		unlink $newghdbfname if (-f $newghdbfname);
		system("mv $ghdbfname $newghdbfname");
	}
	if ($ele=~/^[0-9].*capital\.dbf$/io)
	{
		my $ghdbfname=$qhdir.$ele;
		my $newghdbfname=$qhdir.'capital'.$ele;
		unlink $newghdbfname if (-f $newghdbfname);
		system("mv $ghdbfname $newghdbfname");
	}
}
closedir(DIR);


my $qhdir=$workdir.'source/QHTXT/';
opendir(DIR,$qhdir);
@qhfilelist=readdir(DIR);
closedir(DIR);
my $qhfilename,$firstchar,$lineno;
$qhfile_name=$workdir.'txt/qh.txt';
open FQHOUT,">$qhfile_name";
foreach $ele(@qhfilelist)
{
	$qhfilename=$qhdir.$ele;
	if ((-f $qhfilename) and ($qhfilename=~m/(delivery\.txt$|settlementdetail\.txt$|trade\.txt$|futureprefer\.txt$)/io))
	{
		if ($1 eq 'trade.txt'){$firstchar='0';}
		elsif ($1 eq 'delivery.txt') {$firstchar='1';}
		elsif ($1 eq 'settlementdetail.txt') {$firstchar='2';}
		elsif ($1 eq 'futureprefer.txt') {$firstchar='3';} else {$firstchar='x';}
		$lineno=0;
		open FQH,$qhfilename;
		while(<FQH>)
		{
			$lineno++;
			chomp;
			if ($lineno>4)
			{
				$linestr=$_;
				$linestr=~s/^\s|\s$//go;
				if (length($linestr)>0)
				{
					print FQHOUT $firstchar,$linestr,"\n";
				}
			}
		}
		close FQH;
	}
}
close FQHOUT;
&qhctl($workdir);
$qhctlfile=$workdir.'ctl/qh.ctl';
$qhlogfile=$workdir.'log/qh.log';


&readconfig($prgpath);
$sqlplus='sqlplus '.$opt{u}.' @'.$prgpath.'readconfig.sql';
system($sqlplus);
my $t_ifread,$t_columnid,$t_filetype,$t_tablename,$t_columnname,$t_datatype;
my $t_datalength,$t_datascale,$t_begpos,$t_endpos,$t_memcpy1,$t_memcpy2,$t_loadgroup;


my %hash_allnametype=('SHSE_GH'=>1,'SZSE_SJSHB'=>2,'SZSE_SJSGF'=>3,'SHZD_JSMX'=>4,
                      'SHZD_ZQBD'=>5,'SHSE_BGH'=>6,'SHSE_ZGH'=>7,'SZSE_LOFJS'=>8);
my %hash_nametype;
$tmpfilename=$prgpath.'interface_info.txt';
open F,$tmpfilename || die "can not open";
while(<F>)
{
	chomp;
	~s/\r+$//o;
	if (substr($_,0,1) eq '0'){exit;}
	$_=~m/^[YN]([01])(?:DBF|TXT)([12])([A-Z0-9_\s]{1,30})[A-Z0-9_\s]{1,10}[CND]\d{3}\d{2}\d{5}\d{5}\d{5}\d{5}([0-9])[012]/o;
	$t_columnid=$1;	$t_parsetype=$2;  $t_tablename=$3; $t_loadgroup =$4;
	$t_tablename=~s/\s+//o;
	$t_tablename=~m/^TI_([A-Z0-9]+)_([A-Z0-9]+)/o;
	$provider=$1.'_'.$2;
	if ($t_columnid eq '1')
	{
		$hash_nametype{$provider}=$hash_allnametype{$provider} if ($t_parsetype eq '1');
	}
	if ($t_columnid eq '1')
	{
		$hash_all_parsetype{$provider}=$t_parsetype;
		$hash_all_lenlist{length($2)}.=$1.'|'.$2.',';
		$hash_all_loadgroup{$provider}=$t_loadgroup;
	}
}
close F;


foreach my $keyname(sort {$b<=>$a} keys %hash_all_lenlist)
{
	$files=$hash_all_lenlist{$keyname};
	$files=~s/\,$//go;
	my @array_files=split(/\,/,$files);
	foreach $ele(@array_files)
	{
		$ele=~m/(\S+)\|(\S+)/io;
		$hash_prov_nametype{$1}.=$2.',';
	}
}
undef %hash_all_lenlist;


my %hash_filelist,%hash_filetype;
foreach $prov_dir(keys %hash_prov_nametype)
{
	$f_nametype=$hash_prov_nametype{$prov_dir};
	$f_nametype=~s/\,$//go;
	@nametype_list=split(/\,/,$f_nametype);
	opendir(DIR,$workdir.'source/'.$prov_dir);
	@dirfile_list=readdir(DIR);
	closedir(DIR);


	foreach $file_name(@dirfile_list)
	{
		my $source_file=$workdir.'source/'.$prov_dir.'/'.$file_name;
		if (-f $source_file)
		{
			foreach my $nametype(@nametype_list)
			{
				if ($file_name=~m/^$nametype/i)
				{
					$hash_filelist{$source_file}=$prov_dir.'_'.$nametype;
					$hash_filetype{$prov_dir.'_'.$nametype}=0;
					$hash_filetype{$prov_dir.'_'.$nametype}=$hash_nametype{$prov_dir.'_'.$nametype} if (exists($hash_nametype{$prov_dir.'_'.$nametype}));
					last;
				}
			}
		}
	}
}
close FO;
undef %hash_all_parsetype;


foreach my $keyname(sort keys %hash_filetype)
{
	$hash_actualgroup{$keyname}=$hash_all_loadgroup{$keyname};
}
my %hash_subloadgroup;
my $v_loadgroup;
my $filetype_count=0;
my $subgroup_num=1;
my $v_prior_loadgroup=' ';
foreach my $keyname(sort {$hash_actualgroup{$a}<=>$hash_actualgroup{$b}} keys %hash_actualgroup)
{
	$v_loadgroup=$hash_actualgroup{$keyname};
	if ($v_loadgroup ne $v_prior_loadgroup)
	{
		$filetype_count=0;
		$subgroup_num=1;
	}

	if ($filetype_count==10)
	{
		$filetype_count=0;
		$subgroup_num++;
	}
	$filetype_count++;
	$hash_subloadgroup{uc($keyname)}=$v_loadgroup.'_'.$subgroup_num;
	$v_prior_loadgroup=$v_loadgroup;
}


my %hash_group_allfiles;
foreach my $filename(sort keys %hash_filelist)
{
	my $txtfilename=$filename;
	my $file_nametype=$hash_filelist{$filename};
	$file_nametype=~s/\s+//o;
	$file_nametype=~m/^([A-Z0-9]+_)/o;
	$provier=$1;
	$txtfilename=~m/([^\/]+)$/o;
	$hash_group_allfiles{$hash_subloadgroup{$file_nametype}}.="\n".'infile \''.$workdir.'txt/'.$provier.$1.'.txt\'  '.'badfile \''.$workdir.'bad/'.$provier.$1.'.bad\'';
}

my $loadgroup='';
my $first_column=1;
my $filetype_id=0;
my %hash_cpp,%hash_cpp_mem;

my %hash_control_file,%hash_filetypeid;
my $right=0;
my $subgroup_num;
$tmpfilename=$prgpath.'interface_info.txt';
my %h_tablename,%h_filetypename,$myfiletype;
undef %h_tablename;
open F,$tmpfilename || die "can not open";
while(<F>)
{
	chomp;
	~s/\r+$//o;
	$_=~m/^([YN])([01])(DBF|TXT)([12])([A-Z0-9_\s]{1,30})([A-Z0-9_\s]{1,10})([CND])(\d{3})(\d{2})(\d{5})(\d{5})(\d{5})(\d{5})([0-9])([012])(\d{5})(\d{5})(\d{4})(\d{4})/o;
	$t_ifread    =$1;	 $t_columnid=$2;	 $t_filetype  =$3;  $t_parsetype =$4;  $t_tablename=$5;
	$t_columnname=$6;  $t_datatype=$7;   $t_datalength=$8;  $t_datascale =$9;  $t_begpos   =$10;
	$t_endpos    =$11; $t_memcpy1 =$12;  $t_memcpy2   =$13; $t_loadgroup =$14; $t_firstlast=$15;
	$t_p2offset  =$16; $t_newreclen=$17; $t_memcnt    =$18; $t_fieldcnt  =$19;
	$t_tablename=~s/\s+$//o;
	$t_tablename=~m/^TI_([A-Z0-9]+)_([A-Z0-9]+)/o;
	$provider=$1.'_'.$2;

	$myfiletype=substr($t_tablename,3);
	$t_columnname=~s/^\s+|\s+$//go;
	$h_filetypename{$myfiletype}++;
	if (exists($h_tablename{$myfiletype}))
	{
		$h_tablename{$myfiletype}=$h_tablename{$myfiletype}.','.$t_columnname.'-'.$t_datatype.'-'.$t_datalength.'-'.$t_datascale;
	}
	else
	{
		$h_tablename{$myfiletype}=$h_tablename{$myfiletype}.$t_columnname.'-'.$t_datatype.'-'.$t_datalength.'-'.$t_datascale;
	}
	my $dateformat = (uc($t_datatype) eq uc('D')) ? ' date \'yyyymmdd\'' : '';
	if ($t_columnid eq '1')
	{
		$if_file2load=exists($hash_filetype{$provider}) ? 1 : 0;
		$right=0;
		$right=1 if ($t_parsetype eq '1' and  exists($hash_nametype{$provider}));
		$right=1 if ($t_parsetype eq '2' and !exists($hash_nametype{$provider}));
	}
	if ($if_file2load==1 and $right==1) #这类文件有文件要导入#if ($if_file2load==1) #这类文件有文件要导入
	{
		if ($t_columnid eq '1')
		{
			$loadgroup=$hash_subloadgroup{$provider};
		}
		if ($t_ifread eq uc('Y'))
		{
			if ($t_firstlast eq '1')
			{
				if (!exists($hash_filetypeid{$loadgroup})){$hash_filetypeid{$loadgroup}=0;}
				else
				{
					$hash_filetypeid{$loadgroup}++;
				}
				$filetype_id=$hash_filetypeid{$loadgroup};
				$hash_cpp{$provider}=$t_parsetype.$filetype_id.$t_p2offset.$t_newreclen.$t_memcnt.$t_fieldcnt;
				$hash_control_file{$loadgroup}.='into table '.$t_tablename."\n".'when(1)='.'\''.$filetype_id.'\''."\n".'trailing nullcols'."\n".'('."\n".'  '.$t_columnname.'    position('.($t_begpos+0).':'.($t_endpos+0).')'.$dateformat;
			}
			elsif ($t_firstlast eq '2')
			{
				if (uc($t_tablename) eq uc('TI_SZSE_SJSHB'))
				{
					$hash_control_file{$loadgroup}.=','."\n".'  '.$t_columnname.'    position('.($t_begpos+0).':'.($t_endpos+0).')'.$dateformat.','."\n".'  BLOCKTRADE    position('.($t_endpos+1).':'.($t_endpos+1).')'."\n".')'."\n";
				}
				else
				{
					$hash_control_file{$loadgroup}.=','."\n".'  '.$t_columnname.'    position('.($t_begpos+0).':'.($t_endpos+0).')'.$dateformat."\n".')'."\n";
				}
			}
			else
			{
				$hash_control_file{$loadgroup}.=','."\n".'  '.$t_columnname.'    position('.($t_begpos+0).':'.($t_endpos+0).')'.$dateformat;
			}
		}
		if ($t_memcpy1>0 and $t_memcpy2>0 and $t_parsetype eq '2')
		{
			$hash_cpp_mem{$provider}.=$t_memcpy1.$t_memcpy2;
		}
	}
}
close F;

foreach my $sub_group(keys %hash_control_file)
{
	$ctlname=$workdir.'ctl/'.'ts_control_'.$sub_group.'.ctl';
	open  FCTL,">$ctlname";
	print FCTL 'options(direct=true,rows=30000,errors=0)',"\n";
	print FCTL 'unrecoverable',"\n";
	print FCTL 'load data';
	print FCTL $hash_group_allfiles{$sub_group};
	print FCTL "\n",'append',"\n";
	print FCTL $hash_control_file{$sub_group},"\n";
	close FCTL;
}

$fileparse=$prgpath.'parsedbf.txt';
open FCPP,">$fileparse";

foreach my $filename(sort keys %hash_cpp)
{
	$hash_cpp{$filename}.=$hash_cpp_mem{$filename};
}
foreach my $each_filename(keys %hash_filelist)
{
	my $provider_filetype=$hash_filelist{$each_filename};
	$provider_filetype=~m/^([^_]+)/o;
	my $provider=$1;
	my $output_filename=$each_filename;
	$output_filename=~m/([^\/]+$)/o;
	$output_filename=$workdir.'txt/'.$provider.'_'.$1.'.txt';
	my $inputstr=$hash_cpp{$provider_filetype};
	if (substr($inputstr,0,1) eq '1')
	{
		if (exists($hash_nametype{$provider_filetype}))
		{
			my $cpp_str=$each_filename.'|'.$output_filename.'|'.$hash_filetype{$provider_filetype}.'|'.substr($inputstr,1,1).'|9|9|9|9';
			print FCPP $h_filetypename{$provider_filetype},'|',$h_tablename{$provider_filetype},'|',$cpp_str,"\n";
		}
		else
		{
			print '文件类型',$provider_filetype,'没有预定义导入模式, 请改成自定义模式',"\n";
		}
	}
	else
	{
		my $cpp_str=$each_filename.'|'.$output_filename.'|'.'0'.'|'.substr($inputstr,1,1).'|'.(substr($inputstr,2,5)+0).'|'.(substr($inputstr,7,5)+0).'|'.(substr($inputstr,12,4)+0).'|'.substr($inputstr,20);
		print FCPP $h_filetypename{$provider_filetype},'|',$h_tablename{$provider_filetype},'|',$cpp_str,"\n";
	}
}
close FCPP;
my $qhproc=$prgpath.'proc_qh';
my $filesize= -s $prgpath.'o4qs.log';
if ($filesize>0)
{
	unlink $prgpath.'interface_info.txt' if (-f $prgpath.'interface_info.txt');
	unlink $prgpath.'readconfig.sql' if (-f $prgpath.'readconfig.sql');
	unlink $prgpath.'parsedbf.txt' if (-f $prgpath.'parsedbf.txt');
	close FILEOU;
	exit;
}

$cpp_str=$prgpath.'dbf2txt '.$prgpath.'o4qs.log'.' '.$prgpath.'parsedbf.txt';
system($cpp_str);
$filesize= -s $prgpath.'o4qs.log';
if ($filesize>0)
{
	unlink $prgpath.'interface_info.txt' if (-f $prgpath.'interface_info.txt');
	unlink $prgpath.'readconfig.sql' if (-f $prgpath.'readconfig.sql');
	unlink $prgpath.'parsedbf.txt' if (-f $prgpath.'parsedbf.txt');
  close FILEOU;
	exit;
}

undef %hash_cpp,%hash_cpp_mem;
opendir(DIR,$workdir.'ctl');
@filelist=readdir(DIR);
closedir(DIR);
foreach $control_file(@filelist)
{
	my $ctlfile=$workdir.'ctl/'.$control_file;
	$control_file=~s/ctl$//igo;
	my $logfile=$workdir.'log/'.$control_file.'log';
	my $badfile=$workdir.'bad/'.$control_file.'bad';
	if (-f $ctlfile)
	{
		my $sqlldr='sqlldr silent=all userid='.$opt{u}.' control='.$ctlfile.' log='.$logfile;
		system($sqlldr);
		$retcode=`echo $?`;
		if ($retcode!=0)
		{
			print FILEOU '1012 SQL*Loader未成功导入所有数据, 请查看SQL*Loader的日志文件',"\n";
		}
	}
}
close FILEOU;
undef @filelist;
opendir(DIR,$workdir.'ctl');
@filelist=readdir(DIR);
closedir(DIR);
foreach $ele(@filelist){unlink $workdir.'ctl/'.$ele if (-f $workdir.'ctl/'.$ele);}
}
unlink $prgpath.'interface_info.txt' if (-f $prgpath.'interface_info.txt');
unlink $prgpath.'readconfig.sql' if (-f $prgpath.'readconfig.sql');
unlink $prgpath.'parsedbf.txt' if (-f $prgpath.'parsedbf.txt');
$filesize= -s $prgpath.'o4qs.log';
if ($filesize>0)
{
	exit;
}
if ($dbconn eq '')
{
	$proc1=$prgpath.'proc_hsqs '.$prgpath.' '.$prgpath.'o4qs.log '.$opt{o}.' '.$opt{d}.' '.$fullprocess.' '.$dbuser.' '.$dbpass;
}
else
{
  $proc1=$prgpath.'proc_hsqs '.$prgpath.' '.$prgpath.'o4qs.log '.$opt{o}.' '.$opt{d}.' '.$fullprocess.' '.$dbuser.' '.$dbpass.' '.$dbconn;
}
system($proc1);

sub readconfigbranch
{
	my($prgdir) = @_;
	$filename = $prgdir.'readconfig.sql';
	open FO,">$filename";
	print FO 'declare',"\n";
  print FO '  v_sqlerrm varchar2(200) := \'\';',"\n";
	print FO 'begin',"\n";
	print FO '  for t in (select \'truncate table \'||t1.table_name trun_tbl',"\n";
	print FO '            from   ti_table t1,user_tables t2',"\n";
	print FO '            where  upper(t1.if_load)=upper(\'Y\')',"\n";
	print FO '            and    t1.table_name=t2.table_name',"\n";
	print FO '            union  all select \'truncate table \'||t3.table_name trun_tbl from user_tables t3 where upper(table_name) in(upper(\'TI_QH_SETTLEMENTDETAIL\'),upper(\'TI_QH_FUTRUEPREFER\'),upper(\'TI_QH_DELIVERY\'),upper(\'TI_QH_TRADE\'))) loop',"\n";
	print FO '      execute immediate t.trun_tbl;',"\n";
	print FO '  end loop;',"\n";
	print FO '  for t in (select \'truncate table qs_tlog\' trun_tbl',"\n";
	print FO '            from   user_tables',"\n";
	print FO '            where  table_name=upper(\'qs_tlog\')) loop',"\n";
	print FO '      execute immediate t.trun_tbl;',"\n";
	print FO '  end loop;',"\n";
	print FO '  insert into qs_tlog(log_type,step,step_name,time) values(1,1,\'数据导入开始\',to_char(systimestamp,\'yyyymmdd hh24:mi:ssxff3\'));',"\n";
	print FO '  commit;',"\n";
  print FO '  exception',"\n";
  print FO '     when others then',"\n";
  print FO '       v_sqlerrm := substr(sqlerrm,1,200);',"\n";
  print FO '       insert into qs_tlog(log_type,err_info) values(3,\'QS_TLOG表结构错误, 或者有其它SESSION针对QS_TLOG表的事务未提交\'||chr(10)||v_sqlerrm);',"\n";
  print FO '       commit;',"\n";
	print FO 'end;',"\n";
	print FO '/',"\n";
	print FO 'quit',"\n";
}

sub readconfig
{
	my($prgdir) = @_;
	$filename = $prgdir.'readconfig.sql';
	open FO,">$filename";
	print FO 'begin',"\n";
	print FO '  for t in (select \'truncate table \'||t1.table_name trun_tbl',"\n";
	print FO '            from   ti_table t1,user_tables t2',"\n";
	print FO '            where  upper(t1.if_load)=upper(\'Y\')',"\n";
	print FO '            and    t1.table_name=t2.table_name',"\n";
	print FO '            union  all select \'truncate table \'||t3.table_name trun_tbl from user_tables t3 where upper(table_name) in(upper(\'TI_QH_SETTLEMENTDETAIL\'),upper(\'TI_QH_FUTRUEPREFER\'),upper(\'TI_QH_DELIVERY\'),upper(\'TI_QH_TRADE\'))) loop',"\n";
	print FO '      execute immediate t.trun_tbl;',"\n";
	print FO '  end loop;',"\n";
	print FO '  for t in (select \'truncate table qs_tlog\' trun_tbl',"\n";
	print FO '            from   user_tables',"\n";
	print FO '            where  table_name=upper(\'qs_tlog\')) loop',"\n";
	print FO '      execute immediate t.trun_tbl;',"\n";
	print FO '  end loop;',"\n";
	print FO '  insert into qs_tlog(log_type,step,step_name,time) values(1,1,\'数据导入开始\',to_char(systimestamp,\'yyyymmdd hh24:mi:ssxff3\'));',"\n";
	print FO '  insert into qs_tlog(log_type,err_code)',"\n";
	print FO '  select /*+ no_merge(v1) */ 3,v1.err_code',"\n";
	print FO '  from   (select /*+ full(t1) */ ',"\n";
	print FO '                 case when t1.table_name is null or t1.file_type is null then \'1101\'',"\n";
	print FO '		              		when nvl(t1.file_type,\'x\') not in (upper(\'DBF\'),upper(\'TXT\')) then \'1102\'',"\n";
	print FO '        	            when t1.parse_type=\'1\' and nvl(t1.table_name,\'x\') not in (upper(\'TI_SHSE_GH\'),upper(\'TI_SHZD_JSMX\'),upper(\'TI_SHZD_ZQBD\'),upper(\'TI_SZSE_SJSHB\'),upper(\'TI_SZSE_SJSGF\')) then \'1103\'',"\n";
	print FO '        	            when nvl(t1.parse_type,\'2\')!=\'1\' and upper(t1.table_name)=upper(\'TI_SZSE_SJSHB\') then \'1104\'',"\n";
	print FO '	                    else null end err_code',"\n";
	print FO '          from   ti_table t1) v1',"\n";
	print FO '  where  v1.err_code is not null;',"\n";
	print FO '  insert into qs_tlog(log_type,err_code)',"\n";
	print FO '  select /*+ no_merge(v1) */ 3,\'1105\'',"\n";
	print FO '  from   (select /*+ full(t1) */',"\n";
	print FO '                 count(distinct t1.table_name) uniquecnt,',"\n";
	print FO '                 count(t1.table_name) cnt',"\n";
	print FO '          from   ti_table t1) v1',"\n";
	print FO '  where  v1.uniquecnt!=v1.cnt;',"\n";
	print FO '  insert into qs_tlog(log_type,err_code)',"\n";
	print FO '  select /*+ no_merge(v2) */ 3,err_Code',"\n";
	print FO '  from   (select /*+ all_rows leading(t1) use_hash(t2) no_expand full(t1) full(t2) */',"\n";
	print FO '                 case when t2.table_name is null or t2.COLUMN_NAME is null or DATA_TYPE is null or DATA_LENGTH is null or COLUMN_ID is null then \'1106\'',"\n";
	print FO '                      when nvl(t2.data_type,\'x\') not in (\'C\',\'D\',\'N\') then \'1107\'',"\n";
	print FO '                      when t2.data_length<1 or (t2.data_length-1)<NVL(t2.data_scale,0) then \'1108\'',"\n";
	print FO '                      when t2.data_scale is not null and t2.data_scale<1  then \'1109\'',"\n";
	print FO '                      when lengthb(t2.column_name)>10 then \'1110\'',"\n";
	print FO '                      when nvl(t2.data_length,0)>254 or nvl(t2.data_scale,0)>19 then \'1111\'',"\n";
	print FO '                      else null end err_code',"\n";
	print FO '          from   ti_tablecolumn t2) v2',"\n";
	print FO '   where  err_code is not null;',"\n";
	print FO '  insert into qs_tlog(log_type,err_code,err_info)',"\n";
	print FO '  select 3,\'1112\',table_name',"\n";
	print FO '  from   ti_tablecolumn',"\n";
	print FO '  group  by table_name',"\n";
	print FO '  having count(distinct column_name)<count(column_name)',"\n";
	print FO '  or     count(distinct column_id)<count(column_id);',"\n";
	print FO '  commit;',"\n";
	print FO 'end;',"\n";
	print FO '/',"\n";
	print FO "\n";
	print FO 'set term     off',"\n";
	print FO 'set timi     off',"\n";
	print FO 'set wrap     off',"\n";
	print FO 'set colsep   \'\'',"\n";
	print FO 'set heading  off;',"\n";
	print FO 'set pagesize 0;',"\n";
	print FO 'set feedback off;',"\n";
	print FO 'set linesize 92',"\n";
	print FO 'col linestr  format A92',"\n";
	print FO 'spool ',$prgdir.'interface_info.txt',"\n";
	print FO 'select \'00000\' linestr from qs_tlog where log_type=3 and rownum=1;',"\n";
	print FO 'with   v_tablecolumn as (',"\n";
	print FO '         select /*+ all_rows leading(t1) use_hash(t2) no_expand full(t1) full(t2) */',"\n";
	print FO '                upper(t1.table_name)  table_name,   t1.file_type,     t1.parse_type, t1.load_group,',"\n";
	print FO '                upper(t2.column_name) column_name,',"\n";
	print FO '                t2.data_type,     t2.data_length,   t2.data_scale,    t2.column_id,',"\n";
	print FO '                case when  t1.parse_type=1 and upper(t1.table_name)=upper(\'TI_SHSE_GH\') then',"\n";
	print FO '                       case when upper(t2.column_name) in(upper(\'GDXM\'),upper(\'BCYE\'),upper(\'MJBH\')) THEN \'N\' else \'Y\' end',"\n";
	print FO '                     when  t1.parse_type=1 and upper(t1.table_name)=upper(\'TI_SHZD_ZQBD\') then',"\n";
	print FO '                       case when upper(t2.column_name) in(upper(\'GPNF\'),upper(\'BY\'),upper(\'SCDM\')) THEN \'N\' else \'Y\' end',"\n";
	print FO '                     when  t1.parse_type=1 and upper(t1.table_name)=upper(\'TI_SHZD_JSMX\') then',"\n";
	print FO '                       case when upper(t2.column_name) in(upper(\'CJBH\'),upper(\'CJSJ\'),upper(\'GHF\'),upper(\'GPNF\'),upper(\'JLLX\'),upper(\'JSBH\'),upper(\'JSF\'),upper(\'JSHY\'),upper(\'MMBZ\'),upper(\'QSJE\'),upper(\'QTJE1\'),upper(\'QTJE2\'),upper(\'QTJE3\'),upper(\'QTRQ\'),upper(\'SCDM\'),upper(\'SXF\'),upper(\'TGHY\'),upper(\'WTBH\'),upper(\'WTSJ\'),upper(\'XWHY\'),upper(\'YHS\'),upper(\'ZGF\'),upper(\'ZJZH\')) THEN \'N\' else \'Y\' end',"\n";
	print FO '                     when  t1.parse_type=1 and upper(t1.table_name)=upper(\'TI_SZSE_SJSHB\') then',"\n";
	print FO '                       case when upper(t2.column_name) in(upper(\'HBBYBZ\'),upper(\'HBCDYY\')) THEN \'N\' else \'Y\' end',"\n";
	print FO '                     when  t1.parse_type=1 and upper(t1.table_name)=upper(\'TI_SZSE_SJSGF\') then',"\n";
	print FO '                       case when upper(t2.column_name) in(upper(\'GFBYBZ\'),upper(\'GFSFZH\')) THEN \'N\' else \'Y\' end',"\n";
	print FO '                     else if_read end if_read,',"\n";
	print FO '               case upper(t1.table_name)',"\n";
	print FO '                    when upper(\'TI_SHSE_GH\')    then 1',"\n";
	print FO '                    when upper(\'TI_SZSE_SJSHB\') then 2',"\n";
	print FO '                    when upper(\'TI_SZSE_SJSGF\') then 3',"\n";
	print FO '                    when upper(\'TI_SHZD_JSMX\')  then 4',"\n";
	print FO '                    when upper(\'TI_SHZD_ZQBD\')  then 5',"\n";
	print FO '                    else 9 end l_priority',"\n";
	print FO '         from   ti_table t1,ti_tablecolumn t2',"\n";
	print FO '         where  upper(t1.table_name) = upper(t2.table_name)',"\n";
	print FO '         and    upper(t1.if_load)    = upper(\'Y\')',"\n";
	print FO '         and    upper(t1.file_type)  = upper(\'DBF\')),',"\n";
	print FO '     v_tableload as (',"\n";
	print FO 'select /*+ no_merge(v2) */',"\n";
	print FO '       v2.file_type,   v2.parse_type, v2.load_group, v2.table_name,  v2.column_name, v2.data_type,',"\n";
	print FO '       v2.data_length, v2.data_scale, v2.column_id,  v2.if_read,     v2.ctl_pos,',"\n";
	print FO '       decode(0,v2.if_read,v2.ctl_pos,null) grp,     v2.l_priority',"\n";
	print FO 'from   (select /*+ no_merge(v1) */',"\n";
	print FO '               v1.table_name,  v1.file_type,  v1.parse_type, v1.load_group,  v1.column_name, v1.data_type,',"\n";
	print FO '               v1.data_length, v1.data_scale,',"\n";
	print FO '               row_number() over (partition by v1.table_name order by v1.column_id) column_id,',"\n";
	print FO '               decode(upper(\'N\'),upper(v1.if_read),0,1) if_read,',"\n";
	print FO '               V1.l_priority,',"\n";
	print FO '               sum(decode(upper(\'N\'),upper(v1.if_read),0,v1.data_length)) over (partition by v1.table_name order by v1.column_id rows unbounded preceding) ctl_pos',"\n";
	print FO '        from   v_tablecolumn v1) v2)',"\n";
	print FO 'select /*+ no_merge(v8) */',"\n";
	print FO '       v8.linestr||lpad(to_char(v8.mem_cpy1),5,\'0\')||lpad(to_char(v8.mem_cpy2),5,\'0\')||load_group||v8.first_last||',"\n";
	print FO '       lpad(to_char(sum(case when v8.mem_cpy1=0 and v8.mem_cpy2>0 then v8.mem_cpy2 else 0 end) over (partition by v8.table_name)+1),5,\'0\')||',"\n";
	print FO '       lpad(to_char(sum(v8.mem_cpy1) over (partition by v8.table_name)+2),5,\'0\')||',"\n";
	print FO '       lpad(to_char(sum(case when v8.mem_cpy1>0 and v8.mem_cpy2>0 then 1 else 0 end) over (partition by v8.table_name)),4,\'0\')||',"\n";
	print FO '       lpad(to_char(count(*) over (partition by v8.table_name)),4,\'0\') linestr',"\n";
	print FO 'from   (select /*+ no_merge(v7) */',"\n";
	print FO '               decode(0,v7.if_read,\'N\',\'Y\')||',"\n";
	print FO '               decode(v7.column_id,1,\'1\',\'0\')||',"\n";
	print FO '               v7.file_type||',"\n";
	print FO '               v7.parse_type||',"\n";
	print FO '               rpad(v7.table_name,30,\' \')||',"\n";
	print FO '               rpad(v7.column_name,10,\' \')||',"\n";
	print FO '               v7.data_type||',"\n";
	print FO '               lpad(to_char(v7.data_length),3,\'0\')||',"\n";
	print FO '               lpad(to_char(nvl(v7.data_scale,0)),2,\'0\')||',"\n";
	print FO '               lpad(to_char(v7.beg_pos),5,\'0\')||',"\n";
	print FO '               lpad(to_char(v7.end_pos),5,\'0\') linestr,',"\n";
	print FO '               nvl(case when v7.rn=1 then',"\n";
	print FO '                         case when v7.if_read=0 then',"\n";
	print FO '                                   case when v7.column_id=1 then 0 else v7.cpy1 end',"\n";
	print FO '                              else case when v7.mem_grp=v7.max_grp then v7.mem_step else null end end',"\n";
	print FO '                    else null end,0) mem_cpy1,',"\n";
	print FO '               nvl(case when v7.rn=1 then',"\n";
	print FO '                         case when v7.if_read=0 then',"\n";
	print FO '                                   case when v7.column_id=1 then v7.mem_step else v7.cpy2 end',"\n";
	print FO '                              else case when v7.mem_grp=v7.max_grp then v7.mem_step else null end end',"\n";
	print FO '                    else null end,0) mem_cpy2,',"\n";
	print FO '               to_char(v7.load_group) load_group,',"\n";
	print FO '               case when v7.column_id=v7.first_read then \'1\' when v7.column_id=v7.last_read then \'2\' else \'0\' end first_last,',"\n";
	print FO '               v7.l_priority,v7.table_name,v7.column_id',"\n";
	print FO '        from   (select /*+ no_merge(v6) */',"\n";
	print FO '                       v6.file_type,   v6.parse_type, v6.load_group, v6.table_name, v6.column_name, v6.data_type,',"\n";
	print FO '                       v6.data_length, v6.data_scale, v6.column_id,  v6.if_read,    v6.l_priority,  v6.beg_pos,',"\n";
	print FO '                       v6.end_pos,     v6.mem_grp,    v6.max_grp,    v6.mem_step,   v6.rn,',"\n";
	print FO '                       lag(v6.mem_step,1) over (partition by v6.table_name order by column_id) cpy1,',"\n";
	print FO '                       case when v6.rn=1 and v6.if_read=0 then lag(v6.mem_step,1) over (partition by v6.table_name order by column_id)+mem_step else null end cpy2,',"\n";
	print FO '                       min(case when v6.if_read=1 then v6.column_id else null end) over (partition by v6.table_name) first_read,',"\n";
	print FO '                       max(case when v6.if_read=1 then v6.column_id else 0 end) over (partition by v6.table_name) last_read',"\n";
	print FO '                from   (select /*+ no_merge(v5) */',"\n";
	print FO '                               v5.file_type,  v5.parse_type, v5.load_group, v5.table_name, v5.column_name, v5.data_type, v5.data_length,',"\n";
	print FO '                               v5.data_scale, v5.column_id,  v5.if_read,    v5.l_priority, v5.beg_pos,     v5.end_pos,   v5.mem_grp,',"\n";
	print FO '                               max(mem_grp)     over (partition by table_name) max_grp,',"\n";
	print FO '                               sum(data_length) over (partition by table_name,mem_grp) mem_step,',"\n";
	print FO '                               row_number()     over (partition by table_name,mem_grp order by column_id) rn',"\n";
	print FO '                        from   (select /*+ no_merge(v4) */',"\n";
	print FO '                                       v4.file_type,   v4.parse_type, v4.load_group, v4.table_name,  v4.column_name, v4.data_type,',"\n";
	print FO '                                       v4.data_length, v4.data_scale, v4.column_id,  v4.if_read,     v4.l_priority,',"\n";
	print FO '                                       decode(v4.if_read,0,0,v4.beg_pos)   beg_pos,',"\n";
	print FO '                                       decode(v4.if_read,0,0,v4.ctl_pos+1) end_pos,',"\n";
	print FO '                                       dense_rank() over (partition by v4.table_name order by v4.mem_grp,v4.if_read) mem_grp',"\n";
	print FO '                                from   (select /*+ no_merge(v3) */',"\n";
	print FO '                                               v3.file_type,   v3.parse_type, v3.load_group, v3.table_name, v3.column_name, v3.data_type,',"\n";
	print FO '                                               v3.data_length, v3.data_scale, v3.column_id,  v3.if_read,    v3.ctl_pos,     v3.l_priority,',"\n";
	print FO '                                               nvl(lag(v3.ctl_pos,1) over (partition by v3.table_name order by v3.column_id),0)+2 beg_pos,',"\n";
	print FO '                                               nvl(last_value(v3.grp ignore nulls) over (partition by v3.table_name order by v3.column_id rows unbounded preceding),0) mem_grp',"\n";
	print FO '                                        from   v_tableload v3) v4) v5) v6) v7) v8',"\n";
	print FO 'order  by v8.load_group,v8.l_priority,v8.table_name,v8.column_id;',"\n";
	print FO "\n";
	print FO 'spool off',"\n";
	print FO 'quit',"\n";
  close FO;
}

sub qhctl
{
	my($qh_wotkfile)=@_;
	my $qh_ctlfile=$qh_wotkfile.'ctl/qh.ctl';
	open FOCTL,">$qh_ctlfile";
	print FOCTL 'options(direct=true,rows=10000,errors=0)',"\n";
  print FOCTL 'unrecoverable',"\n";
  print FOCTL 'load data',"\n";
  print FOCTL 'infile \''.$qh_wotkfile.'txt/qh.txt\'  badfile \''.$qh_wotkfile.'bad/qh.bad\'',"\n";
  print FOCTL 'append',"\n";
  print FOCTL 'into table TI_QH_TRADE',"\n";
  print FOCTL 'when(1)=\'0\'',"\n";
  print FOCTL 'trailing nullcols',"\n";
  print FOCTL '(',"\n";
  print FOCTL '    partid      position(2:11)    "trim(:partid)",',"\n";
  print FOCTL '    clientid    position(12:23)   "trim(:clientid)",',"\n";
  print FOCTL '    instrid     position(24:33)   "trim(:instrid)",',"\n";
  print FOCTL '    tradeid     position(34:45)   "trim(:tradeid)",',"\n";
  print FOCTL '    tvolume     position(46:53)   "trim(:tvolume)",',"\n";
  print FOCTL '    tprice      position(54:65)   "trim(:tprice)",',"\n";
  print FOCTL '    tamt        position(66:79)   "trim(:tamt)",',"\n";
  print FOCTL '    ttime       position(82:89)   "trim(:ttime)",',"\n";
  print FOCTL '    direction   position(92:97)   "trim(:direction)",',"\n";
  print FOCTL '    offsetflag  position(98:102)  "trim(:offsetflag)",',"\n";
  print FOCTL '    orderid     position(105:116) "trim(:orderid)",',"\n";
  print FOCTL '    userid      position(117:129) "trim(:userid)"',"\n";
  print FOCTL ')',"\n";
  print FOCTL 'into table TI_QH_DELIVERY',"\n";
  print FOCTL 'when(1)=\'1\'',"\n";
  print FOCTL 'trailing nullcols',"\n";
  print FOCTL '(',"\n";
  print FOCTL '    instrid     position(2:11)    "trim(:instrid)",',"\n";
  print FOCTL '    partid      position(12:25)   "trim(:partid)",',"\n";
  print FOCTL '    partabbr    position(26:39)   "trim(:partabbr)",',"\n";
  print FOCTL '    accountid   position(40:51)   "trim(:accountid)",',"\n";
  print FOCTL '    accattr     position(52:63)   "trim(:accattr)",',"\n";
  print FOCTL '    clearprice  position(64:77)   "trim(:clearprice)",',"\n";
  print FOCTL '    buytot      position(78:91)   "trim(:buytot)",',"\n";
  print FOCTL '    soldtot     position(92:105)  "trim(:soldtot)",',"\n";
  print FOCTL '    transfee    position(106:119) "trim(:transfee)"',"\n";
  print FOCTL ')',"\n";
  print FOCTL 'into table TI_QH_SETTLEMENTDETAIL',"\n";
  print FOCTL 'when(1)=\'2\'',"\n";
  print FOCTL 'trailing nullcols',"\n";
  print FOCTL '(',"\n";
  print FOCTL '    partid      position(2:15)    "trim(:partid)",',"\n";
  print FOCTL '    clientid    position(16:25)   "trim(:clientid)",',"\n";
  print FOCTL '    instrid     position(26:35)   "trim(:instrid)",',"\n";
  print FOCTL '    clearprice  position(36:45)   "trim(:clearprice)",',"\n";
  print FOCTL '    bopenamt    position(46:57)   "trim(:bopenamt)",',"\n";
  print FOCTL '    boffamt     position(58:69)   "trim(:boffamt)",',"\n";
  print FOCTL '    buyamt      position(70:83)   "trim(:buyamt)",',"\n";
  print FOCTL '    sopenamt    position(84:95)   "trim(:sopenamt)",',"\n";
  print FOCTL '    soffamt     position(96:107)  "trim(:soffamt)",',"\n";
  print FOCTL '    sellamt     position(108:121) "trim(:sellamt)",',"\n";
  print FOCTL '    buysum      position(122:135) "trim(:buysum)",',"\n";
  print FOCTL '    sellsum     position(136:149) "trim(:sellsum)",',"\n";
  print FOCTL '    btotalamt   position(150:163) "trim(:btotalamt)",',"\n";
  print FOCTL '    stotalamt   position(164:177) "trim(:stotalamt)",',"\n";
  print FOCTL '    margin      position(178:191) "trim(:margin)",',"\n";
  print FOCTL '    actual      position(192:205) "trim(:actual)",',"\n";
  print FOCTL '    transfee    position(206:219) "trim(:transfee)"',"\n";
  print FOCTL ')',"\n";
  print FOCTL 'into table TI_QH_FUTRUEPREFER',"\n";
  print FOCTL 'when(1)=\'3\'',"\n";
  print FOCTL 'trailing nullcols',"\n";
  print FOCTL '(',"\n";
  print FOCTL '    business_date        position(2:9)     "trim(:business_date)",',"\n";
  print FOCTL '    combi_report_code    position(10:91)   "trim(:combi_report_code)",',"\n";
  print FOCTL '    combi_settle_price   position(92:123)  "trim(:combi_settle_price)",',"\n";
  print FOCTL '    priority             position(124:137) "trim(:priority)",',"\n";
  print FOCTL '    basic_frozen_balance position(138:159) "trim(:basic_frozen_balance)"',"\n";
  print FOCTL ')',"\n";
  close FOCTL;
}
