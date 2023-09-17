#include <bits/stdc++.h>
using namespace std;
bool found = false;

bool isAdjacent(pair<int,int> prevPos, pair<int,int> newPos, set<pair<int,int>>& visitedPos)
{
    //if statements check if next letter is one away from previous letter and make sure that a previously visited letter cannot be visited again
    if((prevPos.first + 1 == newPos.first && prevPos.second == newPos.second && !visitedPos.count(newPos)) || 
        (prevPos.first -1 == newPos.first && prevPos.second == newPos.second && !visitedPos.count(newPos)) ||
        (prevPos.second + 1 == newPos.second && prevPos.first == newPos.first && !visitedPos.count(newPos)) || 
        (prevPos.second - 1 == newPos.second && prevPos.first == newPos.first && !visitedPos.count(newPos)))
        {
            visitedPos.insert(newPos);
            return true;
        }
    return false;
}

void findWord(unordered_multimap<char, pair<int,int>> letterPosMap, string target, pair<int,int> prevPos, int& inGrid, bool isFirstPassthrough, int strIndex, set<pair<int,int>> visitedPos)
{
    if(isFirstPassthrough){
        found = false;
        for(auto it = letterPosMap.equal_range(target[0]).first; it != letterPosMap.equal_range(target[0]).second; it++) //loop through all occurences of first letter in grid
        {
            if(strIndex == target.size()-1){found = true; inGrid++; return;}//for the case in which a 1 letter word exists
            visitedPos.insert(it->second); //put first letter pos in set
            findWord(letterPosMap, target, it->second, inGrid, false, strIndex+1, visitedPos);
        }
    }
    for(auto it = letterPosMap.equal_range(target[strIndex]).first; it != letterPosMap.equal_range(target[strIndex]).second; it++)//loop through all occurences of next letter in word
    {
        if(found)return; //base case to exit recursion if the word has been found in other function calls; uses global variable (admittedly a bad practice)
        if(isAdjacent(prevPos, it->second, visitedPos))
            {
                if(strIndex == target.size()-1){found = true; inGrid++; return;}//if on last letter, return and increment inGrid
                findWord(letterPosMap, target, it->second, inGrid, false, strIndex+1, visitedPos);
            }
    }
}


int main()
{
    freopen("test_input.txt", "r", stdin);
    int width, height, numTargetWords, numInGrid;
    unordered_multimap<char, pair<int,int>> letterPosMap;
    set<pair<int,int>> visitedPos;
    string tempWord;
    cin >> height; cin >> width;
    if(width == 0 || height == 0){ //return 0 and exit if either width or height is 0
        cout << 0;
        return 0;
    }
    for(int i = 0; i < height; i++) //loop to read input
    {
        cin >> tempWord;
        for(int j = 0; j < width; j++)
        {
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
        findWord(letterPosMap, tempstr, pair(0,0), numInGrid, true, 0, visitedPos);
        visitedPos.clear();
    }
    cout << numInGrid;
}