#ifndef PET_H
#define PET_H
#include "common.h"
Pet initPet(const std::string& name, DifficultyLevel diff);
void decayStats(Pet& pet, DifficultyLevel diff);
bool checkEvolution(Pet& pet);
bool checkDeath(Pet& pet, std::string& cause);
void clampStats(Pet& pet);
void agePet(Pet& pet);
std::string stageName(LifeStage s);
void applyTimedDecay(Pet& pet, DifficultyLevel diff, long seconds);
#endif
