#ifndef _DBFFILE_H_
#define _DBFFILE_H_

/* DBF文件头结构 */ 
typedef struct dbf_header 
{ 
    char vers;                        /* 版本标志*/ 
    unsigned char  yy,mm,dd;          /* 最后更新年、月、日 */ 
    unsigned long  no_recs;           /* 文件包含的总记录数 */ 
    unsigned short head_len;          /*文件头长度*/
	unsigned short rec_len;            /*记录长度 */ 
    char reserved[20];                 /* 保留 */ 
} DBF_HEADER; 

/*字段描述结构*/
typedef struct field_element {  
 
	char szFieldName[11];   /* 字段名称 */ 
    char cFieldType;        /* 字段类型 */ 
    unsigned long ulOffset; /* 偏移量 */ 
	unsigned char ucFieldLength; /* 字段长度 */ 
    unsigned char ucFieldDecimal; /* 浮点数整数部分长度 */ 
    char reserved1[2]; /* 保留 */ 
    char dbaseiv_id; /* dBASE IV work area id */ 
    char reserved2[10]; 
    char cProductionIndex;  
} FIELD_ELEMENT; 


#endif //_DBFFILE_H_
