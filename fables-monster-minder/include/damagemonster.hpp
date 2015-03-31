#pragma once

double swordDMG(int baseDMG, int roll, int monsterPWR, double elementMOD);

double spearDMG(int baseDMG, int roll, int monsterDEF, int monsterPWR, double elementMOD);

double axeDMG(int baseDMG, int roll, int monsterPWR, double elementMOD);

double fistDMG(int baseDMG, int roll, int monsterPWR, double elementMOD);

double bowDMG(int baseDMG, int roll, int monsterPWR, double elementMOD);

double crossbowDMG(int baseDMG, int roll, int monsterDEF, int monsterPWR, double elementMOD);

double firearmDMG(int baseDMG, int roll, int monsterDEF, double elementMOD);

double nonmageDMG(int baseDMG, int roll, int monsterPWR);

double knifeDMG(int baseDMG, int roll, int monsterPWR, double elementMOD, double cunningBNS);

double quickcastDMG(int baseDMG, int roll, int monsterRES, double elementMOD);

double customDMG(int baseDMG, int monsterARM, int monsterDEF, int monsterRES, double elementMOD, double dmgMOD);


