#IFNDEF LCD_RS
#DEFINE LCD_RS PIN_E2
#ENDIF

#IFNDEF LCD_RW 
#DEFINE LCD_RW PIN_E1
#ENDIF
#IFNDEF LCD_E
#DEFINE LCD_E PIN_E0
#ENDIF

#IFNDEF OUTPUT_LCD
#define OUTPUT_LCD OUTPUT_D
#ENDIF

#DEFINE FUNCTION_SET          0X38 
#DEFINE DISPLAY_CONTROL       0X0C
#DEFINE CLEAR_DISPLAY         0X01
#DEFINE ENTRY_MODE            0X06
#DEFINE SHIFT_LEFT            0X18
#DEFINE SHIFT_RIGHT           0X1C
#DEFINE LINE1                 0X80
#DEFINE LINE2                 0XC0

#DEFINE LINE3                 0X94
#DEFINE LINE4                 0XD4

void LCD_COMMAND(UNSIGNED CHAR MDK) 
{ 
    OUTPUT_LOW(LCD_RS); 
    OUTPUT_LCD(MDK);
    OUTPUT_HIGH(LCD_E);
    DELAY_US(200);
    OUTPUT_LOW(LCD_E); 
    DELAY_US(200);
}
void LCD_DATA(UNSIGNED CHAR MHT) //RS = 1
{ 
    OUTPUT_HIGH(LCD_RS); 
    OUTPUT_LCD(MHT);
    OUTPUT_HIGH(LCD_E); 
    DELAY_US(20);
    OUTPUT_LOW(LCD_E);
    DELAY_US(20);
}
VOID LCD_SETUP()
{ 
    OUTPUT_LOW(LCD_E); 
    OUTPUT_LOW(LCD_RS); 
    OUTPUT_LOW(LCD_RW);
    LCD_COMMAND(FUNCTION_SET); 
    DELAY_MS(1);
    LCD_COMMAND(DISPLAY_CONTROL);
    LCD_COMMAND(CLEAR_DISPLAY); 
    DELAY_MS(2);
    LCD_COMMAND(ENTRY_MODE);
}
void lcd_goto(unsigned int8 x,unsigned int8 y) 
{                      
   const unsigned int8 lcd_vitri[]={0x80,0xc0,0x94,0xd4};
   lcd_command(lcd_vitri[x]+y);    //delay_us(20);
} 
const unsigned int8 lcd_so_to[10][6] ={
                  0,1,2,4,3,5,    // so 0
                  1,2,32,3,7,3,   // so 1
                  6,6,2,4,3,3,    // so 2
                  6,6,2,3,3,5,    // so 3
                  7,3,7,32,32,7,  // so 4
                  7,6,6,3,3,5,    // so 5                               
                  0,6,6,4,3,5,    // so 6
                  1,1,7,32,32,7,  // so 7
                  0,6,2,4,3,5,    // so 8
                  0,6,2,3,3,5};   // so 9
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//mang tung doan so to cua LCD
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                   
const unsigned int8 lcd_ma_8doan[] = {
   0x07,0x0f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,  //doan f - 0
   0x1f,0x1f,0x1f,0x00,0x00,0x00,0x00,0x00,  //doan a - 1
   0x1c,0x1e,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,  //doan b - 2
   0x00,0x00,0x00,0x00,0x00,0x1f,0x1f,0x1f,  //doan d - 3
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x0f,0x07,  //doan e - 4
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1e,0x1c,  //doan c - 5      
   0x1f,0x1f,0x1f,0x00,0x00,0x00,0x1f,0x1f,  //doan g+d-6 
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f}; //doan i  -7     
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 612: copy mang so to vao cgram
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                                  
void lcd_soto_setup()                                                  
{                                                                      
   unsigned int8 i;
   lcd_command(0x40);
   for(i=0;i<64;i++)  
   lcd_data(lcd_ma_8doan[i]);  
}
void lcd_soto(signed int8 so, x, y) 
{                        
   unsigned int8 i;
   lcd_goto(x,y);
   for(i=0;i<6;i++)
   {                                                           
      if(i==3) lcd_goto(x+1,y);
      lcd_data(lcd_so_to[so][i]);
   }                        
} 
void lcd_xoa_soto(signed int8 x, y)
{  
   unsigned int8 i;
   lcd_goto(x,y);         
   for(i=0;i<6;i++)
   {            
      if(i==3) lcd_goto(x+1,y);    
      lcd_data(' ');
   }
} 
