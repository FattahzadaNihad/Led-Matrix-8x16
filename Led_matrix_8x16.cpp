

#include "Led_matrix_8x16.h"
#include <Arduino.h>

int IIC_SCL=3;
int IIC_SDA=4;

// Character bitmaps for the LED matrix
unsigned char symbols[38][8] = {
  {0xF8, 0xFC, 0x46, 0x46, 0xFC, 0xF8}, // A
  {0xFE, 0xFE, 0x92, 0x92, 0xFE, 0x6C}, // B
  {0x7C, 0xFE, 0x82, 0x82, 0x82, 0x44}, // C
  {0xFE, 0xFE, 0x82, 0x82, 0xFE, 0x7C}, // D
  {0xFE, 0xFE, 0xD6, 0xD6, 0xC6, 0xC6}, // E
  {0xFE, 0xFE, 0x12, 0x12, 0x02, 0x02}, // F
  {0x7C, 0xFE, 0x82, 0x92, 0xF2, 0xF4}, // G
  {0xFE, 0xFE, 0x10, 0x10, 0xFE, 0xFE}, // H
  {0x82,0xFE,0xFE,0x82},               //I
  {0x40, 0x82, 0xFE, 0xFE, 0x02, 0x00}, // J
  {0xFE, 0xFE, 0x18, 0x34, 0xE2, 0xC2}, // K
  {0xFE, 0xFE, 0xC0, 0xC0, 0xC0, 0xC0}, // L
  {0xFE, 0xFE, 0x1C, 0x70, 0x1C, 0xFE,0xFE}, // M
  {0xFE, 0xFE, 0x1C, 0x70, 0xFE, 0xFE}, // N
  {0x7C, 0xFE, 0xC6, 0xC6, 0xFE, 0x7C}, // O
  {0xFE, 0xFE, 0x12, 0x12, 0x1E, 0x0C}, // P
  {0x7C, 0xFE, 0x82, 0xC2, 0xFE, 0xBC}, // Q
  {0xFE, 0xFE, 0x12, 0x32, 0xDE, 0x8C}, // R
  {0x4C, 0x9E, 0x92, 0x92, 0xF2, 0x62}, // S
  {0x02, 0x02, 0xFE, 0xFE, 0x02, 0x02}, // T
  {0x7E, 0xFE, 0x80, 0x80, 0xFE, 0x7E}, // U
  {0x3E, 0x7E, 0xC0, 0xC0, 0x7E, 0x3E}, // V
  {0xFE, 0xFE, 0x70, 0x38, 0x70, 0xFE,0xFE}, // W
  {0xC6, 0xEE, 0x38, 0x38, 0xEE, 0xC6}, // X
  {0x0E, 0x1E, 0xF0, 0xF0, 0x1E, 0x0E}, // Y
  {0xE2, 0xF2, 0x92, 0x9A, 0x8E, 0x86}, // Z
  {0x7C, 0xFE, 0x82, 0x82, 0xFE, 0x7C}, // 0
  {0x82, 0xFE, 0xFE, 0x80}, // 1
  {0xE2, 0xF2, 0x92, 0x92, 0x9E, 0x8C}, // 2
  {0x44, 0xC6, 0x92, 0x92, 0xFE, 0x6C}, // 3
  {0x30, 0x38, 0x24, 0xFE, 0xFE, 0x20}, // 4
  {0x4E, 0xCE, 0x8A, 0x8A, 0xFA, 0x72}, // 5
  {0x7C, 0xFE, 0x92, 0x92, 0xF2, 0x60}, // 6
  {0x06, 0x06, 0xF2, 0xFA, 0x1E, 0x06}, // 7
  {0x6C, 0xFE, 0x92, 0x92, 0xFE, 0x6C}, // 8
  {0x0C, 0x9E, 0x92, 0x92, 0xFE, 0x7C}, // 9
  {0x6C},  // :
  {0x10, 0x54, 0x38, 0x7C, 0x38, 0x54} // *
};
// Function prototypes for LED matrix initialization and control
void led_matrix_init(int IIC_SCL_PIN,int IIC_SDA_PIN){
  IIC_SCL=IIC_SCL_PIN;
  IIC_SDA=IIC_SDA_PIN;
  pinMode(IIC_SCL,OUTPUT);
  pinMode(IIC_SDA,OUTPUT);
  digitalWrite(IIC_SCL,LOW);
  digitalWrite(IIC_SDA,LOW);
}




