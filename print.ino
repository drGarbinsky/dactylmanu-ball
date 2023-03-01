void printIntln(int msg) {
  if (LOG == true) {
    Serial.println(msg);
  }
}

void printInt(int msg) {
  if (LOG == true) {
    Serial.print(msg);
  }
}

void print(String msg) {
  if (LOG == true) {
    Serial.print(msg);
  }
}

void println(String msg) {
  if (LOG == true) {
    Serial.println(msg);
  }
}
void printBytes( byte* bytes, int length) {
  for (int i = 0; i < length; i++) {
    print(bytes[i]);
  }
  println("");
}
void printBits(byte data) {
  byte mask = 1;                            //our bitmask
  for (mask = 128; mask > 0; mask >>= 1) {  //iterate through bit mask
    if (data & mask) {                      // if bitwise AND resolves to true
      print("1");
    } else {  //if bitwise and resolves to false
      print("0");
    }
  }

  println("");
}