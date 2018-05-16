/*
 * Group Members:  Adrian Maceiras	
 									Shawn Gu
									Haley Goldlist
 */

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINES
#ifndef __DEFINE_INTERACTION_FUNCTIONS_CPP__
#define __DEFINE_INTERACTION_FUNCTIONS_CPP__

#include <iostream>
#include <string>
using namespace std;

#include "mapFunctions.cpp"
#include "playerFunctions.cpp"
#include "werewolfFunctions.cpp"
// DO NOT CHANGE OR REMOVE THE PRECEDING LINES

/*
 * KEYBOARD CONSTANTS
 */
const char KEYBOARD_UP    = 'w';
const char KEYBOARD_DOWN  = 's';
const char KEYBOARD_LEFT  = 'a';
const char KEYBOARD_RIGHT = 'd';
const char KEYBOARD_LOOK  = 'l';
const char KEYBOARD_TAKE  = 't';
const char KEYBOARD_USE   = 'u';
const char KEYBOARD_QUIT  = 'Q';
const char KEYBOARD_LOAD_GAME = 'L';
const char KEYBOARD_SAVE_GAME = 'S';
const char KEYBOARD_HELP = 'h';

/*
 * FUNCTION PROTOTYPES
 */
char readCharacterInput();
void doCommand(const char);
void doLook(const int, const int, const char);
void doTake(const int, const int, const char);
void doUse(const int, const int, const char);
void doLoadGame();
void doLoadGame(const char, const bool);
void doSaveGame();
void doLoadDefaultMap();
void doShowHelp();

string lastMessage = "";

char readCharacterInput()
{
	char input;
	bool inputIsValid = false;

	do
	{
		cin >> input;
		while(cin.get() != '\n');

		switch(input)
		{
			case KEYBOARD_UP:
			case KEYBOARD_DOWN:
			case KEYBOARD_LEFT:
			case KEYBOARD_RIGHT:
			case KEYBOARD_LOOK:
			case KEYBOARD_TAKE:
			case KEYBOARD_USE:
			case KEYBOARD_QUIT:
			case KEYBOARD_LOAD_GAME:
			case KEYBOARD_SAVE_GAME:
			case KEYBOARD_HELP:
				inputIsValid = true;
				break;
		}
		if (inputIsValid)
		{
			break;
		}

		cout << "Bad input. Try again." << endl;
	} while (!inputIsValid);

	return input;
}

void doCommand(const char command)
{
	switch(command)
	{
		case KEYBOARD_UP:
			playerSymbol = LOOKING_UP;
			if (isOpenSpace(playerX, playerY - 1))
			{
				playerY -= 1;
			}
			break;
		case KEYBOARD_DOWN:
			playerSymbol = LOOKING_DOWN;
			if (isOpenSpace(playerX, playerY + 1))
			{
				playerY += 1;
			}
			break;
		case KEYBOARD_LEFT:
			playerSymbol = LOOKING_LEFT;
			if (isOpenSpace(playerX - 1, playerY))
			{
				playerX -= 1;
			}
			break;
		case KEYBOARD_RIGHT:
			playerSymbol = LOOKING_RIGHT;
			if (isOpenSpace(playerX + 1, playerY))
			{
				playerX += 1;
			}
			break;
		case KEYBOARD_LOOK:
			doLook(playerX, playerY, playerSymbol);
			break;
		case KEYBOARD_TAKE:
			doTake(playerX, playerY, playerSymbol);
			break;
		case KEYBOARD_USE:
			doUse(playerX, playerY, playerSymbol);
			break;
		case KEYBOARD_LOAD_GAME:
		 //Prevent the Werewolf from moving
            skipWerewolfsTurn = true;  //ADDED BY ADRIAN CORRECT BY EREZ
			doLoadGame();
			break;
		case KEYBOARD_SAVE_GAME:
		 //Prevent the Werewolf from moving
            skipWerewolfsTurn = true;  //ADDED BY ADRIAN CORRECT BY EREZ
			doSaveGame();
			break;
		case KEYBOARD_HELP:
		 //Prevent the Werewolf from moving
            skipWerewolfsTurn = true;  //ADDED BY ADRIAN CORRECT BY EREZ
			doShowHelp();
			break;
	}
}

