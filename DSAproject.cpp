#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
# define CHILDREN 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
# define MAX 100
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

using namespace std;

class trie 
{
	public:
		
    trie* child[CHILDREN];
    bool endOfWord;
    string number;
    
 
trie* createNode()
{

trie *temp = new trie();
    
    for(int i = 0 ; i < CHILDREN ; i++)
    
        // Initially , initialize null to the all child
        temp->child[i] = NULL;
        
        
        temp->endOfWord = false;
    
    return temp;
}

  void insertRecursively(trie* itr, string str, int i,string n)
{
    if(i < str.length())
    {
        int index = str[i] - 'a';
        
        
        if(itr->child[index] == NULL )
        {
          // Create a new node
          itr->child[index] = createNode();
        }
         
      /*
	   Recursive call for insertion of string
      */
      insertRecursively(itr->child[index], str, i + 1,n);
    }
    
    else
    {
                // Make the endOfWord true which represents
                // the end of string
                
                
        itr->endOfWord = true;
        
        itr->number=n;
    }
}

 /*
 *Function call to insert a string
 */
 
void insert(trie* itr, string str,int i,string n)
{
        // Function call with necessary arguments
   
    insertRecursively(itr, str, 0,n);
    cout<<"Contact added successfully :) "<<endl;
  
}

 
/*
 * Function to check whether the node is leaf or not
 */
 
bool isLeafNode(trie* root)
{
    return root->endOfWord != false;
}
/*
* Recursive function to print auto-suggestions for given node
*/
 
 
void suggestionsRec( trie* root,string currPrefix)
{
    // found a string in Trie with the given prefix
    if (root->endOfWord)
        cout << currPrefix << endl;
 
    for (int i = 0; i <CHILDREN; i++)
        if (root->child[i]) {
            // child node character value
            char children = 'a' + i;
            suggestionsRec(root->child[i],
                           currPrefix + children);
        }
}
 
/*
* print suggestions for given query prefix.
*/


int printAutoSuggestions(trie *root, const string query)
{
     trie* temp = root;
    for (char c : query) {
        int ind = CHAR_TO_INDEX(c);
 
        // no string in the Trie has this prefix
        if (!temp->child[ind])
            return 0;
 
        temp = temp->child[ind];
    }
    // If prefix is present as a word, but
    // there is no subtree below the last
    // matching node.
    if (isLeafNode(temp)) {
        cout << query << endl;
        return -1;
    }
    suggestionsRec(temp, query);
    return 1;
}
  /*
  Display function 
 */ 

void display(trie* root, char str[], int level,string n)
{
    // If node is leaf node, it indicates end
    // of string, so a null character is added
    // and string is displayed
    if (isLeafNode(root)) 
    {
        str[level] = '\0';
       // if(str==n){
        cout<<"\tName: " << str<<" \tNumber: "<<root->number<<endl;
    } 
  
    int i;
    for (i = 0; i < CHILDREN; i++) 
    {
        // if NON NULL child is found
        // add parent key to str and
        // call the display function recursively
        // for child node
        if (root->child[i]) 
        {
            str[level] = i + 'a';
            display(root->child[i], str, level + 1,n);
        }
    }
			}

 
 
  void specificdisplay(trie* root, char str[], int level,string w)
{
    // If node is leaf node, it indicates end
    // of string, so a null character is added
    // and string is displayed
    if (isLeafNode(root)) 
    {
        str[level] = '\0';
        if(str==w)
        {
        cout << w<<": "<<root->number<<endl;
    }
    }
  
    int i;
    for (i = 0; i < CHILDREN; i++) 
    {
        // if NON NULL child is found
        // add parent key to str and
        // call the display function recursively
        // for child node
        if (root->child[i]) 
        {
            str[level] = i + 'a';
            specificdisplay(root->child[i], str, level + 1,w);
        }
    }
}
/*
*Is empty function
*/
  
