#include "events.h"
#include "pet.h"
#include <cstdlib>
#include <vector>
std::string rollEvent(GameState& gs) {
    if(rand()%100>=eventChance(gs.difficulty)) return "";
    std::string msg; int t=rand()%100;
    if(t<40)      applyNegativeEvent(gs.pet,gs.difficulty,msg);
    else if(t<70) applyPositiveEvent(gs.pet,msg);
    else          applyNeutralEvent(gs.pet,msg);
    clampStats(gs.pet); return msg;
}
void applyNegativeEvent(Pet& pet, DifficultyLevel diff, std::string& msg) {
    int dr=drainRate(diff),ev=rand()%6;
    switch(ev){
    case 0: pet.isSick=true; pet.health-=10*dr/2;
        msg=pet.name+" caught a cold! (now sick)"; break;
    case 1: pet.happiness-=20*dr/2;
        msg=pet.name+" had a nightmare!"; break;
    case 2: pet.hunger+=30; pet.weight+=5;
        msg=pet.name+" raided the fridge! (+weight)"; break;
    case 3: pet.happiness-=15*dr/2;
        msg=pet.name+" is extremely bored!"; break;
    case 4: pet.health-=12*dr/2;
        msg=pet.name+" got into a fight!"; break;
    case 5:
        if(!pet.inventory.empty()){
            std::string lost=pet.inventory.back().name;
            pet.inventory.pop_back();
            msg=pet.name+" broke the "+lost+"! Lost.";
        } else { pet.happiness-=10; msg=pet.name+" is lonely."; }
        break;
    }
}
void applyPositiveEvent(Pet& pet, std::string& msg) {
    int ev=rand()%6;
    switch(ev){
    case 0: { int c=10+rand()%21; pet.gold+=c;
        msg=pet.name+" found "+std::to_string(c)+" gold!"; break; }
    case 1: pet.happiness+=15; msg=pet.name+" is in a great mood!"; break;
    case 2: { pet.happiness+=10;
        std::vector<std::string> tr={"backflip","high-five","spin","wave","bow"};
        std::string t=tr[rand()%tr.size()]; pet.tricksLearned.push_back(t);
        msg=pet.name+" learned to "+t+"!"; break; }
    case 3: { Item g; g.name="Mystery Candy"; g.type=FOOD; g.hungerMod=15;
        g.happyMod=10; g.healthMod=0; g.energyMod=5; g.weightMod=2; g.price=0;
        pet.inventory.push_back(g); msg="Mystery Candy added to inventory!"; break; }
    case 4: pet.energy+=20; msg=pet.name+" had a great nap! Energy up."; break;
    case 5: pet.health+=10; msg=pet.name+" is glowing with health!"; break;
    }
}
void applyNeutralEvent(Pet& pet, std::string& msg) {
    int ev=rand()%6;
    switch(ev){
    case 0: pet.refusesFood=true; pet.refusedFoodName="Rice Ball";
        msg=pet.name+" refuses Rice Ball today!"; break;
    case 1: pet.energy-=10; msg=pet.name+" is extra sleepy."; break;
    case 2: pet.happiness-=5; msg=pet.name+" is hiding under the bed."; break;
    case 3: pet.happiness+=5; msg=pet.name+" is singing a little song!"; break;
    case 4: msg=pet.name+" is staring at the wall (huh?)"; break;
    case 5: pet.happiness-=5; msg=pet.name+" wants a Ball toy!"; break;
    }
}
