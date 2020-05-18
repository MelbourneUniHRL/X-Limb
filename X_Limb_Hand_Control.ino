/* This code is developed for control of six DC motors using the custom designed PCB (Arduino Mega compatible)  */
/* In the designed X-Limb hand only 5 motors are used for individual actuation of five fingers of the hand. */



#define STATUS_LED  53


//motors
#define ENABLE  38 // enable/disbale all motors

#define MOTOR_A 1
#define MOTOR_B 2
#define MOTOR_C 3
#define MOTOR_D 4
#define MOTOR_E 5
#define MOTOR_F 6

// Motor A Control
#define POTA    A3 // Potentiometer A
#define FBA     A0  // Current feedback for the motor A 
#define PWMA    7   // Speed control A
#define D2A     11  // enbale(HIGH)/disbale(LOW) for motor A
#define DIRA    12  // Directions for motor A
// Motor B Control
#define POTB    A2 // Potentiometer B
#define FBB     A1  // Current feedback for the motor B 
#define PWMB    4   // Speed control B
#define D2B     8   // enbale(HIGH)/disbale(LOW) for motor B
#define DIRB    9   // Directions for motor B
// Motor C Control
#define POTC    A7 // Potentiometer C
#define FBC     A13 // Current feedback for the motor C 
#define PWMC    5   // Speed control C
#define D2C     39  // enbale(HIGH)/disbale(LOW) for motor C
#define DIRC    29  // Directions for motor C
// Motor D Control
#define POTD    A8 // Potentiometer D
#define FBD     A14 // Current feedback for the motor D 
#define PWMD    2   // Speed control D
#define D2D     25  // enbale(HIGH)/disbale(LOW) for motor D
#define DIRD    26  // Directions for motor D
// Motor E Control
#define POTE    A10 // Potentiometer E
#define FBE     A12 // Current feedback for the motor E
#define PWME    3   // Speed control E
#define D2E     37  // enbale(HIGH)/disbale(LOW) for motor E
#define DIRE    36  // Directions for motor E
// Motor F Control
#define POTF    A9 // Potentiometer F
#define FBF     A11 // Current feedback for the motor F
#define PWMF    6   // Speed control F
#define D2F     19  // enbale(HIGH)/disbale(LOW) for motor F
#define DIRF    18  // Directions for motor F

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);

  pinMode(STATUS_LED, OUTPUT);
  
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, LOW);    // Disable all motors
  
  pinMode(D2C, OUTPUT);
  pinMode(DIRC, OUTPUT);
  pinMode(FBC, INPUT);
  pinMode(PWMC, OUTPUT);  //  setPwmFrequency2560(PWMC, 1);
  
  // Enables
  pinMode(D2A, OUTPUT);
  pinMode(D2B, OUTPUT);
  pinMode(D2C, OUTPUT);
  pinMode(D2D, OUTPUT);
  pinMode(D2E, OUTPUT);
  pinMode(D2F, OUTPUT);

 // Enables value
  digitalWrite(D2A, HIGH);
  digitalWrite(D2B, HIGH);
  digitalWrite(D2C, HIGH);
  digitalWrite(D2D, HIGH);
  digitalWrite(D2E, HIGH);
  digitalWrite(D2F, HIGH);

  // Directions
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(DIRC, OUTPUT);
  pinMode(DIRD, OUTPUT);
  pinMode(DIRE, OUTPUT);
  pinMode(DIRF, OUTPUT);

  // Directions value
  digitalWrite(DIRA, HIGH);  
  digitalWrite(DIRB, LOW);  
  digitalWrite(DIRC, LOW);  
  digitalWrite(DIRD, HIGH);  
  digitalWrite(DIRE, HIGH);  
  digitalWrite(DIRF, LOW);  

  // PWM
  pinMode(PWMA, OUTPUT);  //  setPwmFrequency2560(PWMC, 1);
  pinMode(PWMB, OUTPUT);  //  setPwmFrequency2560(PWMC, 1);
  pinMode(PWMC, OUTPUT);  //  setPwmFrequency2560(PWMC, 1);
  pinMode(PWMD, OUTPUT);  //  setPwmFrequency2560(PWMC, 1);
  pinMode(PWME, OUTPUT);  //  setPwmFrequency2560(PWMC, 1);
  pinMode(PWMF, OUTPUT);  //  setPwmFrequency2560(PWMC, 1);

  // PWM value
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  analogWrite(PWMC, 0);
  analogWrite(PWMD, 0);
  analogWrite(PWME, 0);
  analogWrite(PWMF, 0);

  // Current feedback
  pinMode(FBA, INPUT);
  pinMode(FBB, INPUT);
  pinMode(FBC, INPUT);
  pinMode(FBD, INPUT);
  pinMode(FBE, INPUT);
  pinMode(FBF, INPUT);

  // Position feedback
  pinMode(POTA, INPUT);
  pinMode(POTB, INPUT);
  pinMode(POTC, INPUT);
  pinMode(POTD, INPUT);
  pinMode(POTE, INPUT);
  pinMode(POTF, INPUT);

  digitalWrite(ENABLE, HIGH); 
 
}

