#include <windows.h>
#include <VariadicTable.h>
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std ;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int login(){
    string user , pass;
    ifstream testFile ("../admin.txt");

    if (testFile.is_open())
    {

        getline (testFile , user) ;
        getline (testFile , pass) ;

        testFile.close();
    }

    string username , password ;
    SetConsoleTextAttribute(hConsole, 5);
    cout << "Enter admin username =>" ;
    cin >> username ;
    cout << "Admin password =>" ;
    cin >> password ;
    SetConsoleTextAttribute(hConsole, 7);

    if(user == username && pass == password){

        return 0;

    }else {

        return 1;
    }
}

struct player {

    string name , team= " " , role ;

    int price , speed , finishing , defence , ID ;

};
player arrP[150] ;
int counterP = 0 ;

struct team {

    string name ;

    int money , ID , numP , counterGoalZade = 0 , counterGoalkhorde = 0, score = 0 , win = 0 , lose = 0  , mosavi = 0;

};
team  arrT[150] ;
int counterT = 0 ;

team findByNameT(string name){

    team found;

    for(int i = 0 ; i < counterT ; i++){

        if(arrT[i].name == name){

            found = arrT[i];
            break ;

        }

    }

    return found ;

}

player findByNameP(string name){

    player found;

    for(int i = 0 ; i < counterP ; i++){

        if(arrP[i].name == name){

            found = arrP[i];
            break ;

        }

    }

    return found ;

}

int isExits(string nm , char tOrP){

    if(tOrP == 'p') {

        int result = 0 ;

        for (int i = 0; i < counterP; i++) {

            if (arrP[i].name == nm){
                result = 1 ;
                return result;
            }

        }

        return result ;

    }
    else if(tOrP == 't') {

        int result = 0 ;

        for (int j = 0; j < counterT; j++) {


            if (arrT[j].name == nm){

                result = 1 ;

                return result;

            }

        }

        return result ;

    }

}

int newP(){

    string nm ;
    SetConsoleTextAttribute(hConsole, 9);
    cout << endl << "===================================" << endl ;
    SetConsoleTextAttribute(hConsole, 5);
    cout <<  "Please enter player info :" << endl << endl ;
    cout << "Name =>" ;
    cin >> nm ;

    int result = isExits(nm , 'p');
    if(result == 1){
        return 1 ;
    }
    arrP[counterP].name = nm ;

    cout << "Price =>" ;
    cin >> arrP[counterP].price ;

    cout << "Speed =>" ;
    cin >> arrP[counterP].speed ;

    cout << "Finishing =>" ;
    cin >> arrP[counterP].finishing ;

    cout << "Defence =>" ;
    cin >> arrP[counterP].defence ;
    cout << endl ;

    if(arrP[counterP].speed > arrP[counterP].defence ){
        if(arrP[counterP].speed > arrP[counterP].finishing) {
            arrP[counterP].role = "halfback";
        }
        else if(arrP[counterP].speed < arrP[counterP].finishing){
            arrP[counterP].role = "attacker";
        }
    }
    else{
        if( arrP[counterP].defence >  arrP[counterP].finishing){
            arrP[counterP].role = "defence";
        }
    }

    if(arrP[counterP].finishing == arrP[counterP].speed && arrP[counterP].finishing == arrP[counterP].defence){
        arrP[counterP].role = "normal";
    }

    counterP ++ ;
    arrP[counterP - 1].ID = counterP ;


    return 0 ;

}

int newT(){

    string nm ;
    SetConsoleTextAttribute(hConsole, 9);
    cout << endl << "===================================" << endl ;
    SetConsoleTextAttribute(hConsole, 5);
    cout <<  "Please enter team info :" << endl << endl ;
    cout << "Name =>" ;
    cin >> nm ;

    int result = isExits(nm , 't');
    if(result == 1){
        return 1 ;
    }
    arrT[counterT].name = nm ;

    cout << "Money =>" ;
    cin >> arrT[counterT].money ;

    arrT[counterT].ID = counterT + 1 ;
    counterT ++ ;

    return 0 ;

}

