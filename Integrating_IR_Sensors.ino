int ir1 = 12;          //connect IR sensor-1 to arduino pin 12
int ir2 = 14;          //connect IR sensor-2 to arduino pin 14
int ir3 = 27;          //connect IR sensor-3 to arduino pin 27
int ir4 = 26;          //connect IR sensor-4 to arduino pin 26
void setup() {
  // put your setup code here, to run once:
  pinMode(ir1, INPUT);    //IR sensor-1 pin INPUT
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  Serial.begin(9600);    //Init Serila at 9600 baud rate

}

void loop() 
{
  // put your main code here, to run repeatedly:
  int data1 = digitalRead(ir1);  //read and store the input pin 
  int data2 = digitalRead(ir2);
  int data3 = digitalRead(ir3);
  int data4 = digitalRead(ir4);
  Serial.print(data1);   //print the output of IR sensor-1 on serial monitor window
  Serial.print(", ");
  Serial.print(data2);
  Serial.print(", ");
  Serial.print(data3);
  Serial.print(", ");
  Serial.println(data4);
}
