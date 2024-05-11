#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Contact {
	public:
    string name;
    string phone;
    Contact* next;
    
};


class LinkedList{
	
    private:
		Contact* head;
    
	public:
	    LinkedList()
		{
	        head = NULL;
	    }
	
	    ~LinkedList()
		{
	        Contact* current = head;
	        while(current != NULL)
			{
	            Contact* next = current->next;
	            delete current;
	            current = next;
	        }
	    }
	
	bool Repeat(string name, string phone) {
        Contact* current = head;
        while (current != NULL) {
            if (current->phone == phone) {
                return true; 
            }
            current = current->next;
        }
        return false; 
    }
	
	
	    void addContact(string name, string phoneNumber) {
        	 Contact* newContact = new Contact;
        
        
        newContact->name = name;
        newContact->phone = phoneNumber;
        newContact->next = NULL;
        if (head == NULL) {
            
            head = newContact;
        } else {
           
            Contact* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newContact;
        }
        
		
       
		
		
    }

	
	    void searchByName(const char filename[100], string searchName) {
        ifstream file(filename);
        if (!file){
            cout<<"Error opening file."<<endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(file, line)){
        	
            size_t pos = line.find(',');
            if(pos != string::npos) {
                string name = line.substr(0, pos);
                string phoneNumber = line.substr(pos + 1);

                if (name == searchName) {
                    cout << "Contact found: Name: " << name << ", Phone: " << phoneNumber << endl;
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            cout << "Contact not found." << endl;
        }
        

        file.close();
    }
    
    
		void searchByNumber(const char filename[100], string searchNumber) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file." << endl;
            return;
        }

        string line;
        bool found = false;

        while (getline(file, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                string name = line.substr(0, pos);
                string phoneNumber = line.substr(pos + 1);

                if (phoneNumber == searchNumber) {
                    cout << "Contact found: Name: " << name << ", Phone: " << phoneNumber << endl;
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            cout << "Contact not found." << endl;
        }
        

        file.close();
    }
		
	    // Function to update a contact in the phonebook and the file
	    
void updateContactByName(const char filename[100], string searchName, string newName, string newPhoneNumber) {
   
    if (head == NULL) {
        cout << "Phonebook is empty." << endl;
        return;
    }
    Contact* current = head;
    while (current != NULL) {
        if (current->name == searchName) {
        	
            
            current->name = newName;
            current->phone= newPhoneNumber;
            cout << "Contact updated." << endl;
            storeContactsToFile(filename);
            return;
        }
        current = current->next;
    }

    cout << "Contact not found." << endl;
}


	    
void updateContactByNumber(const char filename[100], string searchNumber, string newName, string newPhoneNumber) {
    
    if (head == NULL) {
        cout << "Phonebook is empty." << endl;
        return;
    }

   
    Contact* current = head;
    while (current != NULL) {
        if (current->phone == searchNumber) {
            
            current->name = newName;
            current->phone= newPhoneNumber;
            cout << "Contact updated." << endl;
            storeContactsToFile(filename);
            return;
        }
        current = current->next;
    }

    cout << "Contact not found." << endl;
}

	
	void deleteContactByName(const  char filename[100], const string name) { // Function to Delete contact by name
	    	
	    	
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: cannot open file " << filename << endl;
        return;
    }

    string line;
    bool found = false;

    ofstream outfile("temp.txt");
    while (getline(infile, line)) {
        size_t pos = line.find(',');
        if (pos == string::npos) {
            cerr << "Error: invalid line in file " << filename << endl;
            infile.close();
            outfile.close();
            remove("temp.txt");
            return;
        }

        string contactName = line.substr(0, pos);
        string phone = line.substr(pos + 1);

        if (contactName != name) {
            outfile << line << endl;
        }
        else {
            found = true;
        }
    }


    infile.close();
    outfile.close();

    if (!found) {
        cerr << "Error: contact not found in file " << filename << endl;
        remove("temp.txt");
        return;
    }

    remove(filename);
    rename("temp.txt", filename);
    cout << "Contact deleted successfully from file " << filename << endl;
}

	    
	    
	void deleteContactByNumber(const char filename[100],  string num) { // Function to Delete contact by name
	    	
	    	
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: cannot open file "<< filename << endl;
        return;
    }

    string line;
    bool found = false;

    ofstream outfile("temp.txt");
    while (getline(infile, line)) {
        size_t pos = line.find(',');
        if (pos==string::npos) {
            cerr<<"Error: invalid line in file "<<filename<<endl;
            infile.close();
            outfile.close();
            remove("temp.txt");
            return;
        }

        string contactName=line.substr(0,pos);
        string phone=line.substr(pos + 1);

        if (phone!=num) {
            outfile<<line<<endl;
        }
        else {
            found=true;
        }
    }


    infile.close();
    outfile.close();

    if (!found) {
        cerr << "Error: contact not found in file " << filename << endl;
        remove("temp.txt");
        return;
    }

    remove(filename);
    rename("temp.txt", filename);
    cout << "Contact deleted successfully from file " << filename << endl;
}
	    
