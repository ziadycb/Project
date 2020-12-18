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
	Individual *self;
	Friend *next;
};

struct Individual
{
	char FirstName[30], LastName[30], University[30];
	int Age;
	bool gender;
	Friend *myFriends;
	Individual *next;
	Individual *prev;
};

struct World
{
	Individual *Head, *Tail;
};

bool isEmpty_World(World * world) {
	return world->Head == NULL;
}

bool isEmpty_Friend(Friend * head) {
	return head == NULL;
}

World * Initialize_World() {
	World * w = new World;
	w->Head = NULL;
	w->Tail = NULL;

	return w;
}

Friend * Initialize_Friend() {
	Friend * head = new Friend;
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
	Individual *cur = world->Head;
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

Individual * CheckIfIndividualExists2(World* world, Individual* ind)
{
	
	Individual *cur = world->Head;
	while (cur != NULL)
	{
		//cout << "Comparing: " <<endl << ind->FirstName << "," << ind->LastName << "," << ind->Age << "," << ind->gender << "," << ind->University;
		//cout << endl << cur->FirstName << "," << cur->LastName << "," << cur->Age << "," << cur->gender << "," << cur->University << endl;
		if (strcmp(ind->FirstName, cur->FirstName) == 0 && strcmp(ind->LastName, cur->LastName) == 0 &&
			ind->Age == cur->Age && ind->gender == cur->gender
			&& strcmp(ind->University, cur->University) == 0)
		{
			return cur;
		}
		cur = cur->next;
	}
	
}

World * Insert_Individual(World * w, string individualInfo[], Individual *&ind)
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

void display(World *world)
{
	if (isEmpty_World(world))
	{
		cout << "World is emtpy";
		return;
	}
	Individual *cur = world->Head;
	while (cur != NULL)
	{
		cout << cur->FirstName << "," << cur->LastName << "," << cur->Age << "," << cur->gender << "," << cur->University << endl;
		cur = cur->next;
	}
	return;
}


Friend* InsertFriend(Friend *head, Individual *individualSelf)
{
	struct Friend *temp;
    temp = (struct Friend*)malloc(sizeof(struct Friend));

	temp->self = individualSelf;
	temp->next = head;

	return temp;
}

void CreateRelation(World * w, Individual* ind, Individual *fri)
{
	ind->myFriends = InsertFriend(ind->myFriends, fri);
	fri->myFriends = InsertFriend(fri->myFriends, ind);
}
void DisplayRelations(World * w)
{
	if (isEmpty_World(w))
	{
		cout << "World is emtpy while trying to display relations";
		return;
	}
	Individual *cur = w->Head;

	while (cur != NULL)
	{
		Friend* curr = cur->myFriends;
		if (isEmpty_Friend(curr))
		{
			cout << "No Friends";
		}
        
		while (curr != NULL)
		{
			cout << cur->FirstName << " " << cur->LastName << " is friends with " << curr->self->FirstName << " " << curr->self->LastName << endl;
			curr = curr->next;
		}
		
		cur = cur->next;
        cout<<"------------------"<<endl;
	}
	return;
}

void Parse_World()
{
	ifstream inFile("Filex.txt");
	string line1;
	string line2;
	World *world = Initialize_World();
	int count = 0;
	while (!inFile.eof())
	{
		getline(inFile, line1, ',');
		getline(inFile, line2, '\n');
		cout << line1 << "\n";


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
		cout << line2 << "\n";
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


		Individual * ind = new Individual;
		Individual * fri = new Individual;
		world = Insert_Individual(world, individual1, ind);
		world = Insert_Individual(world, individual2, fri);
		cout << ind->FirstName << "," << ind->LastName << "," << ind->Age << "," << ind->gender << "," << ind->University << endl;
		cout << fri->FirstName << "," << fri->LastName << "," << fri->Age << "," << fri->gender << "," << fri->University << endl;

        if(ind->myFriends==NULL)
            cout<<"HELLO";

		CreateRelation(world, ind, fri);
		cout << "--- END OF LOOP ----" << endl;
	}
	DisplayRelations(world);
	cout << "----- END -------------" << endl;
	display(world);
	inFile.close();
}

int main(int argc, char** argv) {

	Parse_World();

    
	return 0;
}