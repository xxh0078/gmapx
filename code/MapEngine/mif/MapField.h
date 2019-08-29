/************************************************************
  �ļ���: MapField.h
  
  ����:   Ǯ����       Version : 1.0          Date: 2002/12/21
  
  ������: ���������ݵ��ֶεĹ���
  
  �ʼ���ַ��Visual20@sohu.com
***********************************************************/

#ifndef _MAP_FIELD_H_
#define _MAP_FIELD_H_

typedef enum 
{
	
	fdString,    //�ַ�������
	fdInteger,   //����
	fdDouble,    //������
	fdInvaild    //δ֪����

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