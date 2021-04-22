
#include <xc.h>

 
 

unsigned char CHARACTER_WIDTH(unsigned int character,const unsigned short *FONT);
/*
void number_print(unsigned char *buffer,unsigned int x,unsigned int y )
{
    unsigned char count=0;
    while(*buffer)              // Write data to LCD up to null
    {
       
        GLCD_FONT2((*buffer-47),(x+(55*count)) ,y ,Black,White,0,Tahoma47x78);      // Write character to LCD
        
        
        buffer++;  // Increment buffer 
        count++;
    }
}
*/


unsigned int CHARACTER_POSITON;

unsigned char CHARACTER_WIDTH(unsigned int character,const unsigned short *FONT)
{
    
    unsigned char    CHARACTER_WIDTH;    
    CHARACTER_WIDTH = FONT[(8+(character*4))];
    if(character==0){CHARACTER_WIDTH = FONT[(8+(4*4))]; };
    return CHARACTER_WIDTH;

}





void GLCD_FONT2 (unsigned int character,unsigned int x,unsigned int y,unsigned int color1,unsigned int color2,unsigned int space,const unsigned short *FONT)
{
    unsigned int    counter;
    unsigned int    i;
    unsigned int    ii;
    unsigned int    xx;
    unsigned int    STARTINGPOINT;
    unsigned int    CHARACTER_HEIGHT;
    unsigned int    CHARACTER_WIDTH;
    unsigned int    DATA;
    unsigned int    VERTICAL;
    unsigned int    HORIZONTAL;
    unsigned int    HORIZONTAL_COUNTER;
    unsigned int    VERTICAL_COUNTER;
    unsigned int    LOWBYTE;
    unsigned int    HIGHBYTE;
    unsigned int    LOW1;
    unsigned int    HIGH1;
    unsigned int    BYTEWIDTH; 
    
    LOW1=0;
    HIGH1=0;
    CHARACTER_HEIGHT = FONT[6];
    CHARACTER_WIDTH = FONT[(8+(character*4))];
    BYTEWIDTH=((CHARACTER_WIDTH/8));
    if((CHARACTER_WIDTH%8)!=0){BYTEWIDTH++; };
    
    LOWBYTE= FONT[(9+(character*4))];
    HIGHBYTE= FONT[(10+(character*4))];
    HIGH1=((HIGHBYTE<<8)&0xFF00);
    LOW1=((LOWBYTE&0x00FF));
    HORIZONTAL_COUNTER = CHARACTER_WIDTH ;
    VERTICAL_COUNTER = CHARACTER_HEIGHT ;
    STARTINGPOINT= ((LOW1)|(HIGH1));
    
        
    VERTICAL=0;
    HORIZONTAL=0;
    counter=0;      
    DATA = FONT[(STARTINGPOINT)];           
      for(xx=0;xx<CHARACTER_HEIGHT;xx++) 
        {   counter=0;
            for(ii=0;ii<BYTEWIDTH;ii++) 
            {                               
                for(i=0;i<8;i++)          
                {
                    Column_Address_Set(( 320-(counter+x)));
                    if(((DATA>>(i))&0x01)==0){ Write_Data2(color1); }
                    if(((DATA>>(i))&0x01)==1){ Write_Data2(color2); }                           
                            VERTICAL++;
                            counter++;
                }
                    STARTINGPOINT++;
                    DATA = FONT[(STARTINGPOINT)];
            }                                  
                    Page_Address_Set(HORIZONTAL+y),    
                    HORIZONTAL++; VERTICAL=0; 
                    for(i=0;i<space;i++) { Draw_Pixel( (320-((counter+x)+i)),(HORIZONTAL+y),color1);  }; //CLEAR END                           
        }   
        
    
   }    

                 
                        
 

 void text1 (unsigned char *buffer,unsigned int x,unsigned int y,unsigned int spaceing ,unsigned int color1,unsigned int color2)
{
    unsigned char WIDTH; 
    unsigned char count=0;
    CHARACTER_POSITON=0;
    while(*buffer)              // Write data to LCD up to null
    {
        
         
        if(*buffer==32){
        GLCD_FONT2(0,(((CHARACTER_POSITON))+x) ,y,color1,color2,1,Tahoma17x19);      // Write character to LCD
        
         WIDTH = CHARACTER_WIDTH((0),Tahoma17x19);       
         CHARACTER_POSITON=CHARACTER_POSITON+WIDTH+spaceing;
        buffer++;  // Increment buffer 
        count++;
        
        }else{
        
        
        GLCD_FONT2((*buffer-64),(((CHARACTER_POSITON))+x) ,y,color1,color2,1,Tahoma17x19);      // Write character to LCD
        
         WIDTH = CHARACTER_WIDTH((*buffer-64),Tahoma17x19);       
         CHARACTER_POSITON=CHARACTER_POSITON+WIDTH+spaceing;
            buffer++;  // Increment buffer 
            count++;
        }
        
    }
    
    
}
 

