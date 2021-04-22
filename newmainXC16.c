#include "CONFIG.h"
#include "peripheralversion.h"
#include"p24EP64GP206.h"
#include "xc.h"
#include "delay.h"
#include "ILI9341.h"
#include "FONT.h"

#include "I2Cx.h"

#include "ds3231.h" 
#include "DHT22.h"


#include "FUNCTIONS.h"
#include "CLOCK_FUNCTIONS.h"

 


#define Edht22      PORTCbits.RC2
#define Sdht22      LATCbits.LATC2


#define Button1 PORTBbits.RB15 // SELECT
#define Button2 PORTGbits.RG8 // SELECT
#define Button3 PORTGbits.RG7
#define Button4 PORTGbits.RG6


 unsigned char txt01[15]={"HETFO      "} ; 
 unsigned char txt02[15]={"KEDD       "} ;
 unsigned char txt03[15]={"SZERDA     "} ;
 unsigned char txt04[15]={"CSUTORTOK  "} ;
 unsigned char txt05[15]={"PENTEK     "} ;
 unsigned char txt06[15]={"SZOMBAT    "} ;
 unsigned char txt07[15]={"VASARNAP   "} ;

unsigned char  buttonState1=1;
unsigned char  previousState1=1;
unsigned char  buttonState2=1;
unsigned char  previousState2=1;
unsigned char  buttonState3=1;
unsigned char  previousState3=1;
unsigned char  buttonState4=1;
unsigned char  previousState4=1;
unsigned char  buttonState5=1;
unsigned char  previousState5=1;
unsigned char values[8];



unsigned char Seconds;
unsigned char Minutes;
unsigned char Hours;
unsigned char DayOfWeek;
unsigned char Day;
unsigned char Month;
unsigned char Year;
unsigned char data2;
unsigned char data3;
unsigned char data4;  
unsigned int data5;

 

unsigned char increment;

unsigned int i2;
unsigned char data;
unsigned char value;
unsigned char txt1[20];
 unsigned char select;
unsigned char selectoffset;
 unsigned char counter;
 unsigned int counter3;
 unsigned char counter2;
 unsigned char counter_enable;
unsigned int number;
unsigned char buff[10] ;

unsigned char data;
unsigned char x;





void Print_DayOfWeek( unsigned char y)
{
    
        
        getDate();
        
        
        
          
        if(DayOfWeek==1) {text1(txt01,0,y,2,Black,White); }   
         
        if(DayOfWeek==2) {text1(txt02,0,y,2,Black,White); }   
         
        if(DayOfWeek==3){ text1(txt03,0,y,2,Black,White); }   
         
        if(DayOfWeek==4){ text1(txt04,0,y,2,Black,White); }   
         
        if(DayOfWeek==5){ text1(txt05,0,y,2,Black,White); }     
         
        if(DayOfWeek==6){ text1(txt06,0,y,2,Black,White); }      
         
        if(DayOfWeek==7){ text1(txt07,0,y,2,Black,White); }   
       


}



void Select (void)
{


            buttonState1=Button1; 
        if(buttonState1 != previousState1){ if (buttonState1==1){ 
                     select++;  if(select>13){select=13;}  
                     counter_enable=1;
                     counter2=0;
                    } } 
         previousState1 = buttonState1;
         
             buttonState2=Button2; 
         if(buttonState2 != previousState2){ if (buttonState2==1){ 
              select--; if(select>200){select=0;}
                counter_enable=1;
                counter2=0;
              
             } } 
         previousState2 = buttonState2;
       
        
        

}




void Print_Time(void)

