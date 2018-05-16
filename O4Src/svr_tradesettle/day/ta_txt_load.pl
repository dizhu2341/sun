use bytes;
use Getopt::Std;
my(%opt);
#perl ta_txt_load.pl -d ./ -u hsqs/hsqs@ORA10G 1 2 7 678
$mark_group_no=$ARGV[4],$flow_id=$ARGV[5],$operator_no=$ARGV[6],$function_id=$ARGV[7];
getopts("d:u:",\%opt);
#lys ��Ҫ�޸ĵ�����
my $workdir;
my @filelist;

#����һ��ȫ�ֵı���
$v_line=0;
#ɾ�����ܺ�
$sqlarg='sqlplus -L -S '.$opt{u}.' @'.$opt{d}.'delfun.sql '.$mark_group_no.' '.$flow_id.' '.$function_id.' '.$operator_no;
print $sqlarg."\n\n";

$sysflag=system($sqlarg);
if($sysflag eq 256 )
{
	#���ִ�г����˳�perl
	die '���ݿ���������';
}
#  ���ձ�qs_tflowlog �趨������ֵ�����ܳ����ַ������� $mark_group_no ������8λ��������

if($flow_id eq '3')
{
	$v_name='TA';
}elsif($flow_id eq '2')
{
	$v_name='�ճ�����';
}elsif($flow_id eq '10')
{
	$v_name='��ֵ�˶�';
}
#elsif($flow_id eq '5')
#{
#	$v_name='���ս���';
#}
elsif($flow_id eq '99')
{
	$v_name='ί�гɽ�����ͬ��';
}
$v_mess=$v_name.'�ӿ����ݵ��뿪ʼ';
$sqlarg='sqlplus '.$opt{u}.' @'.$opt{d}.'readflowlog.sql 1 '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$v_mess ;
system($sqlarg);