string buyP(){

    int idP , idT ;

    SetConsoleTextAttribute(hConsole, 9);
    cout << endl << "===================================" << endl ;
    SetConsoleTextAttribute(hConsole, 5);
    cout <<  "Please enter payment info :" << endl << endl ;

    cout << "Player id =>";
    cin >> idP ;
    if(idP > counterP){
        SetConsoleTextAttribute(hConsole, 4);
        return "player with the id " + to_string(idP) + " doesnt exist" ;
    }

    cout << "Team id =>";
    cin >> idT ;
    if(idT > counterT){
        SetConsoleTextAttribute(hConsole, 4);
        return "team with the id " + to_string(idT) + " doesnt exist" ;
    }

    int priceP = arrP[idP - 1].price ;
    int balanceT = arrT[idT - 1].money ;

    if(balanceT < priceP){
        SetConsoleTextAttribute(hConsole, 4);
        return "the team cant afford to buy this player" ;
    }

    if(arrP[idP - 1].team != " "){
        SetConsoleTextAttribute(hConsole, 4);
        return "player already has a team" ;
    }

    if(arrT[idT - 1].numP == 11){
        SetConsoleTextAttribute(hConsole, 4);
        return "team is full" ;
    }

    arrT[idT - 1].money -= priceP ;
    arrT[idT - 1].numP ++ ;

    arrP[idP - 1].team = arrT[idT - 1].name ;

    SetConsoleTextAttribute(hConsole, 2);
    return "player " + arrP[idP - 1].name + " added to the team " + arrT[idT - 1].name +" successfully" ;

}

string sellP(){

    int idP , idT ;

    SetConsoleTextAttribute(hConsole, 9);
    cout << endl << "===================================" << endl ;
    SetConsoleTextAttribute(hConsole, 5);
    cout <<  "Please enter payment info :" << endl << endl ;

    cout << "Player id =>";
    cin >> idP ;
    if(idP > counterP){
        SetConsoleTextAttribute(hConsole, 4);
        return "player with the id " + to_string(idP) + " doesnt exist" ;
    }

    cout << "Team id =>";
    cin >> idT ;
    if(idT > counterT){
        SetConsoleTextAttribute(hConsole, 4);
        return "team with the id " + to_string(idT) + " doesnt exist" ;
    }

    int priceP = arrP[idP - 1].price ;

    if(arrP[idP - 1].team == " "){
        SetConsoleTextAttribute(hConsole, 4);
        return "player does not have a team" ;
    }

    if(arrP[idP - 1].team != arrT[idT - 1].name ){
        SetConsoleTextAttribute(hConsole, 4);
        return "The player was not in this team" ;
    }

    arrT[idT - 1].money += priceP ;
    arrT[idT - 1].numP -- ;

    arrP[idP - 1].name = " " ;

    SetConsoleTextAttribute(hConsole, 2);
    return "player " + arrP[idP - 1].name + " removed from the team " + arrT[idT - 1].name +" successfully" ;

}

string friendlyMatch(){

    int idT1 , idT2 ;

    SetConsoleTextAttribute(hConsole, 9);
    cout << endl << "===================================" << endl ;
    SetConsoleTextAttribute(hConsole, 5);
    cout <<  "Please enter match info :" << endl << endl ;

    cout << "Team 1 id =>";
    cin >> idT1 ;
    if(idT1 > counterT){
        SetConsoleTextAttribute(hConsole, 4);
        return "team with the id " + to_string(idT1) + " doesnt exist" ;
    }

    cout << "Team 2 info =>" ;
    cin >> idT2 ;
    if(idT2 > counterT){
        SetConsoleTextAttribute(hConsole, 4);
        return "team with the id " + to_string(idT2) + " doesnt exist" ;
    }

    int numT1 = arrT[idT1 - 1].numP ;
    int numT2 = arrT[idT2 - 1].numP ;

    if(numT1 < 11 || numT2 < 11){
        SetConsoleTextAttribute(hConsole, 4);
        return "the game can not be held due to loss of the players" ;
    }

    int sumT1 = 0, sumT2 = 0 ;

    for(int i = 0 ; i < counterP ; i ++){

        if(arrP[i].team == arrT[idT1 - 1].name){
            sumT1 += arrP[i].speed + arrP[i].finishing + arrP[i].defence ;
        }

        else if(arrP[i].team == arrT[idT2 - 1].name){
            sumT2 += arrP[i].speed + arrP[i].finishing + arrP[i].defence ;
        }

    }

    if(sumT1 == sumT2){
        SetConsoleTextAttribute(hConsole, 7);
        return "the match is draw" ;
    }

    else if(sumT1 > sumT2){
        SetConsoleTextAttribute(hConsole, 2);
        return "team "+ to_string(idT1)+" win";
    }

    else{
        SetConsoleTextAttribute(hConsole, 2);
        return "team "+ to_string(idT2)+" win";
    }

}

