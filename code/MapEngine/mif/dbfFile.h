#ifndef _DBFFILE_H_
#define _DBFFILE_H_

/* DBF�ļ�ͷ�ṹ */ 
typedef struct dbf_header 
{ 
    char vers;                        /* �汾��־*/ 
    unsigned char  yy,mm,dd;          /* �������ꡢ�¡��� */ 
    unsigned long  no_recs;           /* �ļ��������ܼ�¼�� */ 
    unsigned short head_len;          /*�ļ�ͷ����*/
	unsigned short rec_len;            /*��¼���� */ 
    char reserved[20];                 /* ���� */ 
} DBF_HEADER; 

/*�ֶ������ṹ*/
typedef struct field_element {  
 
	char szFieldName[11];   /* �ֶ����� */ 
    char cFieldType;        /* �ֶ����� */ 
    unsigned long ulOffset; /* ƫ���� */ 
	unsigned char ucFieldLength; /* �ֶγ��� */ 
    unsigned char ucFieldDecimal; /* �������������ֳ��� */ 
    char reserved1[2]; /* ���� */ 
    char dbaseiv_id; /* dBASE IV work area id */ 
    char reserved2[10]; 
    char cProductionIndex;  
} FIELD_ELEMENT; 


#endif //_DBFFILE_H_
