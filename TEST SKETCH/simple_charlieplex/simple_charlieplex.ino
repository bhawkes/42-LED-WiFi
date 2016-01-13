unsigned long previousMillis = 0;
const long interval = 500; // milliseconds gap between sending a network request.

// I skipped F because F isn't allowed
#define A 5
#define B 4
#define C 15
#define D 16
#define E 14
#define G 12
#define H 13

const int count = 42;

int lit = 0;

// visual array of how the pins are laid out
int lights[count][2] = {

      {A,B},  {B,C},  {C,D},  {D,E},  {E,G},  {G,H},  {H,A},
      
      {B,A},  {C,B},  {D,C},  {E,D},  {G,E},  {H,G},  {A,H},

      {A,C},  {B,D},  {C,E},  {D,G},  {E,H},  {G,A},  {H,B},
      
      {C,A},  {D,B},  {E,C},  {G,D},  {H,E},  {A,G},  {B,H},

      {A,D},  {B,E},  {C,G},  {D,H},  {E,A},  {G,B},  {H,C},
      
      {D,A},  {E,B},  {G,C},  {H,D},  {A,E},  {B,G},  {C,H}


};

void setup() {

   pinMode(A, INPUT);
   pinMode(B, INPUT);
   pinMode(C, INPUT);
   pinMode(D, INPUT);
   pinMode(E, INPUT);
   pinMode(G, INPUT);
   pinMode(H, INPUT);

   delay(1000);
}



void loop() {

  for(int i=0;i<42;i++){
    if(i == lit){
      light(lights[i]);
    }
  }
    
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    lit++;
    if(lit == 43){
      lit = 0;
    }
  }

}

void light( int pins[2] ){

  reset_pins();
    
  pinMode( pins[0], OUTPUT );
  digitalWrite( pins[0], HIGH );
  
  pinMode( pins[1], OUTPUT );
  digitalWrite( pins[1], LOW );
}

 
void reset_pins()
{
   pinMode(A, INPUT);
   pinMode(B, INPUT);
   pinMode(C, INPUT);
   pinMode(D, INPUT);
   pinMode(E, INPUT);
   pinMode(G, INPUT);
   pinMode(H, INPUT);
   digitalWrite(A, LOW);
   digitalWrite(B, LOW);
   digitalWrite(C, LOW);
   digitalWrite(D, LOW);
   digitalWrite(E, LOW);
   digitalWrite(G, LOW);
   digitalWrite(H, LOW);
   
}