string weather(){

     int result = 1+ (rand() % 4);

     string weather;

     if(result == 1)
         weather = "cloudy" ;
     else if(result == 2)
         weather = "snowy" ;
     else if(result == 3)
         weather = "sunny" ;
     else{
         weather = "rainy";
     }

    return weather ;

}

void printP(int id){

    SetConsoleTextAttribute(hConsole, 9);
    cout << endl << "===================================" ;

    cout << endl ;
    SetConsoleTextAttribute(hConsole, 5);
    cout << "Name => "  << arrT[id - 1].name;
    SetConsoleTextAttribute(hConsole, 2);
    cout << endl ;

    int cn = 1 ;

    for (int i = 0 ; i < counterP ; i++){

        if(arrP[i].team == arrT[id - 1].name){

            cout << cn << " => ";
            SetConsoleTextAttribute(hConsole, 5) ;
            cout << arrP[i].name ;
            SetConsoleTextAttribute(hConsole, 2);
            cout << " <<" << arrP[i].role << ">>" << endl ;

            cn ++ ;

        }

    }

    SetConsoleTextAttribute(hConsole, 9);
    cout << endl << "===================================" << endl ;

}

void goodbye(){
    SetConsoleTextAttribute(hConsole, 9);
    cout << endl << "===================================" << endl ;
    SetConsoleTextAttribute(hConsole, 5);
    cout << "Good luck :)" ;
}

void printInfo(string result , int goal1 , int goal2 , string weather , int counterMatch , int barande , bool isLeague = false){

    if(isLeague){

        SetConsoleTextAttribute(hConsole, 2);
        cout << endl << "[+] Weak => " ;
        SetConsoleTextAttribute(hConsole, 5);
        cout << counterMatch << endl ;

    }

    SetConsoleTextAttribute(hConsole, 2);
    cout << endl << "[+] Weather of game => " ;
    SetConsoleTextAttribute(hConsole, 5);
    cout << weather << endl ;

    SetConsoleTextAttribute(hConsole, 2);
    cout << "<<" << result << ">>" << endl ;
    SetConsoleTextAttribute(hConsole, 5);


    cout << "[+] Number of first team goal => " << goal1 << endl ;
    cout << "[+] Number of second team goal => " << goal2 ;


    SetConsoleTextAttribute(hConsole, 9);
    cout << endl << "===================================" << endl ;
}

