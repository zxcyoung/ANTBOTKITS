
#include "SoftwareSerial.h"
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI 
int trigPin = 9;
int echoPin = 8;
char str1[32];
struct USERDATA{
  char city[16];
  char whether[16];
  char temp[16]; 
  };
struct USERDATALIFE{
  char dressing[16];
  char uv[16];
  char sport[16]; 
  };
USERDATA userdata;
USERDATALIFE userdatalife;
unsigned char menuFlag = 1;
char revBuff[128];
String newString1 = "waitting for data";
String newString2 = "waitting for data";
SoftwareSerial mySerial(10,11);//RX,TX
const   uint8_t bitmap_x []   U8G_PROGMEM  ={0x00,0x00,0x02,0x00,0x01,0x00,0x00,0x80,0x00,0x80,0x04,0x00,0x04,0x08,0x24,0x04,
0x24,0x04,0x24,0x02,0x44,0x02,0x44,0x12,0x84,0x10,0x04,0x10,0x03,0xF0,0x00,0x00};/*"心",0*/
/* (16 X 16 , 宋体 )*/

const   uint8_t bitmap_z []   U8G_PROGMEM  ={0x20,0x00,0x20,0x00,0x20,0x7C,0x7E,0x44,0x48,0x44,0x88,0x44,0x08,0x44,0x08,0x44,
0xFF,0x44,0x08,0x44,0x14,0x44,0x14,0x44,0x22,0x7C,0x22,0x44,0x42,0x00,0x80,0x00};/*"知",1*/
/* (16 X 16 , 宋体 )*/

const   uint8_t bitmap_t []   U8G_PROGMEM  ={0x00,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,
0x02,0x80,0x02,0x80,0x04,0x40,0x04,0x40,0x08,0x20,0x10,0x10,0x20,0x08,0xC0,0x06};/*"天",2*/
/* (16 X 16 , 宋体 )*/

const   uint8_t bitmap_q[]   U8G_PROGMEM  ={0x10,0x00,0x10,0x00,0x3F,0xFC,0x20,0x00,0x4F,0xF0,0x80,0x00,0x3F,0xF0,0x00,0x10,
0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x0A,0x00,0x0A,0x00,0x06,0x00,0x02};/*"气",3*/
/* (16 X 16 , 宋体 )*/

const   uint8_t bitmap_city1[]   U8G_PROGMEM  ={0x20,0x28,0x20,0x24,0x20,0x20,0x27,0xFE,0x24,0x20,0xFC,0x20,0x24,0x24,0x27,0xA4,
0x24,0xA4,0x24,0xA8,0x24,0xA8,0x3C,0x90,0xE6,0x92,0x49,0x2A,0x08,0x46,0x10,0x82};/*"城",0*/

const   uint8_t bitmap_city2[]   U8G_PROGMEM  ={0x02,0x00,0x01,0x00,0x00,0x00,0x7F,0xFC,0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,
0x21,0x08,0x21,0x08,0x21,0x08,0x21,0x08,0x21,0x28,0x21,0x10,0x01,0x00,0x01,0x00};/*"市",1*/

const   uint8_t bitmap_tianqi1[]   U8G_PROGMEM  ={0x00,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,
0x02,0x80,0x02,0x80,0x04,0x40,0x04,0x40,0x08,0x20,0x10,0x10,0x20,0x08,0xC0,0x06};/*"天",0*/

const   uint8_t bitmap_tianqi2[]   U8G_PROGMEM  ={0x10,0x00,0x10,0x00,0x3F,0xFC,0x20,0x00,0x4F,0xF0,0x80,0x00,0x3F,0xF0,0x00,0x10,
0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x0A,0x00,0x0A,0x00,0x06,0x00,0x02};/*"气",1*/

const   uint8_t bitmap_temp1[]   U8G_PROGMEM  ={0x00,0x00,0x23,0xF8,0x12,0x08,0x12,0x08,0x83,0xF8,0x42,0x08,0x42,0x08,0x13,0xF8,
0x10,0x00,0x27,0xFC,0xE4,0xA4,0x24,0xA4,0x24,0xA4,0x24,0xA4,0x2F,0xFE,0x00,0x00};/*"温",0*/

