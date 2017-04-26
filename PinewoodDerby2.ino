#define START 4

long start = 0;
int current_place = 0;

int lane_one_place = 0;
int lane_two_place = 0;
int lane_three_place = 0;

boolean lane_one_sent = false;
boolean lane_two_sent = false;
boolean lane_three_sent = false;
boolean race_over = false;

void setup() {
  Serial.begin(9600);
  //pinMode(START,INPUT_PULLUP);
  //enableInterrupt(START,startInterrupt , CHANGE);
 
    start = millis();
    Serial.print(4);
    Serial.print(",");
    Serial.print("Start");
    Serial.println(start);
  
}

void loop()
{
  
  
  int lane_three = analogRead(A2);
  int lane_two = analogRead(A3);
  int lane_one = analogRead(A1);
  if(lane_one < 500 && lane_one_sent == false)
  {
        long lane_one_time = millis() - start;
        current_place++;
        lane_one_place = current_place; 
        sendResult(1,lane_one_place,lane_one_time);
        lane_one_sent = true;
  }
  
  if(lane_two > 1020 && lane_two_sent == false)
  {
        long lane_two_time = millis() - start;
        current_place++;
        lane_two_place = current_place; 
        sendResult(2,lane_two_place,lane_two_time);
        lane_two_sent = true;
  }
  
  if(lane_three > 1020 && lane_three_sent == false)
  {
        long lane_three_time = millis() - start;
        current_place++;
        lane_three_place = current_place;  
        sendResult(3,lane_three_place,lane_three_time);
        lane_three_sent = true;
  }
  
  if(lane_one_sent && lane_two_sent && lane_three_sent && race_over == false)
  {
    
    //sendMessage("Race over");
    Serial.print(5);
    Serial.print(",");
    Serial.println("Race over");
    //current_place = 0;
    //lane_one_sent = false;
    //lane_two_sent = false;
    //lane_three_sent = false;
    race_over = true;
  }
  
}


void sendResult(int lane, int place, long time)
{
   Serial.print(lane);
   Serial.print(",");
   Serial.print(place);
   Serial.print(",");
   Serial.println(time); 
}

void startInterrupt()
{

 boolean pin_state_new = digitalRead(START);
  if (pin_state_new == LOW && start != 0)
    {
        start = 0;
        //lane_one = 0;
        //lane_two = 0;
        //lane_three = 0;
        current_place = 0;
        lane_one_sent = false;
        lane_two_sent = false;
        lane_three_sent = false;
    }
}