int match(int idT1 , int idT2 , int counterMatch , bool isLeague = false){

    string r1 , winner;

    int goalT1 , goalT2 , numT ;
    if(idT1 > counterT){
        SetConsoleTextAttribute(hConsole, 4);
        cout << "team with the id " + to_string(idT1) + " doesnt exist" ;
        return 1 ;
    }

    if(idT2 > counterT){
        SetConsoleTextAttribute(hConsole, 4);
        cout << "team with the id " + to_string(idT2) + " doesnt exist" ;
        return 1;
    }

    int numT1 = arrT[idT1 - 1].numP ;
    int numT2 = arrT[idT2 - 1].numP ;

    if(numT1 < 11 || numT2 < 11){
        SetConsoleTextAttribute(hConsole, 4);
        cout << "the game can not be held due to loss of the players" ;
        return 1;
    }

    string wr = weather();

    int sumT1 = 0, sumT2 = 0 ;

    if(wr == "cloudy"){

        for(int i = 0 ; i < counterP ; i ++){

            if(arrP[i].team == arrT[idT1 - 1].name){
                sumT1 += arrP[i].speed + arrP[i].finishing + arrP[i].defence ;
            }

            else if(arrP[i].team == arrT[idT2 - 1].name){
                sumT2 += arrP[i].speed + arrP[i].finishing + arrP[i].defence ;
            }

        }

    }
    else if(wr == "snowy"){

        for(int i = 0 ; i < counterP ; i ++){

            if(arrP[i].team == arrT[idT1 - 1].name){
                if(arrP[i].role == "defence"){
                    sumT1 += arrP[i].speed + arrP[i].finishing ;
                }else{
                    sumT1 += arrP[i].speed + arrP[i].finishing + arrP[i].defence ;
                }
            }

            else if(arrP[i].team == arrT[idT2 - 1].name){
                if(arrP[i].role == "defence"){
                    sumT2 += arrP[i].speed + arrP[i].finishing ;
                }else{
                    sumT2 += arrP[i].speed + arrP[i].finishing + arrP[i].defence ;
                }
            }

        }

    }
    else if(wr == "sunny"){

        for(int i = 0 ; i < counterP ; i ++){

            if(arrP[i].team == arrT[idT1 - 1].name){
                if(arrP[i].role == "attacker"){
                    sumT1 += arrP[i].speed + arrP[i].finishing + arrP[i].defence - 10;
                }else{
                    sumT1 += arrP[i].speed + arrP[i].finishing + arrP[i].defence ;
                }
            }

            else if(arrP[i].team == arrT[idT2 - 1].name){
                if(arrP[i].role == "attacker"){
                    sumT2 += arrP[i].speed + arrP[i].finishing + arrP[i].defence - 10;
                }else{
                    sumT2 += arrP[i].speed + arrP[i].finishing + arrP[i].defence ;
                }
            }

        }

    }
    else if(wr == "rainy"){

        for(int i = 0 ; i < counterP ; i ++){

            if(arrP[i].team == arrT[idT1 - 1].name){
                if(arrP[i].role == "halfback"){
                    sumT1 += (arrP[i].speed / 2) + arrP[i].finishing + arrP[i].defence;
                }else{
                    sumT1 += arrP[i].speed + arrP[i].finishing + arrP[i].defence ;
                }
            }

            else if(arrP[i].team == arrT[idT2 - 1].name){
                if(arrP[i].role == "halfback"){
                    sumT2 += (arrP[i].speed / 2) + arrP[i].finishing + arrP[i].defence;
                }else{
                    sumT2 += arrP[i].speed + arrP[i].finishing + arrP[i].defence ;
                }
            }

        }

    }

    if(sumT1 == sumT2){

        int result = rand() % 10;

        goalT1 = result ;
        goalT2 = result ;

        arrT[idT2 - 1].counterGoalZade += goalT2 ;
        arrT[idT2 - 1].counterGoalkhorde += goalT1 ;

        arrT[idT1 - 1].counterGoalZade += goalT1 ;
        arrT[idT1 - 1].counterGoalkhorde += goalT2 ;

        arrT[idT2 - 1].score += 1 ;
        arrT[idT1 - 1].score += 1 ;

        arrT[idT2 - 1].mosavi += 1 ;
        arrT[idT1 - 1].mosavi += 1 ;

        SetConsoleTextAttribute(hConsole, 7);
        r1 = "the match is draw" ;
    }
    else {

        double val = (double) rand() / RAND_MAX;

        int random;
        if (val < 0.5)  //  50%

            random = 1;

        else if (val < 0.8 && val > 0.5)  //  80% - 50%

            random = 2;

        else if (val < 0.95 && val > 0.8)  //  95% - 80%

            random = 3;

        else

            random = 4 + (1 + (rand() % 6));

        if (sumT1 > sumT2) {

            winner = "T1";
            numT = idT1 ;

            goalT1 = random ;
            goalT2 = random - 1 ;

            SetConsoleTextAttribute(hConsole, 2);
            r1 = "team " + to_string(idT1) + " win";

        } else {

            winner = "T2" ;
            numT = idT2 ;

            goalT2 = random ;
            goalT1 = random - 1 ;

            SetConsoleTextAttribute(hConsole, 2);
            r1 = "team " + to_string(idT2) + " win";

        }

    }

    printP(idT1);
    printP(idT2);

    if(isLeague){

        if(winner == "T1"){

            arrT[idT1 - 1].counterGoalZade += goalT1 ;
            arrT[idT1 - 1].counterGoalkhorde += goalT2 ;

            arrT[idT2 - 1].counterGoalZade += goalT2 ;
            arrT[idT2 - 1].counterGoalkhorde += goalT1 ;

            arrT[idT1 - 1].score += 3 ;

            arrT[idT2 - 1].lose += 1 ;
            arrT[idT1 - 1].win += 1 ;

        }
        else{

            arrT[idT1 - 1].counterGoalZade += goalT1 ;
            arrT[idT1 - 1].counterGoalkhorde += goalT2 ;

            arrT[idT2 - 1].counterGoalZade += goalT2 ;
            arrT[idT2 - 1].counterGoalkhorde += goalT1 ;

            arrT[idT2 - 1].score += 3 ;

            arrT[idT1 - 1].lose += 1 ;
            arrT[idT2 - 1].win += 1 ;

        }


        printInfo(r1 , goalT1 , goalT2 , wr , counterMatch , numT , true  );

    }

    else {

        printInfo(r1, goalT1, goalT2, wr, counterMatch , numT );

    }

    return 0 ;

}

