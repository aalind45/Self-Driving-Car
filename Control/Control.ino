//#define trigPinf1 12
//#define echoPinf1 13
//#define trigPinf2 9
//#define echoPinf2 8


int front = 6;
int back = 5;
int left = 4;
int right = 3;
int pot=A0;     // potentiometer 
int pot_max=600;    // potentiometer ranges within which tyre is
int pot_min=450;    // kept for straightening/aligning with body
//const int ref=850;
//int range=constrain(range,825,875);
// front with right = p
// front with left = q

void setup(){
 // Open serial connection.
 Serial.begin(9600);
 //pinMode(ledRed, OUTPUT);
   pinMode(front,OUTPUT);
   pinMode(back,OUTPUT);
   pinMode(left,OUTPUT);
   pinMode(right,OUTPUT);
   digitalWrite(front,HIGH);
   digitalWrite(back,HIGH);
   digitalWrite(right,HIGH);
   digitalWrite(left,HIGH);
   pinMode(trigPinf1, OUTPUT);
   pinMode(echoPinf1, INPUT);
   pinMode(trigPinf2, OUTPUT);
   pinMode(echoPinf2, INPUT);
}


void tyre_straight()   // to straighten up or align the tyres with body from any orientation using the 
{                      //  readings from the potentiometer.
  while(analogRead(pot)>pot_max || analogRead(pot)<pot_min)
  {
  Serial.println(analogRead(pot));
  if (analogRead(pot)< pot_min)
      { 
       digitalWrite(left,LOW);
       delay(10);
       digitalWrite(left,HIGH);  
      }
      
  else if(analogRead(pot)>pot_max)
      { 
        digitalWrite(right,LOW);
         delay(10);
        digitalWrite(right,HIGH); 
      } 
   else
   {
     digitalWrite(left,HIGH);
     digitalWrite(right,HIGH); 
   } 
   if(analogRead(pot)>pot_min && analogRead(pot)<pot_max)
     break;
   delay(10);
  }
}
void move_straight() // movement in straight direction.
{
     digitalWrite(front,LOW);
     digitalWrite(back,HIGH);
     digitalWrite(right,HIGH);
     digitalWrite(left,HIGH);
}
void reverse()
{
     digitalWrite(front,HIGH);
     digitalWrite(back,LOW);
     digitalWrite(right,HIGH); 
     digitalWrite(left,HIGH); 
}
void tyre_left(){                // to turn the front tyres to left (vehicle will not be moving 
     digitalWrite(front,HIGH);  // at this time).
     digitalWrite(back,HIGH);
     digitalWrite(right,HIGH);
     digitalWrite(left,LOW);
}
void move_left(){              // moving left
     digitalWrite(front,LOW);
     digitalWrite(back,HIGH);
     digitalWrite(right,HIGH);
     digitalWrite(left,LOW);
}
void tyre_right(){            // turning front tyres to the right.
     digitalWrite(front,HIGH);
     digitalWrite(back,HIGH);
     digitalWrite(right,LOW);
     digitalWrite(left,HIGH);
}
void move_right(){
     digitalWrite(front,LOW);
     digitalWrite(back,HIGH);
     digitalWrite(right,LOW);
     digitalWrite(left,HIGH);
}
void loop()
{
  tyre_straight();  // straightening tyres on initialisation.
 // move_straight();
 Serial.println(analogRead(pot));
  if(Serial.available() > 0){      // when serial data is received from Decision making module
       char data = Serial.read();
       char str[2];
       str[0] = data;
       str[1] = '\0';              // if data present, blink
       if(str[0] == 'f'){          // f ==> move in front direction
         tyre_straight();
         move_straight();
          }
       else if(str[0] == 'b'){     // b ==> backward motion
         tyre_straight();
         reverse();
       }
       else if(str[0] == 'l'){      // l ==> left turn
         move_left();
         delay(250);
         digitalWrite(left,HIGH);
         tyre_straight();
       }
       else if (str[0]== 'r'){       // r ==> right turn
         move_right();
         delay(250);
         digitalWrite(right,HIGH);
         tyre_straight();
       }
       /*else if (str[0]== 'p'){
         move_right();
       }
      else if (str[0]== 'q'){
         move_left();
       }*/
       else {            //if Serial data is not received, vehicle continues moving straight
         tyre_straight();
         move_straight();
       }
  }
}


