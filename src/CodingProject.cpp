#define NOMINMAX //Used to avoid conflicts cause by matching libraries//
#include <iostream>
#include <vector> //For making vectors//
#include <ctime> //For seeding the random//
#include <cstdlib>//Used for actually using the random//
#include <algorithm> //For bug killer//
#include <string> //For the use of strings//
#include <thread> //For sleep function//
#include <soloud.h> //Library for sound in the game//
#include <soloud_wav.h> //Same thing as previous, still figuring out what the difference is//

using namespace std;
//Global Variable//
SoLoud::Soloud gsoloud; //This is the main sound engine//
SoLoud::Wav SoundFile; //This is the sound file that will be played//
SoLoud::Wav SoundFile2; //Need second file for button clicks//
SoLoud::Wav SoundFile3; //Need third file for winning sound//
int maxnum = 50;

vector<pair<string, int>> Scoreboard = { 
	{ "Syro", 10000}
};//Scoreboard for the game that tracks player name and score.//
void Music()
{
	//Created by Jorge Millet-Nieves//
	// Initialize SoLoud and turns it off if it fails//
	if (gsoloud.init() != SoLoud::SO_NO_ERROR) {
		gsoloud.deinit();
		return;
	}

	// Attempt to load the sound files, if fail, turn off the entire sound system//
	if (SoundFile.load("Assets\\CodeMusic.wav") != SoLoud::SO_NO_ERROR) { 
		gsoloud.deinit(); // Deinitialize if loading fails
		return;
	}
	if (SoundFile2.load("Assets\\CodeClick.wav") != SoLoud::SO_NO_ERROR) {
		gsoloud.deinit(); // Deinitialize if loading fails
		return;
	}
	if (SoundFile3.load("Assets\\CodeWin.wav") != SoLoud::SO_NO_ERROR) {
		gsoloud.deinit(); // Deinitialize if loading fails
		return;
	}
	SoundFile.setLooping(true);
	//Now loading text animation. It had a nice fit. AI generated  //
	const string NowLoading = "Now Loading";
	string dots = "";
	int dotCount = 0;

	for (int i=0; i<13; ++i) {
		cout << "\r" << NowLoading << dots << "   " << flush;

		this_thread::sleep_for(chrono::milliseconds(500));

		dotCount = (dotCount + 1) % 4; // 0 to 3
		dots = string(dotCount, '.');
	}
	}
