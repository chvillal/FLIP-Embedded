extern "C"{
#include "flip.h"
}

void setup() {
  while (!Serial);
  Serial.begin(9600);
  uint32_t result = test_function(1234);
  Serial.println(result);
  
}

void loop() {


}
