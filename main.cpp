#include <iostream>
#include<list>
#include <cstdlib>
#include<string>
#include <ctime>
using namespace std;
 
typedef struct{
    int *row;
}TicList;
 
 
class Player {
private:
    string name;
    int score;
public:
    Player() :Player {" "}{}
    Player(string n) :score{0}, name{n}{}
 
    void won(){
        //increment the score
        score++;
    }
    int getScore(){ return this -> score;}
 
    string getName(){ return this -> name;}
};
 
class Mode {
private:
    char board[9];
    int emptyIndex[9];
    int gameOn, againstYviesAI;
    int emptyCount;
    TicList taclist[8];
 
    void displayBoard(){
        cout << endl;
        cout << "   |   |   "<< endl;
        cout << " "<< board[0] <<" | "<<board[1]<<" | "<<board[2]<<endl;
        cout << "   |   |   "<< endl;
        cout << "___________"<< endl;
        cout << "   |   |   "<< endl;
        cout << " "<< board[3] <<" | "<<board[4]<<" | "<<board[5]<< endl;
        cout << "   |   |   "<< endl;
        cout << "___________"<< endl;
        cout << "   |   |   "<< endl;
        cout << " "<< board[6] <<" | "<<board[7]<<" | "<<board[8]<< endl;
        cout << "   |   |   "<< endl;
        cout << endl;
    }
 //playing vs computer (single player mode)
    void vsComputerInput(){
        int pos;
        pos = rand()%10;
        if(emptyIndex[pos] == 1){
            if(emptyCount < 0)
                return;
            vsComputerInput();
        } else {
            cout<< "Yvie's AI choose: " << pos+1 << endl;
            emptyIndex[pos] =1;
            emptyCount-=1;
            board[pos] = 'O';
        }
 
    }
 
    void playerInput(Player &player){
        int pos;
        cout << endl;
        cout << "\n" << player.getName() <<" Turn: ";
        cout <<"\n Enter the position😉 " << endl;
        cin >> pos;
        pos -=1;
        if(emptyIndex[pos] == 1){
            cout << "______Position not empty______"<< endl;
            playerInput(player);
        } else {
            emptyIndex[pos] =1;
            emptyCount-=1;
            player.getName().compare("Player I") == 0 ? board[pos] ='X': board[pos] ='O';
        }
 
    }
 
    void checkWin(Player &p1,Player &p2){
        int i,j,k;
        bool flag = false;
        char first_symbol;
        for(i=0; i<8; i++){
            first_symbol = board[taclist[i].row[0]];
 
            if((first_symbol != 'X') && (first_symbol != 'O')){
                flag = false;
                continue;
            }
            flag = true;
            for(j=0;j<3;j++){
                if(first_symbol != board[taclist[i].row[j]]){
                    flag = false;
                    break;
                }
            }
            if(flag){
                gameOn = 0;
                if(first_symbol == 'X'){
                    cout << "_______________________"<< endl;
                    cout << "\n Player I WON🎉"<< endl;
                    cout << "_______________________"<< endl;
                    p1.won();
                } else {
                    p2.won();
                    if(againstYviesAI){
                        cout << "_______________________"<< endl;
                        cout << "\n Yvie's AI WON🎉"<< endl;
                        cout << "_______________________"<< endl;
                    } else {
                        cout << "_______________________"<< endl;
                        cout << "\n Player II WON🎉"<< endl;
                        cout << "_______________________"<< endl;
 
                    }
                }
                displayScore(p1,p2);
                break;
            }
        }
    }
 
        void play(Player &p1,Player &p2){
            char rematch ='\0';
            int hand = 0;
            gameOn =1;
            displayBoard();
            while((emptyCount > 0) && (gameOn != 0)){
 
                if(againstYviesAI)
                    hand == 1 ? vsComputerInput(): playerInput(p2);
                else
                    hand == 1 ? playerInput(p1): playerInput(p2);
                hand= !hand;
                displayBoard();
                checkWin(p1,p2);
            }
            if (emptyCount <=0){
                cout << "      _______________________"<< endl;
                cout << "\n It's a Draw🙂"<< endl;
                cout << "     _______________________"<< endl;
            }
            cout<< endl;
            cout << "Play Again? enter Y or N: ";
            cin >> rematch;
            if((rematch == 'Y')||(rematch == 'y')){
                init();
                play(p1,p2);
            }
 
        }
    void displayScore(Player &p1, Player &p2){
        cout << endl;
        cout << "\n SCORE: \n";
        if(againstYviesAI)
            cout<<" Player I: " <<p1.getScore()<<" \n Yvie's AI: "<<p2.getScore()<< endl;
        else
            cout<<" Player I: " <<p1.getScore()<<" \n Player II: "<<p2.getScore()<< endl;
    }
 
public:
    Mode(): emptyCount{0}, gameOn{1}, againstYviesAI{0}{
        init();
        taclist[0].row = new int[3]{0,1,2};
        taclist[1].row = new int[3]{3,4,5};
        taclist[2].row = new int[3]{6,7,8};
        taclist[3].row = new int[3]{0,3,6};
        taclist[4].row = new int[3]{1,4,7};
        taclist[5].row = new int[3]{2,5,8};
        taclist[6].row = new int[3]{0,4,8};
        taclist[7].row = new int[3]{2,4,6};
    }
 
    void init(){
        gameOn = 1;
 
        emptyCount =0;
        srand(time(0));
        for(size_t i=0; i<10; i++){
            emptyIndex[i] = 0;
            board[i] = (i+1) +'0';
            emptyCount++;
        }
        emptyCount--;
    }
 
    void singlePlayerMode(){
        //Creating Player
        Player p("Player I");
        Player c("Yvie's AI");
        cout << "      _______________________"<< endl;
        cout << "\n Player I: X \n Yvie's AI: O"<< endl;
        cout << "       _______________________"<< endl;
        cout << endl;
        againstYviesAI = 1;
        play(c,p);
 
    }
 
    void twoPlayerMode(){
        //Creating Player
        Player p("Player I");
        Player c("Player II");
        cout << "       _______________________"<< endl;
        cout << "\n Player I: X \n Player II: O"<< endl;
        cout << "       _______________________"<< endl;
        cout << endl;
        againstYviesAI = 0;
        play(c,p);
    }
};
 
int main()
{
    int ch;
 
    while(1){
        cout<< "      _____________MENU_____________" << endl;
        cout << "\n 1. Single Player Mode😈" <<endl;
        cout << "\n 2. Two Player Mode🤩" <<endl;
        cout << "\n 3. To exit 😥" <<endl;
        cout <<"      _______________________" << endl;
        cout << endl;
        cout <<"\n Select an option" << endl;
        cin >> ch;
        switch(ch){
        case 1:{
            Mode *game = new Mode;
            game->init();
            game->singlePlayerMode();
            }
            break;
        case 2:{
            Mode *game = new Mode;
            game->init();
            game->twoPlayerMode();
            }
            break;
        case 3:
            return 0;
        default:
            cout << "OUUU You entered an invalid option😑 TRY AGAIN";
        }
 
    }
    return 0;
}

