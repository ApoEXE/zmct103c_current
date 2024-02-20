/*
Made on Dec 22, 2020
By MehranMaleki @ Electropeak
Home
*/
#include <iostream>
#include <limits.h>
#define samples 100
#define volt_offset -0.018

int volt[samples + 1];  //samples for more then a cycle
unsigned int inc = 0;
int max_v = INT_MIN;
int max_i = 0;
int volt_max[samples + 1];
int mean_samples = 100;
int inc2 = 0;
int add_max_v = 0;
void setup() {
  pinMode(A0, INPUT);
  Serial.begin(115200);
}

void loop() {
  delayMicroseconds(10);
  volt[inc] = analogRead(A0);

  if (inc >= samples) {


    for (int i = 0; i < samples; i++) {
      if (volt[i] > max_v) {
        max_v = volt[i];
        max_i = i;
      }
    }
    volt_max[inc2] = max_v;


    max_v = 0;
    max_i = 0;
    inc = 0;

    if (inc2 >= mean_samples) {

      for (int i = 0; i < mean_samples; i++) {
        add_max_v += volt_max[i];
      }
      float volt_p = ((3.3 / 1023) * (add_max_v / mean_samples))*0.707;  //output of ZMCT103 must check offset 2.5v
      if (10 >= (add_max_v / mean_samples)) {
        volt_p = -1*volt_offset;
      }

      Serial.print(" max value ");
      Serial.print((add_max_v / mean_samples));
      Serial.print(" volt_p ");
      Serial.print((volt_p + volt_offset));
      Serial.println("v");
      inc2 = 0;
      add_max_v = 0;
    } else
      inc2++;
  } else
    inc++;
}