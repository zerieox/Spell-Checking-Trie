#include <iostream>
#include <string>
#include <fstream>
#include "trie.h"

int main(){
    Trie myTrie;
    std::ifstream fin("corpus.txt");
    std::string cmd = "";
    std::string addWord = "";
    std::string word = "";
    while(std::cin >> cmd){
        if(cmd == "load"){
            //just read it all
            while(fin>>addWord){
                myTrie.insert(addWord);
                myTrie.numOfWords++;
            }
            std::cout << "success load"<<std::endl;
        }
        else if(cmd == "i"){
            std::cin >> word;
            bool checker = true;
            for (int i=0; i<word.length();i++){
                if(word[i] >123 || word[i]<96){
                    try{
                        throw illegal_exception();
                    }
                    catch(illegal_exception err){
                        err.error();
                        checker = false;
                        break;
                    }
                }
            }
            if(checker == true && myTrie.search(word) == false){
                myTrie.insert(word);
                myTrie.numOfWords++;
                std::cout << "success"<<"\n";
            }
            else if(checker == true){
                std::cout << "failure"<<std::endl;
            }
        }
         else if(cmd == "s"){
            std::cin >> word;
            bool checker = true;
            for (int i=0; i<word.length();i++){
                if(word[i] >123 || word[i]<96){
                    try{
                        throw illegal_exception();
                    }
                    catch(illegal_exception err){
                        err.error();
                        checker = false;
                        break;
                    }
                }
            }
            if(checker == true && myTrie.numOfWords != 0){
                if(myTrie.search(word) == true){
                    std::cout << "found "<< word<<std::endl;
                }
                else{
                    std::cout << "not found" <<std::endl;
                }
            }
            else{
                std::cout << "not found" << std::endl;
            }
            

        }
        else if(cmd == "e"){
            std::cin >> word;
            bool checker = true;
            for (int i=0; i<word.length();i++){
                if(word[i] >123 || word[i]<96){
                    try{
                        throw illegal_exception();
                    }
                    catch(illegal_exception err){
                        err.error();
                        checker = false;
                        break;
                    }
                }
            }
            if(checker == true){
                if(myTrie.search(word) == true && myTrie.numOfWords >1){
                    if(!myTrie.erase(myTrie.root, word)){
                        std::cout <<"success"<<std::endl;
                        myTrie.numOfWords--;
                    }
                }
                else if(myTrie.search(word) == true && myTrie.numOfWords==1){
                    myTrie.clear(myTrie.root);
                }
                else{
                    std::cout << "failure"<<std::endl;
                }
            }
        } 
        else if (cmd =="p"){
            char word[26];
            for(int i=0; i<26;i++){
                word[i] = '\0';
            }
            if(myTrie.numOfWords!=0){
                myTrie.print(myTrie.root,0,word);
                std::cout<<std::endl;
            }
            else{
            }
        }
        else if(cmd == "size"){
            myTrie.size();
        }  
        else if(cmd == "empty"){
            if(myTrie.empty()){
                std::cout << "empty 1" <<std::endl;
            }
            else{
                std::cout << "empty 0" <<std::endl;
            }
        }  
        else if (cmd =="spellcheck"){
            if(myTrie.numOfWords != 0){
                std::cin >> word;
                myTrie.spellCheck(word);
            }
            else{
                std::cout<<std::endl;
            }
        }
        else if (cmd =="clear"){
            if(myTrie.numOfWords !=0){
                myTrie.clear(myTrie.root);
                myTrie.numOfWords = 0;
                myTrie.root = nullptr;
            }
            std::cout << "success"<<std::endl;
        }
        else if(cmd == "exit"){
            if(myTrie.numOfWords != 0){
                myTrie.clear(myTrie.root);
            }            
            break;
        }
}
}
