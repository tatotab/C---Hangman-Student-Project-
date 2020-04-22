//Hangman game 
//By Dimitri Tabagari (red id: 823 356 359)
//For Comp E 160(Proffessor Tinatin Davitashvili)
//Due date December 7, 2019
//TODO ----- does not allow input the same char few times 
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <cstddef>
#include <stdbool.h>
void MainMenu();
void delay(int number_of_seconds);
void Game(char word[20], char hint[20]);
void PlayModeEasy();
void PlayModeHard();
void PlayComp();
void PlayModeRandom();
void PlayMenu();
void addWord();
void PlayModeCountries();
void AddWordFunc(int choice, char buffer1[20], char buffer2[20]);

void delay(int number_of_seconds)
{
	// Converting time into milli_seconds 
	int milli_seconds = 1000 * number_of_seconds;

	// Stroing start time 
	clock_t start_time = clock();

	// looping till required time is not acheived 
	while (clock() < start_time + milli_seconds);
}
typedef struct words_struct {
	char word[20];
	char hint[20];
} words;
void PlayModeCountries() { //MAX size of word/hints in file 20
	printf("Computer is choosing a word...\n");

	words countriesWordList[20]; //word from file will be place in here
	FILE* countriesWord;
	int numRead, i = 0; //i is to count 
	int r;
	countriesWord = fopen("words-countries.txt", "r");  // read words-easy ==3-6 letters words file 
	if (countriesWord == NULL) {
		printf("Can't open file words-countries.txt\n");
		exit(1);
	}
	//take all words
	while (!feof(countriesWord)) { //eof ==end of file
		fscanf(countriesWord, "%s %s", &(countriesWordList[i].word), &(countriesWordList[i].hint)); //copying values to array "words"
		i++;
	}
	//generate random
	{srand(time(NULL));
	r = rand() % i; } //using i and not i+1 because it shows number not index
	//call game(word hint ar random r)
	fclose(countriesWord);
	Game(countriesWordList[r].word, countriesWordList[r].hint);

}
void PlayModeRandom() {
	printf("Computer is choosing a word...\n");

	words randomWordList[20]; //word from file will be place in here
	FILE* randomWord;
	int numRead, i = 0; //i is to count 
	int r;
	randomWord = fopen("word-random.txt", "r");  // read words-easy ==3-6 letters words file 
	if (randomWord == NULL) {
		printf("Can't open file word-random.txt\n");
		exit(1);
	}
	//take all words
	while (!feof(randomWord)) { //eof ==end of file
		fscanf(randomWord, "%s %s", &(randomWordList[i].word), &(randomWordList[i].hint)); //copying values to array "words"
		i++;
	}
	//generate random
	{srand(time(NULL));
	r = rand() % i; } //using i and not i+1 because it shows number not index
	//call game(word hint ar random r)
	fclose(randomWord);
	Game(randomWordList[r].word, randomWordList[r].hint);

}
void Game(char word[20], char hint[20]) { //unda mivce word da hint
	char check = '0', charHistory[20] = { ':' }, displayWord[20], choice; 
	int i, correct = 0, mistakeLeft = 5;//remaining wrong attempt
	bool coincide = true;
	
	for (i = 0; i < strlen(word); i++) {
		displayWord[i] = '-';
	}
	displayWord[i] = '\0'; 
	while (true) {
		system("CLS");
		for (int i = 0; i < strlen(word); i++) {
			if (check == word[i]) {
				displayWord[i] = word[i];
				correct++;
				coincide = true;
			}
		}
		if (!coincide)
		{
			mistakeLeft--;
		}
		coincide = false;
		
		printf("SAVE THE MAN'S LIFE\n");
		if (mistakeLeft < 5) {
			printf("__________________..______\n");
			printf("| .________________))_____|\n");
			if (mistakeLeft < 4) {

				printf("| | / /            ||\n");
				printf("| |/ /             ||\n");
				printf("| | /              ||._``.\n");
				printf("| |/               |/  _ \\\n");
				printf("| |                ||  `/.|\n");
				printf("| |                (\\\\`_.`\n");
			}
			else {
				printf("| | / /\n");
				printf("| |/ /\n");
				printf("| | /\n");
				printf("| |/\n");
				printf("| |\n");
				printf("| |\n");

			}
			if (mistakeLeft < 3 && mistakeLeft >= 2) {
				printf("| |                .-`--'.\n");
				printf("| |                Y . . Y\n");
				printf("| |                 |   | \n");
				printf("| |                 | . |  \n");
				printf("| |                 |   |  \n");
			}
			else if (mistakeLeft < 2) {
				printf("| |                .-`--'.\n");
				printf("| |               /Y . . Y\\\n");
				printf("| |              // |   | \\\\\n");
				printf("| |             //  | . |  \\\\\n");
				printf("| |            .)   |   |   (.\n");
			}
			else {
				printf("| |\n"); printf("| |\n"); printf("| |\n"); printf("| |\n"); printf("| |\n");
	
			}
		
			if (mistakeLeft < 1) {
				printf("| |                 || ||\n");
				printf("| |                 || ||\n");
				printf("| |                 || ||\n");
				printf("| |                 || ||\n");
				printf("| |                / | |\\\n");
				printf("```````````````|_  '-' '-'|```|\n");
			}
			else {
				printf("| |\n");
				printf("| |\n");
				printf("| |\n");
				printf("| |\n");
				printf("| |\n");
				printf("```````````````|_         |```|\n");

			}
			printf("|`|````````````\\          ``|`|\n");
			printf("| |          \\ \\          | |\n");
			printf(": :           \\ \\         : :\n");
			printf(". .            \\ \\        . .\n");
		}
		printf("\n----------------------------------\n");
		printf("Hint: %s\n", hint);
		printf("\nWord: ");
		for (int i = 0; i < strlen(word); i++) {
			printf("%c", displayWord[i]);
		}
		printf("\n\nAlready Used Characters%s", charHistory);
		printf("\n\nRemaining wrong attemp: %d\n", mistakeLeft);
		printf("----------------------------------\n");
		if (correct == strlen(word) || mistakeLeft == 0) {
			break;
		}
		else { //check if this letter has already been inputed, does not allow same input ---------TODO
			printf("\nEnter Letter(Use lowercase letter):\n");
			scanf(" %c", &check);
			
			for (int i = 0; i < strlen(charHistory); i++) {
				if (check == charHistory[i]) {
					printf("\nletter you enter has already been used, enter again:\n");
					scanf(" %c", &check);
					i = 0;
				}
			}
		}
		strncat(charHistory, &check, 1);
		strncat(charHistory, " ", 1);
		
	}
	if (correct == strlen(word)) {
		delay(1);
		system("CLS");
		printf(" ____________________________________________________\n");
		printf("|                                                    |\n");
		printf("|                  CONGRATULATIONS!                  |\n");
		printf("|                                                    |\n");
		printf("|                  YOU WON THE GAME                  |\n");
		printf("|____________________________________________________|\n");
	}
	if (mistakeLeft == 0) {
		delay(3);
		system("CLS");
		printf(" ____________________________________________________\n");
		printf("|                                                    |\n");
		printf("|                   Unfortunately                    |\n");
		printf("|                                                    |\n");
		printf("|                 You Lost the Game!                 |\n");
		printf("|                                                    |\n");
		printf("|        The correct word was >> %s           |\n", word);
		printf("|____________________________________________________|\n");
		
	}
}
void PlayModeEasy(){
	//TODO--------------------DO I NEED TO MALLOC ARRAY?
	printf("Computer is choosing a word...\n");
	words easyWordsList[20]; //word from file will be place in here
	FILE* easyWord;
	int numRead, i = 0; //i is to count 
	int r;
	easyWord = fopen("words-easy.txt", "r");  // read words-easy ==3-6 letters words file 
	if (easyWord == NULL) {
		printf("Can't open file words-easy.txt\n");
		exit(1);
	}
	//take all words
	while (!feof(easyWord)) { //eof ==end of file
		fscanf(easyWord, "%s %s", &(easyWordsList[i].word), &(easyWordsList[i].hint)); //copying values to array "words"
		i++;
	}	
	//generate random
	{srand(time(NULL));
	r = rand() % i; } //using i and not i+1 because it shows number not index
	
	fclose(easyWord);
	Game(easyWordsList[r].word, easyWordsList[r].hint);
}
void PlayModeHard() { 

	printf("Computer is choosing a word...\n");
	words hardWordsList[20]; //word from file will be placed in here
	FILE* hardWord;
	int numRead, i = 0;
	int r;
	hardWord = fopen("words-hard.txt", "r");  // read words-easy ==7+ letters words file 
	if (hardWord == NULL) {
		printf("Can't open file words-easy.txt\n");
		exit(1);
	}
	//take all words
	while (!feof(hardWord)) { //eof ==end of file
		fscanf(hardWord, "%s %s", &(hardWordsList[i].word), &(hardWordsList[i].hint)); //copying values to array "words"
		i++;
	}
	//generate random
	{srand(time(NULL));
	r = rand() % i; }
	//call game(word hint ar random r) -------TODO
	fclose(hardWord);

	Game(hardWordsList[r].word, hardWordsList[r].hint);
}
void PlayFriend() { 
	char friendWord[20], friendHint[20];
	system("CLS");
	printf("\nThe first player enters the word and hint. The second player plays the game\n");
	printf("\nFirst player, Please Enter the word(all in lowercase):\n");
	scanf(" %s", friendWord);
	printf("\nPlease enter the hint(1 word)\n");
	scanf(" %s", friendHint);

	Game(friendWord, friendHint);
	AddWordFunc(4, friendWord, friendHint);
}
void PlayComp() { //Here I use Pointer
	int choice;
	int* ptr;
	ptr = &choice;
	//TODO - - - - - - - - Ask to enter Name
	printf("Choose the difficulty:\n");
	printf("1. Easy (3 to 6 letters)\n");
	printf("2. Hard (7+ letters)\n");
	printf("3. Special>>Countries\n");
	printf("4. Random words\n");
	scanf("%d", &choice);
	switch (*ptr)
	{
	case 1: 
		PlayModeEasy();
		break;
	case 2:
		PlayModeHard();
		break;
	case 3: 
		PlayModeCountries();
		break;
	default:
		PlayModeRandom();
		break;
	}
	
}
void PlayMenu() {
	int playMode;
	system("CLS");//clears the screen
	printf("Enter corresponding digit:\n");
	printf("1. Play Against Computer\n");
	printf("2. Play against a Friend\n");
	scanf("%d", &playMode);
	if (playMode == 1) {
		PlayComp();
	}
	if (playMode == 2) {
		PlayFriend();
	}
}
void AddWord() {
	system("CLS");
	int choice;
	char buffer1[20];
	char buffer2[20];
	printf("Hello, thanks for adding words to my library\n");
	printf("Please choose word lenght:\n1.3-6 Letters\n2.7+ Letters\n3.Countries\n4.random\n");
	scanf("%d", &choice);
	system("CLS");
	printf("Enter word:\n");
	scanf("%s", buffer1);
	printf("Enter its Hint(1 word):\n");
	scanf("%s", buffer2);

	AddWordFunc(choice, buffer1, buffer2);
}
void AddWordFunc(int choice, char buffer1[20], char buffer2[20]){
	system("CLS");
	if (choice == 1) 
	{
		FILE* easyWord;
		easyWord = fopen("words-easy.txt", "a"); //to append 
		if (easyWord == NULL) 
		{
			printf("Can't open file words-easy.txt\n");
			exit(1);
		}
		fprintf(easyWord, "\n%s %s", buffer1, buffer2);
		fclose(easyWord);
	}
	if (choice == 2)
	{
		FILE* hardWord;
		hardWord = fopen("words-hard.txt", "a"); //to append 
		if (hardWord == NULL)
		{
			printf("Can't open file words-hard.txt\n");
			exit(1);
		}
		fprintf(hardWord, "\n%s %s", buffer1, buffer2);
		fclose(hardWord);
	}
	if (choice == 3) {
		FILE* countryWord;
		countryWord = fopen("words-countries.txt", "a");
		if(countryWord == NULL)
		{
			printf("Can't open file words-countries.txt\n");
			exit(1);
		}
		fprintf(countryWord, "\n%s %s", buffer1, buffer2);
		fclose(countryWord);
	}
	if (choice == 4) {
		FILE* randWord;
		randWord = fopen("word-random.txt", "a");
		if (randWord == NULL)
		{
			printf("Can't open file words-countries.txt\n");
			exit(1);
		}
		fprintf(randWord, "\n%s %s", buffer1, buffer2);
		fclose(randWord);
	}
	printf("Word added\n");
	delay(2);
	
}
void MainMenu() {

	int menuChoice;

	system("CLS");//clears the screen
	printf("____________________________________\n");
	printf("\n%s", "Welcome to menu!");
	printf("\n%s\n\n", "Enter corresponding number");
	printf("%s\n", "1. Play Modes");
	printf("%s\n", "2. Add words to guess");
		printf("____________________________________\n");

	scanf("%d", &menuChoice);
	if (menuChoice == 1) {
		PlayMenu();
	}
	if (menuChoice == 2) {
		AddWord();
	}

}

