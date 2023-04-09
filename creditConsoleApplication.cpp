#include <iostream>
#include <cmath>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <string>
#include <iomanip>
#define pathToFile "DB.txt"
using namespace std;

void menu(string message);
void createPerson();
void editPerson(int personCount);


struct person {
	string name;
	string prename;
	string value;
	float sum;
	int days;
	float percent;
};

void deletePerson(person* personArray, int index);
void reWriteDB(person* personArray);
int avaiblePersons = -1;





int main()
{

	menu("");

	return 0;

}


void menu(string message)
{

	enum class choises { add = 1, edit, info } choise;
	system("cls");
	if (!(message == "")) {
		cout << message;
	}
	ifstream readFile;
	readFile.open(pathToFile);
	if (readFile) {
		avaiblePersons = -1;
		string tempLine;
		while (!readFile.eof()) {
			std::getline(readFile, tempLine);
			avaiblePersons++;
		}
		cout << "Were found:\t" << avaiblePersons << " people" << endl;
	}
	else {
		cout << "No person was found." << endl;
	}
	readFile.close();
	cout << "\n\n--------------------------------------" << endl;
	cout << "-                                    -" << endl;
	cout << "\n\tChoose one action:" << endl;
	cout << "\t[1]. Add new person\n" <<
		"\t[2]. Edit person\n" << endl;
	cout << "-                                    -" << endl;
	cout << "--------------------------------------" << endl;
	int input;
	cin >> input;
	if (input > 2) {
		menu("[Warning] You should introduce only one option (1-3)\n\n");
	}
	choise = static_cast<choises>(input);
	switch (choise) {
	case choises::add:
		createPerson();
		break;
	case choises::edit:
		editPerson(avaiblePersons);
		break;
	}
}

void createPerson()
{
	string name, prename, value;
	float percent;
	float sum;
	int days;
	cin.ignore();
	cout << "Add new person:" << endl;
	cout << "Enter person name:\t_\b";
	getline(cin, name);
	cout << "Enter person prename:\t_\b";
	getline(cin, prename);
	cout << "Enter credit value (EUR | USD | MDL ):\t_\b";
	getline(cin, value);
	cout << "Enter the sum of credit:\t_\b";
	cin >> sum;
	cout << "Enter the period of credit:\t_\b";
	cin >> days;
	cout << "Enter person's credit percent:\t__%\b\b\b";
	cin >> percent;
	ofstream writeInFile;
	writeInFile.open(pathToFile, std::ios::app);
	writeInFile << name << "|" << prename << "|" << value << "|" << sum << "|" << days << "|" << percent << endl;
	menu("Person succesfully added!\n\n");



}
void enumAllPersons(person* personArray)
{
	for (int i = 0; i < avaiblePersons; i++) {
		cout << "[" << i << "] " << setw(10) << left << (personArray + i)->name << " " << setw(10) << left << (personArray + i)->prename << setw(10) << left << " " <<
			to_string((personArray + i)->sum) << setw(10) << left << " " << (personArray + i)->value << setw(10) << left << " " << (personArray + i)->percent << "%" << setw(15) << left << " " << (personArray + i)->days << " days" << endl;
	}
}

int chooseOnePerson(int totalPerson)
{
	int index;
	cout << "\n\n             Editing menu\n\n";
	cout << "--------------------------------------" << endl;
	cout << "-                                    -" << endl;
	cout << "\n      Introduce one index [0-" << (totalPerson - 1) << "]" << endl;
	cout << "-                                    -" << endl;
	cout << "--------------------------------------" << endl;
	cin >> index;
	return index;
}


