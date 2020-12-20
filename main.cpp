#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <sstream>
#include <cstring>

using namespace std;

struct Individual;

struct Friend
{
	Individual* self;
	Friend* next;
};

struct Individual
{
	char FirstName[30], LastName[30], University[30];
	int Age;
	bool gender;
	Friend* myFriends;
	Individual* next;
	Individual* prev;
};

struct World
{
	Individual* Head, * Tail;
};

bool isEmpty_World(World* world) {
	return world->Head == NULL;
}

bool isEmpty_Friend(Friend* head) {
	return head == NULL;
}

World* Initialize_World() {
	World* w = new World;
	w->Head = NULL;
	w->Tail = NULL;

	return w;
}

Friend* Initialize_Friend() {
	Friend* head = new Friend;
	head = NULL;

	return head;
}
bool CheckIfIndividualExists(World* world, Individual* ind)
{
	if (isEmpty_World(world))
	{
		cout << "World Is Empty (while checking if individual exists)";
		return false;
	}
	Individual* cur = world->Head;
	while (cur != NULL)
	{
		//cout << "Comparing: " <<endl << ind->FirstName << "," << ind->LastName << "," << ind->Age << "," << ind->gender << "," << ind->University;
		//cout << endl << cur->FirstName << "," << cur->LastName << "," << cur->Age << "," << cur->gender << "," << cur->University << endl;
		if (strcmp(ind->FirstName, cur->FirstName) == 0 && strcmp(ind->LastName, cur->LastName) == 0 &&
			ind->Age == cur->Age && ind->gender == cur->gender
			&& strcmp(ind->University, cur->University) == 0)
		{
			return true;
		}
		cur = cur->next;
	}
	return false;
}

Individual* CheckIfIndividualExists2(World* world, Individual* ind)
{

	Individual* cur = world->Head;
	while (cur != NULL)
	{
		if (strcmp(ind->FirstName, cur->FirstName) == 0 && strcmp(ind->LastName, cur->LastName) == 0 &&
			ind->Age == cur->Age && ind->gender == cur->gender
			&& strcmp(ind->University, cur->University) == 0)
		{
			return cur;
		}
		cur = cur->next;
	}

}

World* Insert_Individual(World* w, string individualInfo[], Individual*& ind)
{
	Individual* curr = new Individual;
	strcpy_s(curr->FirstName, individualInfo[0].c_str());
	strcpy_s(curr->LastName, individualInfo[1].c_str());
	strcpy_s(curr->University, individualInfo[4].c_str());

	stringstream ss(individualInfo[2]);
	ss >> curr->Age;

	if (individualInfo[3] == "male")
	{
		curr->gender = 0;
	}
	else
	{
		curr->gender = 1;
	}
	if (CheckIfIndividualExists(w, curr) == true)
	{
		//cout << "Invidivual Exists -- Continuing..." << endl;
		ind = CheckIfIndividualExists2(w, curr);
		return w;
	}

	curr->next = NULL;
	curr->prev = NULL;
	curr->myFriends = Initialize_Friend();

	cout << "Inserting The Following: " << curr->FirstName << " , " << curr->LastName << " , " << curr->University << " , " << curr->Age << " , " << curr->gender << endl;

	if (isEmpty_World(w))
	{
		w->Head = curr;
		w->Tail = curr;
		ind = curr;
		return w;
	}
	w->Tail->next = curr;
	curr->prev = w->Tail;
	w->Tail = curr;
	ind = curr;
	return w;
}

void display(World* world)
{
	if (isEmpty_World(world))
	{
		cout << "World is emtpy";
		return;
	}
	Individual* cur = world->Head;
	while (cur != NULL)
	{
		cout << cur->FirstName << "," << cur->LastName << "," << cur->Age << "," << cur->gender << "," << cur->University << endl;
		cur = cur->next;
	}
	return;
}


Friend* InsertFriend(Friend* head, Individual* individualSelf)
{
	Friend* temp = new Friend;
	temp = (struct Friend*)malloc(sizeof(struct Friend));

	temp->self = individualSelf;
	temp->next = head;

	return temp;
}

void CreateRelation(World* w, Individual* ind, Individual* fri)
{
	ind->myFriends = InsertFriend(ind->myFriends, fri);
	fri->myFriends = InsertFriend(fri->myFriends, ind);
}

