
short Time_out;
unsigned short T_byte1, T_byte2, RH_byte1, RH_byte2, CheckSum ;
unsigned int  RH;

signed int Temp;

unsigned short _data = 0;
 
#define OUT_DIR  TRISBbits.TRISB4
#define OUT_PIN  PORTBbits.RB4



void start_signal(void)
{
    OUT_DIR = 0;   //Direciona pino RD0 como saída
    OUT_PIN  = 0;      //Leva pino 0 da porta D para 0
    Delay_ms(10); 
    
    //Gera atraso de 25ms
    OUT_PIN  = 1;      //Leva pino 0 da porta D para 1
    Delay_us(40);
    OUT_DIR = 1;   //Direciona pino RD0 como entrada    
}

short check_response(void)
{
    
    
  Delay_us(10);  
  if(OUT_PIN ==0)       //Testa se pino RD0 está em 0
  {
      Delay_us(40); 
        if(OUT_PIN ==1)  //Testa se pino RD0 está em 1
        {
            Delay_us(40); 
            return 1;
        }
 
    }
  
    return 0;
    
}





unsigned char Read_Data(void)
{
  unsigned short i;     // k is used to count 1 bit reading duration
   unsigned char _data;   
  for(i = 0; i < 8; i++)
  {
    
    while(!OUT_PIN );                          // Wait until pin goes high
    
    Delay_us(20);
    
    if(!OUT_PIN )
       _data &= ~(1<<(7-i));
    
    else
    {
      
      _data |= (1<<(7-i));  
        
      while(OUT_PIN );                         // Wait until pin goes low
     
    }
  }
  
  return _data;
}


void read_DS22(void)
{
 
    
          
         start_signal();
             
 
        if(check_response()==1)
        {// If there is response from sensor
       

        
         
            RH_byte1 = Read_Data();                 // read RH byte1
            RH_byte2 = Read_Data();                 // read RH byte2
            T_byte1 = Read_Data();                  // read T byte1
            T_byte2 = Read_Data();                  // read T byte2
            CheckSum = Read_Data();                 // read checksum            
        
                Temp = T_byte1;
                Temp = (Temp << 8) | T_byte2;
                RH = RH_byte1;
                RH = (RH << 8) | RH_byte2;
        } 
    
    
    
    
}