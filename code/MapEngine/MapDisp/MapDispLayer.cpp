#include "stdafx.h"
#include "MapDispLayer.h"
#include "MapDisp.h"
CMapDispLayer::CMapDispLayer(void)
{
	m_iBlockCount = 0;
}
//创建图层
void CMapDispLayer::Create( CMapDisp* pMapDisp )
{
	m_hwnd = pMapDisp->m_hwnd;
	m_pMapDisp = pMapDisp;
	this->m_MapData.Init( pMapDisp );
	//初始化所有数据块
	/*for ( int i=0;i<_BLOCK_MAX_NUM;i++) {
		m_MapBlockUnit[i].Init(m_hwnd);
	}*/
	//建立互斥区，并启动线程
	return;
	//m_bExitProc = false;
	//m_hLoadMutex = CreateMutex( NULL,false,NULL );
	//DWORD dwThreadID = 0;
	//HANDLE h = ::CreateThread( NULL,0 ,&CMapDispLayer::MapLoadProc,this,0,&dwThreadID );
	//CloseHandle( h );
}
CMapDispLayer::~CMapDispLayer(void)
{
}
//检查当前的绘制列表中是否存在改绘制参数
bool CMapDispLayer::CheckParamInDrawList( CMapBlockUnit* pBlockParam, int iLevel, int iMinX, int iMaxX, int iMinY, int iMaxY )
{
	if( pBlockParam->lLevel == iLevel//xxh m_iLevel 
		&&pBlockParam->lNumX >= iMinX && pBlockParam->lNumX <= iMaxX
		&&pBlockParam->lNumY >= iMinY && pBlockParam->lNumY <= iMaxY && pBlockParam->bDraw )
	{
		return true;
	}
	else
		return false;
}
//加载地图数据
void CMapDispLayer::LoadMapData( int iLevel, MPoint& gptMapCenter,VOSRect& rcWnd, bool bZoom )
{
	return;
/*	VOSRect rcWnd;
	rcWnd.left = rcWnd1.left - rcWnd1.width();
	rcWnd.top = rcWnd1.top - rcWnd1.width();
	rcWnd.right = rcWnd1.right + rcWnd1.Height();
	rcWnd.bottom = rcWnd1.bottom + rcWnd1.Height();*/
	vchar strFileName[256]= {0};
	// TODO: Add your message handler code here
	//MPoint gptMapCenter;
	//CMapBase::GetMapPoint( iLevel, m_MapCenter20, gptMapCenter );
	//
	int iCenterOffsetX = rcWnd.width()/2 -  gptMapCenter.lX % 256;
	int iCenterOffsetY = rcWnd.height()/2 - gptMapCenter.lY % 256;

	int iCenterX = gptMapCenter.lX / 256;
	int iCenterY = gptMapCenter.lY / 256;
	
	int iMapMinX = ( gptMapCenter.lX - rcWnd.width()/2 )/ 256 - 3;//5;
	int iMapMinY = ( gptMapCenter.lY - rcWnd.height()/2 )/ 256 - 2;//4;

	int iMapMaxX = ( gptMapCenter.lX + rcWnd.width()/2  )/ 256 + 3;//5;
	int iMapMaxY = ( gptMapCenter.lY + rcWnd.height()/2  )/ 256 + 2;//4;

	if( !bZoom )
	{
		iMapMinX -= 4;
		iMapMinY -= 3;
		iMapMaxX += 4;
		iMapMaxY += 3;
	}
	//检查绘制列表,标记绘制绘制位
	for ( int i=0;i<this->m_iBlockCount;i++ )
	{
		if( CheckParamInDrawList( &m_MapBlockUnit[i],iLevel,iMapMinX,iMapMaxX, iMapMinY,iMapMaxY))
			m_MapBlockUnit[i].bDraw = true;
		else
			m_MapBlockUnit[i].bDraw = false;
	}
	int z = iLevel;
	{
		for ( int y= iMapMinY ; y<=iMapMaxY; y++ )
		{
			//检查是否超过范围
			if ( z == 0 )
			{
				if ( y < 0 || y >= 2>>(1-z) )
				{
					continue;
				}
			}
			else
			{
				if ( y < 0 || y >= 2<<(z-1) )
				{
					continue;
				}
			}

			for ( int x = iMapMinX ; x<= iMapMaxX ; x++ )
			{
				if ( z == 0 )
				{
					if ( x < 0 || x >= 2>>(1-z) )
					{
						continue;
					}
				}
				else
				{
					if ( x < 0 || x >= 2<<(z-1) )
					{
						continue;
					}
				}

				//检查数据是否被加载
				bool bDataIsLoad = false;
				for ( int i=0;i<this->m_iBlockCount;i++ )
				{
					if( m_MapBlockUnit[i].lLevel == iLevel &&m_MapBlockUnit[i].lNumX == x &&m_MapBlockUnit[i].lNumY==y && m_MapBlockUnit[i].bDraw )
					{
//						m_MapBlockUnit[i].lStartX = iCenterOffsetX - (iCenterX - x )*256;
//						m_MapBlockUnit[i].lStartY = iCenterOffsetY - (iCenterY - y )*256;
						bDataIsLoad = true;
						break;
					}
				}
				//如果已经加载，则查找下一个
				if( bDataIsLoad )
				{
					continue;
				}
				else
				{
					//查找空的没有用的列表
					CMapBlockUnit* pParam = NULL;
					int i = 0;
					for ( ;i<this->m_iBlockCount;i++ )
					{
						if( !m_MapBlockUnit[i].bDraw )
						{
							pParam = &m_MapBlockUnit[i];
							break;
						}
					}
					if ( pParam == NULL )
					{
						m_iBlockCount++;
						if ( m_iBlockCount >= _BLOCK_MAX_NUM ) {
//							ASSERT(0);
							m_iBlockCount = 0;
						}
						pParam = &m_MapBlockUnit[m_iBlockCount-1];
					}
					//把要绘制的数据存入绘制列表
					if( z == 7 )
					{
						z = 7;
						if( x > 64 && x < 70 )
						{
							z = 7;
							if( y > 64 && y < 70 )
							{
								z = 7;
							}
						}
					}
					string strFileName;
					if( m_enMapType == GMAP_FILES )
						GetMapPath(x,y,z,strFileName);
					else
						CMapBase::GetMapDataPath( x,y,z,strFileName,m_enMapType );
					//CMapBase::GetMapDataEncryptionPath(x,y,z,strFileName,256);
					
//					TRACE("loadimg x=%d,y=%d,z=%d\r\n",x,y,z );
					//	GetEncryptionFileName( 1,x,y,z,strFileName );
					//m_download.GetEncryptionFileName( x,y,z,strFileName);
					//	if ( LoadPngData( strFileName, pParam ) )
					//TRACE( strFileName.c_str() );
				//	if( GMAP_GOOGLE_IMAGE == m_enMapType || GMAP_GOOGLE_MARK == m_enMapType )
					{
						if ( m_MapBlockUnit[i].LoadImg( strFileName ) )
						{
							m_MapBlockUnit[i].lLevel = z;
							m_MapBlockUnit[i].lNumX = x;
							m_MapBlockUnit[i].lNumY = y;
//							m_MapBlockUnit[i].lStartX = iCenterOffsetX - (iCenterX - x )*256;
//							m_MapBlockUnit[i].lStartY = iCenterOffsetY - (iCenterY - y )*256;
							m_MapBlockUnit[i].bDraw = true;
						}
						else
						{
							if( m_enMapType != GMAP_FILES )
							{
//								this->m_pMapDisp->m_MapDataDown.AddDownLoadList( x, y , z, m_enMapType );
							}
						}
					}
					/*else
					{
						if ( m_MapBlockUnit[i].LoadPng( strFileName ) )
						{
							m_MapBlockUnit[i].lLevel = z;
							m_MapBlockUnit[i].lNumX = x;
							m_MapBlockUnit[i].lNumY = y;
							m_MapBlockUnit[i].lStartX = iCenterOffsetX - (iCenterX - x )*256;
							m_MapBlockUnit[i].lStartY = iCenterOffsetY - (iCenterY - y )*256;
							m_MapBlockUnit[i].bDraw = true;
						}
						else
						{
							this->m_pMapDisp->m_MapDataDown.AddDownLoadList( x, y , z, m_enMapType );
						}
					}*/
				}
			}
		}
	}
}

