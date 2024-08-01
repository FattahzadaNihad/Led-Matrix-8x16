#include <Led_matrix_8x16.h>

unsigned char num[256];

void setup() {

  // init LED matrix 
  led_matrix_init(3,4); // SDA SCL
}

void loop() {

  // Set the address display
  set_address();

  // Limit number, number arrays, time,false Count up 
  Counter(10,num,200,false);  
  delay(1000);

  // Limit number, number arrays, time, true  Count down  
  Counter(10,num,200,true);  
  delay(1000);

  // Set the brightness display
  set_brightness();
}
