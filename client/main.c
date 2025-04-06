/*
 * File:   main.c
 * Author: arunc
 *
 * Created on 28 January, 2025, 10:55 AM
 */


#include "main.h"
#include <xc.h>

void init_eternal_interrupt() {
    GIE = 1; //GLOBAL INTERRUPT ENABLE
    PEIE = 1; //PERRIPHERAL INTERRUPT ENABLE
    INT0IE = 1; //EXTERNAL INTERRUPT ENABLE
    INT0IF = 0; //EXTERNAL INTERRUPT FLAG
    INTEDG0 = 1; //INTERRUPT ON RASING EDGE
    TRISB0 = 1; //Take RB0 as input
}

void init_config() {
    TRISD = 0x00; //set portd as output port
    TRISA = TRISA & 0xf0; //set first 4 pins of port a as output
    PORTA = PORTA & 0xf0; //set all 7 seg display as off
    PORTD = 0x00; //set intial data at portd as 0
    ADCON1 = 0x0f; //set port d as digital pin
    TRISC = TRISC | 0x0f; //set portc as input

    TRISB1 = 0; //pin 1 of port b as output for interrupt
    RB1 = 0;
    init_eternal_interrupt(); //call function to config interrupt.
    init_can();
    init_i2c();
    TRISE0 = 0;
    RE0 = 0;
    //read eeprom for ust and pid
//    unsigned char ad = 0x00;
//    for (int j = 0; j < 8; j++) {
//        read_internal_eeprom(ad);
//        ad++;
//    }
}

void __interrupt() isr() {
    if (INT0IF) {

        inter_flag = !inter_flag;
        INT0IF = 0;
    }
}

void main(void) {
    init_config();
    while (1) {
        if (can_receive() == TRUE) {
            //if (pid[0] == t[4] && pid[1] == t[5] && pid[2] == t[6] && pid[3] == t[7])
            {
                inter_flag = 1;
                ust[0] = t[0];
                ust[1] = t[1];
                ust[2] = t[2];
                ust[3] = t[3];
                pid[0] = t[4];
                pid[1] = t[5];
                pid[2] = t[6];
                pid[3] = t[7];
                e_flag1 = 0;
                flag1 = 1;
            }


        }
        if (inter_flag) {

            key = read_dkp_edge();
            if (e_flag1 == 0 && flag1 == 0) {
                ust[0] = t[0];
                ust[1] = t[1];
                ust[2] = t[2];
                ust[3] = t[3];
                pid[0] = t[4];
                pid[1] = t[5];
                pid[2] = t[6];
                pid[3] = t[7];
                //pid
                //P_ID
                ssd[0] = digits[10];
                ssd[1] = digits[11];
                ssd[2] = digits[12];
                ssd[3] = digits[13];


            } else if (e_flag1 == 1 && flag1 == 0) {
                ssd[0] = digits[14]; //U_ST
                ssd[1] = digits[15];
                ssd[2] = digits[16];
                ssd[3] = digits[17];
            }
            if (key == 0x0b && flag1 == 0) {
                e_flag1 = !e_flag1;
                key = 0x00;
            }
            //            if (key == 0x0b && flag1 == 1) {
            //                flag1 = 0;
            //                key = 0x00;
            //            }
            if (key == 0x0d && flag1 == 0) {
                flag1 = 1;
                field = 3;
                key = 0x00;
            }
            if (flag1 == 1 && e_flag1 == 0) {
                for (int i = 0; i < 4; i++) {
                    if (i == field) {
                        ssd[i] = digits[ust[i]] | 0x10;
                        continue;
                    }
                    ssd[i] = digits[ust[i]];
                }
                if (key == 0x0d) {
                    field--;
                    if (field < 0) {
                        field = 3;
                    }
                    key = 0x00;
                }
                if (key == 0x0e) {
                    ust[field]++;
                    if (ust[field] > 9) {
                        ust[field] = 0;
                    }
                    key = 0x00;
                }
            } else if (flag1 == 1 && e_flag1 == 1) {
                for (int i = 0; i < 4; i++) {
                    if (i == field) {
                        ssd[i] = digits[pid[i]] | 0x10;
                        continue;
                    }
                    ssd[i] = digits[pid[i]];
                }
                if (key == 0x0d) {
                    field--;
                    if (field < 0) {
                        field = 3;
                    }
                    key = 0x00;
                }
                if (key == 0x0e) {
                    pid[field]++;
                    if (pid[field] > 9) {
                        pid[field] = 0;
                    }
                    key = 0x00;
                }
            }
            if (key == 0x0b && flag1 == 1) {
                e_flag1 = 0;
                flag1 = 0;
                field = 3;
                inter_flag = 0;
                key = 0x00;
                t[0] = ust[0];
                t[1] = ust[1];
                t[2] = ust[2];
                t[3] = ust[3];
                t[4] = pid[0];
                t[5] = pid[1];
                t[6] = pid[2];
                t[7] = pid[3];
                can_transmit();
                unsigned char ad = 0x00;
                for (int j = 0; j < 8; j++) {
                    write_internal_eeprom(ad, t[j]);
                    ad++;
                }
                RE0 = 1;
                for (long int i = 0; i < 1000; i++);
                RE0 = 0;
            }
            display(ssd);
        } else {
            //            e_flag1 = 0;
            //            flag1 = 0;
            //            field = 3;
            key = 0x00;
        }
    }
    return;
}
