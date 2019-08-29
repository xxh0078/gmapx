#include "stdafx.h"
#include "MapField.h"

CMapField::CMapField()
{
	m_csFieldName = _T("");
	m_csValue  = _T("");
	m_lFieldType = fdInvaild;
	::VariantInit(&m_varValue);





}

CMapField::CMapField(CMapField& field)
{
	m_csFieldName = field.GetName(); 
	m_csValue  = field.GetValueAsString();  
	m_lFieldType = field.GetType();
	m_varValue = field.GetValue(); 
	

}

CMapField::~CMapField()
{


}

CString CMapField::GetName()
{
	return m_csFieldName;
}

void CMapField::SetName(LPCTSTR lpszName)
{
	m_csFieldName = lpszName;
}

long CMapField::GetType()
{
	return m_lFieldType;
}

void CMapField::SetType(long lType)
{
	m_lFieldType = lType;
}

CString CMapField::GetValueAsString()
{
	CString csValue = _T("");
	switch( m_lFieldType )
    {
		case fdInteger:
			csValue.Format("%d",m_varValue.lVal); 
			break;
        case fdDouble:
			csValue.Format("%f",m_varValue.dblVal);
			break;
        case fdString:
			return m_csValue; 
		    break;
		case fdInvaild:
			break;
		default:
			break;
    }    
	return csValue;
}

void CMapField::SetValueAsString(LPCTSTR lpstr)
{
	m_csValue = lpstr;	
}

VARIANT CMapField::GetValue()
{
	return m_varValue;
}

void CMapField::SetValue(const VARIANT& var)
{
    switch( m_lFieldType )
    {
		case fdInteger:
		    m_varValue.bVal = var.bVal;
			m_varValue.lVal = var.lVal; 
			break;
        case fdDouble:
			m_varValue.bVal = var.bVal;
			m_varValue.dblVal = var.dblVal; 
			break;
       	case fdInvaild:
			break;
		default:
			m_varValue = var;
			break;
    }      

}
