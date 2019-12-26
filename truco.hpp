/*******************************************************************************
* Author:       Shylton Matta
* Date:         12 Aug 2019
* Description:  just a cool card game
*******************************************************************************/

#ifndef TRUCO_HPP
#define TRUCO_HPP

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "helpers.hpp"

enum card { noCrd, c2, c3, c4, c5, cJ, cQ, cK, cA };
enum winner { notSet, tie, player, pc };

class Truco {
private:
  std::vector<card> deck;
  std::vector<card> p1Hand;
  std::vector<card> pcHand;
  winner roundWinner[3];
  winner gameWinner;
  int gamesPlayed,
      round,//NEEDED in p1 Choice function
      gameScore;//+1 each player win -1 each loss, DOES NOT RESET
  card p1Played[3],
       pcPlayed[3];

  std::map<card,char> cardMap {
    //used to print to screen
    {noCrd,'_'},
    {c2,'2'},
    {c3,'3'},
    {c4,'4'},
    {c5,'5'},
    {cJ,'J'},
    {cQ,'Q'},
    {cK,'K'},
    {cA,'A'}
  };

  std::map<winner,std::string> winnerMap {
    //used to print to screen
    {notSet,"not played"},
    {tie,"no one"},
    {player,"player"},
    {pc,"pc"}
  };


public:
  Truco ();
  //~Truco ();
  void resetVariables();
  void printVariables();//good for troubleshoot
  void printHeader();
  void coutCards(std::vector<card> &crds);
  void setDeck();
  void shuffleDeck();
  void dealCards();
  void p1Choice();
  void pcChoiceRd1();
  void pcChoiceRd2();
  card chooseHighest(std::vector<card> &crds);
  void setRdWinner(int rd, card plIn, card pcIn);
  void updateGameScore();//for playing multiple games
  int letsPlay();
};


#endif /* end of include guard: TRUCO_HPP */
