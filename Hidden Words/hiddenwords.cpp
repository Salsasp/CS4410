#include <bits/stdc++.h>
using namespace std;
bool found = false;

bool isAdjacent(pair<int,int> prevPos, pair<int,int> newPos)
{
    //if statements check if next letter is one away from previous letter
    if((prevPos.first + 1 == newPos.first && prevPos.second == newPos.second) || (prevPos.first -1 == newPos.first && prevPos.second == newPos.second) ||
                (prevPos.second + 1 == newPos.second && prevPos.first == newPos.first) || (prevPos.second - 1 == newPos.second && prevPos.first == newPos.first))
                {
                    return true;
                }
    return false;
}

void findWord(char* grid[], unordered_multimap<char, pair<int,int>> letterPosMap, string target, pair<int,int> prevPos, int& inGrid, bool isFirstPassthrough, int strIndex)
{
    if(isFirstPassthrough){
        found = false;
        for(auto it = letterPosMap.equal_range(target[0]).first; it != letterPosMap.equal_range(target[0]).second; it++) //loop through all occurences of first letter in grid
        {
            if(target[strIndex] == target[target.size()-1]){found = true; inGrid++; return;}//for the case in which a 1 letter word exists
            findWord(grid, letterPosMap, target, it->second, inGrid, false, strIndex+1);
        }
    }
    if(found)return; //base case to exit recursion if the word has been found in other function calls; uses global variable (admittedly a bad practice)
    for(auto it = letterPosMap.equal_range(target[strIndex]).first; it != letterPosMap.equal_range(target[strIndex]).second; it++)//loop through all occurences of next letter in word
    {
        if(isAdjacent(prevPos, it->second))
            {
                if(target[strIndex] == target[target.size()-1]){found = true; inGrid++; return;}//if the last letter matches, return and increment inGrid
                findWord(grid, letterPosMap, target, it->second, inGrid, false, strIndex+1);
            }
    }
}


int main()
{
    freopen("test_input.txt", "r", stdin);
    int width, height, numTargetWords, numInGrid;
    unordered_multimap<char, pair<int,int>> letterPosMap;
    string tempWord;
    cin >> width; cin >> height;
    char *wordGrid[width];
    for(int i = 0; i < width; i++)
    {
        wordGrid[i] = new char[height]; //2d array using pointers
    }
    for(int i = 0; i < height; i++) //loop to read input into 2d char matrix
    {
        cin >> tempWord;
        for(int j = 0; j < width; j++)
        {
            wordGrid[i][j] = tempWord[j];
            char tempChar = tempWord[j];
            letterPosMap.insert(make_pair(tempChar, pair(i,j))); //hashmap to allow quick access to location of specific letters
        }
    }
    cin >> numTargetWords;
    string targets[numTargetWords];
    string tempstr;
    numInGrid = 0;
    for(int i = 0; i < numTargetWords; i++)
    {
        cin >> tempstr;
        findWord(wordGrid, letterPosMap, tempstr, pair(0,0), numInGrid, true, 0);
    }
    cout << numInGrid;
}