void deinit()
{
	//Created by Jorge Millet-Nieves//
	gsoloud.deinit();
}

	
void byetext()
{
	//AI generated//
	cout << "\033[2J\033[H";//Literally just clears the console//
}
void addscore(const string& name, int score) {
	//Created by Jorge Millet-Nieves//
	// Add the new score to the vector
	Scoreboard.push_back({ name, score });

	// Sort the vector in descending order of scores
	sort(Scoreboard.begin(), Scoreboard.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
		return a.second > b.second;
		});

	// If there are more than 5 scores, remove the smallest one
	if (Scoreboard.size() > 5) {
		Scoreboard.pop_back();
	}
}
void game()
{
	//Created by Carlos Rivera//
	byetext();
	srand(time(0));
	int snum = rand() % maxnum + 1;
	int guess;
	int attempts = 0;
	int score;

	cout << "\n*** NUMBER GUESSING GAME ***" << endl;
	cout << "Guess the number between 1 and " << maxnum << endl;
	cout << "The quicker you guess the number, the higher your score!" << endl;

	do {
		cout << "Enter your guess : ";
		if (!(cin >> guess)) {
			cout << "Invalid input! Please enter a number." << endl;
			cin.clear(); //Gets rid of error
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		attempts++;

		if (guess < 1 || guess > maxnum) {
			cout << "Please enter a number between 1 and " << maxnum << endl;
			continue;
		}

		if (guess < snum) {
			cout << "Too low! Try again." << endl;
		}
		else if (guess > snum) {
			cout << "Too high! Try again." << endl;
		}
	} while (guess != snum);

	score = 10000 / attempts;
	cout << "\nCongratulations! You guessed the number in " << attempts << " attempts!" << endl;
	cout << "Your score is: " << score << endl;
	//Jorge section//
	string name;
	cout << "What is your name? ";
	cin >> name;
	addscore(name, score); //Add the score to the scoreboard//
	cout << "Thank you! Your score has been recorded." << endl;
	this_thread::sleep_for(chrono::seconds(3));
}


int scoredisplay()
{
	//Created  by Jorge Millet-Nieves//
//Scores are displayed on this function
	int Back;
	byetext();
	cout << "High Scores!" << endl;
	cout << "-------------------------" << endl;
	for (const auto& entry : Scoreboard) {
		cout << entry.first << " - " << entry.second << endl;
	}
	cout << "-------------------------" << endl;
	cout << "1. Back to main menu" << endl;

	//Bug killer//
	if (!(cin >> Back)) {
		gsoloud.play(SoundFile2);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Dude, seriously? Only one option here." << endl;
		this_thread::sleep_for(chrono::milliseconds(700));
		return scoredisplay();
	}

	gsoloud.play(SoundFile2);
	if (Back == 1) {
		cout << "Heading back..." << endl;
		this_thread::sleep_for(chrono::milliseconds(400));
		return 0;
	}
	else {
		cout << "Nuh uh." << endl;
		this_thread::sleep_for(chrono::milliseconds(600));
		return scoredisplay();
	}
}

static void settings()
{
	//Joint effort//
	int choiceSettings;
	float volume=100; //Default volume for SoLoud is 100%//

	while (true) {
		byetext();
		cout << "=== Settings Menu ===" << endl;
		cout << "1. Difficulty Options" << endl;
		cout << "2. Sound Settings (Current: " << volume << "%)" << endl;
		cout << "3. Back to main menu" << endl;
		cout << "What'll it be?" << endl;

		//Bug killer 3000//
		if (!(cin >> choiceSettings)) {
			gsoloud.play(SoundFile2);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input! Please enter a number between 1 and 3." << endl;
			this_thread::sleep_for(chrono::milliseconds(700));
			continue;
		}
		gsoloud.play(SoundFile2);
		switch (choiceSettings)
		{
		case 1:
			//Carlos Rivera//
			byetext();
			int difficultyChoice;
			cout << "=== Difficulty Options ===" << endl;
			cout << "1. Easy (1-50)" << endl;
			cout << "2. Medium (1-100)" << endl;
			cout << "3. Hard (1-200)" << endl;
			cout << "4. Back to settings" << endl;
			cout << "Choose difficulty: ";

			if (!(cin >> difficultyChoice)) {
				gsoloud.play(SoundFile2);
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input!" << endl;
				this_thread::sleep_for(chrono::milliseconds(700));
				break;
			}

			switch (difficultyChoice) {
			case 1: gsoloud.play(SoundFile2); maxnum = 50; cout << "Easy difficulty selected (1-50)" << endl; this_thread::sleep_for(chrono::milliseconds(700)); break;
			case 2: gsoloud.play(SoundFile2); maxnum = 100; cout << "Medium difficulty selected (1-100)" << endl; this_thread::sleep_for(chrono::milliseconds(700)); break;
			case 3: gsoloud.play(SoundFile2); maxnum = 200; cout << "Hard difficulty selected (1-200)" << endl; this_thread::sleep_for(chrono::milliseconds(700)); break;
			case 4: gsoloud.play(SoundFile2); break; // Return to settings menu
			default: cout << "Invalid difficulty option" << endl;
			}
			break;
		case 2:
			//Jorge Millet-Nieves//
			cout << "Enter new volume level (0-100): ";
			//Bug Killer 9k//
			if (!(cin >> volume)) {
				gsoloud.play(SoundFile2);
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Nuh uh." << endl;
				this_thread::sleep_for(chrono::milliseconds(900));
				break;
			}
			if (volume < 0) volume = 0; gsoloud.play(SoundFile2); //Minimum failsafe//
			if (volume > 100) volume = 100; gsoloud.play(SoundFile2); //Maximum failsafe//
			gsoloud.setGlobalVolume(volume / 100.0f); // Changes volume to number between 0 and 1//
			cout << "Volume set to: " << volume << "%" << endl;
			break;

		case 3:
			cout << "Returning to main menu..." << endl;
			return;
		default:
			cout << "That ain't an option, bruh" << endl;
			this_thread::sleep_for(chrono::milliseconds(900));
			break;
		}
	}
}

int main()
{
	//Created by Jorge Millet-Nieves//
	int choiceMain;
	Music(); //Calls the music function, which initializes the sound engine and loads the sound file, while also playing the now loading thing//
	gsoloud.play(SoundFile); //Actually starts the music. It's placed here to let the now loading thing to finish first//
while(true){
	byetext(); //Clears all text from screen using some ASCII nonsense//
	cout << "Welcome to the Random Number Guessing Game!" << endl;
	cout << "You'll have a great time!" << endl;
	cout << "Here are your options!" << endl;
	cout << "1. Play Game" << endl;
	cout << "2. View Score" << endl;
	cout << "3. Settings" << endl;
	cout << "4. Exit" << endl;
	cout << "What'll it be?" << endl;

	//Accidentally found a major bug, fixed it by clearing input after invalid input. AI Assisted, could probably be changed//
	if (!(cin >> choiceMain)) {
		gsoloud.play(SoundFile2);
		cin.clear(); //Gets rid of error
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Throws out the bad input
		cout << "We serve food here, sir." << endl;
		this_thread::sleep_for(chrono::milliseconds(700));
		continue; //Goes back to the loop
	}
	gsoloud.play(SoundFile2);
	//Main menu system//
	switch (choiceMain)
	{
	case 1:
		game();
		break;
	case 2:
		scoredisplay();
		break;
	case 3:
		settings();
		break;
	case 4:  
		cout << "See you soon!" << endl;
		this_thread::sleep_for(chrono::seconds(1));
		deinit();
		return 42;
	default:
		cout << "That ain't an option, bruh" << endl;
		this_thread::sleep_for(chrono::milliseconds(600));
		break;
		}
	}
}

//A game with a main menu, basic settings, a method of keeping score of both player name and player score, the random number guessing game, with the ability to modify how large the number pool is,//
// and how many guesses the player has to make.//
//NEEDS SOUND//
//Settings has volume adjust//