//
// Created by Hege Michalsen on 12/11/2020.
//

#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H

#include <string>
#include<iterator>
using std::string;


class GameObject {
    public:
    bool operator == (const GameObject& s) const {return shortName == s.shortName && longDescription == s.longDescription && keyword == s.keyword; }
    bool operator != (const GameObject& s) const {return !operator == (s); }

    const string* shortName;
    const string* longDescription;
    const string* keyword;

    GameObject(const string *_sName, const string *_lDesc, const string *_kWord);

    const string *getName();
    const string *getDescription();
    const string *getKeyword();
    /*void *GameObject::setName(string _sName);
    void *GameObject::setDescription(string _lDesc);
    void *GameObject::setKeyword(string _kWord);*/
};


#endif //TEXTADV_GAMEOBJECT_H
