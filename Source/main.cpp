#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <sstream>
#include <string>

using namespace sf;
using namespace std;

/*
Funtions and Methods
*/

//Create a new game.
void newGame(Sprite &spritePlayer, float &playerHeight, int &playerColumn, int &playerHeldColour, int &playerHeldNum, bool &playerDeath, int &score, int bricksAnimationDelay, bool Death, bool bricksAreStatic, int &bubbleToTake, int &nextSpaceAvailable, bool &columnFull, int &popNum, bool &spiderComplete, bool &knownLocationAdjacent, float &timeRemaining, int &numShifts, float &timeToDescend, int &currentLevel, int numberOfRows,  int (&bubbleArray)[13][18], int defaultArray[13][18], bool (&knownArray)[13][18], bool &Game)
{
	// Make sure all variables are reset
	//Player
	spritePlayer.setPosition(641.0f, playerHeight);
	playerColumn = 0;
	playerHeight = 890.0f;
	playerHeldColour = 0;
	playerHeldNum = 0;
	playerDeath = false;
	score = 0;
	//Variables for the game
	bricksAnimationDelay = 0;
	Death = false;
	bricksAreStatic = false;
	//Variables for the array
	bubbleToTake = 0;
	nextSpaceAvailable = 0;
	columnFull = false;
	popNum = 0;
	spiderComplete = false;
	knownLocationAdjacent = false;
	//Variables for clock
	timeRemaining = 10.0f;
	numShifts = 0;
	timeToDescend = 10.0f;
	currentLevel = 0;
	//Set the arrays
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < numberOfRows; j++)
		{
			bubbleArray[i][j] = defaultArray[i][j];
			knownArray[i][j] = false;
		}
	}
	//Start the game
	Game = true;
}

//Find the lowest bubble in a column and return its position.
int findLowestBubble(int playerColumn, int bubbleArray[13][18])
{
	for (int i = 17; i >= 0; i--)
	{
		if (bubbleArray[playerColumn][i] > 0)
		{
			//The lowest bubble has been found
			return i;
		}
	}
	//The column is empty
	return -1;
}

//Place a bubble in the array
void placeBubble(int column, int row, int (&bubbleArray)[13][18], Sound place, int &playerHeldNum, int playerHeldColour)
{
	//Put the bubble Down
	bubbleArray[column][row] = playerHeldColour;
	std::cout << "Placing" << playerHeldColour << "In Location:" << column << " " << row << "\n";
	//Remove a bubble from inventory
	playerHeldNum--;
}

//If the timer is 0, shift the rows down and create a new one.
bool shift(bool &playerDeath, int numShifts, int numberOfRows, int &lastRowAdded, int(&bubbleArray)[13][18], int newRows[10][13], int &currentLevel, Text &levelText, float &timeToDescend, float &timeRemaining, float difficulty)
{
	//Shift
	for (int i = 0; i < 13; i++)
	{
		for (int j = numberOfRows - 1; j >= 0; j--)
		{
			bubbleArray[i][j] = bubbleArray[i][j - 1];
		}
	}
	//Create a new row
	srand((int)time(0));
	int newRow = (rand() % 10);
	if (newRow == lastRowAdded)
	{
		int newRow = (rand() % 10);
	}
	lastRowAdded = newRow;
	for (int i = 0; i < 13; i++)
	{
		bubbleArray[i][0] = newRows[newRow][i];
	}

	std::cout << "shifted " << numShifts << " times\n";
	// Has the player reached a new level?
	if (numShifts == 6) // Takeaway 2s from the time after 60s
	{
		// Set the level
		currentLevel++;
		std::stringstream ss;
		ss << "Level = " << currentLevel;
		levelText.setString(ss.str());
		// Change the time inbetween descents
		timeToDescend -= 2;
		// Output for debug
		std::cout << "Now level " << currentLevel << " and rows will descend every " << timeToDescend << "\n";
		//Add a special bubble
		srand((int)time(0));
		int newBubble = (rand() % 3);
		if (newBubble == 0)
		{
			bubbleArray[(rand() % 13)][0] = 6;
		}
		else if (newBubble == 1)
		{
			bubbleArray[(rand() % 13)][0] = 7;
		}
		else
		{
			bubbleArray[(rand() % 13)][0] = 8;
		}
		return true;
	}
	else if (numShifts == 12 * difficulty) // Takeaway 2 from the time after 120s
	{
		// Set the level
		currentLevel++;
		std::stringstream ss;
		ss << "Level = " << currentLevel;
		levelText.setString(ss.str());
		// Change the time inbetween descents
		timeToDescend -= 2;
		// Output for debug
		std::cout << "Now level " << currentLevel << " and rows will descend every " << timeToDescend << "\n";
		//Add a special bubble
		srand((int)time(0));
		int newBubble = (rand() % 3);
		if (newBubble == 0)
		{
			bubbleArray[(rand() % 13)][0] = 6;
		}
		else if (newBubble == 1)
		{
			bubbleArray[(rand() % 13)][0] = 7;
		}
		else
		{
			bubbleArray[(rand() % 13)][0] = 8;
		}
		return true;
	}
	else if (numShifts == 24 * difficulty)
	{
		// Set the level
		currentLevel++;
		std::stringstream ss;
		ss << "Level = " << currentLevel;
		levelText.setString(ss.str());
		// Change the time inbetween descents
		timeToDescend -= 1;
		// Output for debug
		std::cout << "Now level " << currentLevel << " and rows will descend every " << timeToDescend << "\n";
		//Add a special bubble
		srand((int)time(0));
		int newBubble = (rand() % 3);
		if (newBubble == 0)
		{
			bubbleArray[(rand() % 13)][0] = 6;
		}
		else if (newBubble == 1)
		{
			bubbleArray[(rand() % 13)][0] = 7;
		}
		else
		{
			bubbleArray[(rand() % 13)][0] = 8;
		}
		return true;
	}
	else if ((numShifts == 30 && difficulty == 1) || (numShifts == 26 && difficulty == 0.75))
	{
		// Set the level
		currentLevel++;
		std::stringstream ss;
		ss << "Level = " << currentLevel;
		levelText.setString(ss.str());
		// Change the time inbetween descents
		timeToDescend -= 1;
		// Output for debug
		std::cout << "Now level " << currentLevel << " and rows will descend every " << timeToDescend << "\n";
		//Add a special bubble
		srand((int)time(0));
		int newBubble = (rand() % 3);
		if (newBubble == 0)
		{
			bubbleArray[(rand() % 13)][0] = 6;
		}
		else if (newBubble == 1)
		{
			bubbleArray[(rand() % 13)][0] = 7;
		}
		else
		{
			bubbleArray[(rand() % 13)][0] = 8;
		}
		return true;
	}
	else if (numShifts == 36) //Player has reached the final level
	{
		currentLevel++;
		std::stringstream ss;
		ss << "Level = " << currentLevel;
		levelText.setString(ss.str());
		// Output for debug
		std::cout << "Now level " << currentLevel << " and rows will descend every " << timeToDescend << "\n";
		//Add a special bubble
		srand((int)time(0));
		int newBubble = (rand() % 3);
		if (newBubble == 0)
		{
			bubbleArray[(rand() % 13)][0] = 6;
		}
		else if (newBubble == 1)
		{
			bubbleArray[(rand() % 13)][0] = 7;
		}
		else
		{
			bubbleArray[(rand() % 13)][0] = 8;
		}
		return true;
	}
	else
	{
		//Output for debug
		std::cout << "Not time to level up.\n";
	}
	timeRemaining = timeToDescend;
	return false;
}

