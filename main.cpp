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
			cout << "No Friends"<<endl;
			return;
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

World* Parse_World()
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
	return world;
}
Individual* CreateIndividual(string individualInfo[]){
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
	return curr;
}

void Individual_Carateristics(string individualInfo[]) {

	cout<<"Give us the First name: ";
	getline(cin,individualInfo[0]);
	cout<<"Give us the Last name: ";
	getline(cin,individualInfo[1]);
	cout<<"Give us the age: ";
	cin>>individualInfo[2];
	cout<<"Give us the gender(male/female): ";
	cin>>individualInfo[3];
	cout<<"Give us the University name: ";
	cin.ignore();
	getline(cin,individualInfo[4]);
	
}

void UserGivenInd(World *& w)
{
	Individual * ind = new Individual;
	string individual[5];

	Individual_Carateristics(individual);
	w=Insert_Individual(w, individual, ind);
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

Individual *DeleteRelations(Individual *individualSelf){
	 
	struct Friend *temp;
	struct Friend *prev;
	Individual *tempI;

	while(individualSelf->myFriends!=NULL){
		temp=individualSelf->myFriends;
		tempI=temp->self;
		temp=tempI->myFriends;

if(temp->self->Age == individualSelf->Age && strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 && 
			strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 &&
			temp->self->gender == individualSelf->gender
			&& strcmp(temp->self->University, individualSelf->University) == 0 && temp!=NULL)
			{
				individualSelf->myFriends->self->myFriends=temp->next;
			}	
else{
if(temp->next!=NULL){
	int x=0;
		
	while(temp->next!=NULL )
		{
			cout<<"Testing"<<endl;
			prev=temp;
			temp=temp->next;
			cout<<"Testing2"<<endl;
			// if(x>0)
			// individualSelf->myFriends->self->myFriends=individualSelf->myFriends->self->myFriends->next;
			x++;
			if(temp->self->Age == individualSelf->Age && strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 && 
			strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 &&
			temp->self->gender == individualSelf->gender
			&& strcmp(temp->self->University, individualSelf->University) == 0 && temp!=NULL)
			{
				prev->next=temp->next;
				break;
			}	
		}
		
}
else {
	temp=NULL;
}
}
		if(individualSelf->next==NULL)
			break;
		cout<<"Alive"<<endl;
		individualSelf->myFriends=individualSelf->myFriends->next;
}

	return individualSelf;

}
void DeleteUserGivenInd(World * w)
{
	Individual * ind = new Individual;
	string individual_del[5];

	Individual_Carateristics(individual_del);
	ind=CreateIndividual(individual_del);
	if(CheckIfIndividualExists(w,ind)){
		ind=CheckIfIndividualExists2(w,ind);
		ind=DeleteRelations(ind);
	}
	else{
		cout<<"Individual doesn't exist"<<endl;
		return;
	}

	if(ind->prev!=NULL)
		ind->prev->next=ind->next;

	else
		w->Head=ind->next;
	

	if(ind->next!=NULL)
	{
		ind->next->prev=ind->prev;
	}
	else
		w->Tail=ind->next;

	
	return;
}

Friend* RemoveFriend(Friend *head, Individual *individualSelf)
{
	struct Friend *temp;
    temp = (struct Friend*)malloc(sizeof(struct Friend));
	Friend *prev;
	temp= head;

	if(temp->next==NULL)
	{
		head=NULL;
		return head;
	}

if(temp->self->Age == individualSelf->Age && strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 && 
			strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 &&
			temp->self->gender == individualSelf->gender
			&& strcmp(temp->self->University, individualSelf->University) == 0 && temp!=NULL)
			{
				temp=temp->next;
				return head;
			}
else{
	while(temp !=NULL){

		if(temp->self->Age == individualSelf->Age && strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 && 
			strcmp(temp->self->FirstName, individualSelf->FirstName) == 0 &&
			temp->self->gender == individualSelf->gender
			&& strcmp(temp->self->University, individualSelf->University) == 0 && temp!=NULL)
			{
				prev->next=temp->next;
			}
		prev=temp;
		temp=temp->next;
	}
}
	
	return head;
}

void DeleteRelation(World * w, Individual* ind, Individual *fri)
{
	ind->myFriends = RemoveFriend(ind->myFriends, fri);
	fri->myFriends = RemoveFriend(fri->myFriends, ind);
}

bool CheckRelation(Friend *ind,Individual *individualSelf)
{
	while(ind !=NULL)
	{
		if(ind->self->Age == individualSelf->Age && strcmp(ind->self->FirstName, individualSelf->FirstName) == 0 && 
			strcmp(ind->self->FirstName, individualSelf->FirstName) == 0 &&
			ind->self->gender == individualSelf->gender
			&& strcmp(ind->self->University, individualSelf->University) == 0 && ind!=NULL)
				return true;

		ind=ind->next;
	}
	return false;
}

void DisplayMutualRelations(Individual *ind,Individual *ind2)
{
	Friend * temp,*temp2;
	temp=ind->myFriends;
	temp2=ind2->myFriends;

	while(temp!=NULL)
	{
		while(temp2!=NULL)
		{
			if(temp->self->Age == temp2->self->Age && strcmp(temp->self->FirstName, temp2->self->FirstName) == 0 && 
			strcmp(temp->self->LastName, temp2->self->LastName) == 0 &&
			temp->self->gender == temp2->self->gender
			&& strcmp(temp->self->University, temp2->self->University) == 0 && ind!=NULL)
			{
				cout<<temp->self->FirstName<<" "<<temp->self->LastName<<" is a mutual friend"<<endl;
			}
			temp2=temp2->next;
		}
		temp=temp->next;
	}
}

void ChooseIndividuals(World * w ,int bin)
{
	Individual * ind1 = new Individual;
	Individual * ind2 = new Individual;
	string individual1[5],individual2[5];

	Individual_Carateristics(individual1);
	Individual_Carateristics(individual2);
	ind1=CreateIndividual(individual1);
	ind2=CreateIndividual(individual2);

	if(CheckIfIndividualExists(w,ind1)==false || CheckIfIndividualExists(w,ind2)==false )
	{
		cout<<"One of thes Individuals doesn't exist cannot proceed"<<endl;
		return;
	}
	else
	{
		ind1=CheckIfIndividualExists2(w,ind1);
		ind2=CheckIfIndividualExists2(w,ind2);
		if(bin==0)
		{
			if(CheckRelation(ind1->myFriends,ind2))
			{
				cout<<"Relation Already Exists"<<endl;
				return;
			}
			CreateRelation(w,ind1,ind2);
		}
		else if(bin==1)
		{
			if(CheckRelation(ind1->myFriends,ind2))
				DeleteRelation(w,ind1,ind2);
			else
			{
				cout<<"Relation doesn't exist"<<endl;
				return;
			}
		}
		else if(bin==2)
		{
			DisplayMutualRelations(ind1,ind2);
		}	
	}

}

void Unload_World(World *w)
{
	ofstream ofFile("output.txt");
	Individual *ind=w->Head;
	Friend *mfriend=ind->myFriends;
	int lines=0;

	while(ind!=NULL)
	{
		while(mfriend!=NULL)
		{
			ofFile<<ind->FirstName<<"#"<<ind->LastName<<"#"<<ind->Age<<"#";
			if(ind->gender==0)
			{
				ofFile<<"male";
			}
			else
			{
				ofFile<<"female";
			}
			ofFile<<"#"<<ind->University<<",";
			
			ofFile<<mfriend->self->FirstName<<"#"<<mfriend->self->LastName<<"#"<<mfriend->self->Age<<"#";

			if(mfriend->self->gender==0)
			{
				ofFile<<"male";
			}
			else
			{
				ofFile<<"female";
			}
			ofFile<<"#"<<mfriend->self->University<<"\n";
			lines++;
			mfriend=mfriend->next;
		}
		ind=ind->next;
		if(ind !=NULL)
			mfriend=ind->myFriends;
	}
	ofFile.close();

	string Column1[lines],Column2[lines];
	ifstream inFile("output.txt");
	for(int i=0;i<lines;i++)
	{	
		getline(inFile, Column1[i], ',');
		getline(inFile, Column2[i], '\n');
	}

	for(int i=0;i<lines;i++)
	{	
		for(int j=0;j<lines;j++)
		{
			if(Column1[i]==Column2[j] && Column2[i]==Column1[j])
				{
					for(int k=j;k<lines-1;k++)
					{
						Column1[k]=Column1[k+1];
						Column2[k]=Column2[k+1];
						
					}
					lines--;
				}
			
		}
	}
	inFile.close();

	ofstream ofFile2("output.txt");
	for(int i=0;i<lines;i++)
		ofFile2<<Column1[i]<<","<<Column2[i]<<'\n';

}


int main(int argc, char** argv) {

	World *world = Initialize_World();
	
	world=Parse_World();
	//UserGivenInd(world);
	//DisplayRelations(world);
    //display(world);

	// DeleteUserGivenInd(world);
	// DisplayRelations(world);
	// display(world);

	Unload_World(world);

	//ChooseIndividuals(world,2);
	//DisplayRelations(world);
	return 0;
}