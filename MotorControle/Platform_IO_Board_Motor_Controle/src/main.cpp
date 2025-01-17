#ifndef UNIT_TEST

#include <Arduino.h>
#include <ArduinoJson.h>

#include "Comm/SerialComm.h"
#include "Comm/ControlMessage.h"
#include "Comm/MessageIO.h"
#include "StateManager.h"
#include "DriveManager.h"
#include "StepperJoin.h"


//#define BAUD 9600 
#define BAUD 115200 

#define NbrMotor 5
#define NbrMotorDynamixel 4
#define NbrMotorStepper 1
#define NbrMotor 1

MessageIO IO;
SerialComm SC(&Serial);
StateManager* statemanager;
DriveManager* drivemanager;


#define NUMERO_DU_TEST_A_EFFECTUER 0
// voici le liogne a modifier pour vous les gars pour vos tests
// 0 = le mode normal de la programation des moteurs
// 1 = un test unitaire sur le stepper motor qui marche
// 2 = un autre test unitaire sur le stepper motor qui marche aussi

void setup() 
{
  Serial.begin(BAUD);
  IO.addDevice(&SC);

if (NUMERO_DU_TEST_A_EFFECTUER == 0)
  {
  //Définitions des différents joins selon les moteurs!
    StepperJoin* join1 = new StepperJoin(0,228100,0,0,0);
    drivemanager = new DriveManager();
    drivemanager->addJoin(join1);

    StepperJoin* join2 = new StepperJoin(0,228100,0,0,0);
    drivemanager->addJoin(join2);

    statemanager = new StateManager(drivemanager);
  }
}

#define NUMERO_DU_TEST_A_EFFECTUER 1
// voici le liogne a modifier pour vous les gars pour vos tests
void loop() {

  if (NUMERO_DU_TEST_A_EFFECTUER == 0)
  {
    ControlMessage* msg = IO.readMessage(0);
      
    if(msg != 0)
    {
      statemanager->updateState(msg);

      ControlMessage responce(msg->getType()+1, msg->getPayLoadSize(), msg->getPayload());
      IO.sendMessage(0,responce);
      delete msg;
    }else
    {
      //auto responce = ControlMessage(-1);
      //IO.sendMessage(0,responce);
    }
  }
    // put your main code here, to run repeatedly:

  if (NUMERO_DU_TEST_A_EFFECTUER == 1)
  {
      // TEST #1
    delay(5000);
    Serial.println("Start test #1");

    DriveManager driveManager; 
    //StepperJoin stepperjoin(0,2810,3,0,0);
    StepperJoin* stepperjoin = new StepperJoin(0,28100,3,0,0);

    driveManager.addJoin(stepperjoin);
    //TestJoinDevice* testjoin = new TestJoinDevice(6000,281000,3,0,0);
    //driveManager.addJoin(testjoin);
    
    Serial.println("Initialisation complete, light ON");  
    delay(5000);

    Vector <int> array_position;
    array_position.add(2048);
    driveManager.goToPosition(array_position);
    Serial.println("Test end");

    delay(5000);
  }
  
  else if (NUMERO_DU_TEST_A_EFFECTUER == 2)
  {
    //TEST #2:
    delay(5000);
    Serial.println("Start test #2");

    StepperJoin stepperjoin(0,28800,42,0,0);
    delay(7000);
    Serial.println("Initialisation complete, light ON");  
    delay(5000);

    stepperjoin.goTo(1000);
  Serial.println("Test end");

    delay(5000);

  }

}

#endif