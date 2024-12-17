#define MOTOR1_PIN 5
#define MOTOR2_PIN 18
#define MOTOR3_PIN 19
#define MOTOR4_PIN 23

#define MOTOR1_STARTING 184
#define MOTOR2_STARTING 185//()
#define MOTOR3_STARTING 191
#define MOTOR4_STARTING 194

// if need to move anticlockwise, it will start after +2 pulse
// if need to move anticlockwise, it will start after -5 pulse

//No 4 = 189-192
//No 3 = 186
//No 2 = 186
//No 1 = 190  or 48639(16bits)


int motor1_pwm_channel = 2;
int motor2_pwm_channel = 1;
int motor3_pwm_channel = 2;
int motor4_pwm_channel = 3;


int frequency = 500;
int resolution = 8; //max is 255
// int resolution = 16; //max is 65535

int pulse_M[4];

char input;

int speed_count = 0;

void setup() {
  Serial.begin(115200); // initialize serial communication

  ledcSetup(motor1_pwm_channel,frequency,resolution);
  ledcSetup(motor2_pwm_channel,frequency,resolution);
  ledcSetup(motor3_pwm_channel,frequency,resolution);
  ledcSetup(motor4_pwm_channel,frequency,resolution);

  ledcAttachPin(MOTOR1_PIN,motor1_pwm_channel);
  ledcAttachPin(MOTOR2_PIN,motor2_pwm_channel);
  ledcAttachPin(MOTOR3_PIN,motor3_pwm_channel);
  ledcAttachPin(MOTOR4_PIN,motor4_pwm_channel);

  pulse_M[0]=MOTOR1_STARTING;
  pulse_M[1]=MOTOR1_STARTING;
  pulse_M[2]=MOTOR1_STARTING;
  pulse_M[3]=MOTOR1_STARTING;

  // pulse = 48639;

  ledcWrite(motor1_pwm_channel,pulse_M[0]=MOTOR1_STARTING);
  ledcWrite(motor2_pwm_channel,pulse_M[1]=MOTOR2_STARTING);
  ledcWrite(motor3_pwm_channel,pulse_M[2]=MOTOR3_STARTING);
  ledcWrite(motor4_pwm_channel,pulse_M[3]=MOTOR4_STARTING);


}

void loop() {
  while (Serial.available() == 0) {
    // wait for user input
  }
  input = Serial.read(); // read user input

  // if(input == 'c')
  // {
  //   ledcWrite(motor_pwm_channel,pulse);
  //   Serial.print("Middle pulse");
  // }

  if(input == 'u')
  {
    speed_count += 1;
    for(int i = 0; i<4 ; i++)
    {
      pulse_M[0]  -= 1;
		  pulse_M[1]  -= 1;
		  pulse_M[2]  += 1;
		  pulse_M[3]  += 1;
      ledcWrite(i,pulse_M[i]);
  
    }
    Serial.println("Speed now: ");
    Serial.println(speed_count);
  }

  if(input == 'd')
  {
    speed_count -= 1;
    for(int i = 0; i<4 ; i++)
    {
     pulse_M[0]  -= -1;
		  pulse_M[1]  -= -1;
		  pulse_M[2]  += -1;
		  pulse_M[3]  += -1;
      ledcWrite(i,pulse_M[i]);
    }
    Serial.println("Speed now: ");
    Serial.println(speed_count);
  }
  if(input == 'o'){
        pulse_M[0] -= 2;
		    pulse_M[1] -= 2;
		    pulse_M[2] += 1;  
		    pulse_M[3] += 1;
         for(int i = 0; i<4 ; i++){
            ledcWrite(i,pulse_M[i]);
         }

  }

}