int main()
{
	char choice = 'y';
	printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
	printf("                         HH   HH     AAA      NNN   NN  GGGGGGGG   MM      MM      AAA      NNN   NN     \n");
	printf("                         HH   HH    AA AA     NNNN  NN  GG         MMMM  MMMM     AA AA     NNNN  NN	 \n");
	printf("                         HHHHHHH   AA   AA    NN NN NN  GG    GGG  MM  MM  MM    AA   AA    NN NN NN     \n");
	printf("                         HH   HH  AAAAAAAAA   NN  NNNN  GG     GG  MM      MM   AAAAAAAAA   NN  NNNN     \n");
	printf("                         HH   HH AAA     AAA  NN    NN  GGGGGGGGG  MM      MM  AAA     AAA  NN   NNN     \n");
	printf("\n----------------------------------------------------------------------------------------------------------------------");
	printf("\n\n\n\n                                               <<Press Enter to continue>>   \n");
	getchar(); //press enter to continue
	MainMenu(); //directs to menu
	while (choice == 'y') {
		printf("\n<<Do you Want to Play Again?(y/n)>>\n");
		getchar();
		scanf("%c", &choice);
		if (choice == 'y') {
			MainMenu();
		}
	
	}
	printf("Thanks for using my app"); 
	return 0;
}
