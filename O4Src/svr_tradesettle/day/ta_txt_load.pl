use bytes;
use Getopt::Std;
my(%opt);
#perl ta_txt_load.pl -d ./ -u hsqs/hsqs@ORA10G 1 2 7 678
$mark_group_no=$ARGV[4],$flow_id=$ARGV[5],$operator_no=$ARGV[6],$function_id=$ARGV[7];
getopts("d:u:",\%opt);
#lys 需要修改的内容
my $workdir;
my @filelist;

#定义一个全局的变量
$v_line=0;
#删除功能号
$sqlarg='sqlplus -L -S '.$opt{u}.' @'.$opt{d}.'delfun.sql '.$mark_group_no.' '.$flow_id.' '.$function_id.' '.$operator_no;
print $sqlarg."\n\n";

$sysflag=system($sqlarg);
if($sysflag eq 256 )
{
	#如果执行出错退出perl
	die '数据库连接问题';
}
#  按照表qs_tflowlog 设定参数的值，不能超出字符串长度 $mark_group_no 必须是8位以下整数

if($flow_id eq '3')
{
	$v_name='TA';
}elsif($flow_id eq '2')
{
	$v_name='日初结算';
}elsif($flow_id eq '10')
{
	$v_name='估值核对';
}
#elsif($flow_id eq '5')
#{
#	$v_name='日终结算';
#}
elsif($flow_id eq '99')
{
	$v_name='委托成交数据同步';
}
$v_mess=$v_name.'接口数据导入开始';
$sqlarg='sqlplus '.$opt{u}.' @'.$opt{d}.'readflowlog.sql 1 '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$v_mess ;
system($sqlarg);

#------------------------------------------------------------------------------------------
#  在工作目录下删除/创建子目录
#------------------------------------------------------------------------------------------
$workdir=$opt{d};
if (!(-d $workdir))
{
	print 'Directory ',$workdir,' does not exist!',"\n";
	exit 1;
}
if($flow_id eq '3' )
{
 #创建TA的日志文件
  opendir(DIR,$workdir.'ta');
	@filelist=readdir(DIR);
	closedir(DIR);
	foreach $ele(@filelist){unlink $workdir.'ta/'.$ele if (-f $workdir.'ta/'.$ele);}
	undef @filelist;
	mkdir $workdir.'ta' if !(-d $workdir.'ta');
	$workdir.='ta/';
	#spool控制文件里面已经存在/;
	$opt{path}=$opt{d}.'ta';
}elsif($flow_id eq '2' )
{
 #创建RCJS的日志文件
  opendir(DIR,$workdir.'rcjs');
	@filelist=readdir(DIR);
	closedir(DIR);
	foreach $ele(@filelist){unlink $workdir.'rcjs/'.$ele if (-f $workdir.'rcjs/'.$ele);}
	undef @filelist;
	mkdir $workdir.'rcjs' if !(-d $workdir.'rcjs');
 $workdir.='rcjs/';
 #spool控制文件里面已经存在/;
	$opt{path}=$opt{d}.'rcjs';
}elsif($flow_id eq '10' )
{
 #创建JS的日志文件
  opendir(DIR,$workdir.'hdgz');
	@filelist=readdir(DIR);
	closedir(DIR);
	foreach $ele(@filelist){unlink $workdir.'hdgz/'.$ele if (-f $workdir.'hdgz/'.$ele);}
	undef @filelist;
	mkdir $workdir.'hdgz' if !(-d $workdir.'hdgz');
 $workdir.='hdgz/';
 #spool控制文件里面已经存在/;
	$opt{path}=$opt{d}.'hdgz';
}elsif($flow_id eq '99' )
{
 #创建wtcj的日志文件
  opendir(DIR,$workdir.'wtcj');
	@filelist=readdir(DIR);
	closedir(DIR);
	foreach $ele(@filelist){unlink $workdir.'wtcj/'.$ele if (-f $workdir.'wtcj/'.$ele);}
	undef @filelist;
	mkdir $workdir.'wtcj' if !(-d $workdir.'wtcj');
 $workdir.='wtcj/';
 #spool控制文件里面已经存在/;
	$opt{path}=$opt{d}.'wtcj';
}else
{
			$v_mess='流程步骤和市场组编号不正确，退出！！';
			$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'readflowlog.sql 3 '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$v_mess ;
			system($sqlplus);
			#print "1";
			die '流程步骤和市场组编号不正确，退出！！'."\n";
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
#  读取接口表的配置信息
#------------------------------------------------------------------------------------------
#配置参数流程步骤和市场组编号确定使用的哪个导数方式 
#生成文件路径传递进去 $opt{d}
if($flow_id eq '3' )
{
	#txt ta导数 传入1个参数 file_type=6 
$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'pathconfig.sql '.'\'6\''.' '.$opt{path};
}
if( $flow_id eq '2')
{
	#dbf 结算数据倒数方式file_type=2 
$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'pathconfig.sql '.'\'2\''.' '.$opt{path};
}
if( $flow_id eq '10')
{
	#核对数据导入
$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'pathconfig.sql '.'\'3\''.','.'\'4\''.','.'\'5\''.' '.$opt{path};
}
if( $flow_id eq '99')
{
	#委托成交同步数据导入
$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'pathconfig.sql '.'\'8\''.' '.$opt{path};
}
while(!$sqlplus)
{
			$v_mess='流程步骤和市场组编号不正确，退出！！';
			$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'readflowlog.sql 3 '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$v_mess ;
			system($sqlplus);	
			#print "1";
	die '流程步骤和市场组编号不正确，退出！！'."\n";
}
system($sqlplus);
#导入的文件记录到log
my $importlogfile=$opt{path}.'/importfile.log';
print $importlogfile
open FILEOU,">$importlogfile";
#打开文件
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
#修改存在的路径文件的状态
if( -e $path_file_name )
{
	$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'updatepathstatus.sql 2 '.$file_type.' '.$path_file_name;
	system($sqlplus);	
#路径当成数据，路径当成key $table_name 就是导入的表名
$hash_table_file{$path_file_name}=$table_name;
$hash_son_filetype{$path_file_name}=$son_file_type;
$hash_filetype{$path_file_name}=$file_type;
#如果row_number是1 说明第一次导入清空接口表数据，如果不是1 说明第二次导入保留原来数据，不清空
 if($row_number == 1){
 	   $sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'truncatetable.sql '.$table_name;
			system($sqlplus);	
 	   }
#写入实际导入的文件
print FILEOU $path_file_name."\n"; 	   
}

}

