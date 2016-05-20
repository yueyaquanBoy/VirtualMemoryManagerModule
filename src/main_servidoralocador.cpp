//
// Modified by gfbm on 5/20/16.
//

#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <unordered_map>
#include <set>
#include "defines.h"
#include "PageAllocationServer.h"
#include "ShutdownServer.h"


using namespace std;

void execute_child(int idx);

void foo(int d){}

int main(int argc, char **argv) {
    int qtdProcess = QUANTIDADE_USR_PROCESSES;
    int child_id;
    string logStr = "[main]";

    //initiate resources

    cout << logStr << "Creating resources..." << endl;
    if (fork() == 0){
        ResourceManager *rm = ResourceManager::getInstance("config.txt");
        rm->createAllResources();
        exit(0);
    }else{
        int s;
        wait(&s);
    }

    //start page server
    cout << logStr << "start paging server" << endl;
    int pageServerPID;
    if ((pageServerPID = fork()) == 0){
        PageAllocationServer s(10000, true);
        s.run();
        exit(0);
    }




    unordered_map<int, int> pidIdxMap;
    set<int> childIdxDone;

    cout << logStr << "waiting for childs" << endl;
    for (int i = 0; i < qtdProcess; i++) {
        int status;
        int cpid = wait(&status);
        int cidx = pidIdxMap[cpid];

        cout << logStr << "child pid:" << cpid << " idx:" << cidx << " OK" << endl;
    }

    //kill page server
    kill(pageServerPID, SIGUSR2);
    //wait paging server to finish
    int status;
    int cpid = wait(&status);

   
    cpid = wait(&status);

    cout << logStr << "DONE" << endl;

    cout << logStr << "Destroying resources ..." << endl;
    if (fork() == 0){
        ResourceManager *rm = ResourceManager::getInstance("config.txt");
        rm->startAllResources();
        rm->destroyAllResources();
        exit(0);
    }else{
        int s;
        wait(&s);
    }




}