/*

 void text2 (unsigned char *buffer,unsigned int x,unsigned int y,unsigned int spaceing ,unsigned int color1,unsigned int color2)
{
    unsigned char WIDTH; 
    unsigned char count=0;
    CHARACTER_POSITON=0;
    while(*buffer)              // Write data to LCD up to null
    {
        
         
        GLCD_FONT2((*buffer-32),(((CHARACTER_POSITON))+x) ,y,color1,color2,5,Times_New_Roman16x16);      // Write character to LCD
        
         WIDTH = CHARACTER_WIDTH((*buffer-32),Times_New_Roman16x16);       
         CHARACTER_POSITON=CHARACTER_POSITON+WIDTH+spaceing;
        buffer++;  // Increment buffer 
        count++;
    }
    
    
}


*/


void intToStr(unsigned int value, char *str, char leading_zero, char digits)
{
    static long powers[9] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    char temp_digit,digit_cnt=10,first_non_zero=1;
 
    while (digit_cnt!=1)  // initially this value is 10 so the loop is executed 9 times
    {
        temp_digit = 48;  // ASCII 0
        while (value >= powers[digit_cnt-2])  // while number bigger than power value
        {
            value -= powers[digit_cnt-2];       // subtract the power value
            temp_digit++;                       // and increase variable
        }
        if (digit_cnt<=digits) *str++ = temp_digit; // only store requested number of digits  
 
        digit_cnt--;   // used as a counter to detect when we have reached the last char of the array
    }
    *str = (char) value+48; // assign the last character
 
    if (leading_zero==0)   // if parameter is set for no leading zeros
    {   str-=digits;    // go to the first char of the array
        while(first_non_zero==1)    // if the first digit of the number is not found
        {   str++;  // move to next array character
            if (*str=='0') *str=32;      // if digit value is ADCII 0 then replace with space (user selectable)
            else first_non_zero=0;      // else set the flag that the first digit of the number was found
 
        }
    }
}




void Draw_V_Line(signed int x1, signed int y1, signed int y2, unsigned colour)
{
 

    while(y2 > (y1 - 1))
    {
        Draw_Pixel(x1, y2, colour);
        y2--;
    }
}


void Draw_H_Line(signed int x1, signed int x2, signed int y1, unsigned colour)
{
 
    

    while(x2 > (x1 - 1))
    {
        Draw_Pixel(x2, y1, colour);
        x2--;
    }
}



void Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2,  unsigned int colour)
{

             Draw_V_Line(x1, y1, y2, colour);
             Draw_V_Line(x2, y1, y2, colour);
             Draw_H_Line(x1, x2, y1, colour);
             Draw_H_Line(x1, x2, y2, colour);
       
}


void PRINT_0( unsigned int  Number, unsigned int x,unsigned int  y ,const unsigned short *FONT)
{
            unsigned char N0;
            unsigned char N1;
 
 
            N0=((Number/10)%10);
            N1=((Number/1)%10) ;
          
            {GLCD_FONT2(N0,x,y,Black,White,1,FONT );}
               
            GLCD_FONT2(N1,x+75,y ,Black,White,1,FONT );
          
          

}



void PRINT_1( unsigned int  Number, unsigned int x,unsigned int  y ,const unsigned short *FONT)
{
            unsigned char N0;
            unsigned char N1;
            N0=((Number/10)%10);
            N1=((Number/1)%10) ; 
            
            GLCD_FONT2(N0,x+0,y,Black,White,1,FONT );
            GLCD_FONT2(N1,x+20,y,Black,White,1,FONT );
}
 


void PRINT_RH( unsigned int  Number, unsigned int x,unsigned int  y )
{
          
            unsigned char N1;
            unsigned char N2;
            unsigned char N3;
       
            N1=((Number/100)%10);
            N2=((Number/10)%10) ;
            N3=((Number/1)%10);
           
            
           
            GLCD_FONT2(N1,x,y,Black,Orange,1,Tahoma35x54 ); 
             
            GLCD_FONT2(N2,x+35,y,Black,Orange,1,Tahoma35x54 );    
                     
            GLCD_FONT2(0,x+73,y+20,Black,Orange,1,Tahoma35x30);
            
            //text1 ("Humidity",x ,y-20,4,Black,White);
            Draw_Rectangle( (206-x),(y-5),(325-x),(y+57),White);
            
            
            
}

void PRINT_Temp( unsigned int  Number, unsigned int x,unsigned int  y  )
{
                    unsigned char N1;
            unsigned char N2;
            unsigned char N3;
 

            if (Number > 0X8000)
                {
                Number= Number & 0X7FFF; 
                
                GLCD_FONT2(0,x+1,y,Black,Orange,1,Tahoma20x51M ); 
                
                }
                else
               GLCD_FONT2(0,x+1,y,Black,Orange,1,Tahoma20x51S );                             
               

            N1=((Number/100)%10);
            N2=((Number/10)%10) ;
            N3=((Number/1)%10);
            
            GLCD_FONT2(N1,x+22,y,Black,Orange,1,Tahoma35x54 ); 
           
            GLCD_FONT2(N2,x+60,y,Black,Orange,1,Tahoma35x54 );    
            
            GLCD_FONT2(0,x+95,y+43,Black,Orange,1,Times_New_Roman7x7);
            GLCD_FONT2(N3,x+102,y,Black,Orange,1,Tahoma35x54 );
            GLCD_FONT2(0,x+142,y-5,Black,Orange,1,Tahoma26x58);
            
            //text1 ("Temperature",x+10,y-20,6,Black,White);
            Draw_Rectangle( (140-x),(y-5),(320-x),(y+55),White); 

}