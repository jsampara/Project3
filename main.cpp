/* 
Joel Sampara
011028144
Project 3
Linked Lists
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// node class for the linked list
class Node {
public:
    string w;
    Node* next;

    // constructor for Node
    Node(string word)
    {
        w = word;
        next = nullptr;
    }
};

// LinkedList class to store words in alphabetical order
class LinkedList {
private:
    Node* head;
    int tWords;
    int uWords;

public:
    // Constructor
    LinkedList() 
    {
        head = nullptr;
        tWords = 0;
        uWords = 0;

    } 

    // insert a word into the linked list in alphabetical order
    void insertWord(const string& word) {
        Node* newNode = new Node(word);
        tWords++;  // Increments

        // if linked list is empty
        if (head == nullptr) {
            head = newNode;
            uWords++;  // First word is unique
            return;
        }

        // insert at the head
        if (word < head->w) {
            newNode->next = head;
            head = newNode;
            uWords++;  // new unique word at the head
            return;
        }

        // insert in alphabetical order
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr && current-> w < word) {
            previous = current;
            current = current->next;
        }

        // in case of duplicates
        if (current != nullptr && current->w == word) {
            delete newNode;  
            return;
        }

        newNode->next = current;
        previous->next = newNode;
        uWords++;  // New unique word
    }

    // getters for total and unique word counts
    int getTotalWords() const 
    { 
       return tWords; 
    }
    int getUniqueWords() const 
    { 
        return uWords; 
    }

    // Destructor to free memory
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};


// function to read a file and inserting them into the linked list
void read_file(const string& filename, LinkedList& wordList) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string word;
    while (file >> word) {
        string cleanword;
        for (char c : word) 
        {
           if (isalpha(c)) 
           {
              cleanword += tolower(c);
           }
        }
        if (!cleanword.empty()) {
            wordList.insertWord(cleanword);
        }
    }

    file.close();
}

int main() {
    // array of filenames 
    string filenames[] = {"books:CallWild.txt", "books:AnneGables.txt", "books:WarPeace.txt"};

    // process each file
    for (const string& filename : filenames) {
        LinkedList wordList;

        // read the file and insert words 
        read_file(filename, wordList);

        // output the word count results
        cout << "Input file name:        " << filename << endl;
        cout << "Number of unique words: " << wordList.getUniqueWords() << endl;
        cout << "Total number of words:  " << wordList.getTotalWords() << endl;
        cout << endl;
    }

    return 0;
}
