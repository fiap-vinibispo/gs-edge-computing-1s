#include <LiquidCrystal_I2C.h>

#define MAXIMUM_POTENTIOMETER_VALUE 1023.0
#define DEFAULT_VOLTAGE 5.0
#define SCALE_FACTOR_VOLTAGE 100.0
#define SCALE_FACTOR_CURRENT 10.0
#define PRIMARY_BUTTON_PIN 5
#define ACTION_BUTTON_LEFT_PIN 6
#define ACTION_BUTTON_RIGHT_PIN 3
#define DEFAULT_ENERGY_FEE 0.60
#define FEE_STEP 0.05

String currentPage = "ONBOARDING";
LiquidCrystal_I2C lcd(0x27, 20, 4);

float systemEnergyFee = DEFAULT_ENERGY_FEE;

void setup() {
  Serial.begin(9600);

  pinMode(PRIMARY_BUTTON_PIN, INPUT_PULLUP);
  pinMode(ACTION_BUTTON_LEFT_PIN, INPUT_PULLUP);
  pinMode(ACTION_BUTTON_RIGHT_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

}

void loop() {
  mainSystem();
  delay(2000);
}


float fromPotentiometer(float value, float scaleFactor) {
  return value / MAXIMUM_POTENTIOMETER_VALUE * DEFAULT_VOLTAGE * scaleFactor;
}

void mainSystem(){
  Serial.println("main system");
  Serial.println(currentPage);
  if(currentPage == "ONBOARDING"){
    systemOnboarding();
  }
  else if(currentPage == "SET_FEE"){
    setFee();
  }

  else if(currentPage == "FEE_MONITOR"){
    feeMonitor();
  }
}

void systemOnboarding(){
  Serial.println("system onboarding");

  lcd.setCursor(0,0);
  lcd.print("Descubra o seu");
  lcd.setCursor(0,1);
  lcd.print("Gasto com energia!");
  lcd.setCursor(0,3);
  lcd.print("[Iniciar]");

  boolean hasPressedPrimary = false;

  while(hasPressedPrimary == false){
    int primaryButtonAction = digitalRead(PRIMARY_BUTTON_PIN);

    if (primaryButtonAction == 0){
      Serial.println("GO TO SET COST");
      currentPage = "SET_FEE";
      Serial.println(currentPage);
      hasPressedPrimary = true;
    }
  }
}

void setFee(){
  lcd.clear();

  float energyFee = systemEnergyFee;

  lcd.setCursor(0,0);
  lcd.print("Defina a taxa");
  lcd.setCursor(0,1);
  lcd.print("de energia: ");
  

  lcd.setCursor(0,3);
  lcd.print("R$ ");
  lcd.print(energyFee);

  lcd.setCursor(10,3);
  lcd.print("[-]    [+]");



  boolean hasPressedPrimary = false;

  while(hasPressedPrimary == false){
    int primaryButtonAction = digitalRead(PRIMARY_BUTTON_PIN);
    int increaseFee = digitalRead(ACTION_BUTTON_LEFT_PIN);
    int decreaseFee = digitalRead(ACTION_BUTTON_RIGHT_PIN);

    if(primaryButtonAction == 0){   
      systemEnergyFee = energyFee;
      Serial.println("TAXA DEFINIDA: ");
      Serial.println(systemEnergyFee);
      currentPage = "FEE_MONITOR";
      hasPressedPrimary = true;
    }
    if(increaseFee == 0){
      Serial.println("INCREASE FEE");
      energyFee += FEE_STEP;
      updateFee(energyFee, false);
      delay(200);
    }

    if(decreaseFee == 0){
      Serial.println("DECREASE FEE");
      energyFee -= FEE_STEP;
      updateFee(energyFee, true);
      delay(200);
    }
  }
}

void updateFee(float newFee, boolean decreaseFee){
  
  if(decreaseFee){
      lcd.setCursor(10,3);
      lcd.print("       [+]");
      delay(50);
      lcd.setCursor(10,3);
      lcd.print("[-]    [+]");
  }

  else{
      lcd.setCursor(10,3);
      lcd.print("[-]       ");
      delay(50);
      lcd.setCursor(10,3);
      lcd.print("[-]    [+]");
  }
  
  lcd.setCursor(0,3);
  lcd.print("R$ ");
  lcd.print(newFee);
}

void feeMonitor(){
  lcd.clear();

  float power;
  boolean hasPressedPrimary = false;

  float prevCurrent = 0;
  float prevVoltage = 0;

  while(!hasPressedPrimary){
    int primaryButtonAction = digitalRead(PRIMARY_BUTTON_PIN);

    float currentInput = analogRead(A0);
    float voltageInput = analogRead(A2);

    float current = fromPotentiometer(currentInput, SCALE_FACTOR_CURRENT);
    float voltage = fromPotentiometer(voltageInput, SCALE_FACTOR_VOLTAGE);



    lcd.setCursor(0,0);
    lcd.print("W: ");

    if(prevCurrent != current || prevVoltage != voltage){
      power += current*voltage;
    }

    prevCurrent = current;
    prevVoltage = voltage;

    delay(200);

    lcd.print(power);
    lcd.setCursor(0,1);
    lcd.print("kW: ");
    lcd.print(power/1000);
    lcd.setCursor(0,2);
    lcd.print("R$");
    lcd.print(power/1000 * systemEnergyFee);

    if(primaryButtonAction == 0){
      currentPage = "SET_FEE";
      hasPressedPrimary = true;
    }
  }
}
