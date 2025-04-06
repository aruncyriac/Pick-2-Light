/* 
 * File:   main.h
 * Author: arunc
 *
 * Created on 22 February, 2025, 10:55 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include"can.h"
#include"uart.h"
#define TRUE 0
#define FALSE -1
unsigned char t[8] = {0,0,0,0,0,0,0,0},pid[4] = {0,0,0,0},ust[4] = {0,0,0,0};
unsigned char digits[] = {0xe7,0x21,0xcb,0x6b,0x2d,0x6e,0xee,0x23,0xef,0x6f,0xe5,0x40,0x6e,0xcc,0x8f,0x40,0x21,0xe9};
unsigned char ssd[4];
int flag = 0,r_once = 0,u_once = 0,p_once = 0;
void display(unsigned char *ssd);
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