void doLook(const int x, const int y, const char lookingDirection)
{
    int itemX, itemY;
    getLookingAtLocation(x, y, playerSymbol, itemX, itemY); // EREZ: correct
	char mapSquare = getMapSquare(itemX, itemY);
	switch(mapSquare)
	{
		case MAP_SQUARE_CHASM:
			lastMessage = "The chasm in front of you is too wide to jump across. Perhaps there's another way across?";
			break;
		case MAP_SQUARE_EMPTY:
			lastMessage = "You see nothing of interest.";
			break;
		case MAP_SQUARE_KEY:
			lastMessage = "There is a shiny key on the ground. But what is it for?";
			break;
		case MAP_SQUARE_LOCK:
			lastMessage = "The door in front of you is locked.";
			break;
		case MAP_SQUARE_PEBBLE:
			lastMessage = "You see a large pebble on the ground. Stepping on it would hurt.";
			break;
		case MAP_SQUARE_PEBBLES:
			lastMessage = "You see two large pebbles on the ground. Stepping on them would hurt.";
			break;
		case MAP_SQUARE_PLANK:
			lastMessage = "There is a long plank of wood on the ground. You wonder how it got there.";
			break;
		case MAP_SQUARE_PLANK_SET:
			lastMessage = "The two sides of the chasm are bridged by a long plank of wood.";
			break;
		case MAP_SQUARE_ROPE:
			lastMessage = "Someone left a long stretch of rope just lying around. How irresponsible.";
			break;
		case MAP_SQUARE_ROPE_TIED:
			lastMessage = "A rope dangles above the chasm in front of you. You can just barely reach it.";
			break;
		case MAP_SQUARE_ROCK:
			lastMessage = "The rock wall in front of you is dusty with age. Try not to sneeze.";
			break;
		default:
			lastMessage = "You're not sure what it is. You've never seen anything like it before.";
	}
}

void doTake(const int x, const int y, const char lookingDirection)
{
	bool success = false;
	lastMessage = "There is nothing to take.";

//	int itemX = getLookingAtX(x, lookingDirection);
//	int itemY = getLookingAtY(y, lookingDirection);

    int itemX, itemY;
    getLookingAtLocation(x, y, playerSymbol, itemX, itemY); // EREZ: correct

	char mapSquare = getMapSquare(itemX, itemY);
	switch(mapSquare)
	{
		case MAP_SQUARE_KEY:
			lastMessage = "You pick up the key.";
			success = true;
			break;
		case MAP_SQUARE_PEBBLE:
			lastMessage = "You pick up a pebble.";
			success = true;
			break;
		case MAP_SQUARE_PEBBLES:
			lastMessage = "You pick up a couple pebbles.";
			success = true;
			break;
		case MAP_SQUARE_PLANK:
			lastMessage = "You pick up a plank of wood.";
			success = true;
			break;
		case MAP_SQUARE_ROPE:
			lastMessage = "You pick up a long rope.";
			success = true;
			break;
		case MAP_SQUARE_SLINGSHOT:
			lastMessage = "You pick up a slingshot.";
			success = true;
			break;
	}
	if (success)
	{
		inventoryAdd(mapSquare);
		clearMapSquare(itemX, itemY, mapSquare);
	}
}

