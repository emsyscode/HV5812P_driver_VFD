/**********************************************************************/
/*This code is not clean and OFFCOURSE will be possible do it better! */ 
/*this is only a group of functions to be used as independent code,  */ 
/*and by this way will be possible to any person can do the changes   */ 
/*of code and see what happen.                                         */
/*The code don't depend of any external library or extenal functions  */
/*complicated.                                                         */
/*I'm let the values to sent as binnary, this allow swap bit by bit */
/* to is possible test segment by segment without convert to HEX    */
/**********************************************************************/
#define VFD_in 7  // This is the pin number 7 on Arduino UNO
#define VFD_clk 8 // This is the pin number 8 on Arduino UNO
#define VFD_ce 9 // This is the pin number 9 on Arduino UNO
#define VFD_Vlcd 10 // This signal power up the LCD and must be on only after VCC
//ATT: On the Uno and other ATMEGA based boards, unsigned ints (unsigned integers) are the same as ints in that they store a 2 byte value.
//Long variables are extended size variables for number storage, and store 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647.
//*************************************************//
void setup() {
  pinMode(VFD_clk, OUTPUT);
  pinMode(VFD_in, OUTPUT);
  pinMode(VFD_ce, OUTPUT);
  pinMode(VFD_Vlcd, OUTPUT);
 
  pinMode(13, OUTPUT);
  Serial.begin(9600); // only to debug
}
void send_char(unsigned char a)
{
 //
 unsigned char transmit = 15; //define our transmit pin
 unsigned char data = 170; //value to transmit, binary 10101010
 unsigned char mask = 1; //our bitmask
  data=a;
  digitalWrite(VFD_ce, LOW); // When strobe is low, all output is enable. If high, all output will be set to low.
  delayMicroseconds(5);
  digitalWrite(VFD_clk,LOW);// need invert the signal to allow 8 bits is is low only send 7 bits
  delayMicroseconds(5);
  for (mask = 0b00000001; mask>0; mask <<= 1) { //iterate through bit mask
  digitalWrite(VFD_clk,LOW);// need invert the signal to allow 8 bits is is low only send 7 bits
  delayMicroseconds(5);
    if (data & mask){ // if bitwise AND resolves to true
      digitalWrite(VFD_in, HIGH);
      //Serial.print(1);
    }
    else{ //if bitwise and resolves to false
      digitalWrite(VFD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(VFD_clk,HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(5);
    //
    digitalWrite(VFD_ce, HIGH); // When strobe is low, all output is enable. If high, all output will be set to low.
  delayMicroseconds(5);
  }
}
/*********************************************************************/
// I h've created 3 functions to send bit's, one with strobe, other without strobe and one with first byte with strobe followed by remaing bits.
void send_char_without(unsigned char a)
{
 unsigned char data = 170; //value to transmit, binary 10101010
 unsigned char mask = 1; //our bitmask
  data=a;
  for (mask = 0b00000001; mask>0; mask <<= 1) { //iterate through bit mask
  digitalWrite(VFD_clk, LOW);
  delayMicroseconds(5);
    if (data & mask){ // if bitwise AND resolves to true
      digitalWrite(VFD_in, HIGH);
      //Serial.print(1);
    }
    else{ //if bitwise and resolves to false
      digitalWrite(VFD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(VFD_clk,HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(5);
  }
}
/*********************************************************************/
void send_char_4bit(unsigned char a)
{
 unsigned char data = 170; //value to transmit, binary 10101010
 unsigned char mask = 1; //our bitmask
 int i = -1;
  data=a;
  for (mask = 0b00010000; mask>0; mask <<= 1) { //iterate through bit mask
   i++;
   digitalWrite(VFD_clk, LOW);
  delayMicroseconds(5);
    if (data & mask){ // if bitwise AND resolves to true
      digitalWrite(VFD_in, HIGH);
      //Serial.print(1);
    }
    else{ //if bitwise and resolves to false
      digitalWrite(VFD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(VFD_clk,HIGH);// 
    delayMicroseconds(1);
  }
}
/*******************************************************************/
void allON_HV5812(){
  unsigned char group=0;
          digitalWrite(VFD_ce, LOW); //
          delayMicroseconds(1);
          send_char_without(0B11111110);  send_char_without(0B11111111); 
          send_char_4bit(0B11110000); // The chip HV5812P only have 20 pins(10 is to grids, remaning is to segments) The colon dont brigth 
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
/**************************************************************************/
void allOFF_HV5812(){
unsigned char group=0;
        digitalWrite(VFD_ce, LOW); //
        delayMicroseconds(1);
          send_char_without(0B00000000);  send_char_without(0B00000000); 
          send_char_4bit(0B00000000); 
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
/**************************************************************************/
void numberZero(){
        digitalWrite(VFD_ce, LOW); //
        delayMicroseconds(1);
//                            0dcbat9?                        87654321
          send_char_without(0B11111000);  send_char_without(0B00000000);
//                         fgeh  
          send_char_4bit(0B10100000); 
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
void numberOne(){
        digitalWrite(VFD_ce, LOW); //
        delayMicroseconds(1);
//                            0dcba_9?                        87654321
          send_char_without(0B00110000);  send_char_without(0B00000001);
//                         fgeh  
          send_char_4bit(0B00000000); 
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
void numberTwo(){
        digitalWrite(VFD_ce, LOW); //
        delayMicroseconds(1);
//                            0dcba_9?                        87654321
          send_char_without(0B01011000);  send_char_without(0B00000010);
//                         fgeh  
          send_char_4bit(0B01100000); 
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
void numberThree(){
        digitalWrite(VFD_ce, LOW); //
        delayMicroseconds(1);
//                            0dcba_9?                        87654321
          send_char_without(0B01111000);  send_char_without(0B00000100);
//                         fgeh 
          send_char_4bit(0B01000000); 
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
void numberFour(){
        digitalWrite(VFD_ce, LOW); //
        delayMicroseconds(1);
//                            0dcba_9?                        87654321
          send_char_without(0B00110000);  send_char_without(0B00001000);
//                         fgeh  
          send_char_4bit(0B11000000); 
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
void numberFive(){
        digitalWrite(VFD_ce, LOW); //
        delayMicroseconds(1);
//                            0dcba_9?                        87654321
          send_char_without(0B01101000);  send_char_without(0B00010000);
//                         fgeh  
          send_char_4bit(0B11000000); 
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
void numberSix(){
        digitalWrite(VFD_ce, LOW); //
        delayMicroseconds(1);
//                            0dcba_9?                        87654321
          send_char_without(0B01101000);  send_char_without(0B00100000);
//                         fgeh  
          send_char_4bit(0B11100000); 
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
void numberSeven(){
        digitalWrite(VFD_ce, LOW); //
        delayMicroseconds(1);
//                            0dcba_9?                        87654321
          send_char_without(0B00111000);  send_char_without(0B01000000);
//                         fgeh  
          send_char_4bit(0B00000000); 
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
void numberEight(){
        digitalWrite(VFD_ce, LOW); //
        delayMicroseconds(1);
//                            0dcba_9?                        87654321
          send_char_without(0B01111000);  send_char_without(0B10000000);
//                         fgeh  
          send_char_4bit(0B11100000); 
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
void numberNine(){
        digitalWrite(VFD_ce, LOW); //
        delayMicroseconds(1);
//                            0dcba_9?                        87654321
          send_char_without(0B00111010);  send_char_without(0B00000000);
//                         fgeh  
          send_char_4bit(0B11000000); 
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
/*********************************************************************/
void loop() {
 // Attention: 
 //At begin, I've used the "_" to separate the number in the name of function, Got a error after 4 times used it("_").
 numberZero();
 delay(500);
 numberOne();
 delay(500);
 numberTwo();
 delay(500);
 numberThree();
 delay(500);
 numberFour();
 delay(500);
 numberFive();
 delay(500);
 numberSix();
 delay(500);
 numberSeven();
 delay(500);
 numberEight();
 delay(500);
 numberNine();
 delay(500);
    for (int i=0; i< 3; i++){
     allON_HV5812(); // All on
     delay(300);
     allOFF_HV5812(); // All off
     delay(300);
    }
}
