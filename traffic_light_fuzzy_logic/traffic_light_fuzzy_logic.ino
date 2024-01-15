#include <Fuzzy.h>

Fuzzy *fuzzy = new Fuzzy();

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));

  // Input 1 = Queue Count
  FuzzyInput *Q = new FuzzyInput(1);
  FuzzySet *LOW1 = new FuzzySet(0, 1, 2);
  Q->addFuzzySet(LOW1);
  FuzzySet *MEDIUM1 = new FuzzySet(1, 2, 3);
  Q->addFuzzySet(MEDIUM1);
  FuzzySet *HIGH1 = new FuzzySet(2, 3, 4);
  Q->addFuzzySet(HIGH1);
  fuzzy->addFuzzyInput(Q);

   // Input 2 = Waiting Time
  FuzzyInput *W = new FuzzyInput(2);
  FuzzySet *SHORT1 = new FuzzySet(0, 5, 10);
  W->addFuzzySet(SHORT1);
  FuzzySet *MEDIUM2 = new FuzzySet(5, 10, 15);
  W->addFuzzySet(MEDIUM2);
  FuzzySet *LONG1 = new FuzzySet(10, 15, 20);
  W->addFuzzySet(LONG1);
  fuzzy->addFuzzyInput(W);

  // Output = Duration of Green Light
  FuzzyOutput *D = new FuzzyOutput(1);
  FuzzySet *SHORT2 = new FuzzySet(0, 7.5, 15);
  D->addFuzzySet(SHORT2);
  FuzzySet *MEDIUM3 = new FuzzySet(10, 17.5, 25);
  D->addFuzzySet(MEDIUM3);
  FuzzySet *LONG2 = new FuzzySet(20, 27.5, 35);
  D->addFuzzySet(LONG2);
  fuzzy->addFuzzyOutput(D);

  //RULES
  
  // Rule 1: If Q is LOW AND W is SHORT, then D is SHORT
  FuzzyRuleAntecedent *QL_WS = new FuzzyRuleAntecedent();
  QL_WS->joinWithAND(LOW1, SHORT1);
  FuzzyRuleConsequent *DS1 = new FuzzyRuleConsequent();
  DS1->addOutput(SHORT2);
  FuzzyRule *fuzzyRule01 = new FuzzyRule(1, QL_WS, DS1);
  fuzzy->addFuzzyRule(fuzzyRule01);

  // Rule 2: If Q is LOW AND W is MEDIUM, then D is SHORT
  FuzzyRuleAntecedent *QL_WM = new FuzzyRuleAntecedent();
  QL_WM->joinWithAND(LOW1, MEDIUM2);
  FuzzyRuleConsequent *DS2 = new FuzzyRuleConsequent();
  DS2->addOutput(SHORT2);
  FuzzyRule *fuzzyRule02 = new FuzzyRule(2, QL_WM, DS2);
  fuzzy->addFuzzyRule(fuzzyRule02);

  // Rule 3: If Q is LOW AND W is LONG, then D is MEDIUM
  FuzzyRuleAntecedent *QL_WL = new FuzzyRuleAntecedent();
  QL_WL->joinWithAND(LOW1, LONG1);
  FuzzyRuleConsequent *DM1 = new FuzzyRuleConsequent();
  DM1->addOutput(MEDIUM3);
  FuzzyRule *fuzzyRule03 = new FuzzyRule(3, QL_WL, DM1);
  fuzzy->addFuzzyRule(fuzzyRule03);

   // Rule 4: If Q is MEDIUM AND W is SHORT, then D is SHORT
  FuzzyRuleAntecedent *QM_WS = new FuzzyRuleAntecedent();
  QM_WS->joinWithAND(MEDIUM1, SHORT1);
  FuzzyRuleConsequent *DS3 = new FuzzyRuleConsequent();
  DS3->addOutput(SHORT2);
  FuzzyRule *fuzzyRule04 = new FuzzyRule(4, QM_WS, DS3);
  fuzzy->addFuzzyRule(fuzzyRule04);

  // Rule 5: If Q is MEDIUM AND W is MEDIUM, then D is MEDIUM
  FuzzyRuleAntecedent *QM_WM = new FuzzyRuleAntecedent();
  QM_WM->joinWithAND(MEDIUM1, MEDIUM2);
  FuzzyRuleConsequent *DM2 = new FuzzyRuleConsequent();
  DM2->addOutput(MEDIUM3);
  FuzzyRule *fuzzyRule05 = new FuzzyRule(5, QM_WM, DM2);
  fuzzy->addFuzzyRule(fuzzyRule05);

  // Rule 6: If Q is MEDIUM AND W is LONG, then D is LONG
  FuzzyRuleAntecedent *QM_WL = new FuzzyRuleAntecedent();
  QM_WL->joinWithAND(MEDIUM1, LONG1);
  FuzzyRuleConsequent *DL1 = new FuzzyRuleConsequent();
  DL1->addOutput(LONG2);
  FuzzyRule *fuzzyRule06 = new FuzzyRule(6, QM_WL, DL1);
  fuzzy->addFuzzyRule(fuzzyRule06);

  // Rule 7: If Q is HIGH AND W is SHORT, then D is MEDIUM
  FuzzyRuleAntecedent *QH_WS = new FuzzyRuleAntecedent();
  QH_WS->joinWithAND(HIGH1, SHORT1);
  FuzzyRuleConsequent *DM3 = new FuzzyRuleConsequent();
  DM3->addOutput(MEDIUM3);
  FuzzyRule *fuzzyRule07 = new FuzzyRule(7, QH_WS, DM3);
  fuzzy->addFuzzyRule(fuzzyRule07);

  // Rule 8: If Q is HIGH AND W is MEDIUM, then D is LONG
  FuzzyRuleAntecedent *QH_WM = new FuzzyRuleAntecedent();
  QH_WM->joinWithAND(HIGH1, MEDIUM2);
  FuzzyRuleConsequent *DL2 = new FuzzyRuleConsequent();
  DL2->addOutput(LONG2);
  FuzzyRule *fuzzyRule08 = new FuzzyRule(8, QH_WM, DL2);
  fuzzy->addFuzzyRule(fuzzyRule08);

  // Rule 9: If Q is HIGH AND W is LONG, then D is LONG
  FuzzyRuleAntecedent *QH_WL = new FuzzyRuleAntecedent();
  QH_WL->joinWithAND(HIGH1, LONG2);
  FuzzyRuleConsequent *DL3 = new FuzzyRuleConsequent();
  DL3->addOutput(LONG2);
  FuzzyRule *fuzzyRule09 = new FuzzyRule(9, QH_WL, DL3);
  fuzzy->addFuzzyRule(fuzzyRule09);
 
}

void loop()
{
  // Getting a random value
  int input1 = random(0, 4);
  int input2 = random(0, 20);
  
  // Printing something
  Serial.println("\n\n\nEntrance: ");
  Serial.print("\t\t\tQueue: ");
  Serial.println(input1);
  Serial.print("\t\t\tWaiting Time: ");
  Serial.println(input2);

  
  // Enter input into fuzzy
  fuzzy->setInput(1, input1);
  fuzzy->setInput(2, input2);
  fuzzy->fuzzify();
  
  // Running the Defuzzification
  float output = fuzzy->defuzzify(1);
  
  // Printing something
  Serial.println("Result: ");
  Serial.print("\t\t\tDuration: ");
  Serial.println(output);
  // wait 12 seconds
  delay(12000);
}