const   uint8_t bitmap_temp2[]   U8G_PROGMEM  ={0x01,0x00,0x00,0x80,0x3F,0xFE,0x22,0x20,0x22,0x20,0x3F,0xFC,0x22,0x20,0x22,0x20,
0x23,0xE0,0x20,0x00,0x2F,0xF0,0x24,0x10,0x42,0x20,0x41,0xC0,0x86,0x30,0x38,0x0E};/*"度",1*/


const   uint8_t bitmap_dress1[]   U8G_PROGMEM  ={0x02,0x00,0x01,0x00,0x7F,0xFE,0x48,0x22,0x90,0x14,0x00,0x00,0x3F,0xFC,0x00,0x40,
0x10,0x40,0x20,0x40,0x3F,0xFE,0x01,0x40,0x06,0x40,0x18,0x40,0x61,0x40,0x00,0x80};/*"穿",0*/

const   uint8_t bitmap_dress2[]   U8G_PROGMEM  ={0x02,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x02,0x00,0x02,0x00,0x05,0x00,0x05,0x08,
0x08,0x90,0x18,0xA0,0x28,0x40,0x48,0x20,0x88,0x10,0x0A,0x08,0x0C,0x06,0x08,0x00};/*"衣",1*/

const   uint8_t bitmap_sport1[]   U8G_PROGMEM  ={0x00,0x00,0x23,0xF8,0x10,0x00,0x10,0x00,0x00,0x00,0x07,0xFC,0xF0,0x40,0x10,0x80,
0x11,0x10,0x12,0x08,0x17,0xFC,0x12,0x04,0x10,0x00,0x28,0x00,0x47,0xFE,0x00,0x00};/*"运",0*/

const   uint8_t bitmap_sport2[]   U8G_PROGMEM  ={0x00,0x40,0x00,0x40,0x7C,0x40,0x00,0x40,0x01,0xFC,0x00,0x44,0xFE,0x44,0x20,0x44,
0x20,0x44,0x20,0x84,0x48,0x84,0x44,0x84,0xFD,0x04,0x45,0x04,0x02,0x28,0x04,0x10};/*"动",1*/

const   uint8_t bitmap_uv1[]   U8G_PROGMEM  ={0x08,0x80,0x28,0x88,0x2E,0xF0,0x28,0x84,0x2E,0x84,0xF0,0x7C,0x02,0x00,0x04,0x20,
0x1F,0xC0,0x01,0x80,0x06,0x10,0x3F,0xF8,0x01,0x08,0x11,0x20,0x25,0x10,0x42,0x08};/*"紫",0*/

const   uint8_t bitmap_uv2[]   U8G_PROGMEM  ={0x10,0x40,0x10,0x40,0x10,0x40,0x10,0x40,0x3E,0x40,0x22,0x60,0x42,0x50,0x42,0x48,
0xA4,0x44,0x14,0x44,0x08,0x40,0x08,0x40,0x10,0x40,0x20,0x40,0x40,0x40,0x80,0x40};/*"外",1*/

const   uint8_t bitmap_uv3[]   U8G_PROGMEM  ={0x10,0x50,0x10,0x48,0x20,0x40,0x24,0x5C,0x45,0xE0,0xF8,0x40,0x10,0x5E,0x23,0xE0,
0x40,0x44,0xFC,0x48,0x40,0x30,0x00,0x22,0x1C,0x52,0xE0,0x8A,0x43,0x06,0x00,0x02};/*"线",2*/

