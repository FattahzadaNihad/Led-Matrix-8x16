#include <Led_matrix_8x16.h>

unsigned char name[256];

void setup() {

  // init LED matrix 
  led_matrix_init(3,4); // SDA SCL
}

void loop() {

  // Set the address display
  set_address();

  // Scrolling symbols
    int count=0;
    str_array("Hello World",name,&count);
    write_str(name,&count);

  // Set the brightness display
  set_brightness();
}
