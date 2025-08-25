#include <16f887.h>
#fuses nowdt,put,hs,noprotect,nolvp
#use delay(clock=20M)
//***************************************************
#define up       pin_c5
#define dw       pin_c6
#define mod      pin_c7
#define dht11    pin_c4
#define led_t    pin_c2
#define led_h    pin_c3
#define relay_2  pin_c1
#define relay_1  pin_c0
//***************************************************
unsigned int8 humi_set, tempt_set, mode;
void system_init()
{
   set_tris_d(0);
   set_tris_e(0);
   set_tris_c(0);
}
//***************************************************
int1 phim_up()   
{                    
   if (!input(up))   
   {        
      delay_ms(20);                                     
      if (!input(up))
      {
         while(!input(up));
         return 1;      
      }                      
      return 0;   
   }         
  return 0;  
} 
//***************************************************
int1 phim_dw()   
{                    
   if (!input(dw))   
   {        
      delay_ms(20);                                     
      if (!input(dw))
      {
         while(!input(dw));
         return 1;      
      }                      
      return 0;   
   }         
  return 0;  
} 
//***************************************************
int1 phim_mod()   
{                    
   if (!input(mod))   
   {        
      delay_ms(20);                                     
      if (!input(mod))
      {
         while(!input(mod));
         return 1;      
      }                      
      return 0;   
   }         
  return 0;  
} 
