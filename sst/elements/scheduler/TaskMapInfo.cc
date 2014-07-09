// Copyright 2009-2014 Sandia Corporation. Under the terms
// of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
// Government retains certain rights in this software.
// 
// Copyright (c) 2009-2014, Sandia Corporation
// All rights reserved.
// 
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#include "TaskMapInfo.h"

#include "AllocInfo.h"
#include "Job.h"
#include "MeshMachine.h"
#include "output.h"
#include "TaskCommInfo.h"

using namespace SST::Scheduler;

TaskMapInfo::TaskMapInfo(AllocInfo* ai)
{
    allocInfo = ai;
    job = ai->job;
    taskCommInfo = job->taskCommInfo;
    size = job->getProcsNeeded();
    taskToNode = new int[size];
    mappedCount = 0;
    totalHopDist = 0;
}

TaskMapInfo::~TaskMapInfo()
{
    delete allocInfo;
    delete [] taskToNode;
}

void TaskMapInfo::insert(int taskInd, int nodeInd)
{
    taskToNode[taskInd] = nodeInd;
    mappedCount++;
}

//Current version only checks if there is communication
unsigned long TaskMapInfo::getTotalHopDist(const MeshMachine & machine)
{
    if(totalHopDist == 0) {

        //check if every task is mapped
        if(size > mappedCount){
            schedout.fatal(CALL_INFO, 1, "Task mapping info requested before all tasks are mapped.");
        }

        int** commMatrix = taskCommInfo->getCommMatrix();
        //iterate through all tasks
        for(int taskIter = 0; taskIter < size; taskIter++){
            MeshLocation curLoc = MeshLocation(taskToNode[taskIter], machine);
            //iterate through other tasks and add distance for communication
            //assume two-way communication
            for(int otherTaskIter = taskIter + 1 ; otherTaskIter < size; otherTaskIter++){
                if( commMatrix[taskIter][otherTaskIter] != 0 ||
                    commMatrix[otherTaskIter][taskIter] != 0 ){
                    MeshLocation otherNode = MeshLocation(taskToNode[otherTaskIter], machine);
                    totalHopDist += curLoc.L1DistanceTo(otherNode);
                }
            }
        }
        //add duplicates
        totalHopDist *= 2;

        //delete comm matrix
        for(int i = 0 ; i < size; i++){
            delete [] commMatrix[i];
        }
        delete [] commMatrix;
    }

    return totalHopDist;
}    
