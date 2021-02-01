#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Question {
    public:
        string q;
        string t_ans;
        string f_ans;
        Question(string que, string t, string f) {
            q = que;
            t_ans = t;
            f_ans = f;
        }
        void update_left(int k) {
            t_ans = to_string(k);
            return;
        }
        void update_right(int k) {
            f_ans = to_string(k);
            return;
        }
};

class Game {
    public:
        vector<Question> qs;
        int n;
        int i;

        Game() {
            cout << "Welcome to Animal Guessing Game.\n";
            qs = {Question("Is it a small animal?", "rabbit", "tiger")};
            n = 0;
            i = 0;
        }

        void run() {
            bool end = false;
            bool loop = true;
            int restart;
            while (!end) {
                end = next();
            }
            cout << "Game ended, press 1 to restart, press 2 to clear saved questions and press 0 to exit.\n";
            while (loop) {
                cin >> restart;
                if (cin == 1) {
                    i = 0;
                    run();
                }
                else if (cin == 2) {
                    clear_class();
                    run();
                }
                else if (cin == 3) {
                    return;
                }
                else {
                    cout << "Wrong Input " << restart << " try again.\n";
                }
            }
            return;
        }

        bool next() {
            char r;
            char mode;
            string ans;
            bool loop = true;
            Question que = qs[i];
            cout << que.q << "(Y/N)" << endl;
            while (loop) {
                cin >> r;
                if (r=='Y') {
                    ans = que.t_ans;
                    mode = 'l';
                    loop = false;
                }
                else if (r=='N') {
                    ans = que.f_ans;
                    mode = 'r';
                    loop = false;
                }
                else {
                    cout << "Answer not valid, please enter Y or N.\n";
                }
            }
            if all_of(ans.begin(), ans.end(), is_digit) {
                i = atoi(ans);
                return false;
            }
            loop = true;
            char k;
            cout << "Is it a(n) " << ans << "?(Y/N)" << endl;
            while (loop) {
                cin >> k;
                if (k=='Y') {
                    cout << "Hooray!\n"
                    return true;
                }
                else if (r=='N') {
                    cout << "You win!\n";
                    add_question(ans);
                    if (mode == 'l') {
                        que.update_left(n);
                    }
                    else {
                        que.update_right(n);
                    }
                    return false;
                }
                else {
                    cout << "Answer not valid, please enter Y or N.\n";
                }
            }
            return false;
        }

        void add_question(string wrong_ans) {
            string right_ans;
            string question;
            Question new_question;
            bool loop = true;
            cout << "What is the animal you were thinking about?\n";
            while (loop) {
                getline(cin, right_ans);
                if all_of(right_ans.begin(), right_ans.end(), is_digit) {
                    cout << "Please enter a valid animal name\n";
                }
                else {
                    loop = false;
                }
            }
            cout << "Give me a yes-no question that can distinguish ";
            cout << wrong_ans << " from " << right_ans;
            cout << "(Y for " << wrong_ans << " and N for " << right_ans << ")\n";
            getline(cin, question);
            new_question = Question(question, wrong_ans, right_ans);
            qs.push_back(new_question);
            n ++;
            return;
        }

        void clear_class() {
            cout << "Game Restarted.\n";
            qs = {Question("Is it a small animal?", "Rabbit", "Tiger")};
            n = 1;
            i = 0;
        }
}

int main() {
    Game g = Game();
    g.run();
    return 0;
}