void doUse(const int x, const int y, const char lookingDirection)
{
	char itemToUse;
	cout << endl << "What would you like to use? ";
	cin >> itemToUse;
	while(cin.get() != '\n');
	if (itemToUse == MAP_SQUARE_SLINGSHOT && inventoryHas(MAP_SQUARE_SLINGSHOT) && !inventoryHas(MAP_SQUARE_PEBBLE))
	{
		lastMessage = "Can't use the slingshot without some ammunition.";
		return;
	}
	else if (!inventoryHas(itemToUse))
	{
		lastMessage = "You don't have any.";
		return;
	}

	// start with default message
	lastMessage = "You can't use that here.";

//	int itemX = getLookingAtX(x, lookingDirection);
//	int itemY = getLookingAtY(y, lookingDirection);
    int itemX, itemY;
    getLookingAtLocation(x, y, playerSymbol, itemX, itemY); // EREZ: correct

	char mapSquare = getMapSquare(itemX, itemY);

	if (mapSquare == MAP_SQUARE_CHASM && itemToUse == MAP_SQUARE_PLANK)
	{
		inventoryUse(itemToUse);
		setMapSquare(itemX, itemY, mapSquare, MAP_SQUARE_PLANK_SET);
		lastMessage = "You lay the plank of wood over the chasm. It just barely touches both sides.";
	}
	else if (mapSquare == MAP_SQUARE_CHASM && itemToUse == MAP_SQUARE_ROPE)
	{
		inventoryUse(itemToUse);
		setMapSquare(itemX, itemY, mapSquare, MAP_SQUARE_ROPE_TIED);
		lastMessage = "Standing on the tips of your toes, you reach up and tie the rope to a beam above you.";
	}
	else if (mapSquare == MAP_SQUARE_LOCK && itemToUse == MAP_SQUARE_KEY)
	{
		inventoryUse(itemToUse);
		clearMapSquare(itemX, itemY, mapSquare);
		lastMessage = "You turn the key. Hard. Just as the lock opens you feel the key snap in half.";
	}
	else if (mapSquare == MAP_SQUARE_CHASM && itemToUse == MAP_SQUARE_PEBBLE)
	{
		inventoryUse(itemToUse);
		lastMessage = "You drop a pebble into the chasm, counting the seconds until it hits the bottom. You hear nothing.";
	}
	else if (mapSquare == MAP_SQUARE_CHASM && itemToUse == MAP_SQUARE_PEBBLE)
	{
		inventoryUse(itemToUse);
		lastMessage = "You drop a pebble into the chasm, counting the seconds until it hits the bottom. You hear nothing.";
	}
	else if (itemToUse == MAP_SQUARE_SLINGSHOT) //Fix the if statement so that the Boolean expression in the if statement is true if the player is looking at the werewolf AND the werewolf is within shooting range of the slingshot.
	{
        int actionableX, actionableY;
        getFarthestActionableLocation(SLINGSHOT_DISTANCE, false, actionableX, actionableY); // EREZ: no, there is no need for this here
		if (playerIsLookingAt(werewolfX, werewolfY) // EREZ: correct
			&& // EREZ: correct
			actionableX == werewolfX && actionableY == werewolfY ) // EREZ: no, read the instructions carefully Shawn: WITHIN shooting range can mean your actionable distance should be larger than and equal to the coordinate?
		{
			inventoryUse(MAP_SQUARE_PEBBLE);
			int damage = damage = 1 + rand() % SLINGSHOT_MAX_DAMAGE; // EREZ: correct
			doWerewolfHit(damage);

			string damageString = to_string(damage);

			lastMessage = "You hit the werewolf! ";
			if (werewolfIsAlive())
			{
				lastMessage += "He is temporarily stunned. The werewolf took ";
				lastMessage += damageString;
				lastMessage += (damage == 1 ? " point of damage." : " points of damage.");
			}
			else
			{
				lastMessage += "You have killed the werewolf.";
			}
		}
		else
		{
			int pebbleDestinationX, pebbleDestinationY;
			getFarthestActionableLocation(SLINGSHOT_DISTANCE, true, pebbleDestinationX, pebbleDestinationY);
			int distanceShot = manhattanDistance(playerX, playerY, pebbleDestinationX, pebbleDestinationY);
			if (distanceShot > 0)
			{
				string distanceShotString = to_string(distanceShot);

				inventoryUse(MAP_SQUARE_PEBBLE);
				setMapSquare(pebbleDestinationX, pebbleDestinationY, MAP_SQUARE_EMPTY, MAP_SQUARE_PEBBLE);
				lastMessage = "The pebble you shot lands ";
				lastMessage += distanceShotString;
				lastMessage += (distanceShot == 1 ? " square" : " squares");
				lastMessage += " away.";
			}
			else
			{
				lastMessage = "There is nothing to shoot your slingshot at.";
			}
		}
	}
}