void DisplayRelations(World* w)
{
	if (isEmpty_World(w))
	{
		cout << "World is emtpy while trying to display relations";
		return;
	}
	Individual* cur = w->Head;

	while (cur != NULL)
	{
		Friend* curr = cur->myFriends;
		if (isEmpty_Friend(curr))
		{
			cout << "No Friends" << endl;
			return;
		}

		while (curr != NULL)
		{
			cout << cur->FirstName << " " << cur->LastName << " is friends with " << curr->self->FirstName << " " << curr->self->LastName << endl;
			curr = curr->next;
		}

		cur = cur->next;
		cout << "------------------" << endl;
	}
	return;
}

World* Parse_World()
{
	ifstream inFile("Filex.txt");
	string line1;
	string line2;
	World* world = Initialize_World();
	int count = 0;
	while (!inFile.eof())
	{
		getline(inFile, line1, ',');
		getline(inFile, line2, '\n');



		// Individual 1    
		string delimiter = "#";
		size_t pos = 0;
		string individual1[5];
		int i = 0;

		while ((pos = line1.find(delimiter)) != string::npos)
		{
			individual1[i] = line1.substr(0, pos);
			i++;
			line1.erase(0, pos + delimiter.length());
		}
		individual1[4] = line1;


		// Individual 2

		pos = 0;
		i = 0;
		string individual2[5];

		while ((pos = line2.find(delimiter)) != string::npos)
		{
			individual2[i] = line2.substr(0, pos);
			i++;
			line2.erase(0, pos + delimiter.length());
		}
		individual2[4] = line2;


		Individual* ind = new Individual;
		Individual* fri = new Individual;
		world = Insert_Individual(world, individual1, ind);
		world = Insert_Individual(world, individual2, fri);




		CreateRelation(world, ind, fri);

	}

	inFile.close();
	return world;
}
Individual* CreateIndividual(string individualInfo[]) {
	Individual* curr = new Individual;
	strcpy_s(curr->FirstName, individualInfo[0].c_str());
	strcpy_s(curr->LastName, individualInfo[1].c_str());
	strcpy_s(curr->University, individualInfo[4].c_str());

	stringstream ss(individualInfo[2]);
	ss >> curr->Age;

	if (individualInfo[3] == "male")
	{
		curr->gender = 0;
	}
	else
	{
		curr->gender = 1;
	}
	return curr;
}

void Individual_Carateristics(string individualInfo[]) {

	cin.ignore();
	cout << "Give us the First name: ";
	getline(cin, individualInfo[0]);
	cout << "Give us the Last name: ";
	getline(cin, individualInfo[1]);
	cout << "Give us the age: ";
	cin >> individualInfo[2];
	cout << "Give us the gender(male/female): ";
	cin >> individualInfo[3];
	cin.ignore();
	cout << "Give us the University name: ";
	getline(cin, individualInfo[4]);

}

void UserGivenInd(World*& w)
{
	Individual* ind = new Individual;
	string individual[5];

	Individual_Carateristics(individual);
	w = Insert_Individual(w, individual, ind);
}
/* This is obsolete now keeping it in case the program breaks

 void DeleteIndividual(World * w, string individualInfo[], Individual *&ind)
 {
	Individual * curr = new Individual;
	strcpy_s(curr->FirstName, individualInfo[0].c_str());
	strcpy_s(curr->LastName, individualInfo[1].c_str());
	strcpy_s(curr->University, individualInfo[4].c_str());

	stringstream ss(individualInfo[2]);
	ss >> curr->Age;
	if (individualInfo[3] == "male")
	{
		curr->gender = 0;
	}
	else
	{
		curr->gender = 1;
	}
	 if (CheckIfIndividualExists(w, curr) == true)
	{
		cout << "Invidivual Exists -- Continuing..." << endl;
		ind = CheckIfIndividualExists2(w, curr);
		return;
	}

	else
	{
		cout<<"This individual doesn't exist";
	}

 }
 */