int beginLeague(){

    if(counterT < 3){
        cout << "The number of teams is not enough" << endl ;
        return 1 ;
    }

    team arrT2[150];

    for(int i = 0 ; i < counterT ; i++){

        arrT[i].counterGoalkhorde = 0 ;
        arrT[i].counterGoalZade = 0 ;
        arrT[i].win = 0 ;
        arrT[i].lose = 0 ;
        arrT[i].mosavi = 0 ;
        arrT[i].score = 0 ;

    }

    int counterMatch = 0 ;

    for(int i = 0 ; i < counterT ; i++){

        for(int j = i+1 ; j < counterT ; j++){
            counterMatch++;
            int rs = match(i+1 , j+1 , counterMatch , true) ;
        }

    }

    for(int i = 0 ; i < counterT ; i++){

        arrT2[i] = arrT[i];

    }

    //bubble sort
    team temp ;
    for(int i = 0 ; i < counterT ; i++){

        for(int j = 0 ; j < counterT - 1 ; j++){

            if(arrT2[j].score < arrT2[j+1].score){

                temp = arrT2[j] ;
                arrT2[j] = arrT2[j + 1];
                arrT2[j + 1] = temp ;

            }
            else if(arrT2[j].score == arrT2[j+1].score){

                if( (arrT2[j].counterGoalZade - arrT2[j].counterGoalkhorde) < (arrT2[j + 1].counterGoalZade - arrT2[j + 1].counterGoalkhorde) ){

                    temp = arrT2[j] ;
                    arrT2[j] = arrT2[j + 1];
                    arrT2[j + 1] = temp ;

                }

            }

        }

    }


    VariadicTable< string , int , int , int , int , int , int , int > vt({ "Name", "Score", "Goals scored", "Goals conceded" , "Wins" , "Draws" , "Loses" , "Difference" },10);

    for(int i = 0 ; i < counterT ; i++) {

        team tm = arrT2[i];

        vt.addRow(tm.name , tm.score , tm.counterGoalZade , tm.counterGoalkhorde , tm.win , tm.mosavi , tm.lose , (tm.counterGoalZade - tm.counterGoalkhorde));

    }

    vt.print(cout);

    return 0 ;
}