void doCheckForPlayerDamage() // fixed EREZ: correct EXCEPT for your use of the number 4 below; see previous comment
{
    //Fix the first if statement at the top of the function. There's a hint in the comment. Also, the werewolf must still be alive in order to catch the player.
	if (werewolfIsAlive() && werewolfX == playerX && werewolfY == playerY ) // EREZ: correct
	{
        //Fix the code int damage = 0 /* MISSING CODE */; so that damage is a value between 1 and WEREWOLF_MAX_DAMAGE (inclusive).
		int damage = 1 + rand() % WEREWOLF_MAX_DAMAGE; // EREZ: correct
		doPlayerHit(damage);
        //Fix the second if statement in the function. Use a meaningful function call.
		if (playerIsAlive()) // EREZ: correct
		{
			bool werewolfRelocated = getRandomEmptyLocation(playerX, playerY, WEREWOLF_POST_DAMAGE_TELEPORT_DISTANCE, werewolfX, werewolfY);

			const int VERBS_COUNT = 4;
			const string VERBS[VERBS_COUNT] = { "scratched", "clawed", "kicked", "bitten" };
            //Fix the code string verbToUse = VERBS[0 /* MISSING CODE */]; so that it randomly selects one of VERBS_COUNT strings from the array VERBS.
			string verbToUse = VERBS[rand()%VERBS_COUNT]; // fixed EREZ: instead of the number 4, which constant should you be using?
			
			string damageString = to_string(damage);
            //Fix the code lastMessage += " of damage and has been teleported to a random location in the maze."; so that if the werewolf cannot be teleported elsewhere the player is notified.
			lastMessage = "You have been ";
			lastMessage += verbToUse;
			lastMessage += " by the werewolf. He dealt ";
			lastMessage += damageString;
			lastMessage += (damage == 1 ? " point" : " points");
			if (werewolfRelocated) // EREZ: correct
			{
				lastMessage += " of damage and has been teleported to a random location in the maze.";
			}
			else 
			{
				lastMessage += " of damage and has not been teleported.";
			}

		}
		else
		{
			lastMessage = "You have been killed by a werewolf.";
		}
	}
}

void doLoadGame()
{
	cout << endl << "Enter 0-9 to load a saved game. Enter any other visible character to cancel. Input: ";
	char slot;
	cin >> slot;
	doLoadGame(slot, false);
}

void doLoadGame(const char slot, const bool loadDefaultMapOnFailure)
{
	if (!isdigit(slot))
	{
		lastMessage = "Must enter 0-9 to load a saved game.";
		return;
	}

	string fileName = "gameSlot";
//	string fileName = "/Users/haley/c/haleytry/gameSlot";
	fileName += slot;
	fileName += ".txt";
	if (!loadGame(fileName))
	{
		lastMessage = "Could not load '";
		lastMessage += fileName;
		lastMessage += "'. File is corrupt or does not exist.";
		if (loadDefaultMapOnFailure)
		{
			lastMessage += " Loading default map.";
			doLoadDefaultMap();
		}
		return;
	}
	
	playerX = FILE_START_LOCATION_X;
	playerY = FILE_START_LOCATION_Y;
	playerSymbol = ((FILE_START_LOOKING_DIRECTION == LOOKING_UP ||
		FILE_START_LOOKING_DIRECTION == LOOKING_DOWN ||
		FILE_START_LOOKING_DIRECTION == LOOKING_LEFT ||
		FILE_START_LOOKING_DIRECTION == LOOKING_RIGHT) ? FILE_START_LOOKING_DIRECTION : LOOKING_UP);

	inventorySet(FILE_INVENTORY_ITEMS, FILE_INVENTORY_VALUES, FILE_INVENTORY_LENGTH);

	werewolfX = FILE_WEREWOLF_START_X; // EREZ: correct
	werewolfY = FILE_WEREWOLF_START_Y; // EREZ: correct
	werewolfHealth = FILE_WEREWOLF_START_HEALTH; // EREZ: correct
	werewolfStunnedCount = FILE_WEREWOLF_START_STUN_COUNT; // EREZ: correct

	lastMessage = "Loaded game ";
	lastMessage += slot;
	lastMessage += ".";
}