#------------------------------------------------------------------------------------------
#  �ڹ���Ŀ¼��ɾ��/������Ŀ¼
#------------------------------------------------------------------------------------------
$workdir=$opt{d};
if (!(-d $workdir))
{
	print 'Directory ',$workdir,' does not exist!',"\n";
	exit 1;
}
if($flow_id eq '3' )
{
 #����TA����־�ļ�
  opendir(DIR,$workdir.'ta');
	@filelist=readdir(DIR);
	closedir(DIR);
	foreach $ele(@filelist){unlink $workdir.'ta/'.$ele if (-f $workdir.'ta/'.$ele);}
	undef @filelist;
	mkdir $workdir.'ta' if !(-d $workdir.'ta');
	$workdir.='ta/';
	#spool�����ļ������Ѿ�����/;
	$opt{path}=$opt{d}.'ta';
}elsif($flow_id eq '2' )
{
 #����RCJS����־�ļ�
  opendir(DIR,$workdir.'rcjs');
	@filelist=readdir(DIR);
	closedir(DIR);
	foreach $ele(@filelist){unlink $workdir.'rcjs/'.$ele if (-f $workdir.'rcjs/'.$ele);}
	undef @filelist;
	mkdir $workdir.'rcjs' if !(-d $workdir.'rcjs');
 $workdir.='rcjs/';
 #spool�����ļ������Ѿ�����/;
	$opt{path}=$opt{d}.'rcjs';
}elsif($flow_id eq '10' )
{
 #����JS����־�ļ�
  opendir(DIR,$workdir.'hdgz');
	@filelist=readdir(DIR);
	closedir(DIR);
	foreach $ele(@filelist){unlink $workdir.'hdgz/'.$ele if (-f $workdir.'hdgz/'.$ele);}
	undef @filelist;
	mkdir $workdir.'hdgz' if !(-d $workdir.'hdgz');
 $workdir.='hdgz/';
 #spool�����ļ������Ѿ�����/;
	$opt{path}=$opt{d}.'hdgz';
}elsif($flow_id eq '99' )
{
 #����wtcj����־�ļ�
  opendir(DIR,$workdir.'wtcj');
	@filelist=readdir(DIR);
	closedir(DIR);
	foreach $ele(@filelist){unlink $workdir.'wtcj/'.$ele if (-f $workdir.'wtcj/'.$ele);}
	undef @filelist;
	mkdir $workdir.'wtcj' if !(-d $workdir.'wtcj');
 $workdir.='wtcj/';
 #spool�����ļ������Ѿ�����/;
	$opt{path}=$opt{d}.'wtcj';
}else
{
			$v_mess='���̲�����г����Ų���ȷ���˳�����';
			$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'readflowlog.sql 3 '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$v_mess ;
			system($sqlplus);
			#print "1";
			die '���̲�����г����Ų���ȷ���˳�����'."\n";
}
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
#------------------------------------------------------------------------------------------
#  ��ȡ�ӿڱ��������Ϣ
#------------------------------------------------------------------------------------------
#���ò������̲�����г�����ȷ��ʹ�õ��ĸ�������ʽ 
#�����ļ�·�����ݽ�ȥ $opt{d}
if($flow_id eq '3' )
{
	#txt ta���� ����1������ file_type=6 
$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'pathconfig.sql '.'\'6\''.' '.$opt{path};
}
if( $flow_id eq '2')
{
	#dbf �������ݵ�����ʽfile_type=2 
$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'pathconfig.sql '.'\'2\''.' '.$opt{path};
}
if( $flow_id eq '10')
{
	#�˶����ݵ���
$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'pathconfig.sql '.'\'3\''.','.'\'4\''.','.'\'5\''.' '.$opt{path};
}
if( $flow_id eq '99')
{
	#ί�гɽ�ͬ�����ݵ���
$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'pathconfig.sql '.'\'8\''.' '.$opt{path};
}
while(!$sqlplus)
{
			$v_mess='���̲�����г����Ų���ȷ���˳�����';
			$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'readflowlog.sql 3 '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$v_mess ;
			system($sqlplus);	
			#print "1";
	die '���̲�����г����Ų���ȷ���˳�����'."\n";
}
system($sqlplus);
#������ļ���¼��log
my $importlogfile=$opt{path}.'/importfile.log';
print $importlogfile
open FILEOU,">$importlogfile";
#���ļ�
open F,$workdir.'path_load.txt' || die "can not open";
my %hash_table_file;
my %hash_son_filetype;
my %hash_filetype;
while(<F>)
{
	$v_line++;
	chomp;
	~s/\r+$//o;
	$_=~m/^([a-zA-Z_\s]+){1,30}([a-zA-Z0-9_\s])([a-zA-Z0-9_\s]+){1,3}([a-zA-Z0-9_\s])(\/[a-zA-Z0-9_\s].+)/o;
	$table_name=$1;
	$file_type=$2;
	$son_file_type=$3;
	$row_number=$4;
	$path_file_name=$5;
	$table_name=~s/\s+//o;
	$file_type=~s/\s+//o;
	$son_file_type=~s/\s+//o;
	$path_file_name=~s/\s+//o;
	$row_number=~s/\s+//o;
#�޸Ĵ��ڵ�·���ļ���״̬
if( -e $path_file_name )
{
	$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'updatepathstatus.sql 2 '.$file_type.' '.$path_file_name;
	system($sqlplus);	
#·���������ݣ�·������key $table_name ���ǵ���ı���
$hash_table_file{$path_file_name}=$table_name;
$hash_son_filetype{$path_file_name}=$son_file_type;
$hash_filetype{$path_file_name}=$file_type;
#���row_number��1 ˵����һ�ε�����սӿڱ����ݣ��������1 ˵���ڶ��ε��뱣��ԭ�����ݣ������
 if($row_number == 1){
 	   $sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'truncatetable.sql '.$table_name;
			system($sqlplus);	
 	   }
#д��ʵ�ʵ�����ļ�
print FILEOU $path_file_name."\n"; 	   
}

}

