#include "ui.h"
#include "pet.h"
#include "actions.h"
#include <iostream>
#include <iomanip>
#include <limits>

void clearScreen(){ std::cout<<"\033[2J\033[H"; }

void drawPetArt(LifeStage s){
    std::cout<<"\n";
    switch(s){
    case EGG:    std::cout<<"       .--.\n      /    \\\n     | o  o |\n      \\  ~ /\n       `--'\n"; break;
    case BABY:   std::cout<<"      (^_^)\n      /|  |\\\n       /  \\\n"; break;
    case CHILD:  std::cout<<"     (^_^)/\n     /|   |\n      / \\\n"; break;
    case TEEN:   std::cout<<"     (>_<)/\n     /|   |\n      / \\\n"; break;
    case ADULT:  std::cout<<"     (*v*)\n     /|   |\\\n      / \\\n"; break;
    case SENIOR: std::cout<<"     (u_u)~\n     /|   |\\\n      / \\\n"; break;
    case DEAD:   std::cout<<"     (x_x)\n      /|\\\n      / \\\n"; break;
    }
    std::cout<<"\n";
}

static std::string bar(int v){
    std::string b="[";
    for(int i=0;i<10;i++) b+=(i<v/10)?'#':'.';
    return b+"]";
}

void drawStatBars(const Pet& p){
    std::cout<<"  Hunger:    "<<bar(p.hunger)<<"  "<<std::setw(3)<<p.hunger<<"%\n";
    std::cout<<"  Happiness: "<<bar(p.happiness)<<"  "<<std::setw(3)<<p.happiness<<"%\n";
    std::cout<<"  Health:    "<<bar(p.health)<<"  "<<std::setw(3)<<p.health<<"%\n";
    std::cout<<"  Energy:    "<<bar(p.energy)<<"  "<<std::setw(3)<<p.energy<<"%\n";
}

void drawMainScreen(const GameState& gs){
    clearScreen();
    const Pet& p=gs.pet;
    const char* ds=gs.difficulty==EASY?"EASY":gs.difficulty==HARD?"HARD":"NORMAL";
    std::cout<<"  ╔════════════════════════════════════════╗\n";
    std::cout<<"  ║    TAMAGOTCHI TERMINAL  ["<<std::left<<std::setw(7)<<ds<<"]   ║\n";
    std::cout<<"  ╠════════════════════════════════════════╣\n";
    drawPetArt(p.stage);
    std::cout<<"  Name: "<<p.name<<"   Stage: "<<stageName(p.stage)
             <<"   Age: "<<p.age<<" day(s)\n";
    std::cout<<"  Weight: "<<p.weight<<"g   Gold: "<<p.gold<<"\n";
    if(p.isSick) std::cout<<"  !! PET IS SICK !! Use medicine!\n";
    std::cout<<"\n";
    drawStatBars(p);
    std::cout<<"\n";
    if(!gs.message.empty()) std::cout<<"  >> "<<gs.message<<"\n\n";
    std::cout<<"  ╠════════════════════════════════════════╣\n";
}

void showMainMenu(const GameState&){
    std::cout<<"  [1] Feed    [2] Play    [3] Sleep   [4] Heal\n";
    std::cout<<"  [5] Shop    [6] Invent  [7] Status  [8] Leaderboard\n";
    std::cout<<"  [9] Save    [0] Quit\n";
    std::cout<<"  ╚════════════════════════════════════════╝\n";
    std::cout<<"  Choice: ";
}

void showWelcomeScreen(){
    clearScreen();
    std::cout<<"\n";
    std::cout<<"  ╔══════════════════════════════════════╗\n";
    std::cout<<"  ║                                      ║\n";
    std::cout<<"  ║     T A M A G O T C H I             ║\n";
    std::cout<<"  ║         T E R M I N A L             ║\n";
    std::cout<<"  ║                                      ║\n";
    std::cout<<"  ║  Raise your pet from egg to senior.  ║\n";
    std::cout<<"  ║  Stats decay in real time even       ║\n";
    std::cout<<"  ║  while the game is closed!           ║\n";
    std::cout<<"  ║                                      ║\n";
    std::cout<<"  ╚══════════════════════════════════════╝\n\n";
}

DifficultyLevel chooseDifficulty(){
    std::cout<<"  Select Difficulty:\n";
    std::cout<<"  [1] Easy   - Slow decay, rare events, no permadeath\n";
    std::cout<<"  [2] Normal - Standard, permadeath on\n";
    std::cout<<"  [3] Hard   - Fast decay, frequent events, expensive shop\n";
    std::cout<<"  Choice: ";
    int c; while(!(std::cin>>c)||c<1||c>3){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"  Enter 1-3: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    return c==1?EASY:c==3?HARD:NORMAL;
}

void showDeathScreen(const Pet& p,const std::string& cause){
    clearScreen();
    std::cout<<"\n  ╔══════════════════════════════════════╗\n";
    std::cout<<"  ║         YOUR PET HAS DIED            ║\n";
    std::cout<<"  ╚══════════════════════════════════════╝\n";
    drawPetArt(DEAD);
    std::cout<<"  "<<p.name<<" has passed away.\n";
    std::cout<<"  Age: "<<p.age<<" day(s)   Cause: "<<cause<<"\n";
    std::cout<<"  Rest in peace, "<<p.name<<".\n\n";
}

void showEvolutionScreen(const Pet& p){
    clearScreen();
    std::cout<<"\n  *** "<<p.name<<" EVOLVED! ***\n";
    std::cout<<"  New stage: "<<stageName(p.stage)<<"\n";
    drawPetArt(p.stage);
    pressEnterToContinue();
}

void printMessage(const std::string& msg){
    if(!msg.empty()) std::cout<<"\n  *** "<<msg<<" ***\n";
}

void pressEnterToContinue(){
    std::cout<<"  [Press Enter to continue]";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}