string cmd1(){
    string cmd ;

    SetConsoleTextAttribute(hConsole, 6);
    cout << "Please enter your command :" ;
    cin >> cmd ;
    SetConsoleTextAttribute(hConsole, 7);

    return cmd ;

}

int showMenu(){

    VariadicTable< int , string , string > vt({ "num", "Command" , "Description" },100);

    vt.addRow(1 , "new team" , "Create a new team and give name and team's money");
    vt.addRow(2 , "new player" , "Create a new player and give name , price and number of powers");
    vt.addRow(3 , "buy" , "Buy a player and give player id and team id");
    vt.addRow(4 , "sell" , "Sell a player and give player id and team id");
    vt.addRow(5 , "friendlyMatch" , "Only the winner is determined ");
    vt.addRow(6 , "match" , "The number of goals and the winner are determined");
    vt.addRow(7 , "beginLeague" , "The league is between teams");
    vt.addRow(8 , "showMenu" , "The names of commands and their descriptions are printed");
    vt.addRow(9 , "showTeamDetails" , "Show details of team in table");
    vt.addRow(10 , "showPlayerDetails" , "Show details of player in table");
    vt.addRow(11 , "lsP" , "List of players");
    vt.addRow(12 , "lsT" , "List of teams");
    vt.addRow(13 , "end" , "Finish program");

    vt.print(cout);

    return 0 ;

}

int showT(){

    string nm ;
    SetConsoleTextAttribute(hConsole, 9);
    cout << endl << "===================================" << endl ;
    SetConsoleTextAttribute(hConsole, 5);
    cout <<  "Please enter team info :" << endl << endl ;
    cout << "Name =>" ;
    cin >> nm ;

    SetConsoleTextAttribute(hConsole, 9);

    team found = findByNameT(nm);

    int pw0 = 0;

    for(int i = 0 ; i < counterP ; i++) {

        if(arrP[i].team == nm) {

            pw0 += (arrP[i].finishing + arrP[i].speed + arrP[i].defence) ;

        }

    }

    VariadicTable< int , string , int , int , int > vt0({ "id" , "Name", "Money" , "Number of player" , "Power of team"},10);

    vt0.addRow(found.ID , found.name , found.money , found.numP , pw0) ;

    vt0.print(cout);

    cout << endl ;

    SetConsoleTextAttribute(hConsole, 9);

    VariadicTable< int , string , string , int , int > vt1({ "id", "Name" , "Role" , "Price" , "Sum of powers" },10);

    for(int i = 0 ; i < counterP ; i++) {

        if(arrP[i].team == nm) {

            int pw = (arrP[i].finishing + arrP[i].speed + arrP[i].defence) ;
            vt1.addRow(arrP[i].ID , arrP[i].name , arrP[i].role , arrP[i].price , pw ) ;

        }

    }

    cout << "Players =>" << endl ;

    vt1.print(cout);

    return 0 ;

}

int showPlDetail(){

    string nm ;
    SetConsoleTextAttribute(hConsole, 9);
    cout << endl << "===================================" << endl ;
    SetConsoleTextAttribute(hConsole, 5);
    cout <<  "Please enter team info :" << endl << endl ;
    cout << "Name =>" ;
    cin >> nm ;

    player found = findByNameP(nm);

    VariadicTable< int , string , string , int , int , int , string , int> vt({ "id", "Name" , "Role" , "Finishing" , "Speed" , "Defence" , "Team" , "Price" },10);

    if(found.team == " "){

        vt.addRow(found.ID, found.name, found.role, found.finishing, found.speed, found.defence, "Does not have a team" , found.price);

    }
    else {

        vt.addRow(found.ID, found.name, found.role, found.finishing, found.speed, found.defence, found.team , found.price);

    }

    vt.print(cout);

    return 0 ;

}

int lsT(){

    VariadicTable< int , string > vt0({ "id" , "Name"},10);

    for(int i = 0 ; i < counterT ; i++) {
        team rs = arrT[i] ;
        vt0.addRow(rs.ID , rs.name);
    }

    vt0.print(cout);

    return 0 ;

}

