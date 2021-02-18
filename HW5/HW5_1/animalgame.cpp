#include <iostream>
#include <fstream>
#include <string.h>
#include <memory>
#include <utility>
#include <variant>
#define FMT_HEADER_ONLY
#include <fmt/format.h>
using namespace std;
using namespace fmt;

//DECLARE CLASSES
class QuestionNode;
class AnswerNode;
//Define Node
using Node = variant<QuestionNode, AnswerNode>;

//Declare methods within the classes
class QuestionNode
{
public:
    string question;
    unique_ptr<Node> yesChild;
    unique_ptr<Node> noChild;
    QuestionNode(string q, unique_ptr<Node> y, unique_ptr<Node> n);

    void play(unique_ptr<Node>& owner);
    void play();
};

class AnswerNode
{
public:
    string animal;
    AnswerNode(string a);

    void play(unique_ptr<Node>& owner);
    void play();
};

//DEFINE THE METHODS
//For QuestionNode:
QuestionNode::QuestionNode(string q, unique_ptr<Node> y, unique_ptr<Node> n) {
    question = q;
    yesChild = move(y);
    noChild = move(n);
}

void QuestionNode::play(unique_ptr<Node>& owner) {
    play();
}

void QuestionNode::play() {
    cout << question << " ";
    string response;
    getline(cin, response);
    if (response[0] == 'y') {
        unique_ptr<Node> &y = yesChild;
        visit([&y](auto &v) {
            v.play(y);
        }, *yesChild);
    } else {
        unique_ptr<Node> &n = noChild;
        visit([&n](auto &v) {
            v.play(n);
        }, *noChild);
    }
}

//For AnswerNode:
AnswerNode::AnswerNode(string a) {
    animal = a;
}

void AnswerNode::play() {
    //placeholder, should never be called;
    return;
}

void AnswerNode::play(unique_ptr<Node>& owner) {
    cout << format("Were you thinking of a(n) {}? ", animal);
    string response;
    getline(cin, response);
    if (response[0] == 'y'){
        cout << "I knew it!\n";
    }
    else {
        cout << "Congratulations! You beat me\n"
             << "What animal were you thinking of? ";
        string newAnimal;
        getline(cin, newAnimal);
        cout << format("What is a question to tell a {} from a {}? ",
                       newAnimal, animal);
        string newQuestion;
        getline(cin, newQuestion);
        auto newNode = make_unique<Node>(QuestionNode(
            newQuestion, make_unique<Node>(AnswerNode(newAnimal)), move(owner)
        )
    );
        owner = move(newNode);
    }
}



class AnimalGame
{
public:
    void play() {
        visit([](auto &v){
            v.play();
        }, *root);
    }
    void reset() {
        root = startingQuestion();
    }
private:
    static unique_ptr<Node> startingQuestion() {
        return make_unique<Node>(
                    QuestionNode("Does it fly?",
                                 make_unique<Node>(AnswerNode("bird")),
                                 make_unique<Node>(AnswerNode("giraffe"))
                             )
                         );
    }
    unique_ptr<Node> root = startingQuestion();
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