void doSaveGame()
{
	cout << endl << "Enter 0-9 to save the game in that slot. Enter any other visible character to cancel. Input: ";
	char slot;
	cin >> slot;
	if (!isdigit(slot))
	{
		lastMessage = "Must enter 0-9 to load a saved game.";
		return;
	}

	string fileName = "gameSlot";
	fileName += slot;
	fileName += ".txt";

	int numberOfItems = 0;
	char inventoryItems[INVENTORY_LENGTH];
	int inventoryValues[INVENTORY_LENGTH];
	for (int i = 0; i < INVENTORY_LENGTH; i++)
	{
		int itemCount = INVENTORY_ARRAY[i];
		if (itemCount > 0)
		{
			inventoryItems[numberOfItems] = convertInventoryIndexToItemChar(i);
			inventoryValues[numberOfItems] = itemCount;
			numberOfItems++;
		}
	}

	if (!saveGame(fileName, playerX, playerY, playerSymbol, inventoryItems, inventoryValues, numberOfItems, werewolfX, werewolfY, werewolfHealth, werewolfStunnedCount))
	{
		lastMessage = "Could not save '";
		lastMessage += fileName;
		lastMessage += "'. Data is corrupt or writing files is not allowed.";
		return;
	}

	lastMessage = "Saved game to slot ";
	lastMessage += slot;
	lastMessage += ".";
}

//In interactionFunctions.cpp in doLoadDefaultMap() add code to handle werewolf data.
void doLoadDefaultMap()
{
	loadDefaultMap();

	playerX = FILE_START_LOCATION_X;
	playerY = FILE_START_LOCATION_Y;
	playerSymbol = ((FILE_START_LOOKING_DIRECTION == LOOKING_UP ||
		FILE_START_LOOKING_DIRECTION == LOOKING_DOWN ||
		FILE_START_LOOKING_DIRECTION == LOOKING_LEFT ||
		FILE_START_LOOKING_DIRECTION == LOOKING_RIGHT) ? FILE_START_LOOKING_DIRECTION : LOOKING_UP);
    werewolfX = FILE_WEREWOLF_START_X;
    werewolfY = FILE_WEREWOLF_START_Y;
	werewolfHealth = FILE_WEREWOLF_START_HEALTH;
	werewolfStunnedCount = FILE_WEREWOLF_START_STUN_COUNT;

	inventorySet(FILE_INVENTORY_ITEMS, FILE_INVENTORY_VALUES, 0);
}

void doShowHelp()
{
	string tab = "   ";
	lastMessage = "Keyboard commands:\n"
		+ tab + KEYBOARD_UP			+ "  Go up.\n"
		+ tab + KEYBOARD_DOWN		+ "  Go down.\n"
		+ tab + KEYBOARD_LEFT		+ "  Go left.\n"
		+ tab + KEYBOARD_RIGHT		+ "  Go right.\n"
		+ tab + KEYBOARD_LOOK		+ "  Look.\n"
		+ tab + KEYBOARD_TAKE		+ "  Take item.\n"
		+ tab + KEYBOARD_USE		+ "  Use item.\n"
		+ tab + KEYBOARD_QUIT		+ "  Quit game.\n"
		+ tab + KEYBOARD_LOAD_GAME	+ "  Load game.\n"
		+ tab + KEYBOARD_SAVE_GAME	+ "  Save game.\n"
		+ tab + KEYBOARD_HELP		+ "  Display this menu.";
}

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINE
#endif
// DO NOT CHANGE OR REMOVE THE PRECEDING LINE
