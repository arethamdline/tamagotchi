#include "pet.h"
#include <algorithm>
Pet initPet(const std::string& name, DifficultyLevel diff) {
    Pet p; p.name=name; p.hunger=80; p.happiness=70; p.health=100; p.energy=100;
    p.weight=10; p.age=0; p.gold=20; p.isSick=false; p.isSleeping=false;
    p.refusesFood=false; p.refusedFoodName=""; p.stage=EGG;
    p.lastSaveTime=time(nullptr); return p;
}
void clampStats(Pet& p) {
    p.hunger=std::max(0,std::min(100,p.hunger));
    p.happiness=std::max(0,std::min(100,p.happiness));
    p.health=std::max(0,std::min(100,p.health));
    p.energy=std::max(0,std::min(100,p.energy));
    p.weight=std::max(5,std::min(50,p.weight));
    p.gold=std::max(0,p.gold);
}
void decayStats(Pet& pet, DifficultyLevel diff) {
    if(pet.stage==EGG||pet.stage==DEAD) return;
    int dr=drainRate(diff);
    pet.hunger-=dr*2; pet.happiness-=dr; pet.energy-=dr;
    if(pet.hunger<=0)    pet.health-=dr*2;
    if(pet.isSick)       pet.health-=dr*2;
    if(pet.energy<=0)    pet.health-=dr;
    if(pet.weight>40)    pet.health-=1;
    if(pet.happiness<=10)pet.health-=1;
    clampStats(pet);
}
bool checkEvolution(Pet& pet) {
    LifeStage prev=pet.stage;
    if(pet.stage==EGG   &&pet.age>=1) pet.stage=BABY;
    else if(pet.stage==BABY &&pet.age>=3 &&pet.hunger>50&&pet.health>50) pet.stage=CHILD;
    else if(pet.stage==CHILD&&pet.age>=6 &&pet.hunger>55&&pet.happiness>55&&pet.health>60) pet.stage=TEEN;
    else if(pet.stage==TEEN &&pet.age>=10&&pet.hunger>60&&pet.happiness>60&&pet.health>65) pet.stage=ADULT;
    else if(pet.stage==ADULT&&pet.age>=15) pet.stage=SENIOR;
    return pet.stage!=prev;
}
bool checkDeath(Pet& pet, std::string& cause) {
    if(pet.health<=0){
        pet.stage=DEAD;
        cause=(pet.hunger<=0)?"Starvation":(pet.isSick?"Illness":"Neglect");
        return true;
    }
    return false;
}
void agePet(Pet& pet) { pet.age++; }
std::string stageName(LifeStage s) {
    const char* n[]={"Egg","Baby","Child","Teen","Adult","Senior","Dead"};
    return (s>=EGG&&s<=DEAD)?n[s]:"Unknown";
}
void applyTimedDecay(Pet& pet, DifficultyLevel diff, long secs) {
    if(secs<=0||pet.stage==EGG||pet.stage==DEAD) return;
    long turns=std::min(secs/120L,(long)100);
    for(long i=0;i<turns;i++){decayStats(pet,diff);if(pet.health<=0)break;}
    pet.age+=(int)(secs/86400);
}