//Once bubbles have been popped, check the Array doesnt have any floating bubbles.
void removeFloatingBubbles(int (&bubbleArray)[13][18])
{
	bool needsSecondPass = false;
	//all hanging bubbles need to fall
	do
	{
		needsSecondPass = false;
		for (int column = 0; column < 13; column++)
		{
			for (int row = 0; row < 17; row++)
			{
				if (bubbleArray[column][row] == 0 && bubbleArray[column][row + 1] > 0)
				{
					std::cout << "Bubble Swapped" << column << " " << row << " and " << column << " " << row + 1 << "\n";
					std::swap(bubbleArray[column][row], bubbleArray[column][row + 1]);
					needsSecondPass = true;
				}
			}
		}
	} while (needsSecondPass);
}

// Main Loop
int main()
{
	//Variables for games
	bool Menu = true;
	bool Controls = false;
	bool DifficultySelect = false;
	bool Paused = false;
	bool Game = false;
	bool Death = false;

	/*
	Variables for the Menu
	*/

	//Mouse location variable
	Vector2i MouseCursorLocation(0, 0);

	//Background
	Texture textureMenuBackground;
	textureMenuBackground.loadFromFile("Assets/Backgrounds/MenuBackground.png");
	Sprite spriteMenuBackground;
	spriteMenuBackground.setTexture(textureMenuBackground);

	//Play Button
	Texture texturePlayButtonNeutral;
	texturePlayButtonNeutral.loadFromFile("Assets/Interface/Menu UI/Play Button/PlayButton.png");
	Texture texturePlayButtonSelected;
	texturePlayButtonSelected.loadFromFile("Assets/Interface/Menu UI/Play Button/PlayButtonSelected.png");
	Sprite spritePlayButton;
	spritePlayButton.setTexture(texturePlayButtonNeutral);
	spritePlayButton.setPosition(760, 154);

	//Resume Button
	Texture textureResumeButtonNeutral;
	textureResumeButtonNeutral.loadFromFile("Assets/Interface/Menu UI/Resume Button/ResumeButton.png");
	Texture textureResumeButtonSelected;
	textureResumeButtonSelected.loadFromFile("Assets/Interface/Menu UI/Resume Button/ResumeButtonSelected.png");
	Sprite spriteResumeButton;
	spriteResumeButton.setTexture(textureResumeButtonNeutral);
	spriteResumeButton.setPosition(760, 154);

	//Controls Button
	Texture textureControlsButtonNeutral;
	textureControlsButtonNeutral.loadFromFile("Assets/Interface/Menu UI/Controls Button/ControlsButton.png");
	Texture textureControlsButtonSelected;
	textureControlsButtonSelected.loadFromFile("Assets/Interface/Menu UI/Controls Button/ControlsButtonSelected.png");
	Sprite spriteControlsButton;
	spriteControlsButton.setTexture(textureControlsButtonNeutral);
	spriteControlsButton.setPosition(760, 463);

	//Exit Button
	Texture textureExitButtonNeutral;
	textureExitButtonNeutral.loadFromFile("Assets/Interface/Menu UI/Exit Button/ExitButton.png");
	Texture textureExitButtonSelected;
	textureExitButtonSelected.loadFromFile("Assets/Interface/Menu UI/Exit Button/ExitButtonSelected.png");
	Sprite spriteExitButton;
	spriteExitButton.setTexture(textureExitButtonNeutral);
	spriteExitButton.setPosition(760, 771);

	//Controls menu
	Texture textureControlsBackground;
	textureControlsBackground.loadFromFile("Assets/Backgrounds/ControlsBackground.png");
	Sprite spriteControlsBackground;
	spriteControlsBackground.setTexture(textureControlsBackground);

	//Back Button
	Texture textureBackButtonNeutral;
	textureBackButtonNeutral.loadFromFile("Assets/Interface/Menu UI/Back Button/BackButton.png");
	Texture textureBackButtonSelected;
	textureBackButtonSelected.loadFromFile("Assets/Interface/Menu UI/Back Button/BackButtonSelected.png");
	Sprite spriteBackButton;
	spriteBackButton.setTexture(textureBackButtonNeutral);
	spriteBackButton.setPosition(80, 80);

	//Easy Button
	Texture textureEasyButtonNeutral;
	textureEasyButtonNeutral.loadFromFile("Assets/Interface/Menu UI/Easy Button/EasyButton.png");
	Texture textureEasyButtonSelected;
	textureEasyButtonSelected.loadFromFile("Assets/Interface/Menu UI/Easy Button/EasyButtonSelected.png");
	Sprite spriteEasyButton;
	spriteEasyButton.setTexture(textureEasyButtonNeutral);

	//Hard Button
	Texture textureHardButtonNeutral;
	textureHardButtonNeutral.loadFromFile("Assets/Interface/Menu UI/Hard Button/HardButton.png");
	Texture textureHardButtonSelected;
	textureHardButtonSelected.loadFromFile("Assets/Interface/Menu UI/Hard Button/HardButtonSelected.png");
	Sprite spriteHardButton;
	spriteHardButton.setTexture(textureHardButtonNeutral);

	//Frenzy Button
	Texture textureFrenzyButtonNeutral;
	textureFrenzyButtonNeutral.loadFromFile("Assets/Interface/Menu UI/Frenzy Button/FrenzyButton.png");
	Texture textureFrenzyButtonSelected;
	textureFrenzyButtonSelected.loadFromFile("Assets/Interface/Menu UI/Frenzy Button/FrenzyButtonSelected.png");
	Sprite spriteFrenzyButton;
	spriteFrenzyButton.setTexture(textureFrenzyButtonNeutral);
	spriteFrenzyButton.setPosition(450.0f, 340.0f);
	bool frenzyButtonSelected;

	//Infinite Button
	Texture textureInfiniteButtonNeutral;
	textureInfiniteButtonNeutral.loadFromFile("Assets/Interface/Menu UI/Infinite Button/InfiniteButton.png");
	Texture textureInfiniteButtonSelected;
	textureInfiniteButtonSelected.loadFromFile("Assets/Interface/Menu UI/Infinite Button/InfiniteButtonSelected.png");
	Sprite spriteInfiniteButton;
	spriteInfiniteButton.setTexture(textureInfiniteButtonNeutral);
	spriteInfiniteButton.setPosition(1070.0f, 340.0f);
	bool infiniteButtonSelected;

	//Font
	Font font;
	font.loadFromFile("Fonts/font.ttf");

	//Score
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score = 0");
	scoreText.setFillColor(Color::Black);
	scoreText.setPosition(960, 20.0f);
	scoreText.setCharacterSize(48);

	//Added Score
	Text scoreAddedText;
	scoreAddedText.setFont(font);
	scoreAddedText.setString("+ 0!");
	scoreAddedText.setFillColor(Color::Black);
	scoreAddedText.setPosition(1160.0f, 60.0f);
	scoreAddedText.setCharacterSize(40);
	int scoreAdded = 0;
	int scoreAddedAnimationDelay = 0;

	//Level
	Text levelText;
	levelText.setFont(font);
	levelText.setString("Level = 0");
	levelText.setFillColor(Color::Black);
	levelText.setPosition(540.0f, 20.0f);
	levelText.setCharacterSize(48);

	//Frenzy timer
	Text frenzyTimerText;
	frenzyTimerText.setFont(font);
	frenzyTimerText.setString("0:00");
	frenzyTimerText.setFillColor(Color::Red);
	frenzyTimerText.setPosition(900, 1000);
	frenzyTimerText.setCharacterSize(72);
	float frenzyTime = 0.0f;
	int frenzySecondsLeft = 0;
	int frenzyMinutesLeft = 3;

	/*
	Variables for Gameplay
	*/

	// Creating object and fullscreen window
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Magical Drop II", Style::Fullscreen);
	
	//Create background sprite
	Texture textureBackground;
	textureBackground.loadFromFile("Assets/Backgrounds/background.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setOrigin(430, 540);
	spriteBackground.setPosition(960, 540);
	int verticalOffset = 115;

	//Create stage sprite
	Texture textureStage;
	textureStage.loadFromFile("Assets/Backgrounds/stage.png");
	Sprite spriteStage;
	spriteStage.setTexture(textureStage);
	spriteStage.setPosition(530, 0);

	//Create character sprite
	int playerColumn = 0;
	float playerHeight = 890.0f;
	int playerHeldColour = 0;
	int playerHeldNum = 0;
	bool playerDeath = false;
	bool deathNextShift = false;
	int score;
	float difficulty = 1; //Easy = 1, Hard = 0.75
	bool isFrenzyMode; //Frenzy = true, Infinite = false;
	Texture texturePlayer0;
	texturePlayer0.loadFromFile("Assets/Player/player.png");
	Texture texturePlayer1;
	texturePlayer1.loadFromFile("Assets/Player/player_holding_red.png");
	Texture texturePlayer2;
	texturePlayer2.loadFromFile("Assets/Player/player_holding_blue.png");
	Texture texturePlayer3;
	texturePlayer3.loadFromFile("Assets/Player/player_holding_green.png");
	Texture texturePlayer4;
	texturePlayer4.loadFromFile("Assets/Player/player_holding_gold.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer0);
	spritePlayer.setScale(0.49f, 0.49f);
	spritePlayer.setPosition(641.0f, playerHeight);
	
	//Create the bubble array, [column][row]
	int defaultArray[13][18] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},	{2,4,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0}, {3,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {4,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };
	int bubbleArray[13][18];
	//Variables for the array
	int bubbleToTake = 0;
	int nextSpaceAvailable = 0;
	bool columnFull = false;
	int popNum = 0;
	int popPosition;
	int lastPlaced = -1;
	int numberOfRows = 18;
	int popAnimationDelay = 0;
	bool popAnimationRunning = false;
	int lastRowAdded = 0;
	//Variables for the spider-pop
	bool knownArray[13][18];
	bool spiderComplete;
	bool knownLocationAdjacent;


	//Red (1)
	Texture textureBubbleRed;
	textureBubbleRed.loadFromFile("Assets/Bubbles/bubbleRed.png");
	Sprite spriteBubbleRed;
	spriteBubbleRed.setTexture(textureBubbleRed);
	//Blue (2)
	Texture textureBubbleBlue;
	textureBubbleBlue.loadFromFile("Assets/Bubbles/bubbleBlue.png");
	Sprite spriteBubbleBlue;
	spriteBubbleBlue.setTexture(textureBubbleBlue);
	//Green (3)
	Texture textureBubbleGreen;
	textureBubbleGreen.loadFromFile("Assets/Bubbles/bubbleGreen.png");
	Sprite spriteBubbleGreen;
	spriteBubbleGreen.setTexture(textureBubbleGreen);
	//Gold (4)
	Texture textureBubbleGold;
	textureBubbleGold.loadFromFile("Assets/Bubbles/bubbleGold.png");
	Sprite spriteBubbleGold;
	spriteBubbleGold.setTexture(textureBubbleGold);
	//Pop (5)
	Texture texturePop;
	texturePop.loadFromFile("Assets/Bubbles/pop.png");
	Sprite spritePop;
	spritePop.setTexture(texturePop);
	//Horizontal (6)
	Texture textureBubbleHorizontal;
	textureBubbleHorizontal.loadFromFile("Assets/Bubbles/bubbleHorizontal.png");
	Sprite spriteBubbleHorizontal;
	spriteBubbleHorizontal.setTexture(textureBubbleHorizontal);
	//Vertical (7)
	Texture textureBubbleVertical;
	textureBubbleVertical.loadFromFile("Assets/Bubbles/bubbleVertical.png");
	Sprite spriteBubbleVertical;
	spriteBubbleVertical.setTexture(textureBubbleVertical);
	//Cross (8)
	Texture textureBubbleCross;
	textureBubbleCross.loadFromFile("Assets/Bubbles/bubbleCross.png");
	Sprite spriteBubbleCross;
	spriteBubbleCross.setTexture(textureBubbleCross);

	//Bottom arrows
	Texture textureArrowFrame1;
	textureArrowFrame1.loadFromFile("Assets/Interface/Game UI/Arrow1Left.png");
	Texture textureArrowFrame2;
	textureArrowFrame2.loadFromFile("Assets/Interface/Game UI/Arrow2Left.png");
	Sprite spriteArrowLeft;
	spriteArrowLeft.setPosition(640.0f, playerHeight);
	Sprite spriteArrowRight;
	spriteArrowRight.setPosition(1270, playerHeight);
	spriteArrowRight.setScale(-1.0f, 1.0f);
	int arrowAnimationNum = 0;

	//Pointer arrow
	Texture textureColumnPointer;
	textureColumnPointer.loadFromFile("Assets/Interface/Game UI/ColumnPointer.png");
	Sprite spriteColumnPointer;
	spriteColumnPointer.setTexture(textureColumnPointer);
	spriteColumnPointer.setOrigin(10.0f, 5.5f);
	spriteColumnPointer.setPosition(655 + (playerColumn * 49) + 10.0f, ((findLowestBubble(playerColumn, bubbleArray) * 49) + 164) + 5.5f);
	int columnPointerAnimationPosition = -2;
	int columnPointerAnimationDelay = 0;
	
	//Only one movement for each key press
	bool allowKeyPress = true;

	//Sound effects
	//Click
	SoundBuffer clickBuffer;
	clickBuffer.loadFromFile("Audio/Click.wav");
	Sound click;
	click.setBuffer(clickBuffer);
	//Place
	SoundBuffer placeBuffer;
	placeBuffer.loadFromFile("Audio/place.wav");
	Sound place;
	place.setBuffer(placeBuffer);
	//Pop
	SoundBuffer popBuffer;
	popBuffer.loadFromFile("Audio/pop.wav");
	Sound pop;
	pop.setBuffer(popBuffer);
	//pickup
	SoundBuffer pickupBuffer;
	pickupBuffer.loadFromFile("Audio/pickup.wav");
	Sound pickup;
	pickup.setBuffer(pickupBuffer);
	//Cannot pickup
	SoundBuffer cantPickupBuffer;
	cantPickupBuffer.loadFromFile("Audio/errorPickup.wav");
	Sound cantpickup;
	cantpickup.setBuffer(cantPickupBuffer);
	bool playCantPickup = true;
	//Tunnel
	SoundBuffer wooshBuffer;
	wooshBuffer.loadFromFile("Audio/tunnel.wav");
	Sound woosh;
	woosh.setBuffer(wooshBuffer);
	//Level Up
	SoundBuffer lvlUpBuffer;
	lvlUpBuffer.loadFromFile("Audio/levelUp.wav");
	Sound lvlUp;
	lvlUp.setBuffer(lvlUpBuffer);

	//Music
	//Menu background track
	Music menuMusic;
	menuMusic.openFromFile("Audio/menuMusic.ogg");
	menuMusic.play();
	menuMusic.setLoop(true);
	cout << menuMusic.getStatus();
	//Game
	Music gameMusic;
	gameMusic.openFromFile("Audio/gameMusic.ogg");
	gameMusic.setLoop(true);
	
	//Time, for the descending rows
	Clock bubbleClock;
	float timeRemaining = 10.0f;
	float timeToDescend = 10.0f;
	int currentLevel = 0;
	int numShifts = 0;
	int newRows[10][13] = { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}, {1, 2, 3, 4, 1, 4, 3, 2, 1, 4, 1, 2, 3},
	{1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2}, {3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3}, {2, 4, 1, 3, 2, 4 ,1, 3, 1, 3, 1, 3, 1}, {4, 3, 2, 1, 4, 1, 2, 3, 4, 1, 4, 3, 2} };

	//Clock for frenzy mode
	Clock frenzyClock;

	/*
	Variables for death
	*/

	int bricksAnimationDelay = 0;
	bool bricksAreStatic = false;

	//Sprites
	//Bricks
	Texture textureBricks;
	textureBricks.loadFromFile("Assets/Backgrounds/deathBricks.png");
	Sprite spriteBricks;
	spriteBricks.setTexture(textureBricks);
	//Player	To be set to the spritePlayer when the player is dead
	Texture texturePlayerDead;
	texturePlayerDead.loadFromFile("Assets/Player/playerDead.png");
	
	//Sounds
	SoundBuffer descentBuffer;
	descentBuffer.loadFromFile("Audio/descent.wav");
	Sound descent;
	descent.setBuffer(descentBuffer);
	SoundBuffer bricksFinishedBuffer;
	bricksFinishedBuffer.loadFromFile("Audio/bricks2.wav");
	Sound bricksFinished;
	bricksFinished.setBuffer(bricksFinishedBuffer);

	//Text
	//Score words
	Text finalScoreText;
	finalScoreText.setFont(font);
	finalScoreText.setStyle(Text::Bold);
	finalScoreText.setString("Score");
	finalScoreText.setFillColor(Color::Black);
	finalScoreText.setCharacterSize(72);
	//The actual score
	Text finalScoreTotal;
	finalScoreTotal.setFont(font);
	finalScoreTotal.setStyle(Text::Bold);
	finalScoreTotal.setString("0");
	finalScoreTotal.setFillColor(Color::Black);
	finalScoreTotal.setCharacterSize(72);



	// Game Loop
	while (window.isOpen())
	{

		//Check if the player can input. Runs every frame
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased)
			{
				allowKeyPress = true;
			}
			if (event.type == Event::MouseMoved)
			{
				MouseCursorLocation = sf::Mouse::getPosition(window);
			}
		}

		if (Menu)
		{

			/*
			******************
			Handle Input
			******************
			*/

			// Play
			if (MouseCursorLocation.x >= 760 && MouseCursorLocation.x <= 1160 && MouseCursorLocation.y >= 155 && MouseCursorLocation.y <= 309)
			{
				spritePlayButton.setTexture(texturePlayButtonSelected);
				if (allowKeyPress)
				{
					if (event.type == Event::MouseButtonPressed)
					{
						Menu = false;
						DifficultySelect = true;
						click.play();
					}
				}
			}
			// Controls
			else if (MouseCursorLocation.x >= 760 && MouseCursorLocation.x <= 1160 && MouseCursorLocation.y >= 463 && MouseCursorLocation.y <= 617)
			{
				spriteControlsButton.setTexture(textureControlsButtonSelected);
				if (allowKeyPress)
				{
					if (event.type == Event::MouseButtonPressed)
					{
						click.play();
						Menu = false;
						Controls = true;
					}
				}
			}
			// Exit
			else if (MouseCursorLocation.x >= 760 && MouseCursorLocation.x <= 1160 && MouseCursorLocation.y >= 771 && MouseCursorLocation.y <= 925)
			{
				spriteExitButton.setTexture(textureExitButtonSelected);
				if (allowKeyPress)
				{
					if (event.type == Event::MouseButtonPressed)
					{
						click.play();
						window.close();
					}
				}
			}
			else
			{
				spritePlayButton.setTexture(texturePlayButtonNeutral);
				spriteControlsButton.setTexture(textureControlsButtonNeutral);
				spriteExitButton.setTexture(textureExitButtonNeutral);
			}


			/*
			******************
			Update Scene
			******************
			*/



			/*
			******************
			Draw Scene
			******************
			*/

			//Clear the last frame
			window.clear();

			//Draw the Background
			window.draw(spriteMenuBackground);

			//Draw the buttons
			window.draw(spritePlayButton);
			window.draw(spriteControlsButton);
			window.draw(spriteExitButton);

			window.display();
		}

		else if (Controls)
		{
			/*
			******************
			Handle Input
			******************
			*/

			/*
			******************
			Update Scene
			******************
			*/

			//Back button
			if (MouseCursorLocation.x >= 80 && MouseCursorLocation.x <= 180 && MouseCursorLocation.y >= 80 && MouseCursorLocation.y <= 180)
			{
				spriteBackButton.setTexture(textureBackButtonSelected);
				if (allowKeyPress)
				{
					if (event.type == Event::MouseButtonPressed)
					{
						click.play();
						Menu = true;
						Controls = false;
					}
				}
			}
			else
			{
				spriteBackButton.setTexture(textureBackButtonNeutral);
			}

			/*
			******************
			Draw Scene
			******************
			*/
			//Clear the previous frame
			window.clear();

			//Draw the background
			window.draw(spriteControlsBackground);
			window.draw(spriteBackButton);



			window.display();
		}

		else if (DifficultySelect)
		{
			/*
			******************
			Handle Input
			******************
			*/

			//Frenzy Mode
			if (MouseCursorLocation.x >= 450 && MouseCursorLocation.x <= 850 && MouseCursorLocation.y >= 340 && MouseCursorLocation.y <= 740)
			{
				spriteFrenzyButton.setTexture(textureFrenzyButtonSelected);
				frenzyButtonSelected = true;
				//Hovering over easy
				if (MouseCursorLocation.x >= 500 && MouseCursorLocation.x <= 800 && MouseCursorLocation.y >= 373 && MouseCursorLocation.y <= 523)
				{
					spriteEasyButton.setTexture(textureEasyButtonSelected);
					//Easy Selected
					if (event.type == Event::MouseButtonPressed && allowKeyPress)
					{
						allowKeyPress = false;
						menuMusic.stop();
						std::cout << "I will now play Frenzy Easy" << "\n";
						click.play();
						difficulty = 1;
						isFrenzyMode = true;
						bubbleClock.restart();
						frenzyClock.restart();
						newGame(spritePlayer, playerHeight, playerColumn, playerHeldColour, playerHeldNum, playerDeath, score, bricksAnimationDelay, Death, bricksAreStatic, bubbleToTake, nextSpaceAvailable, columnFull, popNum, spiderComplete, knownLocationAdjacent, timeRemaining, numShifts, timeToDescend, currentLevel, numberOfRows, bubbleArray, defaultArray, knownArray, Game);
						DifficultySelect = false;
						gameMusic.play();
					}
				}
				//Hovering over hard
				else if (MouseCursorLocation.x >= 500 && MouseCursorLocation.x <= 800 && MouseCursorLocation.y >= 557 && MouseCursorLocation.y <= 707)
				{
					spriteHardButton.setTexture(textureHardButtonSelected);
					if (event.type == Event::MouseButtonPressed && allowKeyPress)
					{
						allowKeyPress = false;
						menuMusic.stop();
						std::cout << "I will now play Frenzy Hard" << "\n";
						click.play();
						difficulty = 0.75;
						isFrenzyMode = true;
						bubbleClock.restart();
						frenzyClock.restart();
						newGame(spritePlayer, playerHeight, playerColumn, playerHeldColour, playerHeldNum, playerDeath, score, bricksAnimationDelay, Death, bricksAreStatic, bubbleToTake, nextSpaceAvailable, columnFull, popNum, spiderComplete, knownLocationAdjacent, timeRemaining, numShifts, timeToDescend, currentLevel, numberOfRows, bubbleArray, defaultArray, knownArray, Game);
						DifficultySelect = false;
						gameMusic.play();
					}
				}
				//Not
				else
				{
					spriteEasyButton.setTexture(textureEasyButtonNeutral);
					spriteHardButton.setTexture(textureHardButtonNeutral);
				}
			}

			//Infinite Mode
			else if (MouseCursorLocation.x >= 1070 && MouseCursorLocation.x <= 1470 && MouseCursorLocation.y >= 340 && MouseCursorLocation.y <= 740)
			{
				spriteInfiniteButton.setTexture(textureInfiniteButtonSelected);
				infiniteButtonSelected = true;
				//Hovering over easy
				if (MouseCursorLocation.x >= 1120 && MouseCursorLocation.x <= 1420 && MouseCursorLocation.y >= 373 && MouseCursorLocation.y <= 523)
				{
					spriteEasyButton.setTexture(textureEasyButtonSelected);
					//Easy Selected
					if (event.type == Event::MouseButtonPressed && allowKeyPress)
					{
						allowKeyPress = false;
						menuMusic.stop();
						std::cout << "I will now play Infinite Easy" << "\n";
						click.play();
						difficulty = 1;
						isFrenzyMode = false;
						bubbleClock.restart();
						newGame(spritePlayer, playerHeight, playerColumn, playerHeldColour, playerHeldNum, playerDeath, score, bricksAnimationDelay, Death, bricksAreStatic, bubbleToTake, nextSpaceAvailable, columnFull, popNum, spiderComplete, knownLocationAdjacent, timeRemaining, numShifts, timeToDescend, currentLevel, numberOfRows, bubbleArray, defaultArray, knownArray, Game);
						DifficultySelect = false;
						gameMusic.play();
					}
				}
				//Hovering over hard
				else if (MouseCursorLocation.x >= 1120 && MouseCursorLocation.x <= 1420 && MouseCursorLocation.y >= 557 && MouseCursorLocation.y <= 707)
				{
					spriteHardButton.setTexture(textureHardButtonSelected);
					if (event.type == Event::MouseButtonPressed && allowKeyPress)
					{
						allowKeyPress = false;
						menuMusic.stop();
						std::cout << "I will now play Infinite Hard" << "\n";
						click.play();
						difficulty = 0.75;
						isFrenzyMode = false;
						bubbleClock.restart();
						newGame(spritePlayer, playerHeight, playerColumn, playerHeldColour, playerHeldNum, playerDeath, score, bricksAnimationDelay, Death, bricksAreStatic, bubbleToTake, nextSpaceAvailable, columnFull, popNum, spiderComplete, knownLocationAdjacent, timeRemaining, numShifts, timeToDescend, currentLevel, numberOfRows, bubbleArray, defaultArray, knownArray, Game);
						DifficultySelect = false;
						gameMusic.play();
					}
				}
				//Not
				else
				{
					spriteEasyButton.setTexture(textureEasyButtonNeutral);
					spriteHardButton.setTexture(textureHardButtonNeutral);
				}
			}
			//Back button
			else if (MouseCursorLocation.x >= 80 && MouseCursorLocation.x <= 180 && MouseCursorLocation.y >= 80 && MouseCursorLocation.y <= 180)
			{
				spriteBackButton.setTexture(textureBackButtonSelected);
				if (allowKeyPress)
				{
					if (event.type == Event::MouseButtonPressed)
					{
						click.play();
						Menu = true;
						Controls = false;
					}
				}
			}
			else
			{
				frenzyButtonSelected = false;
				infiniteButtonSelected = false;
				spriteFrenzyButton.setTexture(textureFrenzyButtonNeutral);
				spriteInfiniteButton.setTexture(textureInfiniteButtonNeutral);
				spriteBackButton.setTexture(textureBackButtonNeutral);
			}



			/*
			******************
			Update Scene
			******************
			*/



			/*
			******************
			Draw Scene
			******************
			*/

			//Clear the last frame
			window.clear();

			//Draw the Background
			window.draw(spriteMenuBackground);

			//Draw the buttons
			window.draw(spriteFrenzyButton);
			window.draw(spriteInfiniteButton);
			if (frenzyButtonSelected)
			{
				spriteEasyButton.setPosition(500, 373);
				spriteHardButton.setPosition(500, 557);
				window.draw(spriteEasyButton);
				window.draw(spriteHardButton);
			}
			else if (infiniteButtonSelected)
			{
				spriteEasyButton.setPosition(1120, 373);
				spriteHardButton.setPosition(1120, 557);
				window.draw(spriteEasyButton);
				window.draw(spriteHardButton);
			}
			window.draw(spriteBackButton);

			window.display();
		}

		else if (Paused)
		{
			/*
			******************
			Handle Input
			******************
			*/

			if (MouseCursorLocation.x >= 760 && MouseCursorLocation.x <= 1160 && MouseCursorLocation.y >= 155 && MouseCursorLocation.y <= 309)
			{
				spriteResumeButton.setTexture(textureResumeButtonSelected);
				if (allowKeyPress)
				{
					if (event.type == Event::MouseButtonPressed)
					{
						sf::Mouse::setPosition(sf::Vector2i(0, 0));
						click.play();
						Game = true;
						Paused = false;
						gameMusic.play();
					}
				}
			}
			// Exit
			else if (MouseCursorLocation.x >= 760 && MouseCursorLocation.x <= 1160 && MouseCursorLocation.y >= 771 && MouseCursorLocation.y <= 925)
			{
				spriteExitButton.setTexture(textureExitButtonSelected);
				if (allowKeyPress)
				{
					if (event.type == Event::MouseButtonPressed)
					{
						click.play();
						window.close();
					}
				}
			}
			else
			{
				spriteResumeButton.setTexture(textureResumeButtonNeutral);
				spriteExitButton.setTexture(textureExitButtonNeutral);
			}

			/*
			******************
			Update Scene
			******************
			*/



			/*
			******************
			Draw Scene
			******************
			*/

			//Clear the previous frame
			window.clear();

			//Draw the Background
			window.draw(spriteMenuBackground);

			//Draw the buttons
			window.draw(spriteResumeButton);
			window.draw(spriteExitButton);

			window.display();
		}

		else if (Game)
		{
			/*
			******************
			Handle Input
			******************
			*/

			if (allowKeyPress)
			{
				//Pause game
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					gameMusic.pause();
					allowKeyPress = false;
					Paused = true;
					Game = false;
				}
				// Move Right one column
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					allowKeyPress = false;
					if (playerColumn > 0)
					{
						//Update the position
						spritePlayer.setPosition(spritePlayer.getPosition().x - 48, playerHeight);
						//Update the column variable
						playerColumn--;
					}
					else //The player is moving through a tunnel
					{
						//Update the position
						spritePlayer.setPosition(1220, playerHeight);
						//Update the column variable
						playerColumn = 12;
						//Play a sound effect
						woosh.play();
					}
				}
				// Move Right one column
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					allowKeyPress = false;
					if (playerColumn < 12)
					{
						spritePlayer.setPosition(spritePlayer.getPosition().x + 48, playerHeight);
						playerColumn++;
					}
					else //Tunnel
					{
						spritePlayer.setPosition(640, playerHeight);
						playerColumn = 0;
						woosh.play();
					}
				}
				// Take a bubble
				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					allowKeyPress = false;
					for (int i = numberOfRows - 1; i >= 0; i--)
					{
						bubbleToTake = bubbleArray[playerColumn][i];
						if (bubbleToTake > 0 && bubbleToTake != 5)
						{
							if (playerHeldColour == bubbleToTake) //The bubble is the right colour
							{
								bubbleArray[playerColumn][i] = 0;
								playerHeldNum += 1;
								pickup.play();
								playCantPickup = false;
							}
							else if (playerHeldColour == 0) //The player has nothing in their hand
							{
								bubbleArray[playerColumn][i] = 0;
								playerHeldNum += 1;
								playerHeldColour = bubbleToTake;
								pickup.play();
								playCantPickup = false;
							}
							else //There is no bubble / not same colour
							{
								//Play the sound
								if (playCantPickup)
								{
									cantpickup.play();
								}
								//Exit
								i = -1;
							}
						}
					}
				}
				// Place a bubble
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					allowKeyPress = false;
					lastPlaced = -1;
					//Place
					//Find where to put bubble				
					std::cout << playerHeldNum << playerHeldColour;
					while (playerHeldNum > 0 && playerHeldColour > 0)
					{
						//Find the space
						nextSpaceAvailable = findLowestBubble(playerColumn, bubbleArray) + 1;
						//Place it
						if (nextSpaceAvailable >= 0 && nextSpaceAvailable < 18)
						{
							placeBubble(playerColumn, nextSpaceAvailable, bubbleArray, place, playerHeldNum, playerHeldColour);
							//Sound effect
							place.play();
						}
						else
						{
							//set the inventory to 0 player is about to die
						}
						lastPlaced = nextSpaceAvailable;
					}

					//Pop
					popNum = 0;
					//Check how long the chain is
					for (int i = lastPlaced; i >= 0; i--)
					{
						//If the location is the same colour - add to the chain
						if (bubbleArray[playerColumn][i] == playerHeldColour)
						{
							popNum++;
						}
						else
						{
							//If the location is not the same colour - the chain has ended. exit the loop
							i = -1;
						}
					}
					std::cout << "Found a chain of: " << popNum << "\n";
					//Check if it should pop
					if (popNum >= 3)
					{
						popPosition = lastPlaced;
						//Ready the array
						for (int i = popNum; i > 0; i--)
						{
							knownArray[playerColumn][popPosition] = true;
						}
						//While the checking is not complete
						std::cout << "Starting spider... \n";
						spiderComplete = false;
						while (!spiderComplete)
						{
							knownLocationAdjacent = false;
							//While there is not a known location adjacent to the seach location
							while (!knownLocationAdjacent)
							{
								//Step through the array locations
								for (int column = 0; column < 13; column++)
								{
									for (int row = 0; row < 18; row++)
									{
										//If the location is the correct colour and not already 'known'
										if ((bubbleArray[column][row] == playerHeldColour || bubbleArray[column][row] > 5) && knownArray[column][row] == false)
										{
											//Is the location to the right 'known'?
											if (knownArray[column + 1][row] == true && column < 12)
											{
												knownLocationAdjacent = true;
												knownArray[column][row] = true;
											}
											//Is the location to the left 'known'?
											else if (knownArray[column - 1][row] == true && column > 0)
											{
												knownLocationAdjacent = true;
												knownArray[column][row] = true;
											}
											//Is the location above 'known'?
											else if (knownArray[column][row - 1] == true && row > 0)
											{
												knownLocationAdjacent = true;
												knownArray[column][row] = true;
											}
											//Is the location below 'known'?
											else if (knownArray[column][row + 1] == true && row < 17)
											{
												knownLocationAdjacent = true;
												knownArray[column][row] = true;
											}
										}
										//Move on to the next location
									}
								}
								if (!knownLocationAdjacent)
								{
									//Get out the loop
									knownLocationAdjacent = true;
									spiderComplete = true;
								}
							}
						}
						//Now pop everything
						//Step through the array
						for (int column = 0; column < 13; column++)
						{
							for (int row = 0; row < 18; row++)
							{
								//If the location needs popping
								if (knownArray[column][row] == true)
								{
									//Reset the knownArray
									knownArray[column][row] = false;
									//Sound effect
									pop.play();
									//Special?
									if (bubbleArray[column][row] > 5)
									{
										//Horizontal
										if (bubbleArray[column][row] == 6)
										{
											std::cout << "Found a horizontal bubble destroying row " << row << "\n";
											for (int i = 0; i < 13; i++)
											{
												if (bubbleArray[i][row] != 0)
												{
													bubbleArray[i][row] = 5;
													knownArray[i][row] = false;
												}
											}
										}
										//Vertical
										else if (bubbleArray[column][row] == 7)
										{
											std::cout << "Found a Vertical bubble, destroying column " << column << "\n";
											for (int j = 0; j < 18; j++)
											{
												if (bubbleArray[column][j] != 0)
												{
													bubbleArray[column][j] = 5;
													knownArray[column][j] = false;
												}
											}
										}
										//Cross
										if (bubbleArray[column][row] == 8)
										{

											std::cout << "Found a Cross bubble destoying column, row: " << column << row << "\n";
											for (int i = 0; i < 13; i++)
											{
												if (bubbleArray[i][row] != 0)
												{
													bubbleArray[i][row] = 5;
													knownArray[i][row] = false;
												}
											}
											for (int j = 0; j < 18; j++)
											{
												if (bubbleArray[column][j] != 0)
												{
													bubbleArray[column][j] = 5;
													knownArray[column][j] = false;
												}
											}
										}
									}
									//Start animation
									bubbleArray[column][row] = 5;
									popAnimationRunning = true;
									popAnimationDelay = 0;
									//Add Score
									scoreAdded += 8;
									scoreAddedAnimationDelay = 300;
									score += 8;
									stringstream ss;
									ss << "Score = " << score;
									scoreText.setString(ss.str());
									//Output for debug
								}
							}
						}
					}
				}
			}

			/*
			******************
			Update Scene
			******************
			*/
			
			//Update the column pointer
			columnPointerAnimationDelay++;
			if (columnPointerAnimationDelay == 50 || columnPointerAnimationDelay == 100)
			{
				columnPointerAnimationPosition++;
			}
			else if (columnPointerAnimationDelay == 150 || columnPointerAnimationDelay == 200)
			{
				columnPointerAnimationPosition--;
			}
			else if (columnPointerAnimationDelay > 200)
			{
				columnPointerAnimationDelay = 0;
			}
			spriteColumnPointer.setPosition(655 + (playerColumn * 48) + 10.0f, (findLowestBubble(playerColumn, bubbleArray) * 50) + 165 + columnPointerAnimationPosition + 5.5f);

			//Make some sounds available to play
			playCantPickup = true;
			
			//Empty inventory = No Colour
			if (playerHeldNum == 0)
			{
				playerHeldColour = 0;
			}
		
			//Make the sprite hold the correct colour
			if (playerHeldNum > 0)
			{
				spriteColumnPointer.setScale(1.0f, 1.0f);
				if (playerHeldColour == 1)
				{
					spritePlayer.setTexture(texturePlayer1);
				}
				else if (playerHeldColour == 2)
				{
					spritePlayer.setTexture(texturePlayer2);
				}
				else if (playerHeldColour == 3)
				{
					spritePlayer.setTexture(texturePlayer3);
				}
				else if (playerHeldColour == 4)
				{
					spritePlayer.setTexture(texturePlayer4);
				}
			}
			else
			{
				spriteColumnPointer.setScale(1.0f, -1.0f);
				spritePlayer.setTexture(texturePlayer0);
			}
	
			//Animate the pops
			if (popAnimationRunning)
			{
				popAnimationDelay++;
				if (popAnimationDelay > 200)
				{
					for (int i = 0; i < 13; i++)
					{
						for (int j = 0; j < numberOfRows; j++)
						{
							if (bubbleArray[i][j] == 5)
							{
								bubbleArray[i][j] = 0;
							}
						}
					}
					removeFloatingBubbles(bubbleArray);
					popAnimationRunning = false;
					popAnimationDelay = 0;
				}
			}

			//Shifting rows
			Time dt = bubbleClock.restart();
			timeRemaining -= dt.asSeconds();
			if (timeRemaining <= 0.0)
			{
				numShifts += 1;
				if (shift(playerDeath, numShifts, numberOfRows, lastRowAdded, bubbleArray, newRows, currentLevel, levelText, timeToDescend, timeRemaining, difficulty))
				{
					lvlUp.play();
				}
				descent.play();
			}

			//Frenzy mode Timer
			if (isFrenzyMode)
			{
				Time ft = frenzyClock.restart();
				frenzyTime += ft.asSeconds();
				cout << frenzyTime << "\n";
				//If 1 second has elapsed
				if (frenzyTime >= 1.0f)
				{
					frenzySecondsLeft--;
					frenzyTime = 0;
					//If the clock needs to be :00, :01 etc
					if (frenzySecondsLeft < 10)
					{
						stringstream ss;
						ss << frenzyMinutesLeft << ":" << "0" << frenzySecondsLeft;
						frenzyTimerText.setString(ss.str());
					}
					if (frenzySecondsLeft == -1 && frenzyMinutesLeft > 0)
					{
						frenzyMinutesLeft--;
						frenzySecondsLeft = 59;
						stringstream ss;
						ss << frenzyMinutesLeft << ":" << frenzySecondsLeft;
						frenzyTimerText.setString(ss.str());
					}
					else
					{
						stringstream ss;
						ss << frenzyMinutesLeft << ":" << frenzySecondsLeft;
						frenzyTimerText.setString(ss.str());
					}
				}
				if (frenzyMinutesLeft == 0 && frenzySecondsLeft == 0)
				{
					playerDeath = true;
				}
			}

			for (int i = 0; i < 13; i++)
			{
				if (bubbleArray[i][17] > 0 && bubbleArray[i][17] != 5)
				{
					//Dead
					playerDeath = true;
				}
			}

			//End the game if they are dead
			if (playerDeath)
			{
				gameMusic.stop();
				bricksAnimationDelay = 0;
				std::stringstream ss;
				ss << score;
				finalScoreTotal.setString(ss.str());
				sf::FloatRect finalScoreTotalTextRect = finalScoreTotal.getLocalBounds();
				finalScoreTotal.setOrigin(finalScoreTotalTextRect.width / 2, 0);
				finalScoreTotal.setPosition(960, 300);
				sf::FloatRect finalScoretextRect = finalScoreText.getLocalBounds();
				finalScoreText.setOrigin(finalScoretextRect.width / 2, 0);
				finalScoreText.setPosition(960, 200);
				spriteExitButton.setPosition(910, 700);
				spriteBackButton.setPosition(745, 700);
				spriteExitButton.setScale(0.64516129f, 0.64516129f);
				bricksAreStatic = false;
				Game = false;
				Death = true;
			}

			//Animate the arrow
			arrowAnimationNum++;
			if (arrowAnimationNum < 100)
			{
				spriteArrowLeft.setTexture(textureArrowFrame1);
				spriteArrowRight.setTexture(textureArrowFrame1);
			}
			else if (arrowAnimationNum >= 100 && arrowAnimationNum < 200)
			{
				spriteArrowLeft.setTexture(textureArrowFrame2);
				spriteArrowRight.setTexture(textureArrowFrame2);
			}
			else if (arrowAnimationNum >= 200)
			{
				arrowAnimationNum = 0;
			}

			/*
			******************
			Draw Scene
			******************
			*/

			// Clear the last frame
			window.clear();

			// Now draw
			window.draw(spriteBackground);

			// Draw the bubbles
			for (int i = 0; i < 13; i++)
			{
				for (int j = 0; j < numberOfRows; j++)
				{
					//Red Bubble
					if (bubbleArray[i][j] == 1)
					{
						spriteBubbleRed.setPosition(641.0f + (48.0f * i), (50.0f * j) + verticalOffset);
						window.draw(spriteBubbleRed);
					}
					//Blue Bubble
					else if (bubbleArray[i][j] == 2)
					{
						spriteBubbleBlue.setPosition(641.0f + (48.0f * i), (50.0f * j) + verticalOffset);
						window.draw(spriteBubbleBlue);
					}
					//Green Bubble
					else if (bubbleArray[i][j] == 3)
					{
						spriteBubbleGreen.setPosition(641.0f + (48.0f * i), (50.0f * j) + verticalOffset);
						window.draw(spriteBubbleGreen);
					}
					//Yellow Bubble
					else if (bubbleArray[i][j] == 4)
					{
						spriteBubbleGold.setPosition(641.0f + (48.0f * i), (50.0f * j) + verticalOffset);
						window.draw(spriteBubbleGold);
					}
					//Pop Animation
					else if (bubbleArray[i][j] == 5)
					{
						spritePop.setPosition(641.0f + (48.0f * i), (50.0f * j) + verticalOffset);
						window.draw(spritePop);
					}
					//Special H
					else if (bubbleArray[i][j] == 6)
					{
						spriteBubbleHorizontal.setPosition(641.0f + (48.0f * i), (50.0f * j) + verticalOffset);
						window.draw(spriteBubbleHorizontal);
					}
					//Special V
					else if (bubbleArray[i][j] == 7)
					{
						spriteBubbleVertical.setPosition(641.0f + (48.0f * i), (50.0f * j) + verticalOffset);
						window.draw(spriteBubbleVertical);
					}
					//Special C
					else if (bubbleArray[i][j] == 8)
					{
						spriteBubbleCross.setPosition(641.0f + (48.0f * i), (50.0f * j) + verticalOffset);
						window.draw(spriteBubbleCross);
					}
				}
			}

			window.draw(spriteColumnPointer);
			window.draw(spriteStage);
			window.draw(spriteArrowLeft);
			window.draw(spriteArrowRight);

			// Draw the player
			window.draw(spritePlayer);
			//Draw text
			window.draw(scoreText);
			window.draw(levelText);
			if (isFrenzyMode)
			{
				window.draw(frenzyTimerText);
			}
			//ScoreAdded too (a little more complex)
			if (scoreAddedAnimationDelay > 0)
			{
				stringstream ss;
				ss << "+ " << scoreAdded << "!";
				scoreAddedText.setString(ss.str());
				scoreAddedAnimationDelay--;
				window.draw(scoreAddedText);
			}
			else
			{
				scoreAdded = 0;
			}

			// Now display the drawings
			window.display();
		}

		else if (Death)
			{
				/*
				******************
				Handle Input
				******************
				*/

				if (MouseCursorLocation.x >= 910 && MouseCursorLocation.x <= 1168 && MouseCursorLocation.y >= 700 && MouseCursorLocation.y <= 800)
				{
					spriteExitButton.setTexture(textureExitButtonSelected);
					if (allowKeyPress)
					{
						if (event.type == Event::MouseButtonPressed)
						{
							allowKeyPress = false;
							click.play();
							window.close();
						}
					}
				}
				else if (MouseCursorLocation.x >= 745 && MouseCursorLocation.x <= 845 && MouseCursorLocation.y >= 700 && MouseCursorLocation.y <= 800)
				{
					spriteBackButton.setTexture(textureBackButtonSelected);
					if (allowKeyPress)
					{
						if (event.type == Event::MouseButtonPressed)
						{
							allowKeyPress = false;
							click.play();
							spriteExitButton.setPosition(760, 771);
							spriteBackButton.setPosition(80, 80);
							spriteExitButton.setScale(1.0f, 1.0f);
							Menu = true;
							Death = false;
							menuMusic.play();
						}
					}
				}
				else
				{
					spriteExitButton.setTexture(textureExitButtonNeutral);
					spriteBackButton.setTexture(textureBackButtonNeutral);
				}


				/*
				******************
				Update Scene
				******************
				*/

				if (!bricksAreStatic)
				{
					bricksAnimationDelay++;
					if (bricksAnimationDelay == 1)
					{
						spriteBricks.setPosition(641, -590);
						descent.play();
					}
					else if (bricksAnimationDelay == 250)
					{
						spriteBricks.setPosition(641, -340);
						descent.play();
					}
					else if (bricksAnimationDelay == 500)
					{
						spriteBricks.setPosition(641, -90);
						descent.play();
					}
					else if (bricksAnimationDelay == 800)
					{
						spriteBricks.setPosition(641, 100);
						bricksFinished.play();
						bricksAreStatic = true;
						spritePlayer.setTexture(texturePlayerDead);
					}
				}

				//Animate the arrow
				arrowAnimationNum++;
				if (arrowAnimationNum < 100)
				{
					spriteArrowLeft.setTexture(textureArrowFrame1);
					spriteArrowRight.setTexture(textureArrowFrame1);
				}
				else if (arrowAnimationNum >= 100 && arrowAnimationNum < 200)
				{
					spriteArrowLeft.setTexture(textureArrowFrame2);
					spriteArrowRight.setTexture(textureArrowFrame2);
				}
				else if (arrowAnimationNum >= 200)
				{
					arrowAnimationNum = 0;
				}

				/*
				******************
				Draw Scene
				******************
				*/

				// Clear the last frame
				window.clear();

				if (!bricksAreStatic)
				{
					// Now draw
					window.draw(spriteBackground);

					// Draw the bubbles			
					for (int i = 0; i < 13; i++)
					{
						for (int j = 0; j < numberOfRows; j++)
						{
							//Red Bubble
							if (bubbleArray[i][j] == 1)
							{
								spriteBubbleRed.setPosition(641.0f + (48.0f * i), (50.0f * j) + verticalOffset);
								window.draw(spriteBubbleRed);
							}
							//Blue Bubble
							else if (bubbleArray[i][j] == 2)
							{
								spriteBubbleBlue.setPosition(641.0f + (48.0f * i), (50.0f * j) + verticalOffset);
								window.draw(spriteBubbleBlue);
							}
							//Green Bubble
							else if (bubbleArray[i][j] == 3)
							{
								spriteBubbleGreen.setPosition(641.0f + (48.0f * i), (50.0f * j) + verticalOffset);
								window.draw(spriteBubbleGreen);
							}
							//Yellow Bubble
							else if (bubbleArray[i][j] == 4)
							{
								spriteBubbleGold.setPosition(641.0f + (48.0f * i), (50.0f * j) + verticalOffset);
								window.draw(spriteBubbleGold);
							}
							//Pop Animation
							else if (bubbleArray[i][j] == 5)
							{
								spritePop.setPosition(641.0f + (48.0f * i), (50.0f * j) + verticalOffset);
								window.draw(spritePop);
							}
						}
					}
					window.draw(spriteArrowLeft);
					window.draw(spriteArrowRight);
				}
				else
				{
					//Draw the exit to menu, exit to desktop buttons
					//draw the score and such
				}

				window.draw(spriteBricks);
				window.draw(spriteStage);

				// Draw the player
				window.draw(spritePlayer);
				if (bricksAreStatic)
				{
					//Draw text
					window.draw(finalScoreTotal);
					window.draw(finalScoreText);
					window.draw(spriteExitButton);
					window.draw(spriteBackButton);
				}
				// Now display the drawings
				window.display();
			}

		else
			{
				window.close();
			}

	}

	return 0;
}
