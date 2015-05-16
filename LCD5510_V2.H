/*--------------------------------------------------------------*/
//File:	LCD5510_V1.H
//Date:	2009/8/4
//Time: 9:16
//Note: Nokia 5510 LCDҺ����ʾ
//ÿ8λ��ʾ�����ǵ�λ����, ��λ����
//����Ӳ��
//��Ƭ��:  STC89C52RC
//ģʽ:    12T
//����:	   12MHz


/*--------------------------------------------------------------*/
//��ֹ�ظ�����
#ifndef	__LCD5510_V2_H__
#define __LCD5510_V2_H__

/*--------------------------------------------------------------*/
//ָ��궨��
#define X_Col_Addr     0x80		//��λ����0��ָ��(����ʼ��ַ)(0 - 83)
#define Y_Page_Addr    0x40		//��λ����0ҳָ��(ҳ��ʼ��ַ)(0 - 5)


/*--------------------------------------------------------------*/
//���ܺ궨��
//Һ����λ
#define LCD_reset_hard	LCD_RST_L; LCD_RST_H	//Ӳ����λ
#define LCD_reset_soft	LCD_reset_5510()			//������λ
//Һ����ʾ����(��Ӱ��DDRAM)
#define LCD_show_blank		LCD_write_cmd(0x08)		//��ʾ�հ�
#define LCD_show_normal		LCD_write_cmd(0x0c)		//������ʾ
#define LCD_show_black		LCD_write_cmd(0x09)		//��ʾȫ��
#define LCD_show_inverse 	LCD_write_cmd(0x0d)		//��ɫ��ʾ
//��������
#define LCD_write_cmd(cmd)	LCD_write_byte(cmd, 0)	//д��ָ��
#define LCD_write_dat(dat)	LCD_write_byte(dat, 1)	//д������


/*--------------------------------------------------------------*/
//���ݽӿڶ���
//sbit LCD_CLK = P2^0;     //����ʱ��			//������д������
#define LCD_CLK_H        P4OUT |= BIT3
#define LCD_CLK_L        P4OUT &= ~BIT3

//sbit LCD_DIN = P2^1;     //������������		//�ȸߺ��
#define LCD_DIN_H        P4OUT |= BIT0
#define LCD_DIN_L        P4OUT &= ~BIT0

//sbit LCD_DC  = P2^2;     //����ָ����ƶ�	//�ߵ�ƽ���ݣ��͵�ƽָ��
#define LCD_DC_H        P3OUT |= BIT7
#define LCD_DC_L        P3OUT &= ~BIT7

//sbit LCD_CS  = P2^3;     //Ƭѡʹ��			//�͵�ƽ��Ч
#define LCD_CS_H        P8OUT |= BIT1
#define LCD_CS_L        P8OUT &= ~BIT1

//sbit LCD_RST = P2^4;     //LCD��λ��		//�͵�ƽ��λ
#define LCD_RST_H        P8OUT |= BIT2
#define LCD_RST_L        P8OUT |= BIT2

/*--------------------------------------------------------------*/
//��������(˽��)
void LCD_write_byte(unsigned char wbyte, unsigned char dat_cmd);//д���ֽ�
void LCD_reset_5510(void);										//��λLCD5510


/*--------------------------------------------------------------*/
//��������(����)
/*--------------------------------------------------------------*/
//��������(��DDRAM)
void LCD_clr_scr(void);


/*--------------------------------------------------------------*/
//Һ���ֽڶ�λ(1*1)
//Һ���滮:
//x: 0 - 83
//y: 0 - 5
void LCD_pos_byte(unsigned char x, unsigned char y);


/*--------------------------------------------------------------*/
//��ʾ����
//num:	0 - 5
void LCD_clr_row(unsigned char num);


/*--------------------------------------------------------------*/
//Һ���ַ����(6*8����)
//x: 0 - 13
//y: 0 - 5
void LCD_printc(unsigned char x, unsigned char y, unsigned char c_dat);


/*--------------------------------------------------------------*/
//Һ���ַ������(6*8����)
//x: 0 - 13
//y: 0 - 5
void LCD_prints(unsigned char x, unsigned char y, unsigned char *s_dat);


/*--------------------------------------------------------------*/
//Һ���ַ������,�Զ�����(6*8����)
//x: 0 - 13
//y: 0 - 5
void LCD_printsl(unsigned char x, unsigned char y, unsigned char *s_dat);


/*--------------------------------------------------------------*/
//��ʼ��LCD5510
void LCD5510_Init(void);				


/*--------------------------------------------------------------*/
//�����ļ�
//#include "LCD5510_V2.C"

#include <msp430.h>
/*--------------------------------------------------------------*/
#endif





 