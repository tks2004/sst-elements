// Copyright 2013 Sandia Corporation. Under the terms
// of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2013, Sandia Corporation
// All rights reserved.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#ifndef COMPONENTS_FIREFLY_FUNCSM_RECV_H
#define COMPONENTS_FIREFLY_FUNCSM_RECV_H

#include "funcSM/api.h"
#include "funcSM/event.h"
#include "ioapi.h"

namespace SST {
namespace Firefly {

class DataMovement;
class Info;
class MsgEntry;
class ProtocolAPI;

class RecvFuncSM :  public FunctionSMInterface
{
    typedef Arg_Functor<RecvFuncSM, IO::NodeId>             IO_Functor;
    enum { WaitMatch, WaitCopy  } m_state;
  public:

    RecvFuncSM( int verboseLevel, Output::output_location_t loc,
        Info*, SST::Link*&, ProtocolAPI*, IO::Interface*, SST::Link* );

    virtual void handleEnterEvent( SST::Event* );
    virtual void handleProgressEvent( SST::Event* );
    virtual void handleSelfEvent( SST::Event* );

    virtual const char* name() {
       return "Recv"; 
    }

  private:
    void dataReady( IO::NodeId src );
    
    IO_Functor      m_dataReadyFunctor;
    SST::Link*&     m_toProgressLink;
    SST::Link*      m_selfLink;
    DataMovement*   m_dm;
    IO::Interface*  m_io;
    RecvEnterEvent* m_event;
    MsgEntry*       m_entry;
};

}
}

#endif
