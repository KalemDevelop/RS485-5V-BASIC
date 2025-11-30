// ===== Kalem-RS485-5V-Basic : Arduino MASTER =====

#define RS485_SERIAL   Serial1      // Change to Serial if your board has only one UART
#define RS485_DIR_PIN  2            // Connect to DIR (DE+RE) pin on module

void setTransmit()
{
  digitalWrite(RS485_DIR_PIN, HIGH);  // DIR=1 -> TRANSMIT (driver ON)
}

void setReceive()
{
  digitalWrite(RS485_DIR_PIN, LOW);   // DIR=0 -> RECEIVE (receiver ON)
}

void setup()
{
  pinMode(RS485_DIR_PIN, OUTPUT);
  setReceive();                      // start in receive mode

  RS485_SERIAL.begin(9600);

  Serial.begin(115200);              // USB debug (optional)
  while (!Serial) { }                // needed on some boards

  Serial.println("RS485 Master started");
}

void loop()
{
  sendPing();
  waitForPong();
  delay(1000);
}

void sendPing()
{
  setTransmit();
  RS485_SERIAL.print("PING\n");
  RS485_SERIAL.flush();              // wait until sent
  setReceive();

  Serial.println("Sent: PING");
}

void waitForPong()
{
  unsigned long start = millis();
  String line;

  while (millis() - start < 300)     // 300 ms timeout
  {
    while (RS485_SERIAL.available())
    {
      char c = RS485_SERIAL.read();
      if (c == '\n')                 // end of line
      {
        line.trim();                 // remove \r etc.
        if (line == "PONG")
          Serial.println("Got: PONG");
        else
          Serial.print("Got: "), Serial.println(line);

        return;
      }
      line += c;
    }
  }

  Serial.println("No reply");
}