Individual* DeleteRelations(Individual* individualSelf) {

	struct Friend* temp;
	struct Friend* prev;
	Individual* tempI;

	while (individualSelf->myFriends != NULL) {
		temp = individualSelf->myFriends;
		tempI = temp->self;
		temp = tempI->myFriends;

		if (temp->self->Age == individualSelf->Age && strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 &&
			strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 &&
			temp->self->gender == individualSelf->gender
			&& strcmp(temp->self->University, individualSelf->University) == 0 && temp != NULL)
		{
			individualSelf->myFriends->self->myFriends = temp->next;
		}
		else {
			if (temp->next != NULL) {
				int x = 0;

				while (temp->next != NULL)
				{
					//cout<<"Testing"<<endl;
					prev = temp;
					temp = temp->next;
					//cout<<"Testing2"<<endl;
					// if(x>0)
					// individualSelf->myFriends->self->myFriends=individualSelf->myFriends->self->myFriends->next;
					x++;
					if (temp->self->Age == individualSelf->Age && strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 &&
						strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 &&
						temp->self->gender == individualSelf->gender
						&& strcmp(temp->self->University, individualSelf->University) == 0 && temp != NULL)
					{
						prev->next = temp->next;
						break;
					}
				}

			}
			else {
				temp = NULL;
			}
		}
		if (individualSelf->next == NULL)
			break;
		//cout<<"Alive"<<endl;
		individualSelf->myFriends = individualSelf->myFriends->next;
	}

	return individualSelf;

}
void DeleteUserGivenInd(World* w)
{
	Individual* ind = new Individual;
	string individual_del[5];

	Individual_Carateristics(individual_del);
	ind = CreateIndividual(individual_del);
	if (CheckIfIndividualExists(w, ind)) {
		ind = CheckIfIndividualExists2(w, ind);
		ind = DeleteRelations(ind);
	}
	else {
		cout << "Individual doesn't exist" << endl;
		return;
	}

	if (ind->prev != NULL)
		ind->prev->next = ind->next;

	else
		w->Head = ind->next;


	if (ind->next != NULL)
	{
		ind->next->prev = ind->prev;
	}
	else
		w->Tail = ind->next;


	return;
}

Friend* RemoveFriend(Friend* head, Individual* individualSelf)
{
	struct Friend* temp;
	temp = (struct Friend*)malloc(sizeof(struct Friend));
	Friend* prev = new Friend;
	temp = head;

	if (temp->next == NULL)
	{
		head = NULL;
		return head;
	}

	if (temp->self->Age == individualSelf->Age && strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 &&
		strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 &&
		temp->self->gender == individualSelf->gender
		&& strcmp(temp->self->University, individualSelf->University) == 0 && temp != NULL)
	{
		head = temp->next;
		return head;
	}
	else {
		while (temp != NULL) {

			if (temp->self->Age == individualSelf->Age && strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 &&
				strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 &&
				temp->self->gender == individualSelf->gender
				&& strcmp(temp->self->University, individualSelf->University) == 0 && temp != NULL)
			{
				prev->next = temp->next;
			}
			prev = temp;
			temp = temp->next;
		}
	}

	return head;
}

void DeleteRelation(World* w, Individual* ind, Individual* fri)
{
	ind->myFriends = RemoveFriend(ind->myFriends, fri);
	fri->myFriends = RemoveFriend(fri->myFriends, ind);
}

bool CheckRelation(Friend* ind, Individual* individualSelf)
{
	while (ind != NULL)
	{
		if (ind->self->Age == individualSelf->Age && strcmp(ind->self->FirstName, individualSelf->FirstName) == 0 &&
			strcmp(ind->self->FirstName, individualSelf->FirstName) == 0 &&
			ind->self->gender == individualSelf->gender
			&& strcmp(ind->self->University, individualSelf->University) == 0 && ind != NULL)
			return true;

		ind = ind->next;
	}
	return false;
}