{

            
       if(counter2>100){counter_enable=0; counter2=0; select=0;  }
      
        GLCD_FONT2(0,150,30,Black,White,0,Times_New_Roman20x59 );

       data = ((Seconds/1)%10);
      if(select==1){GLCD_FONT2(data,290,110,White,Black,1,Tahoma23x30 ); }
      else{
      GLCD_FONT2(data,290,110,Black,White,1,Tahoma23x30 );}
      
      data = ((Seconds/10)%10);
      if(select==2){GLCD_FONT2(data,265,110,White,Black,1,Tahoma23x30 ); }
      else{
      GLCD_FONT2(data,265,110,Black,White,1,Tahoma23x30 );}
      
      
       
      data = ((Minutes/1)%10);
      if(select==3){GLCD_FONT2(data,246,1,White,Black,1,Tahoma69x103 ); }
      else{
      GLCD_FONT2(data,246,1,Black,White,1,Tahoma69x103 );}
      
      data = ((Minutes/10)%10);
      if(select==4){GLCD_FONT2(data,172,1,White,Black,1,Tahoma69x103 ); }
      else{
      GLCD_FONT2(data,172,1,Black,White,1,Tahoma69x103 );}
       
      
       
      data = ((Hours/1)%10);
      
      if(select==5){GLCD_FONT2(data,75,1,White,Black,1,Tahoma69x103 ); }
      else{
      GLCD_FONT2(data,75,1,Black,White,1,Tahoma69x103 );}
      
      data = ((Hours/10)%10);
      if(select==6){GLCD_FONT2(data,1,1,White,Black,1,Tahoma69x103 ); }
      else{
      GLCD_FONT2(data,1,1,Black,White,1,Tahoma69x103 );}
      
      
      
      


}





void Print_Date(unsigned char x,unsigned char y)

{

      
       
       if(counter2>100){counter_enable=0; counter2=0; select=0;  }

       
      data = ((Day/1)%10);
      if(select==8){GLCD_FONT2(data,y+205,x,White,Black,1,Tahoma23x30 ); }
      else{
      GLCD_FONT2(data,y+205,x,Black,White,1,Tahoma23x30 );}
      
      data = ((Day/10)%10);
      if(select==9){GLCD_FONT2(data,y+180,x,White,Black,1,Tahoma23x30 ); }
      else{
      GLCD_FONT2(data,y+180,x,Black,White,1,Tahoma23x30 );}
       
      
       GLCD_FONT2(0,y+165,x,Black,White,1,Tahoma13x29 );
      

      data = ((Month/1)%10);
      if(select==10){GLCD_FONT2(data,y+140,x,White,Black,1,Tahoma23x30 ); }
      else{
      GLCD_FONT2(data,y+140,x,Black,White,1,Tahoma23x30 );}
      
      data = ((Month/10)%10);
      if(select==11){GLCD_FONT2(data,y+115,x,White,Black,1,Tahoma23x30 ); }
      else{
      GLCD_FONT2(data,y+115,x,Black,White,1,Tahoma23x30 );}      

      
      GLCD_FONT2(0,y+100,x,Black,White,1,Tahoma13x29 );
 
            
     
      data = ((Year/1)%10);
      if(select==12){GLCD_FONT2(data,y+75,x,White,Black,1,Tahoma23x30 ); }
      else{
      GLCD_FONT2(data,y+75,x,Black,White,1,Tahoma23x30 );}
      
      data = ((Year/10)%10);
      if(select==13){GLCD_FONT2(data,y+50,x,White,Black,1,Tahoma23x30 ); }
      else{
      GLCD_FONT2(data,y+50,x,Black,White,1,Tahoma23x30 );}
      
      
      GLCD_FONT2(0,y+25,x,Black,White,1,Tahoma23x30 );
      GLCD_FONT2(2,y,x,Black,White,1,Tahoma23x30 );
      

}









