
#include <SPI.h>
#include <ATM90E36.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

ATM90E36 eic(5);

void setup() {
  /* Initialize the serial port to host */
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.println("Start ATM90E36");
  /*Initialise the ATM90E36 + SPI port */
  eic.begin();
  delay(1000);
}



void loop() {

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.setTextSize(2);
  display.print("--Power--");
  
  /*Repeatedly fetch some values from the ATM90E36 */
  double voltageA, freqT, voltageB, voltageC, currentA, currentB, currentC, totalPower, powerFector, new_current, totalReactivePower, temp,
  currentN,activePowerA,activePowerB,activePowerC,reactivePowerA,reactivePowerB,reactivePowerC,apparentPowerA,apparentPowerB,apparentPowerC;
  double totalApparentPower,powerFactorA,powerFactorB,powerFactorC,phaseA,phaseB,phaseC,energyI,energyE;
  
  int sys0 = eic.GetSysStatus0();
  int sys1 = eic.GetSysStatus1();
  int en0 = eic.GetMeterStatus0();
  int en1 = eic.GetMeterStatus1();
  Serial.println("S0:0x" + String(sys0, HEX));
  delay(10);
  Serial.println("S1:0x" + String(sys1, HEX));
  delay(10);
  Serial.println("E0:0x" + String(en0, HEX));
  delay(10);
  Serial.println("E1:0x" + String(en1, HEX));

  //bool Error = eic.calibrationError();
  //Serial.print("Bool Error: ");
  //Serial.println(Error);

  energyI = eic.GetImportEnergy();
  Serial.print("ImportEnergy");
  Serial.println(energyI);

  energyE = eic.GetExportEnergy();
  Serial.print("ExportEnergy");
  Serial.println(energyE);
  

  voltageA=eic.GetLineVoltageA();
  display.setCursor(0,17);
  display.setTextSize(1);
  display.print("vA:");
  display.println(voltageA);
  Serial.println("VA:"+String(voltageA)+"V");
  
  voltageB=eic.GetLineVoltageB();
  display.setCursor(0,30);
  display.setTextSize(1);
  display.print("vB:");
  display.println(voltageB);
  Serial.println("VB:"+String(voltageB)+"V");
  
  voltageC=eic.GetLineVoltageC();
  display.setCursor(0,42);
  display.setTextSize(1);
  display.print("vC:");
  display.println(voltageC);
  Serial.println("VC:"+String(voltageC)+"V");
  delay(10);
  
  currentA = eic.GetLineCurrentA();
  Serial.println("IA:"+String(currentA)+"A");
  display.setCursor(60,17);
  display.setTextSize(1);
  display.print("iA:");
  display.println(currentA);
  
  currentB = eic.GetLineCurrentB();
  Serial.println("IB:"+String(currentB)+"A");
  display.setCursor(60,30);
  display.setTextSize(1);
  display.print("iB:");
  display.println(currentB);
  
  currentC = eic.GetLineCurrentC();
  Serial.println("IC:"+String(currentC)+"A");
  display.setCursor(60,42);
  display.setTextSize(1);
  display.print("iC:");
  display.println(currentC);
  delay(10);


  activePowerA = (voltageA * currentA * powerFactorA);
  Serial.println("Active Power A: " + String(activePowerA));
  activePowerB = (voltageB * currentB * powerFactorB);
  Serial.println("Active Power B: " + String(activePowerB));
  activePowerC = (voltageC * currentC * powerFactorC);
  Serial.println("Active Power C: " + String(activePowerC));
  totalPower = activePowerA + activePowerB + activePowerC;
  Serial.println("Active Power: " + String(totalPower));
  
  
  totalPower = eic.GetTotalActivePower();
  display.setCursor(0,54);
  display.setTextSize(1);
  display.print("tP:");
  display.println(totalPower);
  Serial.println("Active Power: " + String(totalPower));
  delay(10);

 

  powerFactorA = eic.GetPowerFactorA();
  //Serial.println("pf A : " + String(powerFactorA));
  powerFactorB = eic.GetPowerFactorB();
  //Serial.println("pf B : " + String(powerFactorB));
  powerFactorC = eic.GetPowerFactorC();
  //Serial.println("pf C : " + String(powerFactorC));
  powerFector = eic.GetTotalPowerFactor();
  //Serial.println("P.F. : " + String(powerFector));
  delay(10);

  temp = eic.GetTemperature();
  //Serial.println("Temprature: " + String(temp) + "'C");

  freqT = eic.GetFrequency();
  delay(10);
  display.setCursor(60,54);
  display.setTextSize(1);
  display.print("Fr:");
  display.println(freqT);
  //Serial.println("f; " + String(freqT) + "Hz");
  Serial.println(" ");
  display.display();
  delay(1000);
}
