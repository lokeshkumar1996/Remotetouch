
//------------ stepper motor pins--------------
#define EN 8

//Direction pin
#define X_DIR_PIN 5

//Step pin
#define X_STP_PIN 2

//Direction pin
#define Y_DIR_PIN 6

//Step pin
#define Y_STP_PIN 3

#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])

//-----------------------------------------------------

//------------ server and wifi settings----------------

String esp_data;

//------------------------------------------------------

//------------- Variables ----------------------------
//A4988
int delayTime = 2000;
int stps_per_mm =5;//(1mm = 5 steps)


//Old position
float X_OLD = 0;
float Y_OLD = 0;

//New position
float X_NEW = 0;
float Y_NEW = 0;

//direciton
bool X_DIR = true;  //true clockwise, false anticlockwise
bool Y_DIR = true;  //true clockwise, false anticlockwise

//Calculated change/difference in possiiton
float X_CHANGE = 0;
float Y_CHANGE = 0;

//calcuate slope
int m = 1;
int limit = 0;

//---------------------------check running-----------------
bool motor_ran = true;
bool completed = false;
//------------------------------------------------------

//---------------------------input cordinates-----------------
//char *Cordinates[]= {"1.00,-2.00","5.00,-2.00","7.00,-2.00"}; 
String Cordinates[]= {"1.00,-2.00","5.00,-2.00","7.00,-2.00"}; 
int memorylimit = 5;
String Input_Cordinates[10]; 
int input_cordinate_count = 0;
bool Memoryfull = false;
//------------------------------------------------------------

void setup() 
{
  //----------Motor setup ------------
  pinMode(X_DIR_PIN, OUTPUT); 
  pinMode(X_STP_PIN,OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN,LOW);

  pinMode(Y_DIR_PIN, OUTPUT); 
  pinMode(Y_STP_PIN,OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN,LOW);

//---------------------------------------
  
  Serial.begin(115200);

  //step_right();
  //step_left();
  //step_up();
  //step_down();
  //allstep(true, true); //change values of true false accordingly to move up down righ left

}

void loop() 
{

  //-------------------- function to get messages and put in memeory string[] ----------------
  if(Serial.available() && !Memoryfull)
    {
       esp_data = Serial.readStringUntil('\n');
       
        Serial.println("data from esp: " + esp_data);
        
        
        if(input_cordinate_count <= memorylimit)
        {           
          Input_Cordinates[input_cordinate_count] = esp_data;
          Serial.println();
           Serial.print(" memory count: ");
           Serial.print(input_cordinate_count);
          input_cordinate_count += 1;
          Serial.println("data saved in memory: " + esp_data);
         
        }
        
        if( input_cordinate_count == memorylimit)
        {
          Memoryfull = true;
        }               
        
    }  
    
  //----------------------------------------------------------------

  //-------------------- function to execute message from memory string[] ----------------
  
  
   if(completed == false && Memoryfull == true)
   {      
      Serial.print(ARRAY_SIZE(Input_Cordinates));
      Serial.println();
      
      for (int i=0; i < memorylimit; i++)
         {
            if(motor_ran == true)
            {
              //motor_ran = false;
              Serial.print(Input_Cordinates[i]);
              Serial.println();
              getinput(Input_Cordinates[i]);
            }
         }
         
         completed = true;
    }

    
        
  //----------------------------------------------------------------
  
}

void getinput(String data)
{
        String X_message;
        String Y_message;
        bool Yflag = false;
        
        for (int i=0; i < data.length(); i++)
        { 
            if(data[i]== ',')
            {
              Yflag = true;
              continue;
            }

            if(!Yflag)
            {
              X_message = X_message + data[i];
            }
            else
            {
              Y_message = Y_message + data[i];
            }    
         }

          Serial.print("Cordinates: ");
          Serial.print(X_message);
          Serial.print(" and ");
          Serial.print(Y_message);
          
          Calculation(X_message.toFloat(),Y_message.toFloat());
          
          Serial.println();
          Serial.println("-----------------------");      
}


