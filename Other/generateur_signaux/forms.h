char type = "square";
byte square_N[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b01010,
  0b11011,
  0b00000,
  0b00000
};
byte triangle_N[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b01000,
  0b10101,
  0b00010,
  0b00000
};
byte sinus_N[8] = {
  0b00000,
  0b00000,
  0b01000,
  0b10100,
  0b10101,
  0b00101,
  0b00010,
  0b00000
};
byte square_Y[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b10001,
  0b10101,
  0b00100,
  0b11111,
  0b11111
};
byte triangle_Y[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b10111,
  0b01010,
  0b11111,
  0b11111
};
byte sinus_Y[8] = {
  0b11111,
  0b11111,
  0b10111,
  0b01011,
  0b01010,
  0b11010,
  0b11101,
  0b11111
};

void test_change_signal() {
  if (digitalRead(2) == HIGH) {
    if (type == "square") {
      type = "triangle";
    }
    else if (type == "triangle") {
      type = "sinus";
    }
    else if (type == "sinus") {
      type = "square";
    }
  }
  delay(500);
}
