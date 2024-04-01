#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Student
{
private:
	string Name;
	double Gpa;
	int choiceNo;
	int steal;
public:
	string Choices, Won;
	Student(string name, double gpa, string choices, string won, int steaL) {
		Name = name;
		Gpa = gpa;
		Choices = choices;
		Won = won;
		steal = steaL;
	}
	string getName() { return Name; }
	void setName(string name) { Name = name; }

	double getGpa() { return Gpa; }
	void setGpa(double gpa) { Gpa = gpa; }

	int getChoiceNo() { return choiceNo; }
	void setChoiceNo(int choiceno) { choiceNo = choiceno; }

	int getStealNo() { return steal; }
	void setStealNo(int steaL) { steal = steaL; }

};

bool sortByGpa(Student& A, Student& B)
{
	return (A.getGpa() > B.getGpa());
}

bool resortByGpa(Student& A, Student& B)
{
	return (A.getGpa() < B.getGpa());
}

void fillVector(vector<Student>&);
void Round1(vector<Student>&, string[], int[], vector<vector<Student>>&);
void Round2(vector<Student>&, char specialSport[4], int[], vector<vector<Student>>&);
void Round3(vector<Student>&, string[], int[], vector<vector<Student>>&);
void Round4(vector<Student>&, string[], int[], vector<vector<Student>>&);

int main()
{
	vector<Student> myClass;
	vector<Student> c;
	vector<Student> d;
	vector<Student> g;
	vector<Student> r;
	vector<Student> s;
	vector<Student> t;
	vector<vector<Student>> choice;

	choice.push_back(c);
	choice.push_back(d);
	choice.push_back(g);
	choice.push_back(r);
	choice.push_back(s);
	choice.push_back(t);

	char special[10], specialSport[4];
	string Sport[7];
	int space[7];

	ifstream myfile("VacancyFile.txt");

	if (myfile.is_open())
	{
		for (int i = 0; i < 7 && !myfile.eof(); i++) {
			myfile >> Sport[i];
			myfile.ignore(1);
			myfile >> space[i];
		}

		for (int i = 7; i == 7 && !myfile.eof(); i++)
			myfile >> special >> specialSport;
		myfile.close();
	}
	else cout << "Unable to open file";

	fillVector(myClass);
	Round1(myClass, Sport, space, choice);
	Round2(myClass, specialSport, space, choice);
	Round3(myClass, Sport, space, choice);
	Round4(myClass, Sport, space, choice);

	return 0;

}

void fillVector(vector<Student>& newMyClass) {
	ifstream file("StudentInfo.txt");
	string name, sgpa, choices, won;
	double gpa;
	int steal;
	if (file.is_open())
	{
		for (int i = 0; i < 20; i++) {
			getline(file, name);
			getline(file, sgpa);
			gpa = stod(sgpa);
			getline(file, choices);
			getline(file, won);
			steal = 0;

			Student newStudent(name, gpa, choices, won, steal);
			newMyClass.push_back(newStudent);
		}
		file.close();
	}
	else cout << "Unable to open file";
}

void Round1(vector<Student>& newClass, string sport[], int space[], vector<vector<Student>>& choice) {


	for (unsigned int i = 0; i < newClass.size(); i++) {

		char choice1 = newClass[i].Choices[0];
		switch (choice1) {
		case 'C':choice[0].push_back(newClass[i]);  break;
		case 'D':choice[1].push_back(newClass[i]);  break;
		case 'G':choice[2].push_back(newClass[i]);  break;
		case 'R':choice[3].push_back(newClass[i]);  break;
		case 'S':choice[4].push_back(newClass[i]);  break;
		case 'T':choice[5].push_back(newClass[i]);  break;
		}

	}

	cout << "Round1" << endl;
	cout << "===============" << endl;

	for (int x = 0; x < 6; x++) {
		cout << endl << sport[x] << endl;
		sort(choice[x].begin(), choice[x].end(), resortByGpa);

		vector <Student>::iterator it = choice[x].begin();
		while (choice[x].size() > space[x])
		{
			if ((*it).Won[0] != '1')
				it = choice[x].erase(it);
			else it++;
		}
		it = choice[x].begin();
		sort(choice[x].begin(), choice[x].end(), sortByGpa);
		while (it != choice[x].end()) {
			for (int i = 0; i < 20; i++) {
				if ((*it).getName() == newClass[i].getName()) {
					newClass[i].setChoiceNo(1);
					(*it).setChoiceNo(1);
				}
			}
			cout << (*it).getName() << " " << (*it).getGpa() << " Choice" << (*it).getChoiceNo() << endl;
			it++;
		}
	}

}

