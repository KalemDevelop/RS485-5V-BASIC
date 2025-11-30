// ===== Kalem-RS485-5V-Basic : Arduino SLAVE =====

#define RS485_SERIAL   Serial1      // Change to Serial if needed
#define RS485_DIR_PIN  2            // Connected to DIR (DE+RE)

void setTransmit()
{
  digitalWrite(RS485_DIR_PIN, HIGH);
}

void setReceive()
{
  digitalWrite(RS485_DIR_PIN, LOW);
}

void setup()
{
  pinMode(RS485_DIR_PIN, OUTPUT);
  setReceive();

  RS485_SERIAL.begin(9600);

  Serial.begin(115200);
  while (!Serial) { }

  Serial.println("RS485 Slave started");
}

void loop()
{
  if (RS485_SERIAL.available())
  {
    String line = RS485_SERIAL.readStringUntil('\n');
    line.trim();                     // remove \r, spaces

    if (line.length() == 0) return;

    Serial.print("Received: ");
    Serial.println(line);

    if (line == "PING")
    {
      sendPong();
    }
  }
}

void sendPong()
{
  setTransmit();
  RS485_SERIAL.print("PONG\n");
  RS485_SERIAL.flush();
  setReceive();

  Serial.println("Sent: PONG");
}
