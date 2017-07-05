#include <iostream>

using namespace std;

struct Dictionary
{
	char* ukr_word;
	char* eng_word;
	Dictionary *RightWord;
	Dictionary *LeftWord;
};

void Translation(char* word, Dictionary **vocabulary)
{
	if (!(*vocabulary))
	{
		cout << "This word is not in the dictionary!"<<endl;
		return;
	}

	if (!strcmp(word, (**vocabulary).eng_word))
	{
		cout <<word<< " - "<<(**vocabulary).ukr_word << endl;
		return;
	}

	else
	{
		if (strcmp((**vocabulary).eng_word, word) > 0)
		{
			Translation(word, &(**vocabulary).LeftWord);
		}
		else if (strcmp((**vocabulary).eng_word, word) < 0)
		{
			Translation(word, &(**vocabulary).RightWord);
		}
	}
}

void addWord(char* e_word, char* u_word, Dictionary **vocabulary)
{
	if ((*vocabulary) == NULL)
	{
		(*vocabulary) = new Dictionary;
		(**vocabulary).eng_word = e_word;
		(**vocabulary).ukr_word = u_word;
		(**vocabulary).LeftWord = NULL;
		(**vocabulary).RightWord = NULL;
		return;
	}
	else
	{
		if (strcmp((**vocabulary).eng_word,e_word)<0)
		{
			addWord(e_word, u_word, &(**vocabulary).RightWord);
		}
		else
		{
			addWord(e_word, u_word, &(**vocabulary).LeftWord);
		}
	}
}

void printDictionary(Dictionary *vocabulary)
{
	
	if (vocabulary != NULL)
	{
		printDictionary(vocabulary->LeftWord);
		cout << (*vocabulary).eng_word << " - " << (*vocabulary).ukr_word << endl;
		printDictionary(vocabulary->RightWord);
	}
}

int main()
{
	setlocale(LC_ALL, "ukr");
	Dictionary *dictionary = NULL;
	char word[80];

	cout << "Enter the word which you want to translate: ";
	cin.getline(word,80);
	
	addWord("Apple", "Яблуко", &dictionary);
	addWord("Cherry", "Вишня", &dictionary);
	addWord("Potato", "Картопля", &dictionary);

	Translation(word, &dictionary);
	cout  << "  Dictionary" << endl;
	printDictionary(dictionary);
	system("pause");
	return 0;
}