#if($v_line == 0 )
#{
#	die 'path_load.txt文件没有数据，请检查';
#}
$v_line = 0;
close F;
close FILEOU;
my $importfilesize= -s $opt{path}.'/importfile.log';
#如果是0说明没有要导入的文件退出
if($importfilesize==0)
{
						$v_mess=$opt{path}.'/importfile.log没有要导入的文件，退出';
						$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'readflowlog.sql 3 '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$v_mess ;
						system($sqlplus);	
						die $v_mess,"\n";
}
if($flow_id eq '3' )
{
	#txt ta导数 file_type=6
$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'tableconfig.sql '.'\'6\''.' '.$opt{path};
}
if($flow_id eq '2' )
{
	#dbf 结算导数 file_type=2
	$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'tableconfig.sql '.'\'2\''.' '.$opt{path};
}
if($flow_id eq '10' )
{
	#dbf 估值数据导入 file_type=5
	$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'tableconfig.sql '.'\'3\''.','.'\'4\''.','.'\'5\''.' '.$opt{path};
	
}
if($flow_id eq '99' )
{
	#委托成交同步数据导入 file_type=8
	$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'tableconfig.sql '.'\'8\''.' '.$opt{path};
	
}
$sysflag=system($sqlplus);
if($sysflag eq 256 )
{
	#如果执行出错退出perl
	die '导数tableconfig.sql有问题';
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
				#使用表名 唯一数字加表
				if(uc($t_filetype) eq uc('dbf'))
				{
						$hash_cpp{$t_tablename}=$t_parsetype.$filetype_id.$t_p2offset.$t_newreclen.$t_memcnt.$t_fieldcnt;
						$hash_control_file{$t_tablename}.='into table '.$t_tablename."\n".'when(1)='.'\''.$filetype_id.'\''."\n".'trailing nullcols'."\n".'('."\n".'  '.$t_columnname.'    position('.($t_begpos+0).':'.($t_endpos+0).')'.' '.$sub;
				}elsif(uc($t_filetype) eq uc('txt') and uc($t_tablename) eq uc('qs_ti_tkye')){
				#LYS ADD 如果是txt文件生成ctl的语句按照,插入20140606 fields terminated by ","以，作为分割点
				#txt的控制文件 txt特殊文件需要填写从第几行开始加载
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
			#txt控制文件
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
				#LYS ADD 如果是txt文件生成ctl的语句按照,插入
				#txt控制文件
				$hash_control_file{$t_tablename}.=','."\n".'  '.$t_columnname.'    ';
							}
			}
		}
		if(uc($t_filetype) eq uc('txt') )
		{
			#如果是txt文件不进行操作
		}
		elsif ($t_memcpy1>0 and $t_memcpy2>0 and $t_parsetype eq '2')
		{
			$hash_cpp_mem{$t_tablename}.=$t_memcpy1.$t_memcpy2;
		}

}
#if($v_line == 0 )
#{
#	die 'table_load.txt文件没有数据，请检查';
#}
$v_line = 0;
close F;
foreach my $filename(sort keys %hash_cpp)
{
	$hash_cpp{$filename}.=$hash_cpp_mem{$filename};
}
#打开文件确定导入接口类型  估值类型专用
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
	die 'gztype.txt文件没有数据，请检查';
}
$v_line = 0;
close F;
}
#读取每一个文件 如果是dbf文件生成txt文件
foreach my $each_filename(keys %hash_table_file)
{
	  $each_tablename=$hash_table_file{$each_filename};
	  $each_filename=~m/\/.+\/([a-zA-Z0-9_.]+)/o;
	  $file_name=$1;
		$each_filename=~m/.(DBF|dbf|txt|TXT$)/o;
		$each_filelastname=$1;
		#文件子类型
		$son_filetype=$hash_son_filetype{$each_filename};
		$filetype=$hash_filetype{$each_filename};
		if(uc($each_filelastname) eq uc('txt'))
		{
#因为是txt文件不需要转换文件
#lys需要修改的内容 去掉.$workdir
		$hash_group_allfiles{$file_name}="\n".'infile \''.$each_filename.'\'';	
	}else
	{
	 #因为是dbf文件需要把dbf转换成txt文件 因为调用的都是 自定义的
					$hash_group_allfiles{$file_name}="\n".'infile \''.$workdir.'txt/'.$file_name.'.txt\'';
					my $output_filename=$workdir.'txt/'.$file_name.'.txt';
			##还不能转换dbf格式的文件
					$inputstr=$hash_cpp{$each_tablename};
					#估值导入需要自定义导入$filetype=5 是估值 3，4是核对
					if($flow_id eq '10' and $filetype eq '5')
					{
						#传递 层次类型 和 层次号码  根据文件格式判断文件类型  根据文件内容判断文件序号
						$each_filename=~m/\/.+\/([a-zA-Z0-9_.]+)/o;
						$new_filename=$1;
						if (!defined $son_filetype)
						{
							die '------文件子类型是null-----退出------',"\n\n\n\n\n\n\n\n\n";
						}elsif($gztype eq '1' or $gztype eq '4')
							   {
							   	#不分组基金账号
#							   	$cclxstr=-1;
#							   	$ccxhstr=substr($new_filename,2,6);
#									$new_filename=~m/([a-zA-Z0-9]{2})([a-zA-Z0-9]+)([_])([a-zA-Z0-9]+)([_])([a-zA-Z0-9_.]+)/o;					
									$asset_code=-1;	
									$fund_code=substr($new_filename,2,6);
							   }elsif($gztype eq '2' and $son_filetype eq '503')
							    {
							    	#分组的资产单元
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

						#自定义后最后一个0是输出文件的第一列的值 添加一个接口类型 1 是旧接口 、2 是新接口、4赢时胜的接口
#					    $cpp_str=$opt{d}.'dbf2txt2 '.$each_filename.' '.$output_filename.' '.'1'.' '.$cclxstr.' '.$ccxhstr.' 0'.' '.$gztype; 
 					    $cpp_str=$opt{d}.'dbf2txt2 '.$each_filename.' '.$output_filename.' '.'1'.' '.$asset_code.' '.$fund_code.' 0'.' '.$gztype; 

					}else{
					        $cpp_str=$opt{d}.'dbf2txt2 '.$each_filename.' '.$output_filename.' '.'0'.' '.substr($inputstr,1,1).' '.(substr($inputstr,2,5)+0).' '.(substr($inputstr,7,5)+0).' '.(substr($inputstr,12,4)+0).' '.substr($inputstr,20);
				       }
					$sysflag=system($cpp_str);
					if($sysflag eq 256 )
						{
						#如果执行出错退出perl
						die 'dbf转换文件有问题';
						}
	}
	  	   
}

#生成ctl文件
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
		#跳过前18行 插入
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
#执行ctl文件
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
						#如果执行出错退出perl
						$v_mess='可执行程序没权限，退出！！';
						$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'readflowlog.sql 3 '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$v_mess ;
						system($sqlplus);	
						die '执行ctl文件有问题';
						}
	}
}
#读取log 如果log里面有错误就把这个log文件的路径设置成0，未导入
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
						#如果有一个不是0就说明导入有问题，需要重新导入
						$v_mess=$workdir.$log_file.'文件有问题，退出！！';
						$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'readflowlog.sql 3 '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$v_mess ;
						system($sqlplus);	
						die $v_mess,"\n";
	}
	}
	close F;
}


if($flow_id eq '3' or $flow_id eq '2' or $flow_id eq '10' or $flow_id eq '99')
{
	#ta、结算、估值、文件执行存储过程  修改标志在存储里面
		if($flow_id eq '3')
	{
		$v_name='TA';
	}elsif($flow_id eq '2')
	{
		$v_name='日初结算';
	}elsif($flow_id eq '10')
	{
		$v_name='估值核对';
	}
	#elsif($flow_id eq '5')
	#{
	#	$v_name='日终结算';
	#}
	elsif($flow_id eq '99')
	{
		$v_name='委托成交数据同步';
	}
	$v_mess=$v_name.'接口数据导入完成,准备接口数据处理';
	$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'readflowlog.sql 1 '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$v_mess ;
	system($sqlplus);	
	
	$sqlplus='sqlplus '.$opt{u}.' @'.$opt{d}.'exec_proc.sql'.' '.$mark_group_no.' '.$flow_id.' '.$operator_no.' '.$function_id;
	$sysflag=system($sqlplus);
	if($sysflag eq 256 )
						{
						#如果执行出错退出perl
						die '执行插入数据有问题';
						}
}