void Calculation(float X, float Y)
{
  
 X_OLD = X_NEW;
 Y_OLD = Y_NEW;
  
 X_NEW = X;
 Y_NEW = Y;

 X_CHANGE = X_NEW - X_OLD;
 Y_CHANGE = Y_NEW - Y_OLD; 


 Serial.print("  X_CHANGE : ");
 Serial.print(X_CHANGE);
 Serial.print("Y_CHANGE : ");
 Serial.print(Y_CHANGE);
  
//-------------------calculate slope and limit------------
 if(abs(X_CHANGE) > abs(Y_CHANGE))
 {
   m = round(abs(X_CHANGE) / abs(Y_CHANGE));
   limit = abs(X_CHANGE) * 10;

   Serial.println();
   Serial.print(" X > Y ");
   Serial.println();
   Serial.print("  M valeu: ");
   Serial.print(m);
   Serial.print("  imit: ");
   Serial.print(limit);
   Serial.println();
    
     for(int i=0; i<=limit; i++)
     {   
      
       if( X_CHANGE >= 0)
       {
        step_right();
       }
      
       if( X_CHANGE < 0)
       {
        step_left();
       }
  
       if(i%m == 0)
       {
           if( Y_CHANGE >= 0)
           {
            step_up();
           }
          
           if( Y_CHANGE < 0)
           {
            step_down();
           }
       }
    }
    motor_ran = true;
 }
 else if(abs(X_CHANGE) < abs(Y_CHANGE))
 {
   m = round(abs(Y_CHANGE) / abs(X_CHANGE));
   limit = abs(Y_CHANGE) * 10;

   Serial.println();
   Serial.print(" X < Y ");
   Serial.println();
   Serial.print("  M valeu: ");
   Serial.print(m);
   Serial.print("  imit: ");
   Serial.print(limit);
   Serial.println();
   
   for(int i=0; i<=limit; i++)
     {   
        if( Y_CHANGE >= 0)
           {
            step_up();
           }
          
           if( Y_CHANGE < 0)
           {
            step_down();
           }
  
       if(i%m == 0)
       {
           
           if( X_CHANGE >= 0)
           {
            step_right();
           }
          
           if( X_CHANGE < 0)
           {
            step_left();
           }
       }
     }
     motor_ran = true;
   
 }
 else
 {
   m=1;
   limit = abs(X_CHANGE) *10;

    Serial.println();
   Serial.print(" X = Y ");
   Serial.println();
   Serial.print("  M valeu: ");
   Serial.print(m);
   Serial.print("  imit: ");
   Serial.print(limit);
   Serial.println();
   
    for(int i=0; i<limit; i++)
     {   
        if( Y_CHANGE >= 0)
           {
            step_up();
           }
          
           if( Y_CHANGE < 0)
           {
            step_down();
           }
           
           if( X_CHANGE >= 0)
           {
            step_right();
           }
          
           if( X_CHANGE < 0)
           {
            step_left();
           }
      
     }
     motor_ran = true;
 }
//--------------------------------------------------------
 
  
  

  

}



/*
//-------------------- function to move ----------------

void allstep(boolean X_direction, boolean Y_direction)
{
  digitalWrite(X_DIR_PIN, X_DIR);
  digitalWrite(Y_DIR_PIN, Y_DIR);    
  delay(10);
  
  for (int i = 0; i< stps_per_mm; i++)
  {
    digitalWrite(Y_STP_PIN, HIGH);
    digitalWrite(X_STP_PIN, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(Y_STP_PIN, LOW);
    digitalWrite(X_STP_PIN, LOW);
    delayMicroseconds(delayTime);
  }
}

//----------------------------------------------------------------


//-------------------- function to move horizontally right ----------------

void step_right()
{
  digitalWrite(Y_DIR_PIN, false);
  digitalWrite(X_DIR_PIN, false);
  delay(10);
  for (int i = 0; i< stps_per_mm; i++)
  {
    digitalWrite(Y_STP_PIN, HIGH);
    digitalWrite(X_STP_PIN, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(Y_STP_PIN, LOW);
    digitalWrite(X_STP_PIN, LOW);
    delayMicroseconds(delayTime);
  }
}

//----------------------------------------------------------------

//-------------------- function to move horizontally left ----------------

void step_left()
{
  digitalWrite(Y_DIR_PIN, true);
  digitalWrite(X_DIR_PIN, true);
  delay(10);
  for (int i = 0; i< stps_per_mm; i++)
  {
    digitalWrite(Y_STP_PIN, HIGH);
    digitalWrite(X_STP_PIN, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(Y_STP_PIN, LOW);
    digitalWrite(X_STP_PIN, LOW);
    delayMicroseconds(delayTime);
  }
}

//----------------------------------------------------------------

//-------------------- function to move vertical up----------------

void step_up()
{
  digitalWrite(Y_DIR_PIN, true);
  digitalWrite(X_DIR_PIN, false);
  delay(10);
  for (int i = 0; i< stps_per_mm; i++)
  {
    digitalWrite(Y_STP_PIN, HIGH);
    digitalWrite(X_STP_PIN, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(Y_STP_PIN, LOW);
    digitalWrite(X_STP_PIN, LOW);
    delayMicroseconds(delayTime);
  }
}

//----------------------------------------------------------------

//-------------------- function to move vertical down ----------------

void step_down()
{
  digitalWrite(Y_DIR_PIN, false);
  digitalWrite(X_DIR_PIN, true);
  delay(10);
  for (int i = 0; i< stps_per_mm; i++)
  {
    digitalWrite(Y_STP_PIN, HIGH);
    digitalWrite(X_STP_PIN, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(Y_STP_PIN, LOW);
    digitalWrite(X_STP_PIN, LOW);
    delayMicroseconds(delayTime);
  }
}

//----------------------------------------------------------------

*/

void step_right()
{
  Serial.print("moved right  ");
}

//----------------------------------------------------------------

//-------------------- function to move horizontally left ----------------

void step_left()
{
  Serial.print("moved left  ");
}

//----------------------------------------------------------------

//-------------------- function to move vertical up----------------

void step_up()
{
  Serial.print("moved up  ");
}

//----------------------------------------------------------------

//-------------------- function to move vertical down ----------------

void step_down()
{
  Serial.print("move down  ");
}