void Change(void)
{

       
           buttonState3=Button3; 
        if(buttonState3 != previousState3){ if (buttonState3==1){ 
                    
                   getTime(); 
                   getDate();
              if(select==1){Seconds++; DS3231_Write(secondREG, (decimal_to_bcd(Seconds)));}    
              if(select==2){Seconds=Seconds+10; DS3231_Write(secondREG, (decimal_to_bcd(Seconds)));}      
              if(select==3){Minutes++; DS3231_Write(minuteREG, (decimal_to_bcd(Minutes)));}    
              if(select==4){Minutes=Minutes+10; DS3231_Write(minuteREG, (decimal_to_bcd(Minutes)));}  
              if(select==5){Hours++; DS3231_Write(hourREG, (decimal_to_bcd(Hours)));}    
              if(select==6){Hours=Hours+10; DS3231_Write(hourREG, (decimal_to_bcd(Hours)));}  

                   
                   
                 
              if(select==7){DayOfWeek++;    DS3231_Write(dayREG, (decimal_to_bcd(DayOfWeek)));}    
              if(select==8){Day++;  DS3231_Write(dateREG, (decimal_to_bcd(Day )));}    
              if(select==9){Day=Day+10; DS3231_Write(dateREG, (decimal_to_bcd(Day )));}
              if(select==10){Month++;   DS3231_Write(monthREG, (decimal_to_bcd(Month )));}     
              if(select==11){Month=Month+10;    DS3231_Write(monthREG, (decimal_to_bcd(Month )));}    
              if(select==12){Year++;    DS3231_Write(yearREG, (decimal_to_bcd(Year )));}     
              if(select==13){Year=Year+10;   DS3231_Write(yearREG, (decimal_to_bcd(Year )));} 
    
        
      
                   
                 counter_enable=1;
                 counter2=0;   
                    } } 
             previousState3 = buttonState3;
         
             
             buttonState4=Button4; 
             if(buttonState4 != previousState4){ if (buttonState4==1){ 
       
                
              if(select==1){Seconds--; DS3231_Write(secondREG, (decimal_to_bcd(Seconds)));}    
              if(select==2){Seconds=Seconds-10; DS3231_Write(secondREG, (decimal_to_bcd(Seconds)));}     
              if(select==3){Minutes--; DS3231_Write(minuteREG, (decimal_to_bcd(Minutes)));}    
              if(select==4){Minutes=Minutes-10; DS3231_Write(minuteREG, (decimal_to_bcd(Minutes)));}  
              if(select==5){Hours--; DS3231_Write(hourREG, (decimal_to_bcd(Hours)));}    
              if(select==6){Hours=Hours-10; DS3231_Write(hourREG, (decimal_to_bcd(Hours)));} 
                
                
                
              if(select==7){DayOfWeek--; DS3231_Write(dayREG, (decimal_to_bcd(DayOfWeek)));}     
              if(select==8){Day--; DS3231_Write(dateREG, (decimal_to_bcd(Day )));}     
              if(select==9){Day=Day-10; DS3231_Write(dateREG, (decimal_to_bcd(Day )));} 
              if(select==10){Month--;   DS3231_Write(monthREG, (decimal_to_bcd(Month )));}    
              if(select==11){Month=Month-10; DS3231_Write(monthREG, (decimal_to_bcd(Month )));}   
              if(select==12){Year--;    DS3231_Write(yearREG, (decimal_to_bcd(Year )));}     
              if(select==13){Year=Year-10; DS3231_Write(yearREG, (decimal_to_bcd(Year )));}    
                
                
        
                counter_enable=1;
                 counter2=0; 
                  
             } } 
            previousState4 = buttonState4;
         
            

}








int main(void) {
  TRISB=0x0000; 
  TRISD=0x0000;
    TRISC=0x0000;
    TRISBbits.TRISB15=1;
    
    PLLFBD = 28;                   // M=34      (ANYTHING HIGHER DOESN'T WORK)
    CLKDIVbits.PLLPRE = 0;         // N1=2
    CLKDIVbits.PLLPOST = 0;        // N2=2

    __builtin_write_OSCCONH(0x01);  // set up to switch to FRC+PLL
    __builtin_write_OSCCONL(OSCCON | 0x01);  // do the switch
    
    
    
           
    TFT_init();    
    Delay_ms(500);  
    OpenI2C(); 
    Delay_ms(500);
    DS3231_init();
    fillScreen2(Black);
    
while(1){
    
   
            counter3++;
            if( counter3==5000){counter3=0; fillScreen2(Black);}
            
            Select();
            Change();
            if(counter_enable==1){   counter2++;}

         getTime();
         getDate(); 
        Print_Time();
        Print_DayOfWeek(115);
        Print_Date(140,0);
        
 
        read_DS22();
        
          
       PRINT_Temp(Temp,2,180);
                         
       PRINT_RH((RH),205,180);


        
     }

}