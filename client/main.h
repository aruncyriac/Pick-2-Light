/* 
 * File:   main.h
 * Author: arunc
 *
 * Created on 28 January, 2025, 10:53 AM
 */

#ifndef MAIN_H
#define	MAIN_H
#include <xc.h>
#include "can.h"
#define _XTAL_FREQ 20000000
#define SLAVE_READ_E		0xA1
#define SLAVE_WRITE_E		0xA0
#define TRUE			1
#define FALSE			0
//0xe5 = U
//0x40 = _
//0x6e = s
//0xcc = t

//0x8f = p
//0x40 = _
//0x21 = i
//0xf9 = d
unsigned char ssd[4],ust[4] = {0,0,0,0},pid[4] = {0,0,0,0},t[8] = {0,0,0,0,0,0,0,0};
unsigned char digits[] = {0xe7,0x21,0xcb,0x6b,0x2d,0x6e,0xee,0x23,0xef,0x6f,0xe5,0x40,0x6e,0xcc,0x8f,0x40,0x21,0xe9};
unsigned int key = 0x00;
int inter_flag = 0,field = 3;
int flag1 = 0,flag2 = 0,e_flag1 = 0,e_flag2 = 0;
void init_i2c(void);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
unsigned char read_dkp_edge();
void display(unsigned char *ssd);
void i2c_write(unsigned char data);
unsigned char i2c_read(void);
void write_internal_eeprom(unsigned char address, unsigned char data);
unsigned char read_internal_eeprom(unsigned char address);


#endif	/* MAIN_H */