void DisplayMutualRelations(Individual* ind, Individual* ind2)
{
	Friend* temp = new Friend;
	Friend* temp2 = new Friend;
		
	temp = ind->myFriends;
	

	while (temp != NULL)
	{
		temp2 = ind2->myFriends;
		while (temp2 != NULL)
		{
			if (temp->self->Age == temp2->self->Age && strcmp(temp->self->FirstName, temp2->self->FirstName) == 0 &&
				strcmp(temp->self->LastName, temp2->self->LastName) == 0 &&
				temp->self->gender == temp2->self->gender
				&& strcmp(temp->self->University, temp2->self->University) == 0 && ind != NULL)
			{
				cout << temp->self->FirstName << " " << temp->self->LastName << " is a mutual friend" << endl;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
		
	}
}

void ChooseIndividuals(World* w, int bin)
{
	Individual* ind1 = new Individual;
	Individual* ind2 = new Individual;
	string individual1[5], individual2[5];

	Individual_Carateristics(individual1);
	Individual_Carateristics(individual2);
	ind1 = CreateIndividual(individual1);
	ind2 = CreateIndividual(individual2);

	if (CheckIfIndividualExists(w, ind1) == false || CheckIfIndividualExists(w, ind2) == false)
	{
		cout << "One of thes Individuals doesn't exist cannot proceed" << endl;
		return;
	}
	else
	{
		ind1 = CheckIfIndividualExists2(w, ind1);
		ind2 = CheckIfIndividualExists2(w, ind2);
		if (bin == 0)
		{
			if (CheckRelation(ind1->myFriends, ind2))
			{
				cout << "Relation Already Exists" << endl;
				return;
			}
			CreateRelation(w, ind1, ind2);
		}
		else if (bin == 1)
		{
			if (CheckRelation(ind1->myFriends, ind2))
				DeleteRelation(w, ind1, ind2);
			else
			{
				cout << "Relation doesn't exist" << endl;
				return;
			}
		}
		else if (bin == 2)
		{
			DisplayMutualRelations(ind1, ind2);
		}
	}

}

void Unload_World(World* w)
{
	ofstream ofFile("output.txt");
	Individual* ind = w->Head;
	Friend* mfriend = ind->myFriends;
	int lines = 0;


	while (ind != NULL)
	{

		while (mfriend != NULL)
		{
			ofFile << ind->FirstName << "#" << ind->LastName << "#" << ind->Age << "#";
			if (ind->gender == 0)
			{
				ofFile << "male";
			}
			else
			{
				ofFile << "female";
			}
			ofFile << "#" << ind->University << ",";

			ofFile << mfriend->self->FirstName << "#" << mfriend->self->LastName << "#" << mfriend->self->Age << "#";

			if (mfriend->self->gender == 0)
			{
				ofFile << "male";
			}
			else
			{
				ofFile << "female";
			}
			ofFile << "#" << mfriend->self->University << "\n";
			lines++;
			mfriend = mfriend->next;
		}
		ind = ind->next;
		if (ind != NULL)
			mfriend = ind->myFriends;
	}
	ofFile.close();

	string Column1[300], Column2[300];
	ifstream inFile("output.txt");
	for (int i = 0; i < lines; i++)
	{
		getline(inFile, Column1[i], ',');
		getline(inFile, Column2[i], '\n');
	}

	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < lines; j++)
		{
			if (Column1[i] == Column2[j] && Column2[i] == Column1[j])
			{
				for (int k = j; k < lines - 1; k++)
				{
					Column1[k] = Column1[k + 1];
					Column2[k] = Column2[k + 1];

				}
				lines--;
			}

		}
	}
	inFile.close();

	ofstream ofFile2("output.txt");
	for (int i = 0; i < lines - 1; i++)
	{
		ofFile2 << Column1[i] << "," << Column2[i] << '\n';
	}
	ofFile2 << Column1[lines - 1] << "," << Column2[lines - 1];

}

bool Search_Relation(World* w)
{
	Individual* ind1 = new Individual;
	string individual1[5];
	Individual_Carateristics(individual1);
	ind1 = CreateIndividual(individual1);

	if (CheckIfIndividualExists(w, ind1) == false)
		return NULL;

	else
	{
		cout << "Individual Found";
		return true;
	}
}

