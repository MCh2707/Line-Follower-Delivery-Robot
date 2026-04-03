int sensorPins[8] = {A0, A1, A2, A3, A4, A5, A6, A7};

int leftMotor = 5;
int rightMotor = 6;

int baseSpeed = 120;   
int maxSpeed = 200;

int sensorValues[8];

void setup() {
  for(int i = 0; i < 8; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  int position = 0;
  int sum = 0;


  for(int i = 0; i < 8; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);

    int value = map(sensorValues[i], 0, 1023, 0, 1000);

    position += value * i * 1000; 
    sum += value;
  }

  if(sum == 0) {
    analogWrite(leftMotor, 0);
    analogWrite(rightMotor, 0);
    return;
  }

  int linePosition = position / sum;

  int error = linePosition - 3500;

  int correction = error / 20;

  int leftSpeed = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;

  leftSpeed = constrain(leftSpeed, 0, maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, maxSpeed);

  analogWrite(leftMotor, leftSpeed);
  analogWrite(rightMotor, rightSpeed);

  Serial.println(linePosition);
}