		void deleteAllContacts() 	// Function to Delete all the contacts
		{
			Contact* current = head;
			while(head != NULL)
			{
				Contact* temp = head;
				head = head->next;
				delete temp;
			}
		}
	    
	    
	    void sortContacts() 	// Function to Sort all the contacts in Alphabetical order
		{
	        bool swapped = true;
	        while(swapped)
			{
	            swapped = false;
	            Contact* curr = this->head;
	            Contact* prev = NULL;
	
	            while(curr != NULL && curr->next != NULL)
				{
	                Contact* next = curr->next;
	
	                if(curr->name > next->name)
					{
	                    swapped = true;
	
	                    curr->next = next->next;
	                    next->next = curr;
	
	                    if(prev == NULL){
	                        this->head = next;
	                    } 
						else{
	                        prev->next = next;
	                    }
	                    prev = next;
	                } 
					else{
	                    prev = curr;
	                    curr = next;
	                }
	            }
	        }
	    }
	
	
	    void storeContactsToFile(const char filename[100]) {
	    	
        ofstream file(filename);
        
        if (!file) {
            cout << "Error opening file." << endl;
            return;
        }
       
        Contact* current = head;
        while (current != NULL) {
            file << current->name << "," << current->phone << endl;
            current = current->next;
            
        }
        
        file.close();
        cout << "Contacts stored in the file." << endl;
       
    }
    

     // Function to display all contacts from a file
     
     void loadFromFile(const char filename[100]) 
		{
	    	
	        ifstream infile(filename);
	        if (!infile.is_open()){
	        	
	            cout << "Failed to open file." << endl;
	            return;
	        }
	        string line;
	        while (getline(infile, line)) {
	            size_t pos = line.find(",");
	            if (pos == string::npos) {
	                continue;
	            }
	            string name = line.substr(0, pos);
	            string phone = line.substr(pos + 1);
	            addContact(name, phone);
	        }
	        infile.close();
	    }
     
     	void displayContacts() {
		        Contact* current = head;
		        if (head == NULL){
		            cout << "Phonebook is empty." << endl;
		        }
				 else{
		        	 while (current != NULL){
		        	 	cout << "\t\t\t\t\t---------------------------" << endl;
		        	 	cout << "\t\t\t\t\t"<<current->name << ": " << current->phone << endl;
        	 	  	    cout << "\t\t\t\t\t---------------------------" << endl;
		        	 	
		            
		            current = current->next;
		        }
				}
	    }

};