//重新加载地图数据
void CMapDispLayer::ReLoadMapData( int iLevel, MPoint& gptMapCenter,VOSRect& rcWnd )
{
	for ( int i=0;i<this->m_iBlockCount;i++ )
	{
		m_MapBlockUnit[i].bDraw = false;
	}
	LoadMapData(iLevel,gptMapCenter,rcWnd);
}
void CMapDispLayer::OnMoveMap( int iDx, int iDy )
{
/*	for ( int i=0;i<this->m_iBlockCount;i++ )
	{
		if( m_MapBlockUnit[i].bDraw )
		{
			m_MapBlockUnit[i].lStartX += iDx;
			m_MapBlockUnit[i].lStartY += iDy;
		}
	}*/
}
void CMapDispLayer::OnDraw( HDC hdc,int iLevel, MPoint& gptMapCenter,VOSRect& rcWnd )
{
	unsigned long ultime = ::GetTickCount(); 
	int iTimes = 0;
	if( !hdc )
		return;
	m_MapData.m_MapDataDown.ClearNoDownLoadList();
	int iCenterOffsetX = rcWnd.width()/2 -  gptMapCenter.lX % 256;
	int iCenterOffsetY = rcWnd.height()/2 - gptMapCenter.lY % 256;

	int iCenterX = gptMapCenter.lX / 256;
	int iCenterY = gptMapCenter.lY / 256;

	int iMapMinX = ( gptMapCenter.lX - rcWnd.width()/2 )/ 256;//-3
	int iMapMinY = ( gptMapCenter.lY - rcWnd.height()/2 )/ 256;//-2

	int iMapMaxX = ( gptMapCenter.lX + rcWnd.width()/2  )/ 256;//+3
	int iMapMaxY = ( gptMapCenter.lY + rcWnd.height()/2  )/ 256;//+2

	//检查绘制列表,标记绘制绘制位
	for ( int i=0;i<this->m_iBlockCount;i++ )
	{
		if( CheckParamInDrawList( &m_MapBlockUnit[i],iLevel,iMapMinX,iMapMaxX, iMapMinY,iMapMaxY))
			m_MapBlockUnit[i].bDraw = true;
		else
			m_MapBlockUnit[i].bDraw = false;
	}
	int z = iLevel;
	{
		for ( int y= iMapMinY ; y<=iMapMaxY; y++ )
		{
			//检查是否超过范围
			if ( z == 0 )
			{
				if ( y < 0 || y >= 2>>(1-z) )
				{
					continue;
				}
			}
			else
			{
				if ( y < 0 || y >= 2<<(z-1) )
				{
					continue;
				}
			}

			for ( int x = iMapMinX ; x<= iMapMaxX ; x++ )
			{
				if ( z == 0 )
				{
					if ( x < 0 || x >= 2>>(1-z) )
					{
						continue;
					}
				}
				else
				{
					if ( x < 0 || x >= 2<<(z-1) )
					{
						continue;
					}
				}
				CMapBlockUnit* pBlock = this->m_MapData.GetMapBlockUnit( iLevel, x,y, m_enMapType );
				if(pBlock)
					pBlock->Draw( hdc,iCenterOffsetX - (iCenterX - x )*256,iCenterOffsetY - (iCenterY - y )*256);
				/*
				//检查数据是否被加载
				bool bDataIsLoad = false;
				for ( int i=0;i<this->m_iBlockCount;i++ )
				{
					if( m_MapBlockUnit[i].lLevel == iLevel &&m_MapBlockUnit[i].lNumX == x &&m_MapBlockUnit[i].lNumY==y && m_MapBlockUnit[i].bDraw )
					{
//						m_MapBlockUnit[i].lStartX = iCenterOffsetX - (iCenterX - x )*256;
//						m_MapBlockUnit[i].lStartY = iCenterOffsetY - (iCenterY - y )*256;
						m_MapBlockUnit[i].Draw( hdc,iCenterOffsetX - (iCenterX - x )*256,iCenterOffsetY - (iCenterY - y )*256 );
						bDataIsLoad = true;
						break;
					}
//					iTimes++;
				}*/
			}
		}
	}
	//string strText = "客服QQ:214010522";
	/*ultime = ::GetTickCount() - ultime; 
	char chTemp[100];
	
	sprintf(chTemp,"%d毫秒:%d次, path =%s",ultime,iTimes, m_strRootPath.c_str());
	::DrawText( hdc, chTemp,strlen(chTemp) ,&rcWnd,DT_LEFT | DT_TOP);
	for ( int i=0;i<this->m_iBlockCount;i++ )
	{
		if( m_MapBlockUnit[i].bDraw )
		{
			m_MapBlockUnit[i].Draw( hdc );
		}
	}*/
}
//设置地图类型
void CMapDispLayer::SetMapType( en_MapType eMapType, string strRootPath, string strMapName, string strMapURL )
{
	CMapBase::SetMapType( eMapType );
	m_enMapType = eMapType;
	m_strRootPath = strRootPath;
	switch( m_enMapType )
	{
	case GMAP_GOOGLE_MAP:
		m_strRootPath += _T("gugemap");
		CreateDirectory( m_strRootPath.c_str(),NULL);
		break;
	case GMAP_GOOGLE_IMAGE:;
		m_strRootPath += _T("gugeimap");
		CreateDirectory( m_strRootPath.c_str(),NULL);
		break;
	case GMAP_CHANGLIAN:
		m_strRootPath += _T("clmap");
		CreateDirectory( m_strRootPath.c_str(),NULL);
		break;
	case GMAP_MAPABC:
		m_strRootPath += _T("mapabc");
		CreateDirectory( m_strRootPath.c_str(),NULL);
		break;
	case GMAP_MAPBAR:
		m_strRootPath += _T("mapbar");
		CreateDirectory( m_strRootPath.c_str(),NULL);
		break;
	case GMAP_MAP365:
		m_strRootPath += _T("map365");
		CreateDirectory( m_strRootPath.c_str(),NULL);
		break;
	case GMAP_VM:
		m_strRootPath += _T("virtualearth");
		CreateDirectory( m_strRootPath.c_str(),NULL);
		break;
	case GMAP_SUPERMAP:
		m_strRootPath += _T("SUPERMAP");
		CreateDirectory( m_strRootPath.c_str(),NULL);
		break;
	case GMAP_MYMAP:
		{
			//m_enMapType = GMAP_MYMAP;
			m_strRootPath = strRootPath + strMapName;
			CreateDirectory( m_strRootPath.c_str(),NULL);
			m_strMapURL = strMapURL;
		}
		break;
	case GMAP_GOOGLE_MARK:
		{
			//影像标签
			m_strRootPath += _T("gugemark");
			CreateDirectory( m_strRootPath.c_str(),NULL);
			break;
		}
	case GMAP_GOOGLE_IMAGEMARK:
		{
			string strMarkPath  = m_strRootPath;
			strMarkPath += _T("gugemark");
			CreateDirectory( strMarkPath.c_str(),NULL);
			m_strRootPath += _T("gugeimap");
			CreateDirectory( m_strRootPath.c_str(),NULL);
			break;
		}
	case GMAP_TIANDT:
		m_strRootPath += _T("TIANDT");
		CreateDirectory( m_strRootPath.c_str(),NULL);
		break;
	default:
		;
	}
	m_MapData.SetMapPath( m_strRootPath, m_enMapType );
	//检查绘制列表,标记绘制绘制位
	for ( int i=0;i<this->m_iBlockCount;i++ )
	{
		m_MapBlockUnit[i].bDraw = false;
	}
	m_iBlockCount = 0;
}
//设置地图路径
void CMapDispLayer::SetMapPath( string strMapPath )
{
	m_enMapType = GMAP_FILES;
	m_strMapPath = strMapPath;
	m_MapData.SetMapPath( m_strMapPath, m_enMapType );
	//检查绘制列表,标记绘制绘制位
	for ( int i=0;i<this->m_iBlockCount;i++ )
	{
		m_MapBlockUnit[i].bDraw = false;
	}
	m_iBlockCount = 0;
}
//得到地图文件路径
void CMapDispLayer::GetMapPath( int x,int y,int z,string& strMapPath )
{
	strMapPath = this->m_strMapPath;
	char cTemp[20]={0};
	sprintf( cTemp,"%d",x);
	string flag = "%x";  
	string::size_type position = 0;
	while(1)  
	{
		position = strMapPath.find( flag );
		if( position != strMapPath.npos )
		{
			strMapPath.replace( position,2,cTemp,strlen(cTemp));
		}
		else
			break;
	}
	sprintf( cTemp,"%d",y);
	flag = "%y";
	while(1)  
	{
		position = strMapPath.find( flag );
		if( position != strMapPath.npos )
		{
			strMapPath.replace( position,2,cTemp,strlen(cTemp));
		}
		else
			break;
	}
	sprintf( cTemp,"%d",z);
	flag = "%z";  
	position = 0;
	while(1)  
	{
		position = strMapPath.find( flag );
		if( position != strMapPath.npos )
		{
			strMapPath.replace( position,2,cTemp,strlen(cTemp));
		}
		else
			break;
	}
}
//获得地图数据文件路径
/*
void CMapDispLayer::GetMapDataPath( int x, int y, int z, string& strMapFilePath )
{
	vchar temp[33]={0};
	strMapFilePath =  m_strRootPath;
	//创建比例尺文件目录
	strMapFilePath += _T("\\level");
	sprintf( temp,_T("%d\\"),z );
	//strcat( pPath, temp );
	strMapFilePath += temp;
	CreateDirectory( strMapFilePath.c_str(),NULL);
	//-----y坐标文件名
	memset( temp,0,33);
	sprintf( temp,_T("%d\\"),y );
	strMapFilePath += temp;
	CreateDirectory( strMapFilePath.c_str(),NULL);

	memset( temp,0,33);
	sprintf( temp,_T("%d.png"),x );
	strMapFilePath += temp;
}*/
//加载其他数据
void CMapDispLayer::LoadMapOther()
{
	return;
	vchar strFileName[256]= {0};
	// TODO: Add your message handler code here
	//MPoint gptMapCenter;
	//CMapBase::GetMapPoint( iLevel, m_MapCenter20, gptMapCenter );
	//
	int iCenterOffsetX = m_pMapDisp->m_rcWnd.width()/2 -  m_gptMapCenter.lX % 256;
	int iCenterOffsetY = m_pMapDisp->m_rcWnd.height()/2 - m_gptMapCenter.lY % 256;

	int iCenterX = m_gptMapCenter.lX / 256;
	int iCenterY = m_gptMapCenter.lY / 256;

	int iMapMinX = ( m_gptMapCenter.lX - m_pMapDisp->m_rcWnd.width()/2 )/ 256 - 5;
	int iMapMinY = ( m_gptMapCenter.lY - m_pMapDisp->m_rcWnd.height()/2 )/ 256 - 4;

	int iMapMaxX = ( m_gptMapCenter.lX + m_pMapDisp->m_rcWnd.width()/2  )/ 256 + 5;
	int iMapMaxY = ( m_gptMapCenter.lY + m_pMapDisp->m_rcWnd.height()/2  )/ 256 + 4;

	//检查绘制列表,标记绘制绘制位
	for ( int i=0;i<this->m_iBlockCount;i++ )
	{
		if( CheckParamInDrawList( &m_MapBlockUnit[i],m_iLevel,iMapMinX,iMapMaxX, iMapMinY,iMapMaxY))
			m_MapBlockUnit[i].bDraw = true;
		else
			m_MapBlockUnit[i].bDraw = false;
	}
	int z = m_iLevel;
	{
		for ( int y= iMapMinY ; y<=iMapMaxY; y++ )
		{
			//检查是否超过范围
			if ( z == 0 )
			{
				if ( y < 0 || y >= 2>>(1-z) )
				{
					continue;
				}
			}
			else
			{
				if ( y < 0 || y >= 2<<(z-1) )
				{
					continue;
				}
			}

			for ( int x = iMapMinX ; x<= iMapMaxX ; x++ )
			{
				if ( z == 0 )
				{
					if ( x < 0 || x >= 2>>(1-z) )
					{
						continue;
					}
				}
				else
				{
					if ( x < 0 || x >= 2<<(z-1) )
					{
						continue;
					}
				}

				//检查数据是否被加载
				bool bDataIsLoad = false;
				for ( int i=0;i<this->m_iBlockCount;i++ )
				{
					if( m_MapBlockUnit[i].lLevel == m_iLevel &&m_MapBlockUnit[i].lNumX == x &&m_MapBlockUnit[i].lNumY==y && m_MapBlockUnit[i].bDraw )
					{
//						m_MapBlockUnit[i].lStartX = iCenterOffsetX - (iCenterX - x )*256;
//						m_MapBlockUnit[i].lStartY = iCenterOffsetY - (iCenterY - y )*256;
						bDataIsLoad = true;
						break;
					}
				}
				//如果已经加载，则查找下一个
				if( bDataIsLoad )
				{
					continue;
				}
				else
				{
					//查找空的没有用的列表
					CMapBlockUnit* pParam = NULL;
					int i = 0;
					for ( ;i<this->m_iBlockCount;i++ )
					{
						if( !m_MapBlockUnit[i].bDraw )
						{
							pParam = &m_MapBlockUnit[i];
							break;
						}
					}
					if ( pParam == NULL )
					{
						m_iBlockCount++;
						if ( m_iBlockCount >= _BLOCK_MAX_NUM ) {
//							ASSERT(0);
							m_iBlockCount = 0;
						}
						pParam = &m_MapBlockUnit[m_iBlockCount-1];
					}
					//把要绘制的数据存入绘制列表
					if( z == 7 )
					{
						z = 7;
						if( x > 64 && x < 70 )
						{
							z = 7;
							if( y > 64 && y < 70 )
							{
								z = 7;
							}
						}
					}
					string strFileName;
					if( m_enMapType == GMAP_FILES )
						GetMapPath(x,y,z,strFileName);
					else
						CMapBase::GetMapDataPath( x,y,z,strFileName,m_enMapType );
					{
						if ( m_MapBlockUnit[i].LoadImg( strFileName ) )
						{
							m_MapBlockUnit[i].lLevel = z;
							m_MapBlockUnit[i].lNumX = x;
							m_MapBlockUnit[i].lNumY = y;
//							m_MapBlockUnit[i].lStartX = iCenterOffsetX - (iCenterX - x )*256;
//							m_MapBlockUnit[i].lStartY = iCenterOffsetY - (iCenterY - y )*256;
							m_MapBlockUnit[i].bDraw = true;
						}
						else
						{
							if( m_enMapType != GMAP_FILES )
							{
//								this->m_pMapDisp->m_MapDataDown.AddDownLoadList( x, y , z, m_enMapType );
							}
						}
					}
				}
			}
		}
	}
}