int CountMutualRelations(Individual* indx, Individual* ind2)
{
	Friend* temp, * temp2;
	temp = indx->myFriends;
	temp2 = ind2->myFriends;
	int counter = 0;

	while (temp != NULL)
	{
		while (temp2 != NULL)
		{
			if (temp->self->Age == temp2->self->Age && strcmp(temp->self->FirstName, temp2->self->FirstName) == 0 &&
				strcmp(temp->self->LastName, temp2->self->LastName) == 0 &&
				temp->self->gender == temp2->self->gender
				&& strcmp(temp->self->University, temp2->self->University) == 0 && indx != NULL)
			{
				counter++;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
	return counter;
}

/* This function suggest friends based on a point system i used every criteria Age,University,gender and mutual friends
the smaller the age differnce the more point , same gender is extra points , same univesity is extra points too
for every mutual friend extra points.
*/
void SuggestFriend(World* w)
{
	Individual* ind1 = new Individual;
	Individual* ind = w->Head;
	string individual1[5];
	int ageD;
	int points[100] = { 0 };
	string fullnames[100];
	int counter = 0;

	Individual_Carateristics(individual1);
	ind1 = CreateIndividual(individual1);

	if (CheckIfIndividualExists(w, ind1))
	{
		ind1 = CheckIfIndividualExists2(w, ind1);
		while (ind != NULL)
		{

			if (strcmp(ind->FirstName, ind1->FirstName) == 0 &&
				ind->Age == ind1->Age && strcmp(ind->LastName, ind1->LastName) == 0 &&
				strcmp(ind->University, ind1->University) == 0) {
				ind = ind->next;
			}

			else {
				fullnames[counter] = string(ind->FirstName) + " " + string(ind->LastName);
				if (ind->Age >= ind1->Age)
					ageD = ind->Age - ind1->Age;
				else
				{
					ageD = ind1->Age - ind->Age;
				}

				if (ageD <= 5)
					points[counter] += 5;

				if (ageD > 5 && ageD <= 15)
					points[counter] += 2;

				if (ageD > 15 && ageD < 25)
					points[counter] += 1;

				if (ind->gender == ind1->gender)
					points[counter] += 1;

				if (string(ind->University) == string(ind1->University))
					points[counter] += 5;

				points[counter] += CountMutualRelations(ind, ind1);

				ind = ind->next;
				counter++;
			}

		}
	}

	else
	{
		cout << "Individual doesn't exist";
		return;
	}

	for (int i = 0; i < counter; i++)
	{
		for (int j = 0; j < counter - i; j++)
		{
			if (points[j] < points[j + 1])
			{
				swap(points[j], points[j + 1]);
				swap(fullnames[j], fullnames[j + 1]);
			}
		}
	}

	for (int i = 0; i < counter; i++)
	{
		if(points[i]==0){}
		
		else
			cout << fullnames[i] << " has : " << points[i] << endl;
	}

}


int main(int argc, char** argv) {

	World* world = Initialize_World();
	int x = 0; //to break menu

	world = Parse_World();

	int userInput;
	while (x == 0) {

		cout << endl << "Enter the number of what you want to do" << endl;
		cout << "1- Add Individual to the list " << endl;
		cout << "2- Delete Individual from the list " << endl;
		cout << "3- Search for a person in the list " << endl;
		cout << "4- Create a relation between 2 individuals" << endl;
		cout << "5- Remove a relation between 2 individuals" << endl;
		cout << "6- Get mutual friends of 2 individuals" << endl;
		cout << "7- Output the world to a new txt file" << endl;
		cout << "8- Finish the program" << endl;
		cout << "9- Suggest a friend for individual" << endl;
		cout << "10- Display all relations in console" << endl;
		cout << "11- Display all Individuals in console" << endl << endl;
		cin >> userInput;

		switch (userInput)
		{
		case 1:
			UserGivenInd(world);
			//DisplayRelations(world);
			//display(world);
			break;

		case 2:
			DeleteUserGivenInd(world);
			// DisplayRelations(world);
			// display(world);
			break;

		case 3:
			Search_Relation(world);
			break;

		case 4:
			ChooseIndividuals(world, 0);
			//DisplayRelations(world);
			break;

		case 5:
			ChooseIndividuals(world, 1);
			//DisplayRelations(world);
			break;

		case 6:
			ChooseIndividuals(world, 2);
			//DisplayRelations(world);
			break;

		case 7:
			Unload_World(world);
			break;

		case 8:
			x = 1;
			break;

		case 9:
			SuggestFriend(world);
			break;

		case 10:
			DisplayRelations(world);
			break;

		case 11:
			display(world);
			break;
		}
	}

	return 0;
}