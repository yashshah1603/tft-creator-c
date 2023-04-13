/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
/* Place your initialization/startup code here (e.g. MyInst_Start()) */
#include "7735.h"
#include "word.h"
#include "define.h"
#include "etextern.h"
#include "etprotos.h"
unsigned char  num; 		  
unsigned long j;  
unsigned int i=0;
unsigned char xdata_DATA[512];
#include <stdio.h>
#include <stdint.h>
#include <ADC_DelSig_1.h>
#include <UART_1.h>
void CyDelay (uint32 milliseconds);
char buffer[50];

int main(void)
{
    int i;
//    for(i=0;i<10;i++)
//    {
//     Pin_1_Write(0);
//    delayms(500);
//    Pin_1_Write(1); 
//    delayms(500);
//    }
    CyGlobalIntEnable; /* Enable global interrupts. */ 
    keyboardinit();
   Init();
   flagWake=1;
  
//    LED_A_Write(1);
//    UART_1_Start();
//     ADC_DelSig_1_IRQ_Start();
//    ADC_DelSig_1_Start();
//    ADC_DelSig_1_StartConvert();
  
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
//    ST7735_Initial();
//    ClearScreen(0x00);
                      
     ClearScreen(0x00);
     if(flagHibernate==1)    //Hibernate mode
        {
            flagHibernate=0;
            flagWake=0;
            HibernateMode();
        }
     if(flagWake==1)         //Key action
        {
          // while(1)
             get_action();
                {
                   //adcvaluetopixel();
                  // testing();
                     linejoiningarray();
                }  
        }

}
/* [] END OF FILE */