void editPerson(int personCount)
{

	string message;
	string temp;
	ifstream readFile;
	readFile.open(pathToFile);
	string subTemp[6];
	int tempCount;
	int tempSubStr;
	person* personArray = new person[personCount];
	for (int i = 0; i < personCount; i++) {
		tempCount = 0;
		temp = "";
		tempSubStr = 0;
		std::getline(readFile, temp);
		for (int l = 0; l < temp.length(); l++) {
			if (tempCount == 0 && (temp[l] == '|')) {
				subTemp[tempCount] = temp.substr(0, l);
				tempSubStr = l + 1;
				tempCount++;
			}
			else if (tempCount != 0 && (temp[l] == '|')) {
				subTemp[tempCount] = temp.substr(tempSubStr, l - tempSubStr);
				tempSubStr = l + 1;
				tempCount++;
			}
			else if (l == temp.length() - 1) {
				subTemp[tempCount] = temp.substr(tempSubStr, l - tempSubStr + 1);
			}
		}

		(personArray + i)->name = subTemp[0];
		(personArray + i)->prename = subTemp[1];
		(personArray + i)->value = subTemp[2];
		(personArray + i)->sum = stof(subTemp[3]);
		(personArray + i)->days = stoi(subTemp[4]);
		(personArray + i)->percent = stof(subTemp[5]);
	}

	system("cls");
	enumAllPersons(personArray);
	readFile.close();
	enum class choises { edit = 'a', remove = 'b', back = 'c' } choosen;
	cout << "\n\n--------------------------------------" << endl;
	cout << "-                                    -" << endl;
	cout << "\n\tChoose one action:" << endl;
	cout << "\t[a]. Edit person\n" <<
		"\t[b]. Remove person\n" <<
		"\t[c]. Back to main menu\n" << endl;

	cout << "-                                    -" << endl;
	cout << "--------------------------------------" << endl;

	char input;
	cin >> input;

	choosen = static_cast<choises>(input);
	switch (choosen) {
	case choises::edit:
		system("cls");
		enumAllPersons(personArray);
		int editingPerson;
		editingPerson = chooseOnePerson(avaiblePersons);
		system("cls");
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "-                                                                               -" << endl;
		cout << "\n\tUser information:" << endl;
		cout << setw(15) << left << "\t[Index]" << ":" << setw(10) << right << editingPerson << "\t" << endl;
		cout << setw(15) << left << "\t[Name]" << ":" << setw(10) << right << (personArray + editingPerson)->name << "\t[1]. Edit name" << endl;
		cout << setw(15) << left << "\t[Prename]" << ":" << setw(10) << right << (personArray + editingPerson)->prename << "\t[2]. Edit prename" << endl;
		cout << setw(15) << left << "\t[Value]" << ":" << setw(10) << right << (personArray + editingPerson)->value << "\t[3]. Edit value of credit" << endl;
		cout << setw(15) << left << "\t[Sum]" << ":" << setw(10) << right << (personArray + editingPerson)->sum << "\t[4]. Edit credit sum" << endl;
		cout << setw(15) << left << "\t[Days]" << ":" << setw(10) << right << (personArray + editingPerson)->days << "\t[5]. Edit day count" << endl;
		cout << setw(15) << left << "\t[Percent]" << ":" << setw(10) << right << (personArray + editingPerson)->percent << "\t[6]. Edit percent of credit" << endl;
		cout << "\n\t\t\t[7]. Back to main menu" << endl;
		cout << "-                                                                               -" << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		enum class editChoise { nameOption = 1, prenameOption, valueOption, sumOption, daysOption, percentOption, backToMenu } editChoosed;
		int personInput;
		cin >> personInput;
		editChoosed = static_cast<editChoise>(personInput);
		cin.ignore();
		switch (editChoosed) {
		case editChoise::nameOption:
			system("cls");
			cout << "Introduce new name: " << endl;
			getline(cin, (personArray + editingPerson)->name);
			message = "[<>] Name was successfully changed to\t" + (personArray + editingPerson)->name + "\n\n";
			reWriteDB(personArray);
			delete[] personArray;
			menu(message);
			break;
		case editChoise::prenameOption:
			system("cls");
			cout << "Introduce new prename: " << endl;
			getline(cin, (personArray + editingPerson)->prename);
			message = "[<>] Prename was successfully changed to\t" + (personArray + editingPerson)->prename + "\n\n";
			reWriteDB(personArray);
			delete[] personArray;
			menu(message);
			break;
		case editChoise::valueOption:
			system("cls");
			cout << "Introduce new value (USD | EUR | MDL): " << endl;
			getline(cin, (personArray + editingPerson)->value);
			message = "[<>] Credit value was successfully changed to\t" + (personArray + editingPerson)->value + "\n\n";
			reWriteDB(personArray);
			delete[] personArray;
			menu(message);
			break;
		case editChoise::sumOption:
			system("cls");
			cout << "Introduce new sum: " << endl;
			cin >> (personArray + editingPerson)->sum;
			message = "[<>] Credit sum was successfully changed to\t" + to_string((personArray + editingPerson)->sum) + "\n\n";
			reWriteDB(personArray);
			delete[] personArray;
			menu(message);
			break;
		case editChoise::daysOption:
			system("cls");
			cout << "Introduce new period of credit: " << endl;
			cin >> (personArray + editingPerson)->days;
			message = "[<>] Credit period was successfully changed to\t" + to_string((personArray + editingPerson)->days) + "\n\n";
			reWriteDB(personArray);
			delete[] personArray;
			menu(message);
			break;
		case editChoise::percentOption:
			system("cls");
			cout << "Introduce new credit percent: " << endl;
			cin >> (personArray + editingPerson)->percent;
			message = "[<>] Credit percent was successfully changed to\t" + to_string((personArray + editingPerson)->percent) + "\n\n";
			reWriteDB(personArray);
			delete[] personArray;
			menu(message);
			break;
		case editChoise::backToMenu:
			system("cls");
			message = "[<>] You succesfully accesed main menu\n\n";
			delete[] personArray;
			menu(message);
			break;
		}

		break;

	case choises::remove:
		system("cls");
		enumAllPersons(personArray);
		int personToEdit;
		personToEdit = chooseOnePerson(avaiblePersons);
		deletePerson(personArray, personToEdit);
		delete[] personArray;
		menu("You succesfully removed one person!\n\n");

		break;

	case choises::back:
		delete[] personArray;
		menu("You succesfully returned to main menu!\n\n");
		break;
	}

}

void reWriteDB(person* personArray)
{
	ofstream reWriteFile;
	reWriteFile.open(pathToFile);
	for (int i = 0; i < avaiblePersons; i++) {
		reWriteFile << (personArray + i)->name << "|" << (personArray + i)->prename << "|" << (personArray + i)->value << "|" <<
			(personArray + i)->sum << "|" << (personArray + i)->days << "|" << (personArray + i)->percent << endl;;
	}
	reWriteFile.close();
}
void deletePerson(person* personArray, int index)
{
	ofstream reWriteFile;
	reWriteFile.open(pathToFile);
	for (int i = index; i < avaiblePersons - 1; i++) {
		*(personArray + i) = *(personArray + i + 1);
	}
	avaiblePersons--;
	for (int i = 0; i < avaiblePersons; i++) {
		reWriteFile << (personArray + i)->name << "|" << (personArray + i)->prename << "|" << (personArray + i)->value << "|" <<
			(personArray + i)->sum << "|" << (personArray + i)->days << "|" << (personArray + i)->percent << endl;
	}
	reWriteFile.close();
}