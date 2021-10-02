// C++ code
//


//-------------------------------------------//
//----------------I/O PORTS------------------//
//-------------------------------------------//


static int CD_Input_Ports[] = {2, 3, 4, 5, 6, 7, 8, 9};

#define Pot_Port A0


//-------------------------------------------//
//----------------VARIABLES------------------//
//-------------------------------------------//


int Pot_Reading = 0; 
int Pot_Output_Range_New = 0;


int Digit_Output_Array[1];
static int Num_into_Bits[4];
static int Num_into_Bits_2[4];


//-------------------------------------------//
//------------------SETUP--------------------//
//-------------------------------------------//


void setup()
{
  Serial.begin(9600);
  
  // INITIALIZE ALL OUTPUT PINS
  
  for (int i = 0; i < 9; i++)
    pinMode(CD_Input_Ports[i], OUTPUT);
    
  
  // INITIALIZE ALL INPUT PINS
  
  pinMode(Pot_Port, INPUT); 
  
}



//-------------------------------------------//
//----------------FUNCTIONS------------------//
//-------------------------------------------//



int extract_digits(int Analog_Output_Values) { // INPUT 2 DIGIT INTEGER TO RETURN AN ARRAY OF THEIR SEPERATE DIGITS
  
  int i = 0;
  int index = 0;
  int remainder;
  
  while (Analog_Output_Values > 0) { // loop until it has cycled through each digit of the number
    
    remainder = Analog_Output_Values%10;
    
    
    Digit_Output_Array[i] = remainder;
    i++;
    Serial.print(" digit: ");
    Serial.print(remainder);
    Serial.print(" -- ");
    
    Analog_Output_Values /= 10; // Go to next digit
    
    
  }
  
}

void* Int_to_Bits(int num_digit, bool Is_First) { // CONVERTS INTEGER INTO ITS 4 BIT COMPONENTS, AND RETURNS ARRAY
  
  
  // Made into 2 seperate cases to deal with if the integer was 1 digit only.
  
  if (Is_First == 0){
    
    for (int i = 0; i < 4; i++) // loop for all 4 outputs and place the corresponding bit to display number
      Num_into_Bits[i] = bitRead(num_digit, i);
  	
    
    return Num_into_Bits; // return Num_into_bits array
    
  } else {
    
    for (int i = 0; i < 4; i++) // same as first 'for' loop, but stored in Num_into_Bits_2 instead.
    	Num_into_Bits_2[i] = bitRead(num_digit, i);
  	
    
    return Num_into_Bits_2; // return Num_into_bits_2 array
    
  }
  
}


void Display_Seg_Num(int CD_Ports[4], int Bits_Stored[4], bool Is_First) { // WRITES INTO OUTPUT PORTS OF ARDUINO AND THEN CONVERTED BY THE cd4511 INTO THE 7 OUTPUTS 
  
  
  if (Is_First == 0){
    
    for (int i = 0; i < 4; i++) // Writes to the output ports the corresponding digits that have been converted to bits for first display.
    	digitalWrite(CD_Ports[i], Bits_Stored[i]);
    
    
  } else {
    
    for (int i = 4; i < 8; i++) // Writes to the output ports the corresponding digits that have been converted to bits for second display.
    	digitalWrite(CD_Ports[i], Bits_Stored[i]);
    
  }
  
}



//-------------------------------------------//
//-------------------Main--------------------//
//-------------------------------------------//



void loop() // Loop forever until end of program
{ 
  // Initially gathering data from analog input
  
  Pot_Reading = analogRead(Pot_Port); // Get value from analog input
  Pot_Output_Range_New = map(Pot_Reading, 0, 1023, 0, 99); // maps from 0 to 99
  
  Serial.println(Pot_Output_Range_New); // Print into the Serial Monitor
  
  extract_digits(Pot_Output_Range_New); // Extract the digits of Pot_Output_Range_New.
  
  
  if (Pot_Output_Range_New > 9) { // Check if analog mapping is a 2 digit number
    
  	Int_to_Bits(Digit_Output_Array[1], 0); // Turn first digit into its binary components
  
  	Display_Seg_Num(CD_Input_Ports, Num_into_Bits, 0); // Display first digit
  
  	Int_to_Bits(Digit_Output_Array[0], 1); // Turn second digit into its binary components
  
  	Display_Seg_Num(CD_Input_Ports, Num_into_Bits, 1); // Display second digit
    
  } else { // If it's only a 1 digit number (e.g. 3) then 
    
    	Int_to_Bits(Digit_Output_Array[0], 1); // Turn first digit into its binary components
  
  	Display_Seg_Num(CD_Input_Ports, Num_into_Bits, 1); // Display first digit
    
    	Digit_Output_Array[1] = 0; // Set digit to 0.
    
    	Int_to_Bits(Digit_Output_Array[1], 0); // bits 0000.
    
    	Display_Seg_Num(CD_Input_Ports, Num_into_Bits, 0); // Display second digit
    
  }
  
  
}