vector<vector<Student>>& stealing(int wons, int space[], int pos, vector<Student>& newClass, char specialSport[4], vector<vector<Student>>& choice) {
	for (int x = 0; x < 6; x++) {
		sort(choice[x].begin(), choice[x].end(), resortByGpa);
		for (int j = 0; j < space[pos]; j++) {
			if (x == pos) {
				if (choice[x][j].Won[0] == '1')
					wons++;
			}
		}
	}
	while (wons < 3)
	{
		for (int i = 0; i < 20; i++) {
			if (newClass[i].Choices[2] == specialSport[0] && newClass[i].Won[2] == '1') {
				for (int j = 0; j < space[pos]; j++) {
					if (choice[pos][j].Won[0] != 1) {
						if (newClass[i].getChoiceNo() == 1) {
							cout << newClass[i].getName() << "is stolen from " << newClass[i].Choices[0] << " to " << specialSport << endl;
							for (int x = 0; x < 6; x++) {

								vector <Student>::iterator it = choice[x].begin();
								it = choice[x].begin();
								while (it != choice[x].end()) {
									if ((*it).getName() == newClass[i].getName())
										it = choice[x].erase(it);
									else
										it++;
								}
							}
							newClass[i].setStealNo(1);
							newClass[i].setChoiceNo(2);
							choice[pos][j].setChoiceNo(2);
						}
						choice[pos][j] = newClass[i];
						j = 4;
					}
				}
				wons++;
			}
			else if (newClass[i].Choices[4] == specialSport[0] && newClass[i].Won[4] == '1') {
				for (int j = 0; j < space[pos]; j++) {
					if (choice[pos][j].Won[0] != '1') {
						if (newClass[i].getChoiceNo() == 1) {
							cout << newClass[i].getName() << "is stolen from " << newClass[i].Choices[0] << " to " << specialSport << endl;
							for (int x = 0; x < 6; x++) {

								vector <Student>::iterator it = choice[x].begin();
								it = choice[x].begin();
								while (it != choice[x].end()) {
									if ((*it).getName() == newClass[i].getName())
										it = choice[x].erase(it);
									else
										it++;
								}
							}
							newClass[i].setStealNo(1);
							newClass[i].setChoiceNo(3);
							choice[pos][j].setChoiceNo(3);
						}
						choice[pos][j] = newClass[i];
						j = 4;
					}
				}
				wons++;
			}

		}
		if (wons < 3) {
			cout << "No more winning records students can be steal" << endl; break;
		}
	}

	if (wons >= 3)
		cout << "Enough" << endl;

	return choice;
}
void Round2(vector<Student>& newClass, char specialSport[4], int space[], vector<vector<Student>>& choice) {

	cout << endl << "Round 2" << endl;
	cout << "===============" << endl;
	int wons = 0, pos = 0;

	switch (specialSport[0]) {
	case 'C': {
		choice = stealing(wons, space, pos, newClass, specialSport, choice);
		break;
	}
	case 'D': {
		pos = 1;
		choice = stealing(wons, space, pos, newClass, specialSport, choice);
		break;
	}
	case 'G': {
		pos = 2;
		choice = stealing(wons, space, pos, newClass, specialSport, choice);
		break;
	}
	case 'R': {
		pos = 3;
		choice = stealing(wons, space, pos, newClass, specialSport, choice);
		break;
	}
	case 'S': {
		pos = 4;
		choice = stealing(wons, space, pos, newClass, specialSport, choice);
		break;
	}
	case 'T': {
		pos = 5;
		choice = stealing(wons, space, pos, newClass, specialSport, choice);
		break;
	}
	}
}


void Round3(vector<Student>& newClass, string sport[], int space[], vector<vector<Student>>& choice) {

	for (unsigned int i = 0; i < newClass.size(); i++) {

		char choice2 = newClass[i].Choices[2];
		if (newClass[i].getChoiceNo() != 1 && newClass[i].getStealNo() != 1) {
			switch (choice2) {
			case 'C':choice[0].push_back(newClass[i]);  break;
			case 'D':choice[1].push_back(newClass[i]);  break;
			case 'G':choice[2].push_back(newClass[i]);  break;
			case 'R':choice[3].push_back(newClass[i]);  break;
			case 'S':choice[4].push_back(newClass[i]);  break;
			case 'T':choice[5].push_back(newClass[i]);  break;
			}
		}
	}

	cout << endl << "Round3" << endl;
	cout << "===============" << endl;

	for (int x = 0; x < 6; x++) {
		cout << endl << sport[x] << endl;
		sort(choice[x].begin(), choice[x].end(), resortByGpa);

		vector <Student>::iterator it = choice[x].begin();
		while (choice[x].size() > space[x])
		{
			if ((*it).Won[2] != '1' && (*it).getChoiceNo() != 1)
				it = choice[x].erase(it);
			else it++;
		}
		it = choice[x].begin();
		sort(choice[x].begin(), choice[x].end(), sortByGpa);
		while (it != choice[x].end()) {
			for (int i = 0; i < 20; i++) {
				if ((*it).getName() == newClass[i].getName() && (*it).getChoiceNo() != 1 && (*it).getChoiceNo() != 3) {
					newClass[i].setChoiceNo(2);
					(*it).setChoiceNo(2);
				}
			}
			cout << (*it).getName() << " " << (*it).getGpa() << " Choice" << (*it).getChoiceNo() << endl;
			it++;
		}
	}
}

