// Title        : Attack.cpp
// Purpose      : Allows AI to attack an enemy bot
//

#include "Attack.h"             
#include "staticmap.h"            // For LineOfSight()
#include "dynamicObjects.h"       // For GetBot() MAYBE NOT NEEDED


// Initialise pInstance as nullptr
Attack* Attack::pInstance = nullptr;


Attack::Attack()
{
  sprintf_s(name, "Attacking");
} // Attack()


Attack* Attack::GetInstance()
{ // Returns the instance of the class, if none currently exists create one

  if (!pInstance)
    pInstance = new Attack;

  return pInstance;

} // GetInstance()


void Attack::Enter(Bot* pBot)
{ // Sets behaviours for the attack state

  // Turn on Pursue and avoid walls
  pBot->SetBehaviours(0, 0, 1, 0, 0, 1, 0);

} // Enter()


void Attack::Execute(Bot* pBot)
{ // Checks for line of sight to enemy bot, if so switches behaviours. If close
  // enough, aims at bot and fires is accuracy check passes

  if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), 
    DynamicObjects::GetInstance()->GetBot(1, pBot->botTarget).GetLocation()))
  { // If LineOfSight, adjust behaviours and do distance check

    // Turn on arrive and avoid walls
    pBot->SetBehaviours(0, 1, 0, 0, 0, 1, 0);

    if ((pBot->GetLocation() - DynamicObjects::GetInstance()->GetBot(1, pBot->botTarget).GetLocation()).magnitude() <= 300)
    { // Check if distance is below set amount, if so start aiming and check
      // accuracy

      if (pBot->GetTargetTeam() == 1)
      { // Tells the bot to start aiming at target if not already

        pBot->SetTarget(1,pBot->botTarget);
      }

      // If accuracy is above set amount, shoot at enemy
      if (pBot->GetAccuracy() >= 0.8)
        pBot->Shoot();

    } // if magnitude()

  } // if LineOfSight()

} // Execute()


void Attack::Exit(Bot* pBot)
{ // Tidies up after the state activity is completed

} // Exit()


char* Attack::GetStateName()
{
  return name;
}


void Attack::Release()
{ // If called while pInstance is valid, deletes and defines as nullptr

  if (pInstance)
  {
    delete pInstance;
    pInstance = nullptr;
  }

} // Release()