unsigned int CommandCloseOpen; // Closing/Opening the hand
unsigned int CommandGraspType;  // Switching to the desired grip

// Variables for potentiometer values
unsigned int PotA; 
unsigned int PotB; 
unsigned int PotC; 
unsigned int PotD; 
unsigned int PotE;  
unsigned int PotF;

// Variables for motor current values
unsigned int CurrentA;
unsigned int CurrentB;
unsigned int CurrentC;
unsigned int CurrentD;
unsigned int CurrentE;
unsigned int CurrentF;

// Variables for motors opening and closing speed
unsigned int speedA_Close=90; unsigned int speedA_Open=80; 
unsigned int speedB_Close=100; unsigned int speedB_Open=90; 
unsigned int speedC_Close=50; unsigned int speedC_Open=40;
unsigned int speedD_Close=0; unsigned int speedD_Open=0;
unsigned int speedE_Close=90; unsigned int speedE_Open=80; 
unsigned int speedF_Close=100; unsigned int speedF_Open=90;


// Zero motor speeds
//unsigned int speedA_Close=0; unsigned int speedA_Open=0; 
//unsigned int speedB_Close=100; unsigned int speedB_Open=90; 
//unsigned int speedC_Close=0; unsigned int speedC_Open=0;
//unsigned int speedD_Close=0; unsigned int speedD_Open=0;
//unsigned int speedE_Close=100; unsigned int speedE_Open=90; 
//unsigned int speedF_Close=0; unsigned int speedF_Open=0;

// Grasp type
unsigned int Type=1;
  
