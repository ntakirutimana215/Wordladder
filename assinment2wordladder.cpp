


#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <set>
using namespace std;

/* Constants */
const int ALPHA_LENGTH = 26;

/* Prototypes arguments */
void getWords(string &wd1, string &wd2);
void printWordLadder(string wd1, string wd2);

/* Main function */
int main() {
    
  string wd1, wd2;
  getWords(wd1, wd2); 
  printWordLadder(wd1, wd2);
    
  return 0;
}

/*
 * Function: getWords
 * Usage: getWords(word1, word2)
 * -----------------------------
 * This function takes two strings as parameter (passed by reference), 
 * prompts the user for her input and stores her answer in those two
 * parameters.
 *
 * The user must enter strings of same length, otherwise the function
 * keeps asking for new words.
 */

void getWords(string &wd1, string &wd2) {
  while (true) {
    cout << "Please enter a word: ";
    cin>>wd1;
    
    cout << "Please enter another word of the same length: ";
    cin>>wd2;
    
    if (wd1.length() == wd2.length()) {
      break;
    }
    cout << "Please enter two words of the same length in size." << endl;
  }
}


/* Function: printWordLadder
 * Usage: printWordLadder(word1, word2) 
 * ------------------------------
 * This function takes two strings as parameters and prints the 
 * minimal word ladder between two words.
 * 
 * A word ladder is a connection from one word to another formed 
 * by changing one letter at a time with the constraint that at each 
 * step the sequence of letters still forms a valid word.
 */

void printWordLadder(string wd1, string wd2){
    
    // creates an empty queue of stacks
    queue<stack<string> > myQueue;
    
    //Create a stack which will contain a final word ladder
    stack<string> wordladder;
    
    // creates and adds a stack containing word1 to the queue
    stack<string> myStack;
    myStack.push(wd1);
    myQueue.push(myStack);
    
    // creates two sets: one for the dictionary and one for the tested words
    string care;
    ifstream dictionary("dictionary.txt");
    set<string> myDictionary;
    set<string> wordstested;
    
    if(dictionary.is_open()) {
      
	      while (dictionary >> care) {
	    	myDictionary.insert(care);
	      }
	      
	      // while the queue is not empty:
	      while (!(myQueue.empty())) {
	        
	        // dequeue the partial-ladder stack from the front of the queue.
			stack<string> ladder = myQueue.front();
			myQueue.pop();
			string word = ladder.top();
		        
			// if the word on top of the stack is the destination word:
			if (word == wd2) {
			
			  // Yeey! output the elements of the stack as the solution.
			  cout << "The ladder from " << wd1 << " to " << wd2 << " is \n";
			 
			  //Copy the ladder stack to worldladder to take it in the order.
			  while(!ladder.empty()){
			  	wordladder.push(ladder.top());
			  	ladder.pop();
			  }
			  while(!wordladder.empty()){
			  	cout<<wordladder.top()<<" > ";
			  	wordladder.pop();
			  }
		} 
		else {
			  // for each valid English word that is a "neighbor" (differs by 1 letter) of the word on top of the stack:
			  string test;
			  for (int n = 0; n < word.size(); n++) {
			    for (char m = 'a'; m <= 'z'; m++) {
			    test = word.substr(0, n) + m + word.substr(n + 1);
		            
			    // if that word is an english word
			    if (myDictionary.count(test)) {
			      
			      // if that neighbor word has not already been used in a ladder before:
			      if (!wordstested.count(test)) {
				
						
						stack<string> copy = ladder;
				                
						
						copy.push(test);
				                
						
						myQueue.push(copy);
			      }
			    }
		            
			    
			    wordstested.insert(test);
			}
		}
	      }
	    }
    } else {
      cerr << "Couldn't open the dictionary" << endl;
    }
    
    
}
