//
// Created by Hege Michalsen on 19/11/2020.
//

#include "GameObject.h"
#include <list>
#include <iostream>

GameObject::GameObject(const string *_sName,
                       const string *_lDesc,
                       const string *_kWord) {
            this->shortName = _sName;
            this->longDescription = _lDesc;
            this->keyword = _kWord;
    };

const string *GameObject::getName() {
    return this->shortName;
}

const string *GameObject::getDescription() {
    return this->longDescription;
}

const string *GameObject::getKeyword() {
    return this->keyword;
}


/*
void *GameObject::setName(string _sName) {
    shortName = _sName;
}

void *GameObject::setDescription(string _lDesc) {
    longDescription = _lDesc;
}

void *GameObject::setKeyword(string _kWord) {
    keyword = _kWord;
}*/