int lsP(){

    VariadicTable< int , string > vt0({ "id" , "Name"},10);

    for(int i = 0 ; i < counterP ; i++) {
        player rs = arrP[i] ;
        vt0.addRow(rs.ID , rs.name);
    }

    vt0.print(cout);

    return 0;

}


int main() {

    int isLogin ;

    while(isLogin == 1)
    {
        isLogin = login();
        if(isLogin == 1) {

            SetConsoleTextAttribute(hConsole, 4);
            cout << endl <<  "Username or password is wrong !" << endl;
            SetConsoleTextAttribute(hConsole, 9);
            cout << endl << "===================================" << endl ;

        }
        else{

            SetConsoleTextAttribute(hConsole, 2);
            cout << endl << "Login successfully !" << endl;
            SetConsoleTextAttribute(hConsole, 9);
            cout << endl << "===================================" << endl ;
            break;
        }
    }

//    Sleep(3000);
//    system("cls");
    showMenu();

    string cmd ;
    while(true) {

        cmd = cmd1();

        if(cmd == "end"){
            break ;
        }

        else if(cmd == "new"){

            cin >> cmd ;

            if(cmd == "player"){

                int result = newP() ;

                if(result == 1){
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "This name was used !" << endl ;
                    SetConsoleTextAttribute(hConsole, 9);
                    cout << "===================================" << endl << endl ;
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else{
                    SetConsoleTextAttribute(hConsole, 2);
                    cout << "Player added successfully !" << endl ;
                    SetConsoleTextAttribute(hConsole, 9);
                    cout << "===================================" << endl << endl ;
                    SetConsoleTextAttribute(hConsole, 7);
                }

            }
            else if (cmd == "team"){

                int result = newT() ;

                if(result == 1){
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "This name was used !" << endl ;
                    SetConsoleTextAttribute(hConsole, 9);
                    cout << "===================================" << endl << endl ;
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else {
                    SetConsoleTextAttribute(hConsole, 2);
                    cout << "Team added successfully !" << endl  ;
                    SetConsoleTextAttribute(hConsole, 9);
                    cout << "===================================" << endl << endl ;
                    SetConsoleTextAttribute(hConsole, 7);
                }


            }

        }

        else if(cmd == "buy"){

            string result = buyP();

            cout << result << endl;
            SetConsoleTextAttribute(hConsole, 9);
            cout << "===================================" << endl << endl ;
            SetConsoleTextAttribute(hConsole, 7);

        }

        else if(cmd == "sell"){

            string result = sellP();

            cout << result << endl ;
            SetConsoleTextAttribute(hConsole, 9);
            cout << "===================================" << endl << endl ;
            SetConsoleTextAttribute(hConsole, 7);

        }

        else if(cmd == "friendlyMatch"){

            string result = friendlyMatch();

            cout << result << endl ;
            SetConsoleTextAttribute(hConsole, 9);
            cout << "===================================" << endl << endl ;
            SetConsoleTextAttribute(hConsole, 7);

        }

        else if(cmd == "match"){

            int idT1 , idT2 ;

            SetConsoleTextAttribute(hConsole, 9);
            cout << endl << "===================================" << endl ;
            SetConsoleTextAttribute(hConsole, 5);
            cout <<  "Please enter match info :" << endl << endl ;

            cout << "Team 1 id =>";
            cin >> idT1 ;

            cout << "Team 2 info =>" ;
            cin >> idT2 ;

            int c1 = 0 ;
            int num0 = match(idT1 , idT2 , c1 );

        }

        else if(cmd == "beginLeague"){

            int num1 = beginLeague();

        }

        else if(cmd == "showMenu"){

            int num = showMenu();

        }

        else if(cmd == "showTeamDetails"){

            int num = showT();

        }

        else if(cmd == "showPlayerDetails"){

            showPlDetail();

        }

        else if(cmd == "lsP"){
            lsP();
        }

        else if(cmd == "lsT"){
            lsT();
        }

    }

    goodbye();

    return 0;

}