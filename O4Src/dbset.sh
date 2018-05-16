#! /bin/bash

#set following params
JCDBUSR=hsjc
JCDBPWD=hsjc
JCDBSOURCE=ora10g

HGDBUSR=hshg
HGDBPWD=hshg
HGDBSOURCE=ora10g

O3DBUSR=trade32
O3DBPWD=trade32wu
O3DBSOURCE=50.85

#deal function
function jcdbset()
{
        connstr=$1/$2@$3
        for file in `ls *.gcc` 
        do
		sed -i 's\hsjc/hsjc@ora10g\'$connstr'\' $file       
	done;
}

#
function hgdbset()
{
        connstr=$1/$2@$3
        for file in `ls *.gcc` 
        do
		sed -i 's\hshg/hshg@ora10g\'$connstr'\' $file       
	done;
}

function o3dbset()
{
  connstr=$1/$2@$3
  sed -i 's\trade0331/trade0331@ora10g_221\'$connstr'\' s_as_hg_o32queryflow.gcc
}
#
jcdbset $JCDBUSR $JCDBPWD $JCDBSOURCE
hgdbset $HGDBUSR $HGDBPWD $HGDBSOURCE
o3dbset $O3DBUSR $O3DBPWD $O3DBSOURCE
