/* HE THONG DIEU HOA NHIET DO SU DUNG CAM BIEN DHT11
   1. PHAN NUT NHAN:
    + NHAN MOD DE CHON CHINH GIOI HAN NHIET DO HAY DO AM: 
      MODE TU 0 - 2, 0 - K CHINH, 1- CHINH DO AM, 2 - CHINH NHIET DO
      KHI CHINH SE NHAP NHAY GIA TRI 0.3S
    + NHAN UP TANG, NHAN DW GIAM
    2. PHAN HIEN THI: LCD 20X4
    3. PHAN DIEU KHIEN
    + SU DUNG CHAN RELAY 1 DIEU KHIEN RELAY 1 DE MO MAY TAO DO AM KHI DO AM NHO HON GIOI HAN
    + SU DUNG CHAN RELAY 2 DIEU KHIEN RELAY 2 DE MO QUAY KHI NHIET DO VUOT QUA GIOI HAN
    
*/
#include <tv_pic_16f887_def.c>
#include <tv_dht_11.c>
#include <tv_lcd_20x4.c>
unsigned int8 bdn;
#int_timer1
void interrupt_timer1()
{
   bdn++;
   set_timer1(3036);
}
//***************************************************
void display_limit()
{
   lcd_goto(0,0);
   printf(lcd_data, "H_SET:%02u%% T_SET:%02u", humi_set, tempt_set);
   lcd_data(223);
   lcd_data("C");
}
//***************************************************
void phim_mode()
{
      if(phim_mod())
   {
      mode++;
      if(mode>2) mode=0;
   }
}
void phim_ud()
{
      if(mode==1)
   {
      if(phim_up() && humi_set<100)  
      {
         humi_set++;
         display_limit();
      }
      if(phim_dw() && humi_set>0)   
      {
         humi_set--;
         display_limit();
      }
   }
   else if(mode==2)
   {
      if(phim_up() && tempt_set<100) 
      {
         tempt_set++;
         display_limit();
      }
      if(phim_dw() && tempt_set>0)    
      {
         tempt_set--;
         display_limit();
      }
   }
}
//***************************************************
void clear_displays()
{
   if(mode == 1)
   {
      lcd_goto(0,6);
      lcd_data("  ");
   }
  else if(mode == 2)
  {
      lcd_goto(0,16);
      lcd_data("  ");
  }
}
//***************************************************
void blink_display()
{
 if(mode != 0)
 {
     if(bdn < 4)
     display_limit();
     else if(bdn < 8)
     clear_displays();
     else bdn = bdn - 8;
 } else display_limit();
}
//***************************************************
void display_dht11()
{
      lcd_soto(hum_bh/10, 1, 0);
      lcd_soto(hum_bh%10, 1, 3);
      lcd_data("%");
      lcd_soto(tem_bh/10, 1, 12);
      lcd_soto(tem_bh%10, 1, 15);
      lcd_data(0xdf);
      lcd_data("C");
}
//***************************************************
void alarm_system()
{
   if(hum_bh<humi_set) 
   {
      output_high(led_h);
      output_high(relay_1);
   } else
   {
      output_low(led_h);
      output_low(relay_1);
   }
   if(tem_bh>tempt_set) 
   {
      output_high(led_t);
      output_high(relay_2);
   } else
   {
      output_low(led_t);
      output_low(relay_2);
   }
}
//***************************************************
void main()
{
   system_init();
   
   setup_timer_1 (t1_internal|t1_div_by_8);
   set_timer1(3036);
   enable_interrupts (global);
   enable_interrupts (int_timer1);
   
   lcd_setup();
   lcd_soto_setup();
   humi_set=70; tempt_set=29; mode=0;
   display_limit();
   lcd_goto(3,0);
   lcd_data("VO TUAN VY: 21161221");
   while(true)
   {    
      phim_mode();
      phim_ud();
      dht11_read_temp_humi();
      display_dht11();
      blink_display();
      alarm_system();
   }
}