int main(){
	
	cout<<"\n";
	
	LinkedList contacts;
	
    contacts.loadFromFile("contacts.txt");
    
	string name, newname, no, newno, sure;
	int choice;

do{
	cout<<"\n";
	cout<<"\t\t\t\t---------------------------------------------"<<endl;
	cout<<"\t\t\t\t\t   PHONEBOOK APPLICATION"<<endl;
	cout<<"\t\t\t\t---------------------------------------------\n"<<endl;
	cout<<"\t\t\t\t _____________________________________________\n"<<endl;
	cout<<"\t\t\t\t|    Press 1 for Add Contacts                 |"<<endl;
	cout<<"\t\t\t\t|    Press 2 for Search Contacts by Name      |"<<endl;
	cout<<"\t\t\t\t|    Press 3 for Search Contacts by Number    |"<<endl;
	cout<<"\t\t\t\t|    Press 4 for Update Contacts by Name      |"<<endl;
	cout<<"\t\t\t\t|    Press 5 for Update Contacts by Number    |"<<endl;
	cout<<"\t\t\t\t|    Press 6 for Delete Contacts by Name      |"<<endl;
	cout<<"\t\t\t\t|    Press 7 for Delete Contacts by Number    |"<<endl;
	cout<<"\t\t\t\t|    Press 8 for Delete All Contacts          |"<<endl;
	cout<<"\t\t\t\t|    Press 9 for Display Contacts             |"<<endl;
	cout<<"\t\t\t\t|    Press 0 for Exit                         |"<<endl;
	cout<<"\t\t\t\t _____________________________________________\n"<<endl;	
	
	cout<<"Enter your Choice : ";
    cin>>choice;
	
	switch(choice)
	{
		case 1:
			
			// Add contacts
			cout<<"\n\t\t'Add contacts' "<<endl;
			cout<<"\nEnter the Name: ";
			cin>>name;
			
			cout<<"\nEnter the Number: ";
			cin>>no;
			if(contacts.Repeat(name,no)){
				cout<<"No Duplication is Allowed"<<endl;
			}
			else{
				contacts.addContact(name,no);
				contacts.storeContactsToFile("contacts.txt");
			}
		
			
			break;
			
		case 2:
			
			// Search contact by name
			cout<<"\n\t\t'Search Contact by Name'"<<endl;
			cout<<"\nEnter the Name you want to search: ";
			cin>>name;
		
			contacts.searchByName("contacts.txt",name);
			break;
			
		case 3:
			
			// Search contact by number
			cout<<"\n\t\t'Search Contact by Number'"<<endl;
			cout<<"\nEnter the Number you want to search: ";
			cin>>no;
			cout<<endl;
			contacts.searchByNumber("contacts.txt",no);
			break;
		
		case 4:
			
			// Update contact by name
			cout<<"\n\t\t'Update Contact by Name'"<<endl;
			cout<<"\nEnter Previous data which you want to update  : ";
			cout<<"\nEnter Name: ";
			cin>>name;
			cout<<"\nEnter New Name: ";
			cin>>newname;
			cout<<"\nEnter New Number: ";
			cin>>newno;
			contacts.updateContactByName("contacts.txt",name,newname,newno);
			
			break;
		
		case 5:
			
			// Update contact by number
			cout<<"\n\t\t'Update Contact by Number'"<<endl;
			cout<<"\nEnter Previous data which you want to update  : ";
			cout<<"\nEnter Number: ";
			cin>>no;
			cout<<"\nEnter New Name: ";
			cin>>newname;
			cout<<"\nEnter New Number: ";
			cin>>newno;
			contacts.updateContactByNumber("contacts.txt",no,newname,newno);
			break;
	
		case 6:
			
			// Delete contact by name
			cout<<"\n\t\t'Delete Contact by Name'"<<endl;
			cout<<"\nEnter Name which you want to delete : ";
			cin>>name;
			cout<<"\nAre you sure ?? \n Enter yes to delete : ";
			cin>>sure;
			if(sure=="yes"){
				contacts.deleteContactByName("contacts.txt",name);
			
			}
			else{
				cout<<"Cancelled"<<endl;
			}
			break;
	
		case 7:
			
			// Delete contact by number
			cout<<"\n\t\t'Delete Contact by Number'"<<endl;
			cout<<"\nEnter Number which you want to delete : ";
			cin>>no;
			cout<<"\nAre you sure ?? \n Enter yes to delete : ";
			cin>>sure;
			if(sure=="yes"){
				contacts.deleteContactByNumber("contacts.txt",no);
			}
			else{
				cout<<"Cancelled"<<endl;
			}
			break;
			
	    case 8:
			
			// Delete all the contacts
			contacts.deleteAllContacts();
			cout<<"\tAll contacts deleted successfully"<<endl;
			break;
			
		case 9:
			
			// Display all the contacts
			
			cout<<"\n\n\t\t\t\t---------------------------------------------"<<endl;
			cout<<"\t\t\t\t\t        'All CONTACTS'"<<endl;
			cout<<"\t\t\t\t---------------------------------------------"<<endl;
			contacts.sortContacts();
			cout<<"\t\t\t\t\t NAMES"<<"\t\t\t"<<"NUMBERS"<<endl;
		
			contacts.displayContacts();
			
			
		
			
			break;
	
		case 0:
			
			exit(0);
		
		default:
			
			cout<<"INVALID INPUT "<<endl;
			break;
			
	}
	
 }while(choice!=0);




return 0;

}





