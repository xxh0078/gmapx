/************************************************************
  文件名: MapField.h
  
  作者:   钱军洪       Version : 1.0          Date: 2002/12/21
  
  类描述: 对属性数据的字段的管理
  
  邮件地址：Visual20@sohu.com
***********************************************************/

#ifndef _MAP_FIELD_H_
#define _MAP_FIELD_H_

typedef enum 
{
	
	fdString,    //字符串类型
	fdInteger,   //整型
	fdDouble,    //浮点型
	fdInvaild    //未知类型

} DBFFIELDTYPE;

class CMapField {

public:
	CMapField();
	CMapField(CMapField& field);
	~CMapField();

//Attribute
public:
	CString GetName();
	void SetName(LPCTSTR);
	long GetType();
	void SetType(long);
	CString GetValueAsString();
	void SetValueAsString(LPCTSTR);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	//VARIANT Get_Value();
	//void Set_Value(const VARIANT&);
private:
	CString m_csFieldName;
	long    m_lFieldType;
    VARIANT m_varValue;
	CString m_csValue;

};
#endif //_MAP_FIELD_H_