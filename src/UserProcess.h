//
// Created by jasf on 5/15/16.
//

#ifndef VIRTUALMEMORYMANAGER_CHILDPROCESS_H
#define VIRTUALMEMORYMANAGER_CHILDPROCESS_H


#include <fstream>
#include "jMessageQueue.h"
#include "jLock.h"
#include "ResourceManager.h"
#include "AbstractProcess.h"

using namespace std;

class UserProcess : public AbstractProcess {
private:

    ifstream is;

    void referencia_pagina(int page);


public:

    UserProcess(string filename);

    void run();


};


#endif //VIRTUALMEMORYMANAGER_CHILDPROCESS_H
