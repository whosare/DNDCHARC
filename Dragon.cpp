/*
CSCI235 Spring 2024
Project 4 - MycoMorsels
Hozair Ibrahimkhail
4/18/24
Dragon.cpp implements the constructors and private and public functions of the Dragon class
*/

#include "Dragon.hpp"

Dragon::Dragon() : element_{NONE}, number_of_heads_{1}, flight_{false}
{
    setCategory(MYSTICAL); 
    
}


Dragon::Dragon(const std::string& name, Category category, int hitpoints, int level, bool tame, Element element, int number_of_heads, bool flight) : Creature(name, category, hitpoints, level, tame)
{
    element_ = element;
    if(!setNumberOfHeads(number_of_heads))
    {
        number_of_heads_ = 1;
    }
    flight_ = flight;
}

std::string Dragon::getElement() const
{
    switch(element_)
    {
        case FIRE:
            return "FIRE";
        case WATER:
            return "WATER";
        case EARTH:
            return "EARTH";
        case AIR:
            return "AIR";
        default:
            return "NONE";
    }
}

void Dragon::setElement(const Element& element)
{
    element_ = element;
}

int Dragon::getNumberOfHeads() const
{
    return number_of_heads_;
}

bool Dragon::setNumberOfHeads(const int& number_of_heads)
{
    if(number_of_heads > 0)
    {
        number_of_heads_ = number_of_heads;
        return true;
    }
    else
    {
        return false;
    }
}

bool Dragon::getFlight() const
{
    return flight_;
}

void Dragon::setFlight(const bool& flight)
{
    flight_ = flight;
}


void Dragon::display() const
{
    std::cout << "DRAGON - " << getName() << std::endl;
    std::cout << "CATEGORY: " << getCategory() << std::endl;
    std::cout << "HP: " << getHitpoints() << std::endl;
    std::cout << "LVL: " << getLevel() << std::endl;
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl;
    std::cout << "ELEMENT: " << getElement() << std::endl;
    std::cout << "HEADS: " << getNumberOfHeads() << std::endl;
    std::cout << "IT " << (getFlight() ? "CAN" : "CANNOT") << " FLY" << std::endl;
}



