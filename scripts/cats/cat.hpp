#pragma once

#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include <scripts/game.hpp>

enum class Age : unsigned char {
    Newborn, Kitten, Adolescent, YoungAdult, Adult, SeniorAdult, Senior
};

enum class Status : unsigned char {
    Newborn, Kitten,  Warrior, Apprentice, Mediator, MediatorApprentice, MedicineCat, MedicineCatApprentice, Elder, Deputy, Leader
};


enum class Backstory : unsigned char {
    RetiredLeader, OstracizedWarrior, MedicineCat, ClanFounder, ClanBorn, HalfClan1, HalfClan2, OutsiderRoots1, OutsiderRoots2, Loner1, Loner2, Disgraced1, Disgraced2, Disgraced3,
    Kittypet1, Kittypet2, Kittypet3, Kittypet4, Rogue1, Rogue2, Rogue3, Abandoned1, Abandoned2, Abandoned3, Abandoned4, OtherClan1, OtherClan2, OtherClan3, OtherClan4, 
    Refugee1, Refugee2, Refugee3, Refugee4, Refugee5,  TragedySurvivor1, TragedySurvivor2, TragedySurvivor3, TragedySurvivor4, 
    Orphaned1, Orphaned2, Orphaned3, Orphaned4, Orphaned5, Orphaned6,  WanderingHealer1, WanderingHealer2, 
    Guided1, Guided2, Guided3, Guided4, Outsider1, Outsider2, Outsider3
};

namespace BackstoryCategories {
    Backstory Clanborn[] = {
        Backstory::ClanBorn, Backstory::HalfClan1, Backstory::HalfClan2, Backstory::OutsiderRoots1, Backstory::OutsiderRoots2
    };
    Backstory FormerClancat[] = {
        Backstory::OstracizedWarrior, Backstory::Disgraced1, Backstory::Disgraced2, Backstory::Disgraced3
    };
    Backstory Otherclan[] = {
        Backstory::OtherClan1, Backstory::OtherClan2, Backstory::OtherClan3, Backstory::OtherClan4
    };
    Backstory Loner[] = {
        Backstory::Loner1, Backstory::Loner2, Backstory::Refugee2, Backstory::TragedySurvivor4
    };
    Backstory Rogue[] = {
        Backstory::Rogue1, Backstory::Rogue2, Backstory::Rogue3, Backstory::Refugee4, Backstory::TragedySurvivor2
    };
    Backstory Kittypet[] = {
        Backstory::Kittypet1, Backstory::Kittypet2, Backstory::Kittypet3, Backstory::Kittypet4, Backstory::Refugee3, Backstory::TragedySurvivor3
    };
    Backstory Healer[] = {
        Backstory::MedicineCat, Backstory::WanderingHealer1, Backstory::WanderingHealer2
    };
    Backstory Orphan[] = {
        Backstory::Orphaned1, Backstory::Orphaned2, Backstory::Orphaned3, Backstory::Orphaned4, Backstory::Orphaned5, Backstory::Orphaned6
    };
    Backstory Abandoned[] = {
        Backstory::Abandoned1, Backstory::Abandoned2, Backstory::Abandoned3, Backstory::Abandoned4
    };
};


enum class Skill : unsigned char {
    Smart, SmartGood, SmartGreat,
    Teacher, TeacherGood, TeacherGreat,
    Tactitian, TactitianGood, TacticianGreat,  Insight,
    Storyteller, StorytellerGood, StorytellerGreat,
    Hunter, HunterGood, HunterGreat,
    Fighter, FighterGood, FighterGreat,
    Speaker, SpeakerGood, SpeakerGreat,
    Mediator, MediatorGood, MediatorGreat,
    Healer, HealerGood, HealerGreat,
    Kitsitter, KitsitterGood, KitsitterGreat, CampKeeper, DenBuilder,
    StarclanConnection, 
    OmenSight,  DreamWalker, Clairvoyant, Prophet, LoreKeeper, KeenEye,
};

namespace SkillGroups {
    Skill smart[]     = { Skill::Smart, Skill::SmartGood, Skill::SmartGreat };
    Skill teach[]     = { Skill::Teacher, Skill::TeacherGood, Skill::TeacherGreat };
    Skill tactician[] = { Skill::Tactitian, Skill::TactitianGood, Skill::TacticianGreat, Skill::Insight };
    Skill story[]     = { Skill::Storyteller, Skill::StorytellerGood, Skill::StorytellerGreat };
    Skill hunt[]      = { Skill::Hunter, Skill::HunterGood, Skill::HunterGreat };
    Skill fight[]     = { Skill::Fighter, Skill::FighterGood, Skill::FighterGreat };
    Skill speak[]     = { Skill::Speaker, Skill::SpeakerGood, Skill::SpeakerGreat };
    Skill mediate[]   = { Skill::Mediator, Skill::MediatorGood, Skill::MediatorGreat };
    Skill heal[]      = { Skill::Healer, Skill::HealerGood, Skill::HealerGreat };
    Skill home[]      = { Skill::Kitsitter, Skill::KitsitterGood, Skill::KitsitterGreat, Skill::CampKeeper, Skill::DenBuilder };
    Skill star[]      = { Skill::StarclanConnection };
    Skill special[]   = { Skill::OmenSight, Skill::DreamWalker, Skill::Clairvoyant, Skill::Prophet, Skill::LoreKeeper, Skill::KeenEye };
};