void loop() {



// Reading potentimeter values
   PotA = analogRead(A3);  Serial.print("  PotA: "); Serial.println(PotA);
   PotB = analogRead(A2);  Serial.print("  PotB: "); Serial.println(PotB);
   PotC = analogRead(A7);  Serial.print("  PotC: "); Serial.println(PotC);
 //  PotD = analogRead(A8);  Serial.print("  PotD: "); Serial.println(PotD);
   PotE = analogRead(A10);  Serial.print("  PotE: "); Serial.println(PotE);
   PotF = analogRead(A11);  Serial.print("PotF: "); Serial.println(PotF);

// Reading current values
//  CurrentA=analogRead(A0);  Serial.print("CurrentA: "); Serial.println(CurrentA);
//  CurrentB=analogRead(A1);  Serial.print("CurrentB: "); Serial.println(CurrentB);
//  CurrentC=analogRead(A13);  Serial.print("CurrentC: "); Serial.println(CurrentC);
//  CurrentD=analogRead(A14);  Serial.print("CurrentD: "); Serial.println(CurrentD);
//  CurrentE=analogRead(A12);  Serial.print("CurrentE: "); Serial.println(CurrentE);
//  CurrentF=analogRead(A11);  Serial.print("CurrentF: "); Serial.println(CurrentF);


  CommandCloseOpen = analogRead(A4);   
  CommandGraspType = analogRead(A5);   
   


   Serial.print("CommandCloseOpen: "); Serial.print(CommandCloseOpen);
   Serial.print("   CommandGraspType: "); Serial.print(CommandGraspType);


 if (CommandGraspType<100){ 
  delay(600);
    Type=Type+1;
    if (Type>3){
        Type=3;
    }
 }

  if (CommandGraspType>1000){ 
      delay(600);
    Type=Type-1;
    if (Type<1){
        Type=1;
    }
 }

  Serial.print("   GraspType: "); Serial.print(Type);


//Type=3;
//************* Pinch Grasp ****************//

if (Type==1) {

     PotA = analogRead(A3); PotB = analogRead(A2); PotC = analogRead(A7); PotE = analogRead(A10); PotF = analogRead(A11); 

//            Close Fingers

if (CommandCloseOpen<100){ 

  // Thumb
   if (PotE<750){
     digitalWrite(DIRE, HIGH); 
     analogWrite(PWME, map(speedE_Close, 0, 100, 0, 255));}
   else{
     analogWrite(PWME, map(0, 0, 100, 0, 255));}

// Index
     if (PotA<800){
       if (PotE>650){
       digitalWrite(DIRA, HIGH); 
       analogWrite(PWMA, map(speedA_Close, 0, 100, 0, 255));}}
     else{
       analogWrite(PWMA, map(0, 0, 100, 0, 255));}

      
     
     }
else if(CommandCloseOpen>1000){

    // Thumb
   if (PotE>250){
     if (POTA<200){
     digitalWrite(DIRE, LOW); 
     analogWrite(PWME, map(speedE_Open, 0, 100, 0, 255));}}
   else{
     analogWrite(PWME, map(0, 0, 100, 0, 255));}

// Index
     if (PotA>100){
       digitalWrite(DIRA, LOW); 
       analogWrite(PWMA, map(speedA_Open, 0, 100, 0, 255));}
     else{
       analogWrite(PWMA, map(0, 0, 100, 0, 255));}

       
     
     }
     
 else{
     analogWrite(PWMA, map(0, 0, 100, 0, 255));
     analogWrite(PWMB, map(0, 0, 100, 0, 255));
     analogWrite(PWMC, map(0, 0, 100, 0, 255));
     analogWrite(PWMD, map(0, 0, 100, 0, 255));
     analogWrite(PWME, map(0, 0, 100, 0, 255));
     analogWrite(PWMF, map(0, 0, 100, 0, 255));}

}



//************* Tripod Grasp ****************//

if (Type==2) {

     PotA = analogRead(A3); PotB = analogRead(A2); PotC = analogRead(A7); PotE = analogRead(A10); PotF = analogRead(A11); 

//            Close Fingers

if (CommandCloseOpen<100){ 

// Thumb
   if (PotE<800){
     digitalWrite(DIRE, HIGH); 
     analogWrite(PWME, map(speedE_Close, 0, 100, 0, 255));}
   else{
     analogWrite(PWME, map(0, 0, 100, 0, 255));}

// Index
     if (PotA<980){
       if (PotE>600){
       digitalWrite(DIRA, HIGH); 
       analogWrite(PWMA, map(speedA_Close, 0, 100, 0, 255));}}
     else{
       analogWrite(PWMA, map(0, 0, 100, 0, 255));}

// Middle
     if (PotB>500){
       if (PotE>600){
       digitalWrite(DIRB, LOW); 
       analogWrite(PWMB, map(speedB_Close, 0, 100, 0, 255));}}
     else{
       analogWrite(PWMB, map(0, 0, 100, 0, 255));}

       
// Ring
     if (PotF>400){
       digitalWrite(DIRF, LOW); 
       analogWrite(PWMF, map(speedF_Close, 0, 100, 0, 255));}
     else{
       analogWrite(PWMF, map(0, 0, 100, 0, 255));} 
       
// Little
     if (PotC>200){
       digitalWrite(DIRC, LOW); 
       analogWrite(PWMC, map(speedC_Close, 0, 100, 0, 255));}
     else{
       analogWrite(PWMC, map(0, 0, 100, 0, 255));}
     
     }
else if(CommandCloseOpen>1000){

// Thumb
   if (PotE>100){
     if (POTA<200){
     digitalWrite(DIRE, LOW); 
     analogWrite(PWME, map(speedE_Open, 0, 100, 0, 255));}}
   else{
     analogWrite(PWME, map(0, 0, 100, 0, 255));}

// Index
     if (PotA>150){
       digitalWrite(DIRA, LOW); 
       analogWrite(PWMA, map(speedA_Open, 0, 100, 0, 255));}
     else{
       analogWrite(PWMA, map(0, 0, 100, 0, 255));}

// Middle
     if (PotB<960){
       digitalWrite(DIRB, HIGH); 
       analogWrite(PWMB, map(speedB_Open, 0, 100, 0, 255));}
     else{
       analogWrite(PWMB, map(0, 0, 100, 0, 255));}       

// Ring
     if (PotF<980){
           if (POTA<200){
       digitalWrite(DIRF, HIGH); 
       analogWrite(PWMF, map(speedF_Open, 0, 100, 0, 255));}}
     else{
       analogWrite(PWMF, map(0, 0, 100, 0, 255));} 

// Little
     if (PotC<790){
           if (POTA<200){
       digitalWrite(DIRC, HIGH); 
       analogWrite(PWMC, map(speedC_Open, 0, 100, 0, 255));}}
     else{
       analogWrite(PWMC, map(0, 0, 100, 0, 255));} 
            
     }
 else{
     analogWrite(PWMA, map(0, 0, 100, 0, 255));
     analogWrite(PWMB, map(0, 0, 100, 0, 255));
     analogWrite(PWMC, map(0, 0, 100, 0, 255));
     analogWrite(PWMD, map(0, 0, 100, 0, 255));
     analogWrite(PWME, map(0, 0, 100, 0, 255));
     analogWrite(PWMF, map(0, 0, 100, 0, 255));}

}


//************* Power Grasp ****************//

if (Type==3) {

     PotA = analogRead(A3); PotB = analogRead(A2); PotC = analogRead(A7); PotE = analogRead(A10); PotF = analogRead(A11); 

//            Close Fingers

if (CommandCloseOpen<100){ 

  // Thumb
   if (PotE<750){
     digitalWrite(DIRE, HIGH); 
     analogWrite(PWME, map(speedE_Close, 0, 100, 0, 255));}
   else{
     analogWrite(PWME, map(0, 0, 100, 0, 255));}

// Index
     if (PotA<800){
       digitalWrite(DIRA, HIGH); 
       analogWrite(PWMA, map(speedA_Close, 0, 100, 0, 255));}
     else{
       analogWrite(PWMA, map(0, 0, 100, 0, 255));}

// Little
     if (PotC>200){
       digitalWrite(DIRC, LOW); 
       analogWrite(PWMC, map(speedC_Close, 0, 100, 0, 255));}
     else{
       analogWrite(PWMC, map(0, 0, 100, 0, 255));} 
              
// Middle
     if (PotB>100){
       digitalWrite(DIRB, LOW); 
       analogWrite(PWMB, map(speedB_Close, 0, 100, 0, 255));}
     else{
       analogWrite(PWMB, map(0, 0, 100, 0, 255));}

// Ring
     if (PotF>300){
       digitalWrite(DIRF, LOW); 
       analogWrite(PWMF, map(speedF_Close, 0, 100, 0, 255));}
     else{
       analogWrite(PWMF, map(0, 0, 100, 0, 255));} 
       

     }
     
else if(CommandCloseOpen>1000){

    // Thumb
   if (PotE>250){
     digitalWrite(DIRE, LOW); 
     analogWrite(PWME, map(speedE_Open, 0, 100, 0, 255));}
   else{
     analogWrite(PWME, map(0, 0, 100, 0, 255));}

// Index
     if (PotA>150){
       digitalWrite(DIRA, LOW); 
       analogWrite(PWMA, map(speedA_Open, 0, 100, 0, 255));}
     else{
       analogWrite(PWMA, map(0, 0, 100, 0, 255));}

// Little
     if (PotC<790){
       digitalWrite(DIRC, HIGH); 
       analogWrite(PWMC, map(speedC_Open, 0, 100, 0, 255));}
     else{
       analogWrite(PWMC, map(0, 0, 100, 0, 255));}
              
// Middle
     if (PotB<960){
       digitalWrite(DIRB, HIGH); 
       analogWrite(PWMB, map(speedB_Open, 0, 100, 0, 255));}
     else{
       analogWrite(PWMB, map(0, 0, 100, 0, 255));}  


// Ring
     if (PotF<980){
       digitalWrite(DIRF, HIGH); 
       analogWrite(PWMF, map(speedF_Open, 0, 100, 0, 255));}
     else{
       analogWrite(PWMF, map(0, 0, 100, 0, 255));} 

 
     
     }

 else{
     analogWrite(PWMA, map(0, 0, 100, 0, 255));
     analogWrite(PWMB, map(0, 0, 100, 0, 255));
     analogWrite(PWMC, map(0, 0, 100, 0, 255));
     analogWrite(PWMD, map(0, 0, 100, 0, 255));
     analogWrite(PWME, map(0, 0, 100, 0, 255));
     analogWrite(PWMF, map(0, 0, 100, 0, 255));}

}

} // void loop