void IIC_start(){

  digitalWrite(IIC_SCL,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,LOW);
  delayMicroseconds(3);
}
void IIC_send(unsigned char send_data){
  for(char i = 0;i < 8;i++)
  {
      digitalWrite(IIC_SCL,LOW);
      delayMicroseconds(3); 
      if(send_data & 0x01)
      {
        digitalWrite(IIC_SDA,HIGH);
      }
      else
      {
        digitalWrite(IIC_SDA,LOW);
      }
      delayMicroseconds(3);
      digitalWrite(IIC_SCL,HIGH); 
      delayMicroseconds(3);
      send_data = send_data >> 1;
  }
}
void IIC_end(){
  digitalWrite(IIC_SCL,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,HIGH);
  delayMicroseconds(3);
}


// Set the address display
void set_address(){
  IIC_start();
  IIC_send(0x40);
  IIC_end(); 
}

// Set the brightness display
void set_brightness(){
  IIC_start();
  IIC_send(0x8A);
  IIC_end(); 
}

// Retrieve the corresponding value from the array of symbols according to the corresponding character
char choose_value(char character){
  if(character>=48&&character<=58){
    character-=22;
  }
  else if(character>=97&&character<=122){
    character-=97;
  }
  else if(character>=64&&character<=90){
    character-=65;
  }
    else if(character>=97&&character<=122){
    character-=97;
  }
  else if(character==42){
    character=37;
  }
  return character;
}

// Adding values ​​to char array by matching character
void add_char(unsigned char value[],int *k,unsigned char selection){
  int i=0;
  while (symbols[selection][i]) {
    value[*k]=symbols[selection][i];
    *k+=1;
    i++;   
  }
  value[*k]=0x00;
  *k+=1;
}

// Prepare a set of symbols to be given to the anchor
void str_array(unsigned char *str,unsigned char value[],int *k){

  while (*str) {
    if (*str==' ') {
      for (int i=0; i<3; i++) {
        value[*k]=0x00;
        *k+=1;
      }
      str++;
    }
    else {
      add_char(value,k,choose_value(*str));
      str++;
    }
  }
  if (*k>16) {
    value[*k+=1]=0x00;
    *k+=2;
    for (int i=0; i<16; i++) {
      value[*k+i]=value[i];
      
    }
    *k+=16;
  }
}

// Write scrolling symbols
void write_str(unsigned char value[],int *k){
  IIC_start();
  IIC_send(0xc0);
  if (*k>16) {
    for (int m=0; *k-m-16; m++) {
      for (int i=0; i<16; i++) {
        IIC_send(value[i+m]);
      }
      delay(100);
    }

  }
  else {
    for (int i=0; i<*k; i++) {
      IIC_send(value[i]);
    }
  }
    IIC_end();
}

// Write center location
void write_location(unsigned char value[],int *k){
  IIC_start();
  IIC_send(0xc1+(((16-(*k))/2)));
  for(int i=0;i<*k;i++){
    IIC_send(value[i]);
  }
  IIC_end();
}

// Clean the led matrix
void clear8x16(){
  IIC_start();
  IIC_send(0xc0);
  for(int i=0;i<16;i++){
      IIC_send(0x00);
  }
  IIC_end();
}

// Count down from a given number or count up to a given number
void Counter(int num,unsigned char char_tuple[],int time,bool UpOrDown){
  if (num>=0&&num<=99) {
    if (UpOrDown) {
      for (int i=num; i>=0; i--) {
        int count_=0;
        String new_num=String(i);
        str_array(new_num.c_str(),char_tuple,&count_);
        write_location(char_tuple,&count_);
        delay(time);
        clear8x16();
        delay(time);
      }
    }
    else {
      for (int i=0; i<=num; i++) {
        int count_=0;
        String new_num=String(i);
        str_array(new_num.c_str(),char_tuple,&count_);
        write_location(char_tuple,&count_);
        delay(time);
        clear8x16();
        delay(time);
      }
    }
  }
  else{
        int count_=0;
        str_array("*",char_tuple,&count_);
        write_location(char_tuple,&count_);
        delay(time);
        clear8x16();
        delay(time);
  }

}
