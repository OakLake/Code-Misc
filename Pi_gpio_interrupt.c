/*
C++ threaded interrupts on Raspberry Pi
compile with gcc -o output Pi_gpio_interrupt.c -lwiringPi
*/

#include<stdio.h>
#include<sys/time.h>
#include<wiringPi.h>
#include<unistd.h>

#define PIN 0
// Pins layout for wiringPi:
// http://wiringpi.com/pins/
struct timeval last_change;

void callback17(void);

int main(int argc, char * argv[]){
  wiringPiSetup();
  pinMode(PIN,INPUT);
  pullUpDnControl(PIN, PUD_UP);
  gettimeofday(&last_change,NULL);
  if (wiringPiISR(PIN,INT_EDGE_BOTH, &callback17) < 0){
    printf("Unable to setup ISR\n");
  }

  for(;;){
    //printf("waiting...\n");
    sleep(1);
  }

}

void callback17(void){
  struct timeval now;
  unsigned long diff;
  gettimeofday(&now,NULL);

  // Time difference in usec
  diff = (now.tv_sec*1000000 + now.tv_usec) - (last_change.tv_sec*1000000 + last_change.tv_usec);
  printf("time since last trigger: %d usec\n",diff);
  last_change = now;

}