#if($v_line == 0 )
#{
#	die 'path_load.txt�ļ�û�����ݣ�����';
#}
$v_line = 0;
close F;
close FILEOU;
my $importfilesize= -s $opt{path}.'/importfile.log';
#�����0˵��û��Ҫ������ļ��˳�
if($importfilesize==0)
{
						$v_mess=$opt{path}.'/importfile.logû��Ҫ������ļ����˳�';
						$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'readflowlog.sql 3 '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$v_mess ;
						system($sqlplus);	
						die $v_mess,"\n";
}
if($flow_id eq '3' )
{
	#txt ta���� file_type=6
$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'tableconfig.sql '.'\'6\''.' '.$opt{path};
}
if($flow_id eq '2' )
{
	#dbf ���㵼�� file_type=2
	$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'tableconfig.sql '.'\'2\''.' '.$opt{path};
}
if($flow_id eq '10' )
{
	#dbf ��ֵ���ݵ��� file_type=5
	$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'tableconfig.sql '.'\'3\''.','.'\'4\''.','.'\'5\''.' '.$opt{path};
	
}
if($flow_id eq '99' )
{
	#ί�гɽ�ͬ�����ݵ��� file_type=8
	$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'tableconfig.sql '.'\'8\''.' '.$opt{path};
	
}
$sysflag=system($sqlplus);
if($sysflag eq 256 )
{
	#���ִ�г����˳�perl
	die '����tableconfig.sql������';
}
open F,$workdir.'table_load.txt' || die "can not open";
my %hash_control_txtfile;
while(<F>)
{
	$v_line++;
	chomp;
	~s/\r+$//o;
	$_=~m/^([YN])([01])(DBF|TXT)([12])([A-Z0-9_\s]{1,30})([A-Z0-9_\s]{1,50})([CND])(\d{3})(\d{2})(\d{5})(\d{5})(\d{5})(\d{5})([0-9])([012])(\d{5})(\d{5})(\d{4})(\d{4})/o;
	$t_ifread    =$1;	 $t_columnid=$2;	 $t_filetype  =$3;  $t_parsetype =$4;  $t_tablename=$5;
	$t_columnname=$6;  $t_datatype=$7;   $t_datalength=$8;  $t_datascale =$9;  $t_begpos   =$10;
	$t_endpos    =$11; $t_memcpy1 =$12;  $t_memcpy2   =$13; $t_loadgroup =$14; $t_firstlast=$15;
	$t_p2offset  =$16; $t_newreclen=$17; $t_memcnt    =$18; $t_fieldcnt  =$19;
	$t_tablename=~s/\s+$//o;
	$t_columnname=~s/\s+$//o;
	$filetype_id=0;
	if(uc($t_datatype) eq uc('N') and uc($t_tablename) eq uc('qs_ti_tfadata'))
	{
		$sub='"nvl(replace(trim(replace(:'.$t_columnname.',chr(0),chr(32))),\',\',\'\'),0)"';
	}elsif(uc($t_datatype) eq uc('C') and uc($t_tablename) eq uc('qs_ti_tfadata')){
		$sub='"trim(replace(:'.$t_columnname.',chr(0),chr(32)))"';
	}
		if ($t_ifread eq 'Y')
		{
			if ($t_firstlast eq '1')
			{
				#ʹ�ñ��� Ψһ���ּӱ�
				if(uc($t_filetype) eq uc('dbf'))
				{
						$hash_cpp{$t_tablename}=$t_parsetype.$filetype_id.$t_p2offset.$t_newreclen.$t_memcnt.$t_fieldcnt;
						$hash_control_file{$t_tablename}.='into table '.$t_tablename."\n".'when(1)='.'\''.$filetype_id.'\''."\n".'trailing nullcols'."\n".'('."\n".'  '.$t_columnname.'    position('.($t_begpos+0).':'.($t_endpos+0).')'.' '.$sub;
				}elsif(uc($t_filetype) eq uc('txt') and uc($t_tablename) eq uc('qs_ti_tkye')){
				#LYS ADD �����txt�ļ�����ctl����䰴��,����20140606 fields terminated by ","�ԣ���Ϊ�ָ��
				#txt�Ŀ����ļ� txt�����ļ���Ҫ��д�ӵڼ��п�ʼ����
						$hash_control_file{$t_tablename}.='into table '.$t_tablename."\n".'when(1)<>'.'\''.'O'.'\''."\n".'trailing nullcols'."\n".'('."\n".'  '.$t_columnname.'    position('.($t_begpos-1).':'.($t_endpos-1).')';
				}else{
						$hash_control_file{$t_tablename}.='into table '.$t_tablename."\n".'fields terminated by ","'."\n".'trailing nullcols'."\n".'('."\n".'  '.$t_columnname.'    ';
				}
			}
			elsif($t_firstlast eq '2')

			{
				if(uc($t_filetype) eq uc('dbf'))
				{
					$hash_control_file{$t_tablename}.=','."\n".'  '.$t_columnname.'    position('.($t_begpos+0).':'.($t_endpos+0).')'.' '.$sub."\n".')'."\n";
				}elsif(uc($t_filetype) eq uc('txt') and uc($t_tablename) eq uc('qs_ti_tkye')){
					$hash_control_file{$t_tablename}.=','."\n".'  '.$t_columnname.'    position('.($t_begpos-1).':'.($t_endpos-1).')'."\n".')'."\n";
				}else{
			#txt�����ļ�
							$hash_control_file{$t_tablename}.=','."\n".'  '.$t_columnname.'    '."\n".')'."\n";
							}
			}
			else
			{
				if(uc($t_filetype) eq uc('dbf'))
				{
				 $hash_control_file{$t_tablename}.=','."\n".'  '.$t_columnname.'    position('.($t_begpos+0).':'.($t_endpos+0).')'.' '.$sub;	
				}elsif(uc($t_filetype) eq uc('txt') and uc($t_tablename) eq uc('qs_ti_tkye')){
				 $hash_control_file{$t_tablename}.=','."\n".'  '.$t_columnname.'    position('.($t_begpos-1).':'.($t_endpos-1).')';	
				}else{
				#LYS ADD �����txt�ļ�����ctl����䰴��,����
				#txt�����ļ�
				$hash_control_file{$t_tablename}.=','."\n".'  '.$t_columnname.'    ';
							}
			}
		}
		if(uc($t_filetype) eq uc('txt') )
		{
			#�����txt�ļ������в���
		}
		elsif ($t_memcpy1>0 and $t_memcpy2>0 and $t_parsetype eq '2')
		{
			$hash_cpp_mem{$t_tablename}.=$t_memcpy1.$t_memcpy2;
		}

}
#if($v_line == 0 )
#{
#	die 'table_load.txt�ļ�û�����ݣ�����';
#}
$v_line = 0;
close F;
foreach my $filename(sort keys %hash_cpp)
{
	$hash_cpp{$filename}.=$hash_cpp_mem{$filename};
}
#���ļ�ȷ������ӿ�����  ��ֵ����ר��
if($flow_id eq '10'){
$sqlgztype='sqlplus '.$opt{u}.' @'.$opt{d}.'gztype.sql '.$opt{path};
print $sqlgztype."\n";
system($sqlgztype);
open F,$workdir.'gztype.txt' || die "can not open";
while(<F>)
{
	$v_line++;
	chomp;
	~s/\r+$//o;
	$_=~m/^(\d)/o;
	$gztype=$1;
}
if($v_line == 0 )
{
	die 'gztype.txt�ļ�û�����ݣ�����';
}
$v_line = 0;
close F;
}
#��ȡÿһ���ļ� �����dbf�ļ�����txt�ļ�
foreach my $each_filename(keys %hash_table_file)
{
	  $each_tablename=$hash_table_file{$each_filename};
	  $each_filename=~m/\/.+\/([a-zA-Z0-9_.]+)/o;
	  $file_name=$1;
		$each_filename=~m/.(DBF|dbf|txt|TXT$)/o;
		$each_filelastname=$1;
		#�ļ�������
		$son_filetype=$hash_son_filetype{$each_filename};
		$filetype=$hash_filetype{$each_filename};
		if(uc($each_filelastname) eq uc('txt'))
		{
#��Ϊ��txt�ļ�����Ҫת���ļ�
#lys��Ҫ�޸ĵ����� ȥ��.$workdir
		$hash_group_allfiles{$file_name}="\n".'infile \''.$each_filename.'\'';	
	}else
	{
	 #��Ϊ��dbf�ļ���Ҫ��dbfת����txt�ļ� ��Ϊ���õĶ��� �Զ����
					$hash_group_allfiles{$file_name}="\n".'infile \''.$workdir.'txt/'.$file_name.'.txt\'';
					my $output_filename=$workdir.'txt/'.$file_name.'.txt';
			##������ת��dbf��ʽ���ļ�
					$inputstr=$hash_cpp{$each_tablename};
					#��ֵ������Ҫ�Զ��嵼��$filetype=5 �ǹ�ֵ 3��4�Ǻ˶�
					if($flow_id eq '10' and $filetype eq '5')
					{
						#���� ������� �� ��κ���  �����ļ���ʽ�ж��ļ�����  �����ļ������ж��ļ����
						$each_filename=~m/\/.+\/([a-zA-Z0-9_.]+)/o;
						$new_filename=$1;
						if (!defined $son_filetype)
						{
							die '------�ļ���������null-----�˳�------',"\n\n\n\n\n\n\n\n\n";
						}elsif($gztype eq '1' or $gztype eq '4')
							   {
							   	#����������˺�
#							   	$cclxstr=-1;
#							   	$ccxhstr=substr($new_filename,2,6);
#									$new_filename=~m/([a-zA-Z0-9]{2})([a-zA-Z0-9]+)([_])([a-zA-Z0-9]+)([_])([a-zA-Z0-9_.]+)/o;					
									$asset_code=-1;	
									$fund_code=substr($new_filename,2,6);
							   }elsif($gztype eq '2' and $son_filetype eq '503')
							    {
							    	#������ʲ���Ԫ
#							    	$cclxstr=substr($new_filename,9,4);
#							    	$ccxhstr=substr($new_filename,2,6);
									$new_filename=~m/([a-zA-Z0-9]{2})([a-zA-Z0-9]+)([_])([a-zA-Z0-9]+)([_])([a-zA-Z0-9_.]+)/o;
									$asset_code=$4;
									$fund_code=$2;
							   	}else
							   	     {
#							   	     	$cclxstr=-1;
#							   	      $ccxhstr=substr($new_filename,2,6);
												$asset_code=-1;
												$fund_code=substr($new_filename,2,6);
							   	     }

						#�Զ�������һ��0������ļ��ĵ�һ�е�ֵ ���һ���ӿ����� 1 �Ǿɽӿ� ��2 ���½ӿڡ�4Ӯʱʤ�Ľӿ�
#					    $cpp_str=$opt{d}.'dbf2txt2 '.$each_filename.' '.$output_filename.' '.'1'.' '.$cclxstr.' '.$ccxhstr.' 0'.' '.$gztype; 
 					    $cpp_str=$opt{d}.'dbf2txt2 '.$each_filename.' '.$output_filename.' '.'1'.' '.$asset_code.' '.$fund_code.' 0'.' '.$gztype; 

					}else{
					        $cpp_str=$opt{d}.'dbf2txt2 '.$each_filename.' '.$output_filename.' '.'0'.' '.substr($inputstr,1,1).' '.(substr($inputstr,2,5)+0).' '.(substr($inputstr,7,5)+0).' '.(substr($inputstr,12,4)+0).' '.substr($inputstr,20);
				       }
					$sysflag=system($cpp_str);
					if($sysflag eq 256 )
						{
						#���ִ�г����˳�perl
						die 'dbfת���ļ�������';
						}
	}
	  	   
}

