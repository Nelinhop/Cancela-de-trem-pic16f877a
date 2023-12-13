#include <xc.h>          
#include <pic16f877a.h>  
#include <stdio.h>       

#define _XTAL_FREQ 4000000 

int flag;  

void __interrupt() TrataInt(void)
{   
    PORTDbits.RD2 = 1; //BUZZER
    
    while(PORTBbits.RB0 == 0){
        
      if(PORTCbits.RC0 == 1){
           while(PORTBbits.RB3 != 0){
               PORTCbits.RC0 = 1;
               PORTDbits.RD0 = 1;
           }
      }
     PORTCbits.RC0 = 0;
     PORTDbits.RD0 = 0;   
     
     if(PORTBbits.RB3 == 0){
     __delay_ms(2000);
           while(PORTBbits.RB2 != 0){
                PORTCbits.RC1 = 1;
                PORTDbits.RD1 = 1;
     }
    }
     PORTCbits.RC1 = 0;
     PORTDbits.RD1 = 0;  
    }
    
    PORTDbits.RD2 = 0; //BUZZER
    int flag = 1;  
    INTCONbits.INTF = 0;
    return;
}

void main(void) 
{   
   TRISB = 0b11111111;
   TRISC = 0b00000000;  
   TRISD = 0b00000000;  
   OPTION_REG = 0b00111111; 
   
  
   //OPTION_REGbits.INTEDG = 1; 
   INTCONbits.GIE=1;    
   INTCONbits.INTE=1;   

  
   while (1)   
   {
     flag = 0;
     
     while (flag == 0)
      {
         PORTCbits.RC0 = 0; //abrindo
         PORTCbits.RC1 = 0; //m abrindo
         PORTDbits.RD0 = 0; //fechando
         PORTDbits.RD1 = 0; //m //fechando
         PORTDbits.RD2 = 0; //buzzer
        
         if(flag == 0 && PORTBbits.RB1 == 0 ){
             while(flag == 0 && PORTBbits.RB3 != 0){
                 PORTCbits.RC0 = 1;
                 PORTDbits.RD0 = 1;
             }
             PORTCbits.RC0 = 0;
             PORTDbits.RD0 = 0;
             if(flag == 0){
                __delay_ms(2000);
             }
             while(PORTBbits.RB2 != 0){
                 PORTCbits.RC1 = 1;
                 PORTDbits.RD1 = 1;
             }
             PORTCbits.RC1 = 0;
             PORTDbits.RD1 = 0;
            }
        }
    }
}
