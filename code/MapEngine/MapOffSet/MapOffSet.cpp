// MapOffSet.cpp: implementation of the CMapOffSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmap.h"
#include "MapOffSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define MAPOFFSET_INTAVAL 25000//10000//25000
#define MAPOFFSET_STARTX  7300
#define MAPOFFSET_STARTY  1800
#define MAPOFFSET_ENDX	  13600
#define MAPOFFSET_ENDY	  5400
#define MAPOFFSET_X_COUNT 2512
#define MAPOFFSET_Y_COUNT 1440

#include <stdio.h>
CMapOffSet::CMapOffSet()
{
	m_file = NULL;
	m_iFileLen = 0;
}

CMapOffSet::~CMapOffSet()
{
	if( m_file )
	{
		fclose(m_file);
		m_file = NULL;
	}
//	m_file.Close();
}
bool CMapOffSet::Init( string strRootPath )
{
	string strFileName = strRootPath;
	char strValue[10] = {0};
	sprintf( strValue, "%d.mos",MAPOFFSET_INTAVAL);
	strFileName += strValue;
//	if( !m_file.Open( strFileName.c_str(),fomShareOnlyRead) )
	m_file = fopen( strFileName.c_str(),"rb" );
	if ( !m_file )
	{
		return false;
	}
	fseek(m_file, 0L, SEEK_END);
	m_iFileLen = ftell(m_file);
	//测试
	/*xxh long yyy = 4318;
	yyy = yyy/( MAPOFFSET_INTAVAL/ 10000 );
	yyy = yyy*MAPOFFSET_INTAVAL;
	double x = 116;
	double y = 39;
	GetMapOffSetFromLoc( x,y);
	GetMapOffSetOnLine( x,y );*/
	return true;
	//以下为加载哈希表
/*	MapOffSet offset,offset1;
	int iLen = sizeof(MapOffSet);
	int i = 0;
//	CVOSFile f111;
//	f111.Open( "c://25000.csv",fomCreate|fomReadWrite);
	char cTemp[32]={0};
	while( 1 )
	{
		int readlen = fread( &offset, 1, iLen, m_file );//m_file.Read( &offset,sizeof(MapOffSet));//fread( &offset, 1, iLen, m_file );
		if( readlen != iLen )
		{
			break;
		}
	//	offset1.lxy = offset.lxy;
	//	memset(cTemp,0,32);
	//	sprintf(cTemp,"%d;%d;%d\r\n",offset.lxy,offset.loffsetx,offset.loffsety);
	//	f111.Write(cTemp,strlen(cTemp));
		m_mapMapOffSet.insert(pair<int, MapOffSet>( offset.lxy, offset ) );
	}
//	f111.Close();
	*/
	return true;
}
bool CMapOffSet::GetMapOffSetFromLoc( double& lon, double& lan )
{
//	outx = x;
//	outy = y;
	if( lon*100 > MAPOFFSET_ENDX || lon*100 < MAPOFFSET_STARTX || lan*100 > MAPOFFSET_ENDY || lan*100 < MAPOFFSET_STARTY )
	{
		return true;
	}
	int idx = ( lon*1000000 - MAPOFFSET_STARTX*10000 )/MAPOFFSET_INTAVAL;
	int idy = ( lan*1000000 - MAPOFFSET_STARTY*10000 )/MAPOFFSET_INTAVAL;
	int pos  = idx*MAPOFFSET_Y_COUNT+idy;
	int iSize = sizeof(MapOffSet);
	pos = pos*iSize;
	if( pos > m_iFileLen )
	{
		return false;
	}
	if( m_file == NULL )
	{
		return true;
	}
	fseek(m_file, pos, SEEK_SET);
	MapOffSet offset;
	if( !fread(&offset, iSize, 1, m_file) )//m_file.Read( &offset2,iLen);
	{
		return false;
	}
	//检验读取数据是否正确，确实很发布版本可以去掉
	long dx = INT( lon*1000000 );// ((int)(x*1000000)) / MAPOFFSET_INTAVAL 
	dx = (dx / MAPOFFSET_INTAVAL);
	dx = dx * MAPOFFSET_INTAVAL;

	long dy = INT( lan*1000000 );
	dy = (dy / MAPOFFSET_INTAVAL);
	dy = dy * ( MAPOFFSET_INTAVAL/ 10000 ); 
	long xy = dx + dy;
	if( xy != offset.lxy )
	{
		ASSERT(FALSE);
		return false;
	}
	//纠偏
	lon += ( offset.loffsetx / 1000000.0 );
	lan += ( offset.loffsety / 1000000.0 );
	return true;
}
bool CMapOffSet::GetMapOffSet( double& lon, double& lan )
{
	if( lon*100 > MAPOFFSET_ENDX || lon*100 < MAPOFFSET_STARTX || lan*100 > MAPOFFSET_ENDY || lan*100 < MAPOFFSET_STARTY )
	{
		return true;
	}
	long dx = INT( lon*1000000 );// ((int)(x*1000000)) / MAPOFFSET_INTAVAL 
	dx = (dx / MAPOFFSET_INTAVAL);
	dx = dx * MAPOFFSET_INTAVAL;

	long dy = INT( lan*1000000 );
	dy = (dy / MAPOFFSET_INTAVAL);
	//	float iiiiii = MAPOFFSET_INTAVAL/ 10000;
	dy = dy * ( MAPOFFSET_INTAVAL/ 10000 ); 
	//-------------
	long xy = dx + dy;
	//------------
	MapOffSet offset;
	map<int, MapOffSet>::iterator iter;
	iter = m_mapMapOffSet.find( xy );
	if(iter != m_mapMapOffSet.end())
	{
		offset = iter->second;
		lon += ( offset.loffsetx / 1000000.0 );
		lan += ( offset.loffsety / 1000000.0 );
		return true;
	}
	else
		return false;
		
	return true;
}
bool CMapOffSet::GetMapOffSetOnLine( double& lon, double& lan )
{
	if( lon*100 > MAPOFFSET_ENDX || lon*100 < MAPOFFSET_STARTX || lan*100 > MAPOFFSET_ENDY || lan*100 < MAPOFFSET_STARTY )
	{
		return true;
	}
	long dx = INT( lon*1000000 );// ((int)(x*1000000)) / MAPOFFSET_INTAVAL 
	dx = (dx / MAPOFFSET_INTAVAL);
	dx = dx * MAPOFFSET_INTAVAL;

	long dy = INT( lan*1000000 );
	dy = (dy / MAPOFFSET_INTAVAL);
	dy = dy * ( MAPOFFSET_INTAVAL/ 10000 ); 
	//-------------
	long xy = dx + dy;
	//
	char temp[256]={0};
	sprintf( temp,"http://www.gmapx.com/api/getmapoffset.php?key=temp1&mosxy=%d",xy );
	MemoryStruct chunk;
	int errcode= curl_httpget( temp,&chunk,NULL);
	if(!errcode)
	{
		if(chunk.memory)
		{
			if ( chunk.memory[0]=='1' ) 
			{
				int ilen = strlen( chunk.memory );
				if( ilen > 5 )
				{
					if( chunk.memory[1] == ',' )
					{
						char* pTemp = chunk.memory+2;
						char* pTemp1 = strstr( pTemp, "," );
						if( pTemp1 != NULL )
						{
							char cTemp[20]={0};
							memcpy( cTemp, pTemp, pTemp1 - pTemp );
							int imosx = atoi( cTemp );
							pTemp = pTemp1+1;
							int imosy = atoi( pTemp );
							lon += ( imosx/ 1000000.0 );
							lan += ( imosy / 1000000.0 );
						//	outx = x + ( imosx / 1000000.0 );
						//	outy = y + ( imosy / 1000000.0 );
							free(chunk.memory);
							return true;
						}
					}	
				}	
			}
		}	
	}
	if(chunk.memory)
		free(chunk.memory);
	return false;
}