void setup() {
  Serial.begin(9600);

}

void loop() {
  int joystick_1_y_value = analogRead(A0);
  int joystick_2_x_value = analogRead(A1);
  int vals[2] = {0,0};

  if (joystick_1_y_value > 510){
    vals[0] = map(joystick_1_y_value,510,802,0,255);
  }
  else if (joystick_1_y_value < 500){
    vals[0] = -1*map(joystick_1_y_value,500,210,0,255);
  }

  if (joystick_2_x_value > 525){
    vals[1] = map(joystick_2_x_value,525,750,0,255);
  }
  else if (joystick_2_x_value < 515){
    vals[1] = -1*map(joystick_2_x_value,515,295,0,255);
  }

  Serial.print(vals[0]);
  Serial.print(",");
  Serial.println(vals[1]);
  delay(50);

}