bool Dragon::eatMycoMorsel()
{
    if(getCategory() == "UNDEAD")
    {
        setTame(true);
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getCategory() == "ALIEN")
    {
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getCategory() == "MYSTICAL")
    {
        if(getElement() == "FIRE" || getElement() == "EARTH")
        {
            setHitpoints(getHitpoints() + 1);
            return false;
        }
        else if(getHitpoints() == 1)
        {
            return true;
        }
        else
        {
            setHitpoints(getHitpoints() - 1);
            setTame(false);
            return false;
        }
    }
    else
    {
        return false;
    }
}

    /**
     * @param: A const reference to int corresponding to the attack to be added to the attack queue.
     * @post: Adds an attack to the attack queue based on the int parameter.
     * Here are the attacks for the Dragon:
     
    * 1: Attack name: BITE
    *      if ALIEN: 4 PHYSICAL
    *      if MYSTICAL: 2 PHYSICAL, and additional damage of 1 [FIRE/WATER/EARTH/AIR] if the Dragon has an elemental affinity of FIRE, WATER, EARTH, or AIR)
    *      if UNDEAD: 2 PHYSICAL, 1 POISON
    *      if UNKNOWN: 2 PHYSICAL

    * 2: Attack name: STOMP
    *      if ALIEN: 2 PHYSICAL
    *      if MYSTICAL: 1 PHYSICAL, and additional damage of 1 [FIRE/WATER/EARTH/AIR] if the Dragon has an elemental affinity of FIRE, WATER, EARTH, or AIR)
    *      if UNDEAD: 1 PHYSICAL, 1 POISON
    *      if UNKNOWN: 1 PHYSICAL

    * 3: Attack name: [ELEMENTAL BREATH/BAD BREATH], where the name is ELEMENTAL BREATH if the Dragon has an elemental affinity, otherwise it is BAD BREATH
    *      if ALIEN: 6 [POISON/FIRE/WATER/EARTH/AIR], where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
    *      if MYSTICAL: 3 [POISON/FIRE/WATER/EARTH/AIR], where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
    *      if UNDEAD: 3 [POISON/FIRE/WATER/EARTH/AIR], 1 POISON. The damage types and amount are added to the vector as two separate entries, even if both entries are POISON type.
    *      if UNKNOWN: 3 [POISON/FIRE/WATER/EARTH/AIR] where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON  
    */
    void Dragon::addAttack(const int& attack){
        Attack Drag_temp_attack; //temp holder to store our queues, which we will then add to creature using add attack, because we cannot directly add our attack without init it. 
        switch(attack){ // switch to see if attack=1 or 2 or 3
            case 1:{//case if input is 1
            Drag_temp_attack.name_="BITE"; //bite for 1
            //gets for category and appends what needs to be added
            if (getCategory()=="ALIEN"){//basic category checking
                Drag_temp_attack.damage_.push_back(4);
                Drag_temp_attack.type_.push_back("PHYSICAL");
            }
            else if(getCategory()=="MYSTICAL"){ //mystical
                Drag_temp_attack.type_.push_back("PHYSICAL");
                Drag_temp_attack.damage_.push_back(2);
                if (getElement()!="NONE"){
                    // Drag_temp_attack.type_.push_back(getElement());
                    Drag_temp_attack.damage_.push_back(1);
                }
                
            }
            else if (getCategory()=="UNDEAD"){
                Drag_temp_attack.damage_.push_back(2);//for phsyical
                Drag_temp_attack.damage_.push_back(1);//for poison
                Drag_temp_attack.type_.push_back("PHYSICAL");
                Drag_temp_attack.type_.push_back("POISON");
            }
            else {//checks for unknown
                Drag_temp_attack.type_.push_back("PHYSICAL");
                Drag_temp_attack.damage_.push_back(2);
            }
            break;}

            case 2:{//case if input is 2

            Drag_temp_attack.name_=("STOMP");
            if (getCategory()=="ALIEN"){
                Drag_temp_attack.damage_.push_back(2);
                Drag_temp_attack.type_.push_back("PHYSICAL");
            }
            else if(getCategory()=="MYSTICAL"){ //mystical
                Drag_temp_attack.type_.push_back("PHYSICAL");
                Drag_temp_attack.damage_.push_back(1);
                if (getElement()!="NONE"){//checks for if element exists, if it does it has an extra dmg
                    Drag_temp_attack.damage_.push_back(1);
                    // Drag_temp_attack.type_.push_back(getElement());
                }
                
            }
            else if (getCategory()=="UNDEAD"){
                Drag_temp_attack.damage_.push_back(1);//for physical
                Drag_temp_attack.damage_.push_back(1);//for poison
                Drag_temp_attack.type_.push_back("PHYSICAL");
                Drag_temp_attack.type_.push_back("POISON");
            }
            else {//checks for unknown
                Drag_temp_attack.type_.push_back("PHYSICAL");
                Drag_temp_attack.damage_.push_back(1);
            }
            break;}

            case 3:{//case if input is 3
      
            if (getElement()!="NONE"){//checks if there exists elemental affinity, if not, it will be bad breath. Does this by checking get element returns anything buy NONE
                Drag_temp_attack.name_="ELEMENTAL BREATH";
            }
            else{//if no element exists
                Drag_temp_attack.name_="BAD BREATH";
            }
            if (getCategory()=="ALIEN"){
                Drag_temp_attack.damage_.push_back(6);
                if (getElement()!="NONE"){//check if poison can be an affinity
                    Drag_temp_attack.type_.push_back(getElement());
                }
                else{
                    Drag_temp_attack.type_.push_back("POISON");//adds poison element
                }
            }
            else if(getCategory()=="MYSTICAL"){ //mystical
                Drag_temp_attack.damage_.push_back(3);
                if (getElement()!="NONE"){//check if poison can be an affinity
                    Drag_temp_attack.type_.push_back(getElement());
                }
                else{//checks for unknown
                    Drag_temp_attack.type_.push_back("POISON");//adds poison element
                }
            }
            else if (getCategory()=="UNDEAD"){
                Drag_temp_attack.damage_.push_back(3);
                if (getElement()!="NONE" || getElement()=="POISON"){//check if poison can be an affinity
                    Drag_temp_attack.type_.push_back(getElement());
                }
                else {//checker for poison
                    Drag_temp_attack.type_.push_back("POISON");
                }
                Drag_temp_attack.damage_.push_back(1);
                Drag_temp_attack.type_.push_back("POISON");
            }
            else {
                Drag_temp_attack.damage_.push_back(3);
                if (getElement()!="NONE" || getElement()=="POISON"){//check if poison can be an affinity or if has element
                    Drag_temp_attack.type_.push_back(getElement());
                }
                else{
                    Drag_temp_attack.type_.push_back("POISON");//adds poison element, lacks element
                }
            }
            break;}

        }
        Creature::addAttack(Drag_temp_attack);//adds the temp holder for queue attack to creature vector
    }

    /**
     * @post:  displays the attacks of the Dragon in the form:
     *        [DRAGON] Choose an attack (1-3):\n1: BITE\t\t2: STOMP\t\t3: ELEMENTAL BREATH\n
     */
    void Dragon::displayAttacks()const {
        std::cout<<"[DRAGON] Choose an attack (1-3):\n1: BITE\t\t2: STOMP\t\t3: ELEMENTAL BREATH\n";
    }
