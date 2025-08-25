//***************************************************
#define dht11_pin_low()    output_drive(dht11); output_low(dht11)
#define dht11_pin_high()   output_drive(dht11); output_high(dht11)
#define dht11_pin_float()  output_float(dht11)
#define dht11_pin_read()   input_state(dht11)  
//*************************************************** 
void dht11_start()        
{                                
   dht11_pin_low();
   delay_ms(20);                                       
   dht11_pin_high();
   dht11_pin_float();
   delay_us(40);   
} 
//***************************************************
int1 dht11_check_response()        
{                                
   unsigned int8 cnt=0;   
   int1 tt=1, tt1=1;
   do
   {
      if(dht11_pin_read()==0) cnt++; //      
      else                    tt=0;  //het o muc 0,xung lên 1,       
   }while ((cnt<200)&&(tt==1));      //dung: cnt<200 và tt=1; sai 
                                               
   cnt=0; tt1=1;
   do
   {
      if(dht11_pin_read()==1) cnt++;       
      else                    tt1=0;  //het o muc 1, xung xuong muc 0       
   }while ((cnt<200)&&(tt1==1));              
   return tt; 
}       
//***************************************************  
unsigned int8 dht11_read()        
{                                                                               
   unsigned int8 kq,j;    
   for(j=0;j<8;j++)                                               
   {                                                         
      while(!dht11_pin_read());  //doi het muc 0    
      delay_us(30);
      if(dht11_pin_read()==1) 
      {             
         kq = (kq<<1)+1;    
         delay_us(40);           //bit 1 thi them delay
      }                          
      else kq = kq<<1;  
   }    
   return kq; 
}  
//***************************************************  
unsigned int8 hum_bl,hum_bh,tem_bl,tem_bh,sum, sum_ss; 
int1 presence;
void dht11_read_temp_humi()
{
   dht11_start();
   presence = dht11_check_response(); 
  if(!presence==true) 
  {
      hum_bh = dht11_read(); hum_bl = dht11_read(); 
      tem_bh = dht11_read(); tem_bl = dht11_read(); 
      sum = dht11_read();
      sum_ss = hum_bh+hum_bl+tem_bh+tem_bl; 
   }
}

