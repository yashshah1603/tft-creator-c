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
#include "define.h"
#include "etprotos.h"
#include "etextern.h"
#include "7735.h"
#include <stdio.h>
#include <stdint.h>
#include <ADC_DelSig_1.h>
#include <UART_1.h>
char buffer[50];
                                                    

int iii=0,max=30000,min=-30000,median,pixdiff; 
long linejoinarray[2],dataarray[32];
                                                                            
void linejoiningarray()
{
  unsigned int j=1,i=1,k=1,x0,y0,x1,y1,ci=159,ri,re,col1,col2,r,c=154,cp=150,rp;
  long val,vall=40000,valm=45000,dal,dall=40000,dalm=45000;
while(1)
{
        for(k=0;k<30;k++)   
        {
            if (dataarray[k]>max)
                {
                    max=dataarray[k]+3000;
                }
            if (dataarray[k]<min)
                {
                    min=dataarray[k]-3000;
                }
            median=(max+min)/2;
            pixdiff=(max-median)/40;
            if (dataarray[k]>median)
                {
                r=40-((dataarray[k]-median)/pixdiff);
                }
                else
                   {
                    pixdiff=(median-min)/40;
                    r=40+((median-dataarray[k])/pixdiff);
                   } 
                c=c-5;
                if(dataarray[k]>40000)
                {
                    r=0;
                }    
                if(dataarray[k]<-40000)
                {
                    r=80;
                }    
                       for(i=c;i>=c-5;i--)
                        {
                        DDAerase(0,i,80,i);
                        }
                if (k==0)
                   {
                     for(i=0;i<10;i++)
                            {
                             DDAerase(0,159-i,80,159-i);
                              DDAerase(0,5-i,80,5-i);
                            }
                                                           
                    if (dataarray[k+1]>max)
                        {
                            max=dataarray[k+1]+3000;
                        }
                    if (dataarray[k+1]<min)
                        {
                            min=dataarray[k+1]-3000;
                        }
                    median=(max+min)/2;
                    pixdiff=(max-median)/40;
                    if (dataarray[k+1]>median)
                        {
                        ri=40-((dataarray[k+1]-median)/pixdiff);
                        }
                        else
                           {
                            pixdiff=(median-min)/40;
                            ri=40+((median-dataarray[k+1])/pixdiff);
                           }
                   }           
           DDA(r,c,ri,ci);
            ci=c;
            ri=r;
             if(ci==4)
            {
                c=154;
                ci=159;
            }    
        } 
          sprintf(buffer,"yash");
        UART_1_PutString(buffer);
}
}   
  
CY_ISR(update_isr_Handler)
{
    key_scan--;
    if(key_scan<=0) 
        {
            key_scan=KEY_REFRESH;
            key_board_scan();
        }
        
         if(hib_done==1)
        {
            hibCnt--;    
            if(hibCnt<=0)
                {
                    hib_done = 0;
                    hibCnt = HIBERNATE_WAKE;
                }
        }
    unsigned int i;
    adcReadTimeout++;
  if (adcReadTimeout>=10)
{
    adcReadTimeout=0;
     ADC_DelSig_1_IsEndConversion( ADC_DelSig_1_WAIT_FOR_RESULT);
    if (dataarray[31]==0)
    { 
    for(i=0;i<32;i++)
          {
           dataarray[iii++]=ADC_DelSig_1_GetResult32();
          }  
    }  
    else //dataarray[30]!=0)
        {
            for(i=0;i<31;i++)
                {
                    dataarray[i]=dataarray[i+1];
                }
             dataarray[i] = ADC_DelSig_1_GetResult32();   
//                 sprintf(buffer,"update=%ld\r\n",dataarray[5]);
//                 UART_1_PutString(buffer);
        }    
   }     
}       
                    

void erase()
{
    unsigned int r,c;
    for (c=0;c<=159;c++)
    {
        for(r=0;r<61;r++)
            rctoxy(r,c,0x00);
    }
}    

void testing()
{
   long ADCvalue=-20000,value=10000,max=40000,min=-40000,median;
   int i,j,k,pixdiff;
   unsigned int r,c=154,ri,ci=159;
   for(i=0;i<41;i++)
    {
        {   
            {
                //ADCvalue=ADCvalue+5000;
                if (ADCvalue>max)
                {
                    max=ADCvalue+3000;
                }
                if (ADCvalue<min)
                {
                    min=ADCvalue-3000;
                }
               median=(max+min)/2;
            }
              if (ADCvalue>median)
            {
                pixdiff=(max-median)/40;
                r=40-((ADCvalue-median)/pixdiff);
                sprintf(buffer,"ADCvalue=%ld\r\n",ADCvalue);
                UART_1_PutString(buffer);
            }
            else
                   {
                    pixdiff=(median-min)/40;
                    r=40+((median-ADCvalue)/pixdiff);
                    sprintf(buffer,"ADCvalue=%ld\r\n",ADCvalue);
                    UART_1_PutString(buffer);
                    }    
        }
         if (value>max)
                {
                    max=value+3000;
                }
            if (dataarray[k+1]<min)
                {
                    min=value-3000;
                }
            median=(max+min)/2;
            pixdiff=(max-median)/40;
            if (value>median)
                {
                ri=40-((value-median)/pixdiff);
                }
                else
                   {
                    pixdiff=(median-min)/40;
                    ri=40+((median-value)/pixdiff);
                   }
             c=c-5;
            ci=ci-5;    
            DDA(r,c,ri,ci);
            c=c-5;
            ci=ci-5;
            DDA(ri,c,r,ci);        
          //rctoxy(r,c,0xff);
    }    
     
 }   

/* [] END OF FILE */
