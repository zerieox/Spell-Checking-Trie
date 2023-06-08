#include <iostream>
#include "trie.h"
TrieNode::TrieNode(){
    for (int i=0; i<26; i++){
        children[i] = nullptr;
    }
    endOfWord = false;
}

Trie::Trie(){
    prefixRoot = nullptr;
    chCounter=0;
    root = nullptr;
    numOfWords = 0;
    duplicate = false;
}
Trie::~Trie(){
    clear(root);
}
void Trie::insert(std::string word){
    if(root == nullptr){
        root = new TrieNode;
    }
    TrieNode *currentNode = root;
    for (int i = 0; i < word.length(); i++)
    {
        int index = word[i] - 'a';
        if (currentNode->children[index] == nullptr)
        {
            TrieNode *newNode = new TrieNode();
            newNode->endOfWord = false;
            // for(int j=0; j<26; j++){
            //     newNode->children[j] = nullptr;
            // }
            currentNode->children[index] = newNode;
            //           std::cout <<currentNode->children[index] << "\n";
        }

        currentNode = currentNode->children[index];
    }
    currentNode->endOfWord = true; // Need to check if duplicated
};
bool Trie::erase(TrieNode*& currentNode, std::string word){
    //case 1 tree is empty

    if(currentNode == nullptr){
        return false;
    }
    //if end of the word is not reached
    if(word.length()){
        if(currentNode!=nullptr && 
        currentNode->children[word[0]-'a'] != nullptr&&
        erase(currentNode->children[word[0]-'a'], word.substr(1)) &&
        currentNode->endOfWord == false){
            if(hasChild(currentNode) == false){
                delete (currentNode);
                currentNode = nullptr;
                return true;
            }
            else{
                return false;                
            }
        }
    }
    //Final character of the word being handled
    if(word.length() == 0 && currentNode->endOfWord == true){
        if(hasChild(currentNode) == false){
            delete (currentNode);
            currentNode = nullptr;
            return true;
        }
        else{
            //current node is not end of the word anymore
            currentNode->endOfWord = false;
            //do not delete parent nodes
            return false;
        }
    }
    
    return false;
}
bool Trie::hasChild(TrieNode* currentNode){
    int count =0;
    while(count<26){
        if(currentNode->children[count] != nullptr){
            return true;
        }
        count++;
    }
    return false;
}

bool Trie::search(std::string word){
    chCounter =0;
    TrieNode* currentNode = root;
    bool foundWord = true;
    if (numOfWords == 0){
        return false;
    }
    for(int i=0; i<word.length();i++){
        int index = word[i]-'a'; //char minus 97 
        if(currentNode->children[index] == nullptr){
            foundWord = false;
            break;
        }
        currentNode = currentNode->children[index];
        chCounter++;//count how many characters parsed thru

    }
    //if the word is found or word ended and it is the end of the word
    if(foundWord == true && currentNode->endOfWord == true){
        prefixRoot = currentNode;
        return true;
    }
    //if word is not found which means overextended
    else if(foundWord == false && currentNode != root){
        prefixRoot = currentNode; //tags the last common root
        return false;
    }
    else{
        prefixRoot = currentNode;
        return false;
    }
};
void Trie::print(TrieNode* currentNode, int position, char word[]){
    if(currentNode->endOfWord == true){
        word[position] = '\0';
        std::cout << word <<" ";
    }
    for(int i=0; i<26;i++){
        if(currentNode->children[i] != nullptr){
            word[position] = i+'a';
            print(currentNode->children[i], position+1, word);
        }
    }
};
void Trie::spellCheck(std::string word){
    TrieNode* currentNode = root;
    int iteration = 0;
    bool wantedWord = search(word);
    if (wantedWord == true){
        std::cout<< "correct" <<"\n";    
    }
    // if number of words is greater than 0 or if the child of 
    // current node index is not a null pointer 
    else if(numOfWords > 0 || currentNode->children[word[0]-'a'] != nullptr){

        char ch[word.length()]={};
        //initializes the character array
        for(int i =0; i<word.length();i++){
            ch[i] = '\0';
        }
        //fill the character array with the word
        for(int i =0; i<chCounter;i++){
            ch[i] = word[i]; 
        }
        std::string letters = ch;
        letters = letters.substr(0,chCounter);
        char concatenation[26];
        for (int i=0;i<26;i++){
            concatenation[i]='\0';
        }
        suggestionPrinter(prefixRoot, 0, concatenation,letters);
        std::cout<<std::endl;
    }
    else {
        //do nothing
    }
}
void Trie::suggestionPrinter(TrieNode* currentNode, int position,char ch[],std::string word){
    // std::cout<< "word: "<<word <<"\n";
    if(currentNode->endOfWord == true){
            ch[position] = '\0';
            std::cout <<word<< ch <<" ";
        }
    for(int i=0; i<26;i++){
        if(currentNode->children[i] != nullptr){
                ch[position] = i+'a';
                suggestionPrinter(currentNode->children[i],position+1,ch, word);
        }
    }

}

bool Trie::empty(){
    if(numOfWords == 0){
        return true;
    }
    else{
        return false;
    }
};
void Trie::clear(TrieNode* currentNode){

    if (hasChild(currentNode)){
        for (int i=0; i<26; i++){
            if(currentNode->children[i]!=nullptr){
                clear(currentNode->children[i]);
                currentNode->children[i] = nullptr;
            }
        }
    }
    numOfWords = 0;
    delete (currentNode); 
};

void Trie::size(){
    std::cout <<"number of words is: "<<numOfWords<<std::endl;
};