 bool isEmpty(trie* root)
{
    for (int i = 0; i < CHILDREN; i++)
        if (root->child[i])
            return false;
    return true;
}

bool searchRecursively(trie* root, char str[], int i,int len)
{
    // When a string or any character
    // of a string is not found
    if (root == NULL)
        return false;
 
    // Condition of finding string successfully
    if (root->endOfWord == true && i == len - 1) {
        // Return true when endOfWord
        // of last node containes true
        return true;
    }
 
    int index = str[i] - 'a';
    // Recursive call and return
    // value of function call stack
    return searchRecursively(root->child[index],
                                   str, i + 1, len);
}

bool search(trie* root, string str)
{
    char arr[str.length() + 1];
    strcpy(arr, str.c_str());
    // If string found
    if (searchRecursively(root, arr, 0, str.length() + 1))
    return true;
 
    else {
        return false;
    }
}



/*
remove function 
*/	


trie* remove(trie* root, string key, int depth = 0)
{
    // If tree is empty
    if (!root){
    //	cout<<"Name not found"<<endl;
    	return root;

	}
 
    // If last character of key is being processed
    if (depth == key.size()) {
 
        // This node is no more end of word after
        // removal of given key
        if (root->endOfWord)
            root->endOfWord = false;
 
        // If given is not prefix of any other word
        if (isEmpty(root)) {
            delete (root);
            root = NULL;
        
        }
 
        return root;
    }
 
    // If not last character, recur for the child
    // obtained using ASCII value

    int index = key[depth] - 'a';
    root->child[index] =
          remove(root->child[index], key, depth + 1);
 
    // If root does not have any child (its only child got
    // deleted), and it is not end of another word.

    if (isEmpty(root) && root->endOfWord== false) {
        delete (root);
        root = NULL;
    }
 
    return root;
}
/*
* function to edit the contact
*/

trie *modify(trie* root, string key, int depth = 0)
{
	int level=0;
	  char str[20];
	string name,num;


//search condition to check if contact exist

	
if(search(root,key)==true)
{
	remove(root,key,depth = 0);
	cout<<"Enter the new name: ";
	cin>>name;
	cout<<"Enter new number: ";
	cin>>num;
	insert(root,name,0,num);
	
	return 0;
}
return 0;
	
}




};

int main()
{

cout<<"\t\xDB\xDB\xDB\xDB\xB2   WELCOME TO CONTACTBOOK  \xDB\xDB\xDB\xDB\xB2\t\n   ";
	cout<<endl<<endl;
	

	trie t;
    trie* root = t.createNode();

	string name;
	string num;

	trie x;
	
	 int option;
	 int val;
	 
while(1){

            cout<<"  ***********  "<<endl;
	    	cout<<"  1. Add Contact"<<endl;
	    	cout<<"  2. Edit the Contact"<<endl;
	    	cout<<"  3. Delete Contact"<<endl;
	    	cout<<"  4. Search Contact"<<endl;
	    	cout<<"  5. Display Specific Name"<<endl;
	    	cout<<"  6. Display All Contacts"<<endl;
	    	cout<<"  0. Exit program"<<endl;
	    	cout<<"  ***********  "<<endl;

 
    
   
     //string name,number;
      int level = 0;
     char str[20];
     int i=0;
     char y;
     
    cin >> option;
 
     switch(option)
     {
     	case 0:
     		exit(1);
     	case 1:
     		system("cls");
     		cout<<"Enter the name: ";
			 cin>>name;
     		cout<<"Enter the number: ";
     		cin>>num;
     		 t.insert(root,name,i,num);
     	cout<<endl;
     	//	system("pause");
     		 break;
     		 
    	case 2:	
    	system("cls");
		cout<<"Enter the name to be modified: ";
		cin>>name;
	if(t.search(root,name)==true)
	{
	
		t.modify(root, name);	
	}
	else
	{
		
		cout<<"Not found!"<<endl;
		cout<<"Enter the name to be modified: ";
		cin>>name;
		t.modify(root,name);
	}
	cout<<endl;
        break;
        
    	case 3:
    		
    	system("cls");	
	cout<<"Enter the name to be removed: ";
    	cin>>name;	
 if(t.search(root,name)==true)
	 {
		    	 t.remove(root,name);
		    	 cout<<"Contact removed"<<endl;
   }
	else
{
		
		cout<<"Not found!"<<endl;
		system("cls");
		cout<<"Enter the correct name to be removed: ";
		cin>>name;
		t.remove(root,name);
		cout<<"Contact removed"<<endl;
	//	continue;
}
  	cout<<endl;

		break;
		
		case 4:
			
			system("cls");
			cout<<"Enter the name/prefix to be searched: ";
			cin>>name;
		    t.printAutoSuggestions(root,name);
		  	
			  cout<<endl;
			  cout<<"select the name: ";
			  cin>>name;
		t.specificdisplay	(root,str,level,name);
	
		break;
	
		case 5:
			
			system("cls");
			cout<<"Enter the name to be searched: ";
			cin>>name;
			t.specificdisplay	(root,str,level,name);
				
			
			break;
			
		case 6:
				
			system("cls");
			cout<<"---------------******---------------"<<endl;
			cout<<"\t    CONTACT LIST: "<<endl;
			cout<<"---------------******---------------"<<endl;
			t.display(root,str,level,name);
		  	
			  cout<<endl;
			
			break;			
	 }
	 
}
return 0;
}