void draw(void) {
  u8g.setFont(u8g_font_unifont);
  // graphic commands to redraw the complete screen should be placed here  
 u8g.drawBitmapP ( 32 , 0 , 2 , 16 , bitmap_x); 
 u8g.drawBitmapP ( 49 , 0 , 2 , 16 , bitmap_z );
 u8g.drawBitmapP ( 66 , 0 , 2 , 16 , bitmap_t); 
 u8g.drawBitmapP ( 83 , 0 , 2 , 16 , bitmap_q );

 u8g.drawBitmapP ( 2 , 22 , 2 , 16 , bitmap_city1 );
 u8g.drawBitmapP ( 19 , 22 , 2 , 16 , bitmap_city2 );
 u8g.drawBitmapP ( 48 , 22 , 2 , 16 , bitmap_tianqi1 );
 u8g.drawBitmapP ( 65 , 22 , 2 , 16 , bitmap_tianqi2 );
 u8g.drawBitmapP ( 91 , 22 , 2 , 16 , bitmap_temp1 );
 u8g.drawBitmapP ( 108 , 22 , 2 , 16 , bitmap_temp2);

// u8g.drawBitmapP ( 2 , 22 , 2 , 16 , bitmap_dress1 );
// u8g.drawBitmapP ( 19 , 22 , 2 , 16 , bitmap_dress2 );
// u8g.drawBitmapP ( 38 , 22 , 2 , 16 , bitmap_uv1 );
// u8g.drawBitmapP ( 55 , 22 , 2 , 16 , bitmap_uv2 );
// u8g.drawBitmapP ( 72 , 22 , 2 , 16 , bitmap_uv3 );
// u8g.drawBitmapP ( 91 , 22 , 2 , 16 , bitmap_sport1 );
// u8g.drawBitmapP ( 108 , 22 , 2 , 16 , bitmap_sport2);
}
void draw1(void) {
  u8g.setFont(u8g_font_unifont);
  // graphic commands to redraw the complete screen should be placed here  
  u8g.drawBitmapP ( 32 , 0 , 2 , 16 , bitmap_x); 
 u8g.drawBitmapP ( 49 , 0 , 2 , 16 , bitmap_z );
 u8g.drawBitmapP ( 66 , 0 , 2 , 16 , bitmap_t); 
 u8g.drawBitmapP ( 83 , 0 , 2 , 16 , bitmap_q );
 
 u8g.drawBitmapP ( 2 , 22 , 2 , 16 , bitmap_dress1 );
 u8g.drawBitmapP ( 19 , 22 , 2 , 16 , bitmap_dress2 );
 u8g.drawBitmapP ( 38 , 22 , 2 , 16 , bitmap_uv1 );
 u8g.drawBitmapP ( 55 , 22 , 2 , 16 , bitmap_uv2 );
 u8g.drawBitmapP ( 72 , 22 , 2 , 16 , bitmap_uv3 );
 u8g.drawBitmapP ( 91 , 22 , 2 , 16 , bitmap_sport1 );
 u8g.drawBitmapP ( 108 , 22 , 2 , 16 , bitmap_sport2);
}
void setup(void) {
Serial.begin(115200);
mySerial.begin(9600);
pinMode(2,INPUT);
pinMode(3,INPUT);
//Serial1.begin(1200);
   // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  delay(200);
  draw();
  delay(2000);
}

void loop(void) {
  char disdata[128];
  if(digitalRead(2)==0)
  menuFlag = 1;
  if(digitalRead(3)==0)
  menuFlag = 2;
  /*while(mySerial.available()>0)
  {
   data = mySerial.read();//保存接收字符
   Serial.print(data);
   delay(2); 
  }*/
  // picture loop
  saveData(getData());
//  sprintf(disdata,"%s",newString1);
   
  u8g.firstPage();  
  do {  
     if(menuFlag==1)
     {
      newString1.toCharArray(disdata,newString1.length()); 
      u8g.drawStr(0, 56,disdata);
      draw(); 
      }else if(menuFlag==2){
        newString2.toCharArray(disdata,newString1.length()); 
      u8g.drawStr(0, 56,disdata);
      draw1(); 
        }
      
          
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(500);
}
unsigned char getData()
{
     char data;
     int cnt=0;     
     unsigned char flag=0;
     memset(revBuff,0,sizeof(revBuff));
     //Serial.flush();
     while(mySerial.available()>0)
     {
          data = mySerial.read();//保存接收字符
          if(data=='[')//天气
          {
            flag = 1;
            }else if(data=='(')//生活
            {
              flag = 2;
              }else if(data=='#')//生活
            {
              //flag = 3;
              break;
              }else if(data==':')//8266异常
              {
                flag = 4;
                mySerial.flush();
                return flag;
                }
           if(flag!=0)
           {
            revBuff[cnt++] = data;
            } 
      }
      if(flag!=0)
      {
        //Serial.println(revBuff);
        //delay(200);
      }
      
      return flag;
  }
void saveData(unsigned char flag)
{  
  
  
  if(flag==1)
  {
    newString1=revBuff+1;
    newString1.replace("]["," ");
    newString1.replace("]"," ");
    Serial.println(newString1);delay(200);
    }else if(flag==2)
    {
      newString2=revBuff+1;
      newString2.replace(")("," ");
      newString2.replace(")"," ");
      Serial.println(newString2);delay(200);
      }
  
  }