#����ctl�ļ�
foreach my $each_file_name(keys %hash_table_file)
{
	$each_table_name=$hash_table_file{$each_file_name};
	$each_table_name=~m/^[\d]{0,3}(.+)/o;
	$true_table_name=$1;
	$each_file_name=~m/^\/.+\/(.+)/;
	$each_file_name=$1;
	$ctlname=$workdir.'ctl/'.'ts_control_'.$each_file_name.'.ctl';
	open  FCTL,">$ctlname";
	if(uc($each_table_name) eq uc('qs_ti_tkye')){
		#����ǰ18�� ����
		print FCTL 'options(skip=18,direct=true,rows=30000,errors=0)',"\n";
	}else{
	print FCTL 'options(direct=true,rows=30000,errors=0)',"\n";
  }
	print FCTL 'unrecoverable',"\n";
	print FCTL 'load data';
	print FCTL $hash_group_allfiles{$each_file_name};
	print FCTL "\n",'append',"\n";
	print FCTL $hash_control_file{$each_table_name},"\n";
	close FCTL;
}
#ִ��ctl�ļ�
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
		my $sqlldr='sqlldr silent=all userid='.$opt{u}.' control='.$ctlfile.' log='.$logfile.' bad='.$badfile;
		$sysflag=system($sqlldr);
					if($sysflag eq 256 )
						{
						#���ִ�г����˳�perl
						$v_mess='��ִ�г���ûȨ�ޣ��˳�����';
						$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'readflowlog.sql 3 '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$v_mess ;
						system($sqlplus);	
						die 'ִ��ctl�ļ�������';
						}
	}
}
#��ȡlog ���log�����д���Ͱ����log�ļ���·�����ó�0��δ����
opendir(DIR,$workdir.'log');
@loglist=readdir(DIR);
closedir(DIR);
foreach $log_file(@loglist)
{
	$logdir=$workdir.'log/';
	$log_file=~m/(ts_control_)([\w]+[\.][\w]+)([\.])(log)/o;
	$filename=$2;
	open F,$logdir.$log_file || die "can not open";
	while(<F>)
	{
	chomp;
	~s/\s+//o;
	$_=~m/^(\d)([\s]+)(Row[s]{0,1} not loaded)(.+)/o;
	$errors=$1;
  $logflag=$3;
	if (($errors ne '0') and ($logflag eq 'Rows not loaded' or $logflag eq 'Row not loaded') )
	{
		
		        $sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'updatepathstatus.sql 0 '.'0 '.$filename;
						system($sqlplus);
						#�����һ������0��˵�����������⣬��Ҫ���µ���
						$v_mess=$workdir.$log_file.'�ļ������⣬�˳�����';
						$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'readflowlog.sql 3 '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$v_mess ;
						system($sqlplus);	
						die $v_mess,"\n";
	}
	}
	close F;
}


if($flow_id eq '3' or $flow_id eq '2' or $flow_id eq '10' or $flow_id eq '99')
{
	#ta�����㡢��ֵ���ļ�ִ�д洢����  �޸ı�־�ڴ洢����
		if($flow_id eq '3')
	{
		$v_name='TA';
	}elsif($flow_id eq '2')
	{
		$v_name='�ճ�����';
	}elsif($flow_id eq '10')
	{
		$v_name='��ֵ�˶�';
	}
	#elsif($flow_id eq '5')
	#{
	#	$v_name='���ս���';
	#}
	elsif($flow_id eq '99')
	{
		$v_name='ί�гɽ�����ͬ��';
	}
	$v_mess=$v_name.'�ӿ����ݵ������,׼���ӿ����ݴ���';
	$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'readflowlog.sql 1 '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$v_mess ;
	system($sqlplus);	
	
	$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'exec_proc.sql'.' '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$function_id;
	$sysflag=system($sqlplus);
	if($sysflag eq 256 )
						{
						#���ִ�г����˳�perl
						die 'ִ�в�������������';
						}
}
