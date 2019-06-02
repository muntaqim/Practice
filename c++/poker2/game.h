#ifndef GAME_H
#define GAME_H 

#include <vector>
#include <string>
#include <sstream>
#include "cardUtilities.h"

using namespace std;

typedef CardGroup Hand;

class GameInputs{
friend class ResultFinder;
private:
    CardGroup _hand1;
    CardGroup _hand2;
    CardGroup _board;
public:
    GameInputs(){}
    GameInputs(string h1, string h2, string b)
    {
        _hand1 = CardGroup(h1);
        _hand2 = CardGroup(h2);
        _board = CardGroup(b);
    }
    void print()
    {
        _hand1.printCards();
        _hand2.printCards();
        _board.printCards();
    }
};

// this class will find results based on the game input
class ResultFinder{
private:
    GameInputs _gI;
    string _highHand; // string with final results
    string _lowHand;
    string _finalResult;


    // give all permutations given an array and number of things to choose
    // Tested by pprinintg outputs and coomparing against total number of
    // possible permutations
    // (6 for hand 10 for board)
    void allCombos(vector<Card> h, vector<vector<Card>> &ret, int numToPick, vector<Card> &cur, int start)
    {
        if(cur.size() == numToPick)
        {
            ret.emplace_back(cur);
            return;
        }

        for (int i = start; i < h.size(); i++)
        {
            cur.push_back(h[i]);
            allCombos(h, ret, numToPick, cur, i + 1);
            cur.pop_back();
        } 

        return;
    }
    CombinedGroup getWorstHand(Hand h)
    {
        vector<vector<Card>> allHandCombos;
        vector<vector<Card>> allBoardCombos;
       
        vector<Card> cur;
        allCombos(h.getCards(), allHandCombos, 2, cur, 0);
        allCombos(_gI._board.getCards(), allBoardCombos, 3, cur, 0);


        // now mix and match each hand with each board permutation.
        // there will be 60 combinatiosn total to evaluate per hand
        // This is brute force effort for simplicity
 
        CombinedGroup ret;
        for (auto hand : allHandCombos)
        {
            for (auto board : allBoardCombos)
            {
                vector<Card> curCombo;
                curCombo.insert(curCombo.end(), hand.begin(), hand.end());
                curCombo.insert(curCombo.end(), board.begin(), board.end());

                CombinedGroup curGroup (curCombo);

                // for low hand nothing can be greater than 8
                // all cards must be unique
                // ace is 1

                if (curGroup.qualifyForLowHand())
                {
                    // if we don't have anything, just use the cur group
                    if(!ret.getIsInitialized())
                        ret = curGroup;
                    // choose the lower of the two
                    else if(CombinedGroup::compareGroupsForLow(ret, curCombo) == -1)
                    {
                        ret = curGroup;
                    }
                }   
            }
        }
        return ret;
    }
    CombinedGroup getBestHand(Hand h)
    {
        vector<vector<Card>> allHandCombos;
        vector<vector<Card>> allBoardCombos;
       
        vector<Card> cur;
        allCombos(h.getCards(), allHandCombos, 2, cur, 0);
        allCombos(_gI._board.getCards(), allBoardCombos, 3, cur, 0);


        // now mix and match each hand with each board permutation.
        // there will be 60 combinatiosn total to evaluate per hand
        // This is brute force effort for simplicity
 
        CombinedGroup ret;
        for (auto hand : allHandCombos)
        {
            for (auto board : allBoardCombos)
            {
                vector<Card> curCombo;
                curCombo.insert(curCombo.end(), hand.begin(), hand.end());
                curCombo.insert(curCombo.end(), board.begin(), board.end());

                CombinedGroup curGroup (curCombo);
                // if new hand is better, replace the old hand
                if(CombinedGroup::compareGroups(ret, curCombo) == -1)
                {
                    ret = curCombo;
                }
            }
        }
        return ret;
    }
    // high level function to determine the highHand
    string getHighHand()
    {
        CombinedGroup hA = getBestHand(_gI._hand1);
        CombinedGroup hB = getBestHand(_gI._hand2);
        
        // compare the two hands and work with the best
        // one. 
        int best = CombinedGroup::compareGroups(hA, hB);
        string ret;
        // hA is better
        if (best == 1)
        {
            ret = "=> HandA wins Hi (" + hA.getRankString() + "); ";
        }
        // hB is btter
        else if(best == -1)
        {
            ret = "=> HandB wins Hi (" + hB.getRankString() + "); ";
        }
        // they are the same. Split Hi
        else
        {
            ret = "=> Split Pot Hi (" + hB.getRankString() + "); ";
        }
/*
        cout << "Hand 1" << endl;
        hA.printCards();
    
        cout << "Hand 2" << endl;
        hB.printCards();
        cout << ret << endl; 
*/
        return ret;
    }

    // high level function to determine the lowHand
    string getLowHand()
    {
        CombinedGroup hA = getWorstHand(_gI._hand1);
        CombinedGroup hB = getWorstHand(_gI._hand2);
        string ret;
/*
        cout << "Hand 1" << endl;
        hA.printCards();

        cout << "Hand 2" << endl;
        hB.printCards();
*/
        // if hand A and B aren't initialized return nothing
        if (!hA.getIsInitialized() && !hB.getIsInitialized())
        {
            ret = "No hand qualified for Low";
  //          cout << ret << endl;
            return ret;
        }
        // compare the two hands and work with the worst 
        // one.
        int worst = CombinedGroup::compareGroupsForLow(hA, hB);

        // hB is lower 
        if (worst == -1 || !hA.getIsInitialized())
        {
            ret = "HandB wins Lo (" + hB.getLowHandString() + ")";
        }
        // hA is lower
        else if(worst == 1 || !hB.getIsInitialized())
        {
            ret = "HandA wins Lo (" + hA.getLowHandString() + ")";
        }
        // they are the same so split
        else
        {
            ret = "Split Pot Lo (" + hA.getLowHandString() + ")";
        }

  //      cout << ret << endl;

        return ret;
    }
public:
    ResultFinder(GameInputs gI)
    {
        _gI = gI;
        _highHand = getHighHand();
        _lowHand =  getLowHand();
        
    }
    string getFinalResult()
    {
        _finalResult = _highHand + _lowHand;
        return _finalResult;
    }
};

#endif
