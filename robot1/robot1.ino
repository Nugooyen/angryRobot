
/* 
Motor Diagram TOP VIEW
0[\] - [/]1
  |     |
  |     |
2[/] - [\]3
up is positive forward
right is positive sideways
conterclockwise is positive rotation

forwards [ 1, 1, 1, 1]
sideways [ 1,-1,-1, 1]
rotation [ 1, 1,-1,-1]

Start Byte = 0x78 : char "x" : int 120
Stop Byte  = 0x7a : char "z" : int 122

Data
Backwards int 49 : char "1"
neutral   int 50 : char "2"
forwards  int 51 : char "3"
*/





// MOTOR PIN DEFINITIONS
const int FL_fwd = 3;
const int FL_bkw = 4;
const int FR_fwd = 5;
const int FR_bkw = 6;
const int BR_fwd = 7;
const int BR_bkw = 8;
const int BL_fwd = 9;
const int BL_bkw = 10;

bool FL_fwd_output = 0;
bool FL_bkw_output = 0;
bool FR_fwd_output = 0;
bool FR_bkw_output = 0;
bool BR_fwd_output = 0;
bool BR_bkw_output = 0;
bool BL_fwd_output = 0;
bool BL_bkw_output = 0;



int val_unprocessed[5] = {0,0,0,0,0};
// [s,x,x,x,e] [e,s,x,x,x] [x,e,s,x,x]
int vals[3] = {0,0,0};
int list_size = 5;
int S_count = 0;

const int forwards[4] = {1,1,1,1};
const int sideways[4] = {1,-1,-1,1};
const int rotation[4] = {-1,1,-1,1};

int final_motors[4] = {0,0,0,0};

const int neutral = 50;


void setup() {
  Serial.begin(9600);
  pinMode(FL_fwd, OUTPUT);
  pinMode(FL_bkw, OUTPUT);
  pinMode(FR_fwd, OUTPUT);
  pinMode(FR_bkw, OUTPUT);
  pinMode(BR_fwd, OUTPUT);
  pinMode(BR_bkw, OUTPUT);
  pinMode(BL_fwd, OUTPUT);
  pinMode(BL_bkw, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:

  
  while(Serial.available()>0){
    
    val_unprocessed[S_count] = Serial.read(); 
    S_count++;
    if (S_count >= list_size) S_count = 0;
    if (val_unprocessed[S_count] == 0x78 && val_unprocessed[(S_count+4) % list_size] ==0x7a){
      for (int i=0; i< list_size-2; i++){
        vals[i] = val_unprocessed[(S_count + 1 + i) % list_size];
      }
      for(int i = 0; i < 4 ; i++){
        final_motors[i]  = (vals[0] - neutral) * forwards[i];
        final_motors[i] += (vals[1] - neutral) * sideways[i];
        final_motors[i] += (vals[2] - neutral) * rotation[i];
      
      }
    }
    
    
  }
  



// motor 0
  if (final_motors[0]>0){
    digitalWrite(FL_fwd, 1); 
    digitalWrite(FL_bkw, 0);
  }
  if (final_motors[0]< 0){
    digitalWrite(FL_fwd, 0); 
    digitalWrite(FL_bkw, 1);
  }
  else if(final_motors[0] == 0){
    digitalWrite(FL_fwd, 0); 
    digitalWrite(FL_bkw, 0);
  }

// motor 1
  if (final_motors[1]>0){
    digitalWrite(FR_fwd, 1); 
    digitalWrite(FR_bkw, 0);
  }
  if (final_motors[1]<0){
    digitalWrite(FR_fwd, 0); 
    digitalWrite(FR_bkw, 1);
  }
  else if(final_motors[1] == 0){
    digitalWrite(FR_fwd, 0); 
    digitalWrite(FR_bkw, 0);
  }

// motor 2
  if (final_motors[2]>0){
    digitalWrite(BL_fwd, 1); 
    digitalWrite(BL_bkw, 0);
  }
  if (final_motors[2]<0){
    digitalWrite(BL_fwd, 0); 
    digitalWrite(BL_bkw, 1);
  }
  else if(final_motors[2] == 0){
    digitalWrite(BL_fwd, 0); 
    digitalWrite(BL_bkw, 0);
  }

//motor 3
  if (final_motors[3]>0){
    digitalWrite(BR_fwd, 1); 
    digitalWrite(BR_bkw, 0);
  }
  if (final_motors[3]<0){
    digitalWrite(BR_fwd, 0); 
    digitalWrite(BR_bkw, 1);
  }
  else if(final_motors[3] == 0){
    digitalWrite(BR_fwd, 0); 
    digitalWrite(BR_bkw, 0);
  }
    
  

}
