// Title        : Capture.h
// Purpose      : Handles the bot being sent on a magical journey to capture DP
//

#pragma once


#include "State.h"  // For inheritance
#include "bot.h"    // For definition of bot type


class Capture : public State
{

private:
  static Capture* pInstance;  // Holds the instance of the class

  // Private constructor to avoid unauth access
  Capture();

public:
  // Returns the instance of the class, if none currently exists create one
  static Capture* GetInstance();

  // Sets behaviours for the capture state
  void Enter(Bot* pBot);

  // Checks to see if there is a lineofsight to a DP, if so switches behaviours
  // otherwise just continue following path
  void Execute(Bot* pBot);

  // Tidies up after the state activity has completed
  void Exit(Bot* pBot);

  // Calls GeneratePath to get a path to desired DP, then sets the bots path
  // to the generated path
  void GetPath(Bot* pBot);

  // Sets the DP target of the bot with the given parameter
  void SetTarget(Bot* pBot, DominationPoint* target);

  // If pInstance is valid, deletes the instance then defines al nullptr
  static void Release();

};
