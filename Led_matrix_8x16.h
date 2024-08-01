#ifndef LED_MATRIX_8X16_H
#define LED_MATRIX_8X16_H

// Character bitmaps for the LED matrix
extern unsigned char symbols[38][8];

// Function prototypes for LED matrix initialization and control
extern void led_matrix_init(int IIC_SCL_PIN,int IIC_SDA_PIN);

// Communication function prototypes
extern void IIC_start();
extern void IIC_send(unsigned char send_data);
extern void IIC_end();
// Communication function prototypes

// LED matrix control function prototypes
// Set the address display
extern void set_address();

// Set the brightness display
extern void set_brightness();

// Retrieve the corresponding value from the array of symbols according to the corresponding character
extern char choose_value(char character);

// Adding values ​​to char array by matching character
extern void add_char(unsigned char value[256],int *k,unsigned char selection);

// Prepare a set of symbols to be given to the anchor
extern void str_array(unsigned char *str,unsigned char value[256],int *k);

// Write scrolling symbols
extern void write_str(unsigned char value[256],int *k);

// Write center location
extern void write_location(unsigned char value[256],int *k);

// Clean the led matrix
extern void clear8x16();

// Count down from a given number or count up to a given number
extern void Counter(int num,unsigned char char_tuple[256],int time,bool UpOrDown);

#endif