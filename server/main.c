/*
 * File:   main.c
 * Author: arunc
 *
 * Created on 22 February, 2025, 10:54 AM
 */


#include "main.h"
char ch = '\0';

void init_config() {
    init_can();
    init_uart();
    /* Enabling peripheral interrupt */
    PEIE = 1;

    /* Enabling global interrupt */
    GIE = 1;
    TRISE0 = 0;
    RE0 = 0;
}

void __interrupt() isr(void) {
    if (RCIF == 1) {
        if (OERR == 1)
            OERR = 0;

        ch = RCREG;

        RCIF = 0;
    }
}

void main(void) {
    int i = 0;
    init_config();
    while (1) {
        if (can_receive() == TRUE) {
            //                        ust[0] = t[0];
            //                        ust[0] = t[1];
            //                        ust[0] = t[2];
            //                        ust[0] = t[3];
            //                        pid[0] = t[4];
            //                        pid[0] = t[5];
            //                        pid[0] = t[6];
            //                        pid[0] = t[7];

            puts("Recevived Data: ID-");
            putch(t[7] + 48);
            putch(t[6] + 48);
            putch(t[5] + 48);
            putch(t[4] + 48);
            puts(":U-");
            putch(t[3] + 48);
            putch(t[2] + 48);
            putch(t[1] + 48);
            putch(t[0] + 48);
            puts("\n\r");

        }
        if (flag == 0 && u_once == 0) {
            puts("Enter the Data to be sent [Note: Max 4 bytes,Extra would be trancated!]:");
            u_once = 1;
        }
        if (ch != '\0') {
            //puts("hi\n\r");
            putch(ch);
            if (ch >= '0' && ch <= '9') {
                if (i < 4 && p_once == 0) {
                    t[i++] = ch;
                } else if (i < 8 && p_once == 1) {
                    t[i++] = ch;
                }
            }
            if (ch == '\r' && flag == 0) {
                flag = !flag;
                while (i < 4) {
                    t[i] = '0';
                    i++;
                }
                puts("\n\r");
                putch(t[0]);
                putch(t[1]);
                putch(t[2]);
                putch(t[3]);
            } else if (ch == '\r' && flag == 1) {
                flag = !flag;
                puts("\n\r");
                while (i > 4 && i < 8) {
                    t[i] = '0';
                    i++;
                }
                putch(t[4]);
                putch(t[5]);
                putch(t[6]);
                putch(t[7]);

                can_transmit();
                RE0 = 1;
                for (long int i = 0; i < 1000; i++);
                RE0 = 0;

                u_once = 0;
                r_once = 0;
                p_once = 0;
                flag = 0;
                i = 0;
            }
            ch = '\0';
        }
        if (flag == 1 && p_once == 0 && u_once == 1) {
            puts("Enter the Pid to be sent [Note: Max 4 bytes,Extra would be trancated!]:");
            p_once = 1;
        }
    }
}

