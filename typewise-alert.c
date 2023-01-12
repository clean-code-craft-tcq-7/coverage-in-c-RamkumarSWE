#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) 
{
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
  CoolingType coolingType, double temperatureInC) 
  {
  int lowerLimit = 0;
  int upperLimit = 0;
  upperLimit = cooling_type_setLimit(coolingType);
  
  return inferBreach(temperatureInC, 0, upperLimit); 
}

int cooling_type_setLimit(CoolingType coolingType)
{
    int upperLimit = (coolingType == PASSIVE_COOLING) ? 35 : ((coolingType == HI_ACTIVE_COOLING) ?  45 : 40 );
    return upperLimit;
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";

  if (breachType != NORMAL) {
     char* BreachType = (breachType == TOO_LOW) ? "low" : "high";
     printf("To: %s\n", recepient);
     printf("Hi, the temperature is too %s\n", BreachType);
   }
}