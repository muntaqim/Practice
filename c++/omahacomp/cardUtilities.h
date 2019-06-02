#ifndef CARD_UTILITES_H
#define CARD_UTILITES_H 


#include <vector>
#include <string>
#include <algorithm>
#include "generalUtilities.h"
#include <unordered_map>
#include <ctype.h>
using namespace std;

class Card{
private:
    int _value;
    char _suit;

    int convertRanktoNum(char rank)
    {
        if (rank == '2') return 2;
        if (rank == '3') return 3;
        if (rank == '4') return 4;
        if (rank == '5') return 5;
        if (rank == '6') return 6;
        if (rank == '7') return 7;
        if (rank == '8') return 8;
        if (rank == '9') return 9;
        if (rank == 'T') return 10;
        if (rank == 'J') return 11;
        if (rank == 'Q') return 12;
        if (rank == 'K') return 13;
        if (rank == 'A') return 14;
    }
public:
    Card(){}
    Card(string in)
    {
        _value = convertRanktoNum(in[0]);
        _suit = tolower(in[1]);
    }
    string getCard()
    { return to_string(_value) + _suit; }

    int getValue()
    { return _value; }

    int getSuit()
    { return _suit; }
};
// will be used to represent the board and a hand
class CardGroup{
protected:
    vector<Card> _cards;
public:
    CardGroup(){}
    // this function expects a comma seperate list of cards
    // and the number of cards to expect
    CardGroup(string input)
    {
        // parse input string and place each card into vector
        // split string is '-'
        vector<string> cards = split(input, '-');


        for(int i = 0; i < cards.size(); i++)
            _cards.emplace_back(cards[i]);
    }
    CardGroup(vector<Card> cards)
    {
        _cards = cards;
    }
    vector<Card> getCards()
    {
        return _cards;
    }
    void printCards()
    {
        for(int i = 0; i < _cards.size(); i++)
        {
            cout << _cards[i].getCard() << " ";
        }
        cout << endl;
    }
    
    static bool compareForHighest (Card c1, Card c2)
    {
        return c1.getValue() > c2.getValue();
    }
    static bool compareForLowest (Card c1, Card c2)
    {
        // ace is can be treated as lowest when needed
        if (c2.getValue() == 14)
            return false;

        if (c1.getValue() == 14)
            return true;

        return c1.getValue() < c2.getValue();
    }

    void sortCardsHighest()
    {
        sort(_cards.begin(), _cards.end(), compareForHighest);
    }
};



class CombinedGroup : public CardGroup
{
private:
    int rank;
    unordered_map <int, int> numCards;
    int isInitialized;
    std::vector<std::pair<int, int>> pairs;
    
    // const definitions to identify group
    static const int STRAIGHT_FLUSH = 9;
    static const int FOURS = 8;
    static const int FULL_HOUSE = 7;
    static const int FLUSH = 6;
    static const int STRAIGHT = 5;
    static const int THREES = 4;
    static const int TWO_PAIR = 3;
    static const int TWO = 2;
    static const int HIGH = 1;

    // identify whether hand is a straight
    bool isStraight()
    {
        // since the cards are already ordered, 
        // make sure the cards next to each other
        // only have a dif of 1. 
        // Ace is a special case because it can be treated
        // as a low or high
        //

        bool isStraight = true ;
        int firstToCheck = 0;

        // Ace check. make sure last card is 2 or next card
        // is king. If neither true, not a straight
        if (_cards[0].getValue() == 14 &&
            !(_cards[1].getValue() == 13 || 
             _cards[_cards.size() - 1].getValue() == 2))
            return !isStraight;
        else if (_cards[0].getValue() == 14)
            firstToCheck = 1; // don't need to check any more. Rest have to be good
        
        for (int i = firstToCheck; i < _cards.size() - 1; i++)
        {
            // if the diff of two neightbours isn't 1
            // return false
            if(_cards[i].getValue() - _cards[i+1].getValue() != 1)
            {
                return !isStraight;
            }
        }
        return isStraight;
    }
    
    bool isFlush()
    {
        // check suit of first card.
        // make sure rest of the suits is 
        // the same
        char suitCheck = _cards[0].getSuit();

        for (auto i : _cards)
        {
            if (i.getSuit() != suitCheck)
                return false;
        }
        return true;
    }

