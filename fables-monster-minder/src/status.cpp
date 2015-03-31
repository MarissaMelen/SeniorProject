#include "status.hpp"
#include <string>

statustype read_statustype(std::string input){
  //Make input lowercase
  for (unsigned int i=0; i<input.size(); ++i){
    input[i] = tolower(input[i]);
  }
  if(input == "damage"){
    return damage;
  }else if(input == "healing"){
    return healing;
  }else if(input == "mana drain"){
    return manadrain;
  }else if(input == "mana regen"){
    return manaregen;
  }else if(input == "burn"){
    return burn;
  }else if(input == "freeze"){
    return freeze;
  }else if(input == "poison"){
    return poison;
  }else if(input == "petrify"){
    return petrify;
  }else if(input == "headwind"){
    return headwind;
  }else if(input == "paralyze"){
    return paralyze;
  }else if(input == "silence"){
    return silence;
  }else if(input == "blind"){
    return blind;
  }else if(input == "confuse"){
    return confuse;
  }else if(input == "infatuate"){
    return infatuate;
  }else if(input == "bind"){
    return bind;
  }else if(input == "bleed"){
    return bleed;
  }else if(input == "blight"){
    return blight;
  }else if(input == "asleep"){
    return asleep;
  }else if(input == "taunt"){
    return taunt;
  }else if(input == "curse"){
    return curse;
  }else if(input == "stat decrease"){
    return statdown;
  }else if(input == "stat increase"){
    return statup;
  }else{
    return specialstatus;
  }
}

 
std::string write_statustype(statustype s){
  if(s == damage){
    return "damage";
  }else if(s == healing){
    return "healing";
  }else if(s == manadrain){
    return "manadrain";
  }else if(s == manaregen){
    return "manaregen";
  }else if(s == burn){
    return "burn";
  }else if(s == freeze){
    return "freeze";
  }else if(s == poison){
    return "poison";
  }else if(s == petrify){
    return "petrify";
  }else if(s == headwind){
    return "headwind";
  }else if(s == paralyze){
    return "paralyze";
  }else if(s == silence){
    return "silence";
  }else if(s == blind){
    return "blind";
  }else if(s == confuse){
    return "confuse";
  }else if(s == infatuate){
    return "infatuate";
  }else if(s == bind){
    return "bind";
  }else if(s == bleed){
    return "bleed";
  }else if(s == blight){
    return "blight";
  }else if(s == asleep){
    return "asleep";
  }else if(s == taunt){
    return "taunt";
  }else if(s == curse){
    return "curse";
  }else if(s == statdown){
    return "stat decrease";
  }else if(s == statup){
    return "stat increase";
  }else{
    return "special";
  }
}