void Round4(vector<Student>& newClass, string sport[], int space[], vector<vector<Student>>& choice) {

	vector<Student> left;
	vector<string> sportsV;


	for (unsigned int i = 0; i < newClass.size(); i++) {

		char choice2 = newClass[i].Choices[4];
		if (newClass[i].getChoiceNo() != 1 && newClass[i].getChoiceNo() != 2 && newClass[i].getStealNo() != 1) {
			switch (choice2) {
			case 'C':choice[0].push_back(newClass[i]);  break;
			case 'D':choice[1].push_back(newClass[i]);  break;
			case 'G':choice[2].push_back(newClass[i]);  break;
			case 'R':choice[3].push_back(newClass[i]);  break;
			case 'S':choice[4].push_back(newClass[i]);  break;
			case 'T':choice[5].push_back(newClass[i]);  break;
			}
		}
	}

	cout << endl << "Round4" << endl;
	cout << "===============" << endl;

	for (int x = 0; x < 6; x++) {

		sort(choice[x].begin(), choice[x].end(), resortByGpa);

		vector <Student>::iterator it = choice[x].begin();
		while (choice[x].size() > space[x])
		{
			if ((*it).Won[4] != '1' && (*it).getChoiceNo() != 1 && (*it).getChoiceNo() != 2)

				it = choice[x].erase(it);

			else it++;
		}
		it = choice[x].begin();
		sort(choice[x].begin(), choice[x].end(), sortByGpa);
		while (it != choice[x].end()) {
			for (int i = 0; i < 20; i++) {
				if ((*it).getName() == newClass[i].getName() && (*it).getChoiceNo() != 1 && (*it).getChoiceNo() != 2) {
					newClass[i].setChoiceNo(3);
					(*it).setChoiceNo(3);
				}
			}
			it++;
		}
	}


	for (int x = 0; x < 6; x++) {
		if (choice[x].size() < space[x]) {
			sportsV.push_back(sport[x]);

		}

	}

	for (int y = 0; y < newClass.size(); y++) {
		if (newClass[y].getChoiceNo() != 1 && newClass[y].getChoiceNo() != 2 && newClass[y].getChoiceNo() != 3) {
			newClass[y].setChoiceNo(4);
			left.push_back(newClass[y]);
		}

	}


	for (int a = 0; a < left.size(); a++) {
		if (sportsV.size() > 0) {
			srand(time(0));
			int RandomInt = rand() % sportsV.size();

			char sportLeft = sportsV[RandomInt][0];

			switch (sportLeft) {
			case 'C':choice[0].push_back(left[a]); cout << left[a].getName() << "has randomly assign to " << sport[0] << endl;  break;
			case 'D':choice[1].push_back(left[a]); cout << left[a].getName() << "has randomly assign to " << sport[1] << endl;  break;
			case 'G':choice[2].push_back(left[a]); cout << left[a].getName() << "has randomly assign to " << sport[2] << endl; break;
			case 'R':choice[3].push_back(left[a]); cout << left[a].getName() << "has randomly assign to " << sport[3] << endl; break;
			case 'S':choice[4].push_back(left[a]); cout << left[a].getName() << "has randomly assign to " << sport[4] << endl; break;
			case 'T':choice[5].push_back(left[a]); cout << left[a].getName() << "has randomly assign to " << sport[5] << endl; break;
			}
		}
	}

	for (int x = 0; x < 6; x++) {
		cout << endl << sport[x] << endl;
		sort(choice[x].begin(), choice[x].end(), resortByGpa);

		vector <Student>::iterator it = choice[x].begin();

		it = choice[x].begin();
		sort(choice[x].begin(), choice[x].end(), sortByGpa);
		while (it != choice[x].end()) {
			if ((*it).getChoiceNo() == 4) {

				cout << (*it).getName() << " " << (*it).getGpa() << "Random" << endl;
			}
			else cout << (*it).getName() << " " << (*it).getGpa() << " Choice" << (*it).getChoiceNo() << endl;
			it++;
		}
	}
}