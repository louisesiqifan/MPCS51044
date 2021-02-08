#include <iostream>
#include <fstream>
#include <string.h>
#include <memory>
#include <utility>
#define FMT_HEADER_ONLY
#include <fmt/format.h>
using namespace std;
using namespace fmt;

class Node
{
public:
  virtual void play(unique_ptr<Node> &owner) = 0;
};

class QuestionNode : public Node
{
public:
  string question;
  unique_ptr<Node> yesChild;
  unique_ptr<Node> noChild;
  QuestionNode(string question, unique_ptr<Node> y, unique_ptr<Node> n) 
      : question(question), yesChild(move(y)), noChild(move(n)) {};

  void play(unique_ptr<Node>& owner) override {
    play();
  }

  void play() {
    cout << question << " ";
    string response;
    getline(cin, response);
    if (response[0] == 'y') {
      yesChild->play(yesChild);
    } else {
      noChild->play(noChild);
    }
  }

};

class AnswerNode : public Node
{
public:
  string animal;
  AnswerNode(string a) : animal(a) {}

  void play(unique_ptr<Node>& owner) {
    cout << format("Were you thinking of a(n) {}? ", animal);
    string response;
    getline(cin, response);
    if (response[0] == 'y')
      cout << "I knew it!\n";
    else {
      cout << "Congratulations! You beat me\n"
        << "What animal were you thinking of? ";
      string newAnimal;
      getline(cin, newAnimal);
      cout << format("What is a question to tell a {} from a {}? ",
        newAnimal, animal);
      string newQuestion;
      getline(cin, newQuestion);
      auto newNode = make_unique<QuestionNode>(
        newQuestion, make_unique<AnswerNode>(newAnimal), move(owner));
      owner = move(newNode);
    }
  }
};

class AnimalGame
{
public:
  void play() { root->play(); }
  void reset() {
    root = startingQuestion();
  }
private:
  static unique_ptr<QuestionNode> startingQuestion() { 
    return make_unique<QuestionNode>("Does it fly?",
       make_unique<AnswerNode>("bird"), make_unique<AnswerNode>("giraffe")); 
  }
  unique_ptr<QuestionNode> root = startingQuestion();
};

int main()
{
  AnimalGame game;
  for(;;) {
    game.play();
    cout << "That was fun\n"
         << "Would you like to play again (y)es/(n)o/(r)eset? ";
    string answer;
    getline(cin, answer);
    if (answer[0] == 'n')
      break;
    if (answer[0] == 'r')
      game.reset();
  }
  cout << "Goodbye. Thanks for playing!\n";
  return 0;
}