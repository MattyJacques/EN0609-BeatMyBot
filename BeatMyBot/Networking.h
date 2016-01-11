// Title        : Networking.h
// Purpose      : Gives network functionality to game


#pragma once

// For TEAMNUMS and MAXBOTS
#include "rules.h" 

// For threads
#include <Windows.h>
#include <process.h>

// For std::vectors
#include <vector>

// For all int types
#include <stdint.h>

// Doubt this port will be used by other apps
#define PORT 65534
#define IP "172.16.1.117"

// For degrees conversion
#define PI 3.141592

class DynamicObjects;
//#include "dynamicObjects.h"


class Networking
{
private:
  static Networking* pInstance;
  int sock;   // ID of the socket to use
  sockaddr_in servAddr;   // Holds address of server
  DWORD thread;       // Thread that waits for connection
  std::vector<sockaddr_in> clients; // Holds the clients to server

  // Holds the data on the bots to be passed across network
  struct BotData
  {
    int16_t xValue;   // X value of the bots position, shortened to 16 bit int
    int16_t yValue;   // Y value of the bots position, shortened to 16 bit int
    int16_t dir;     // Degrees used so int can be used with more effectiveness
    bool isAlive;     // If the bot is alive or not
  };

  // Holds the data on shots by the bots such as aiming and damage
  struct ShotData
  {
    int8_t team;        // Holds which team is shooting
    int8_t bot;         // Which bot is shooting
    int8_t damage;     // How much damage it caused, can't be negative
    bool firing;        // For m_bfiring
  };

  // Holds arrays of bots and the shots they are making
  struct TeamData
  {
    BotData bots[NUMBOTSPERTEAM];     // Array of info on bots
    ShotData shots[NUMBOTSPERTEAM];   // Array of info on shots
  };

  // Holds arrays of the teams, allows for any num of teams
  struct NetData
  {
    TeamData teams[NUMTEAMS]; // Holds bot and shots data
  };

  // When server is closed, tells clients to exit so they do not crash while
  // waiting to recieve
  void SendClientExit();

  // Converts radians to degrees
  uint16_t RadsToDegrees(double radians);

  // Private constructor for singleton
  Networking();

public:
  NetData data; // Holds the current data for the frame

  // Holds the initial data for the server to send to the client, this is only
  // done once to save sending scores and captures over.
  struct InitialData
  {
    double scoreUpdateTimer;
    int8_t dpStates[NUMDOMINATIONPOINTS];
    int16_t scores[NUMTEAMS];
  };

  // Is the server active
  static bool isActive;

  // Returns a pointer to the current instance of the class, if none currently
  // exists, create on then return that pointer
  static Networking* GetInstance();

  // Loads WSA, creates a socket, constructs address struct and then binds the
  // socket to the server address
  void SetupServer();

  // Initialises the client and attempts to connect to server asking to
  // retrieve the initial data the server would send
  void ConnectToServer();

  // Makes a new thread to check for clients
  void CreateThread();

  // Stores the client in the vector of clients
  void StoreClient(sockaddr_in address);

  // Sends data to all clients within the vector
  void Send();

  // Recieves the data from the server
  void Recieve();

  // If called while pInstance is valid, deletes and defines as nullptr
  static void Release();

};

