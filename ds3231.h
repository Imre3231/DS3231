 


#define DS3231_Address              0x68           
                                                 
#define DS3231_Read_addr            ((DS3231_Address << 1) | 0x01)
#define DS3231_Write_addr           ((DS3231_Address << 1) & 0xFE)
                                           
#define secondREG                   0x00
#define minuteREG                   0x01
#define hourREG                     0x02
#define dayREG                      0x03
#define dateREG                     0x04                             
#define monthREG                    0x05                           
#define yearREG                     0x06                   
#define alarm1secREG                0x07       
#define alarm1minREG                0x08
#define alarm1hrREG                 0x09           
#define alarm1dateREG               0x0A 
#define alarm2minREG                0x0B   
#define alarm2hrREG                 0x0C
#define alarm2dateREG               0x0D
#define controlREG                  0x0E
#define statusREG                   0x0F
#define ageoffsetREG                0x10
#define tempMSBREG                  0x11
#define tempLSBREG                  0x12
                                 
#define _24_hour_format             0
#define _12_hour_format             1
#define am                          0
#define pm                          1



unsigned char Seconds;
unsigned char Minutes;
unsigned char Hours;
unsigned char DayOfWeek;
unsigned char Day;
unsigned char Month;
unsigned char Year;

                                                               
unsigned char bcd_to_decimal(unsigned char d);
unsigned char decimal_to_bcd(unsigned char d);                     
unsigned char DS3231_Read(unsigned char address);
void DS3231_Write(unsigned char address, unsigned char value);
void DS3231_init(); 
void getTime(); 
void getDate();   
void setTime(unsigned char hSet, unsigned char mSet, unsigned char sSet, short am_pm_state, short hour_format);
void setDate(unsigned char daySet, unsigned char dateSet, unsigned char monthSet, unsigned char yearSet);   
float getTemp();




                                                        
unsigned char bcd_to_decimal(unsigned char d)               
{                                                                                         
         return ((d & 0x0F) + (((d & 0xF0) >> 4) * 10));
}                               
                                                             

unsigned char decimal_to_bcd(unsigned char d)
{
         return (((d / 10) << 4) & 0xF0) | ((d % 10) & 0x0F);
}                                                   
                                       
unsigned char DS3231_Read(unsigned char address)
{                                     
         unsigned char value = 0;
          IdleI2C();
         StartI2C(); // issue I2C start signal
         IdleI2C();
         WriteI2C(DS3231_Write_addr);  
         IdleI2C();;
         WriteI2C(address);
         IdleI2C();
         StartI2C(); // issue I2C start signal     
                 
         IdleI2C();
         WriteI2C(DS3231_Read_addr);  
            IdleI2C();
         value = ReadI2C();
        
        IdleI2C();
         StopI2C();
           IdleI2C();       
         return value;
}                     
 

void DS3231_Write(unsigned char address, unsigned char value)   
{ 
             IdleI2C();
         StartI2C(); // issue I2C start signal  
         IdleI2C();
         WriteI2C(DS3231_Write_addr);
         IdleI2C();
         WriteI2C(address);
         IdleI2C();
         WriteI2C(value);
         
         IdleI2C();
         
         StopI2C();
        IdleI2C();
} 



void DS3231_init()
{                                   
         DS3231_Write(controlREG, 0x00); 
         DS3231_Write(statusREG, 0x08);
}                       

 
void getTime(void )
{           
    
 
         Seconds = DS3231_Read(secondREG);
         Seconds = bcd_to_decimal(Seconds);
         Minutes = DS3231_Read(minuteREG);
         Minutes = bcd_to_decimal(Minutes);
 
                          Hours = (0x3F & DS3231_Read(hourREG));           
                          Hours= bcd_to_decimal(Hours);  
}                                 
                                                     
                               
void getDate(void)
{
         Year = DS3231_Read(yearREG);
         Year = bcd_to_decimal(Year);                 
         Month = (0x1F & DS3231_Read(monthREG));
         Month = bcd_to_decimal(Month);
  
         
         DayOfWeek = (0x07 & DS3231_Read(dayREG));
         DayOfWeek = bcd_to_decimal(DayOfWeek);
         
         Day = (0x3f & DS3231_Read(dateREG));   
         Day = bcd_to_decimal(Day);   
         
                 
}

                                                   
void setTime(unsigned char hSet, unsigned char mSet, unsigned char sSet, short am_pm_state, short hour_format) 
{                                                                                                             
         unsigned char tmp = 0;
         DS3231_Write(secondREG, (decimal_to_bcd(sSet)));
         DS3231_Write(minuteREG, (decimal_to_bcd(mSet)));       
         switch(hour_format)
         {
                  case 1:
                  {       
                           switch(am_pm_state)
                           {
                                    case 1:
                                    {           
                                             tmp = 0x60;
                                             break;
                                    }
                                    default:
                                    {   
                                             tmp = 0x40;
                                             break;
                                    }
                           }                           
                           DS3231_Write(hourREG, ((tmp | (0x1F & (decimal_to_bcd(hSet))))));                   
                           break;
                  }                                             
                 
                  default:
                  {
                           DS3231_Write(hourREG, (0x3F & (decimal_to_bcd(hSet))));
                           break;
                  } 
         }   
}                                                 

                                   
void setDate(unsigned char daySet, unsigned char dateSet, unsigned char monthSet, unsigned char yearSet)
{         
         DS3231_Write(dayREG, (decimal_to_bcd(daySet)));           
         DS3231_Write(dateREG, (decimal_to_bcd(dateSet))); 
         DS3231_Write(monthREG, (decimal_to_bcd(monthSet)));
         DS3231_Write(yearREG, (decimal_to_bcd(yearSet)));   
}


                               
float getTemp()                                                 
{
         register float t = 0.0;
         unsigned char lowByte = 0;
         signed char highByte = 0;
         lowByte = DS3231_Read(tempLSBREG);
         highByte = DS3231_Read(tempMSBREG); 
         lowByte >>= 6;                 
         lowByte &= 0x03;     
         t = ((float)lowByte); 
         t *= 0.25;     
         t += highByte;         
         return t;
                                     
}	

