/*
 * KEYPAD.c
 *
 * Created: 30/01/2016 06:38:37 م
 *  Author: hossam
 */ 
#include "DIO.h"
#include "KEYPAD.h"

/*Local Symbols*/
#define KPD_COL_PORT (PD)
#define KPD_ROW_PORT (PD)
#define KPD_COL_MASK (0x70u)
#define KPD_ROW_MASK (0x0fu)
#define KPD_COL_PIN_NUM (4u)
#define KPD_ROW_PIN_NUM (0u)
/**************************************************/
static void KPD_COL_INIT(void);
static void KPD_ROW_INIT(void);
static void KPD_COL_READ(unsigned char* VALPTR);
static void KPD_ROW_WRITE(unsigned char DATA);

void KPD_Init(void)
{
	KPD_COL_INIT();
	KPD_ROW_INIT();
	
}
void KPD_ReadVal(unsigned char* ValuePtr)
{
    static const unsigned char KeysLut[]= {'1' , '2' , '3' , '4' , '5' , '6','7' , '8' , '9','*' , '0' , '#'};
    unsigned char Rowdata;
	unsigned char ColData;
	unsigned char LoopTermnate = 0u;
	for(Rowdata = 0u ; (Rowdata < 4u) && (LoopTermnate == 0u) ; Rowdata ++)
	{
		KPD_ROW_WRITE((unsigned char)((unsigned char)1 << Rowdata));
		KPD_COL_READ(&ColData);
		if(ColData != 0u)
		{
			*ValuePtr = KeysLut[(Rowdata*3u) + (ColData/2u)];
			LoopTermnate = 1u;
		}
		else
		{
			*ValuePtr = (unsigned char)'n';
		}
	}
}
static void KPD_COL_INIT(void)
{
    DIO_InitPortDirection(KPD_COL_PORT,KPD_COL_MASK,0x00u);
}
static void KPD_ROW_INIT(void)
{
    DIO_WritePort(KPD_ROW_PORT,KPD_ROW_MASK,0xffu);
    DIO_WritePort(KPD_ROW_PORT,KPD_ROW_MASK,0x00u);
}
static void KPD_COL_READ(unsigned char* VALPTR)
{
    DIO_ReadPort(KPD_COL_PORT,KPD_COL_MASK);
    *(VALPTR) = (*(VALPTR)) >> KPD_COL_PIN_NUM;
}
static void KPD_ROW_WRITE(unsigned char DATA)
{
    DIO_WritePort(KPD_ROW_PORT,KPD_ROW_MASK,((DATA) << KPD_ROW_PIN_NUM));
}