Skill SkillWarrior[] = {
    Skill::Hunter, Skill::HunterGood, Skill::HunterGreat, Skill::Smart, Skill::SmartGood, Skill::SmartGreat,
    Skill::Fighter, Skill::FighterGood, Skill::FighterGreat, Skill::Speaker, Skill::SpeakerGood, Skill::SpeakerGreat,
    Skill::StarclanConnection, Skill::Teacher, Skill::TeacherGood, Skill::TeacherGreat
};
Skill SkillMedicine[] = {
    Skill::Healer, Skill::HealerGood, Skill::HealerGreat,  Skill::OmenSight, Skill::DreamWalker, Skill::StarclanConnection, Skill::LoreKeeper,
    Skill::Teacher, Skill::TeacherGood, Skill::TeacherGreat, Skill::KeenEye, Skill::Smart, Skill::SmartGood, Skill::SmartGreat, 
    Skill::Mediator, Skill::MediatorGood, Skill::MediatorGreat, Skill::Clairvoyant, Skill::Prophet
};
Skill SkillMediator[] = {
    Skill::Mediator, Skill::MediatorGood, Skill::MediatorGreat, Skill::Storyteller, Skill::StorytellerGood, Skill::StorytellerGreat,
    Skill::Tactitian, Skill::TactitianGood, Skill::TacticianGreat, Skill::Insight, Skill::Smart, Skill::SmartGood, Skill::SmartGreat,
    Skill::Speaker, Skill::SpeakerGood, Skill::SpeakerGreat,
};
Skill SkillElder[] = {
    Skill::Storyteller, Skill::StorytellerGood, Skill::StorytellerGreat, Skill::Tactitian, Skill::TactitianGood, Skill::TacticianGreat, Skill::Insight,
    Skill::Mediator, Skill::MediatorGood, Skill::MediatorGreat, Skill::Teacher, Skill::TeacherGood, Skill::TeacherGreat, Skill::CampKeeper, Skill::DenBuilder,
    Skill::StarclanConnection,  Skill::Smart, Skill::SmartGood, Skill::SmartGreat, Skill::Kitsitter, Skill::KitsitterGood, Skill::KitsitterGreat, 
};



struct Personality {
    Personality();
    ~Personality();
};



struct Name {
    Name();
    ~Name();

    bool specsuffix_hidden;
    unsigned short prefix;
    unsigned short suffix;
    Status status;
};



struct Pronoun {
    Pronoun() {
        subject = "???";
        object = "???";
        possessive = "???";
        inpossessive = "???";
        self = "???";
        conjugate = false;
    };
    Pronoun(std::string subject, std::string object, std::string possessive, std::string inpossessive, std::string self, bool conjugate) {
        subject = subject;
        object = object;
        possessive = possessive;
        inpossessive = inpossessive;
        self = self;
        conjugate = conjugate;
    }
    ~Pronoun() {};

    std::string subject;
    std::string object;
    std::string possessive;
    std::string inpossessive;
    std::string self;
    
    bool conjugate;
};

Pronoun pronouns_they {"they", "them", "their", "theirs", "themself", false};
Pronoun pronouns_she {"she", "her", "her", "hers", "herself", true};
Pronoun pronouns_he {"he", "him", "his", "his", "himself", true};



class Cat {
    private:

    public:
        Cat();
        ~Cat();

        SDL_Texture* sprite;

        Name name;
        Pronoun pronouns;
        Status status;

        std::string gender;
        bool birth_gender;

        unsigned short moons;
        unsigned short experience;

        Personality personality;

        Backstory backstory;
        Skill skill;

        Cat* parent1;
        Cat* parent2;
        std::vector<Cat*> adoptive_parents;

        std::vector<Cat*> mates;
        std::vector<Cat*> former_mates;

        Cat* apprentice;
        std::vector<Cat*> former_apprentices;

        Cat* mentor;
        std::vector<Cat*> former_mentor;
        unsigned short patrol_with_mentor;

        bool isAlive;
        bool isDarkforest;
};



Cat* KittyArray[1024];