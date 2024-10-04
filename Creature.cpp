/*
CSCI235 Spring 2024
Project 4 - MycoMorsels
Hozair Ibrahimkhail
4/18/24
Creature.hpp declares the Creature class along with its private and public members
*/

#include "Creature.hpp"


/**
    Default constructor.
    Default-initializes all private members. 
    Default creature name: "NAMELESS". 
    Booleans are default-initialized to False. 
    Default enum value: UNKNOWN 
    Default Hitpoints and Level: 1.
*/
Creature::Creature(): name_{"NAMELESS"},  category_{UNKNOWN}, hitpoints_{1}, level_{1}, tame_{false}
{ 
    
}

/**
    Parameterized constructor.
    @param      : A reference to the name of the creature (a string). Set the creature's name to NAMELESS if the provided string contains non-alphabetic characters.
    @param      : The category of the creature (a Category enum) with default value UNKNOWN
    @param      : The creature's hitpoints (an integer) , with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : The creature's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : A flag indicating whether the creature is tame, with default value False
    @post       : The private members are set to the values of the corresponding parameters.
    Hint: Notice the default arguments in the parameterized constructor.
*/
Creature::Creature(const std::string& name, Category category, int hitpoints, int level, bool tame): category_{category}
{
    if(!setName(name))
    {
        name_ = "NAMELESS";
    }
    
    if(!setHitpoints(hitpoints))
    {
        hitpoints_ = 1;
    }
    if(!setLevel(level))
    {
        level_ = 1;
    }
    tame_ = tame;

} 

/**
    @param : the name of the Creature, a reference to string
    @post  : sets the Creature's name to the value of the parameter in UPPERCASE. 
             (convert any lowercase character to uppercase)
             Only alphabetical characters are allowed. 
           : If the input contains non-alphabetic characters, do nothing.
    @return : true if the name was set, false otherwise
*/
bool Creature::setName(const std::string& name)
{
    if (name.length() == 0)
    {
        return false;
    }
    else
    {
        std::string nameUpper = name;
        for (int i = 0; i < name.length(); i++)
        {
            if (!isalpha(name[i]))
            {
                return false;
            }
            else
            {
                nameUpper[i] = toupper(name[i]);
            }
        }
        name_ = nameUpper;
        return true;
    }
}

/**
     @return : the name of the Creature
*/
std::string Creature::getName() const
{
    return name_;
}


/**
    @param  : the category of the Creature (an enum)
    @post   : sets the Creature's category to the value of the parameter
*/
void Creature::setCategory(const Category& category)
{
    category_ = category;
}


/**
     @return : the category of the Creature (in string form)
*/
std::string Creature::getCategory() const
{
    switch(category_)
    {
        case UNDEAD:
            return "UNDEAD";
        case MYSTICAL:
            return "MYSTICAL";
        case ALIEN:
            return "ALIEN";
        default:
            return "UNKNOWN";
    }
}

/**
    @param  : an integer that represents the creature's hitpoints
    @pre    : hitpoints > 0 : Creatures cannot have 0 or negative hitpoints (do nothing for invalid input)
    @post   : sets the hitpoints private member to the value of the parameter
    @return : true if the hitpoints were set, false otherwise
*/
bool Creature::setHitpoints(const int& hitpoints)
{
    if (hitpoints > 0)
    {
        hitpoints_ = hitpoints;
        return true;
    }
    else
    {
        return false;
    }
}


/**
     @return : the value stored in hitpoints_
*/
int Creature::getHitpoints() const
{
    return hitpoints_;
}

/**
    @param  : an integer level
    @pre    : level >  0 : Characters cannot have 0 or negative levels (do nothing for invalid input)
    @post   : sets the level private member to the value of the parameter
    @return : true if the level was set, false otherwise
*/
bool Creature::setLevel(const int& level)
{
    if (level > 0)
    {
        level_ = level;
        return true;
    }
    else
    {
        return false;
    }
}


/**
     @return : the value stored in level_
*/
int Creature::getLevel() const
{
    return level_;
}


/**
    @param  : a boolean value
    @post   : sets the tame flag to the value of the parameter
*/
void Creature::setTame(const bool& tame)
{
    tame_ = tame;
}


/**
    @return true if the creature is tame, false otherwise
    Note: this is an accessor function and must follow the same convention as all accessor functions even if it is not called getTame
*/
bool Creature::isTame() const
{
    return tame_;
}

/**
    @post     : displays Creature data in the form:
    "[NAME]\n
    Category: [CATEGORY]\n
    Level: [LEVEL]\n
    Hitpoints: [Hitpoints]\n
    Tame: [TRUE/FALSE]"   
*/
// void Creature::display() const
// {
//     std::cout << name_ << std::endl;
//     std::cout << "Category: " << getCategory() << std::endl;
//     std::cout << "Level: " << level_ << std::endl;
//     std::cout << "Hitpoints: " << hitpoints_ << std::endl;
//     std::cout << "Tame: " << (tame_ ? "TRUE" : "FALSE") << std::endl;
// }

bool Creature::operator==(const Creature& other_creature) const
{
    return (name_ == other_creature.name_ && category_ == other_creature.category_ && level_ == other_creature.level_ && tame_ == other_creature.tame_);
}

bool Creature::operator!=(const Creature& other_creature) const
{
    return !(*this == other_creature);
}

/**
 * @return a copy of the attackQueue
*/
std::queue<Attack> Creature::getAttackQueue() const{
    return queue_attack_; //returns the current queue of attacks
}


/**
 * @param: A const reference to attack to be added to the queue. 
 * @post: The attack is added to the queue
 */
void Creature::addAttack(const Attack& attack) {//add attack for creature objects
    queue_attack_.push(attack); //adds attack using push
}


/**
 * @post: the attackQueue is emptied
*/
void Creature::clearAttackQueue() {//clears current attack queue
    while(!queue_attack_.empty()){//iterating while not empty and pop each top
        queue_attack_.pop();
    }
}