    // gives a rank to the current group 
    int identifyGroup()
    {
        // sort the map based on value
        for (auto itr = numCards.begin(); itr != numCards.end(); ++itr)
            pairs.push_back(*itr);
        
        sort(pairs.begin(), pairs.end(), [=](std::pair<int, int>& a, std::pair<int, int>& b)
        {
            return a.second > b.second;
        }
        );

        auto it = pairs.begin();
        if(it->second == 4)
            return FOURS;
        else if (it->second == 3)
        {
            // in this case, it can either be threes 
            // or a full_house

            it++;
            if(it->second == 2)
                return FULL_HOUSE;
            else
                return THREES;
        }
        else if(it->second == 2)
        {
            it++;
            // either TWO or TWO_PAIR
            if(it->second == 2)
                return TWO_PAIR;
            else
                return TWO;
        }
        // this is the case where all cards are unique.
        else
        {
            if (isStraight())
            {
                if (isFlush())
                    return STRAIGHT_FLUSH;
                else
                    return STRAIGHT;
            }
            else if (isFlush())
                return FLUSH;
            else
                return HIGH;
        }
    }

    
public:
    CombinedGroup(){isInitialized = 0;}
    CombinedGroup(vector<Card> Cards):CardGroup(Cards)
    {
        // sorting to identify card quickly
        sortCardsHighest();
        for (auto i : _cards)
        {
            if (numCards.find(i.getValue()) == numCards.end())
                numCards[i.getValue()] = 1;
            else
                numCards[i.getValue()] ++;
        }

        rank = identifyGroup();
        isInitialized = 1;
    }
    int getRank()
    {
        return rank;
    }
    int getIsInitialized()
    {
        return isInitialized;
    }

    // this function will be used to compare to groups
    // 1 if g1 is greater. -1 if smaller. 0 if equal
    static int compareGroups (CombinedGroup g1, CombinedGroup g2)
    {
        if (!g1.isInitialized && !g2.isInitialized)
            return 0;
        else if (!g1.isInitialized)
            return -1;
        else if (!g2.isInitialized)
            return 1;

        if(g1.rank > g2.rank)
            return 1;
        else if(g1.rank < g2.rank)
            return -1;

        else{
            // both groups have the same rank. Need to see
            // who has the highest card

            auto it1 = g1._cards.begin();
            auto it2 = g2._cards.begin();

            // special case where ace is low card in straight
            if((g1.rank == STRAIGHT || g1.rank == STRAIGHT_FLUSH) && g1._cards[0].getValue() == 14 && 
               g1._cards[g1._cards.size() -1].getValue() == 2)
            {
                // the highest card for the other guy is something other
                // than ace. This means the straight is higher
                if (g2._cards[0].getValue() != 14)
                    return -1;
            }

            for(;it1 != g1._cards.end() && it2 != g2._cards.end(); it1++, it2++)
            {
                // as soon as there is a difference, we know which group is
                // higher
                if(it1->getValue() != it2->getValue())
                {
                    if (it1->getValue() > it2->getValue())
                        return 1;
                    else
                        return -1;
                }
            }

            return 0;
        }
    }
    
    // 1 means g1 is lower
    // -1 means g1 is higher
    // 0 means both are equal
    static int compareGroupsForLow (CombinedGroup g1, CombinedGroup g2)
    {
        auto it1 = g1._cards.begin();
        auto it2 = g2._cards.begin();

        if (!g1.isInitialized && !g2.isInitialized)
            return 0;
        if (!g1.isInitialized)
            return -1;
        if (!g2.isInitialized)
            return 1;

        int numAces1 = 0;
        int numAces2 = 0;
        // skip the aces
        while(it1->getValue() == 14)
        {
            numAces1++;
            it1++;
        }
        while(it2->getValue() ==  14)
        {
            numAces2++;
            it2++;
        }
        for(;it1 != g1._cards.end() && it2 != g2._cards.end(); it1++, it2++)
        {
            // as soon as there is a difference, we know which group is
            // higher
            if(it1->getValue() != it2->getValue())
            {
                if (it1->getValue() > it2->getValue())
                    return -1;
                else
                    return 1;
            }

            // g1 has more acess which means at this point
            // it has lower cards
            if (numAces1 > numAces2)
                return 1;
            else if (numAces2 > numAces1)
                return -1;

        }
        return 0;

    }
    bool qualifyForLowHand()
    {
        // check to see if anything greater than 8
        for (auto a : _cards)
        {
            // aces always qualify
            if (a.getValue() == 14)
                continue;

            else if (a.getValue() > 8)
                return false;
        }

        // make sure there's no duplicates.
        // Can use pairs again to check the highest
        // number of duplicates
        
        auto it = pairs.begin();
        if (it->second > 1)
            return false;

        return true;
    }
    string getRankString()
    {
        switch (rank){
            case STRAIGHT_FLUSH:
                return "Straight Flush";
            case FOURS:
                return "4-of-a-Kind";
            case FULL_HOUSE:
                return "Full House";
            case FLUSH:
                return "Flush";
            case STRAIGHT:
                return "Straight";
            case THREES:
                return "3-of-a-Kind";
            case TWO_PAIR:
                return "Two Pair";
            case TWO:
                return "One Pair";
            case HIGH:
                return "High Card";
            default:
                return "Error";
        }

    }
    string getLowHandString()
    {
        string ret;
        int count = 0;
        for (auto i : _cards)
        {
            if (i.getValue() == 14)
                count ++;
            else
                ret += to_string(i.getValue());
        }

        while (count)
        {
            ret += "A";
            count --;
        }
        return ret;
    }
};




#endif
