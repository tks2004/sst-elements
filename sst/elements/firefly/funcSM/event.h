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

#ifndef COMPONENTS_FIREFLY_FUNCSM_EVENT_H
#define COMPONENTS_FIREFLY_FUNCSM_EVENT_H

#include <sst/core/sst_types.h>
#include <sst/core/event.h>
#include "sst/elements/hermes/msgapi.h"
#include "entry.h"
#include "api.h"

namespace SST {
namespace Firefly {

class InitEnterEvent : public SMEnterEvent {
  public:
    InitEnterEvent( int type, SST::Link* retLink, Hermes::Functor* retFunc ) :
        SMEnterEvent( type, retLink, retFunc )
    { }
};

class FiniEnterEvent : public SMEnterEvent {
  public:
    FiniEnterEvent( int type, SST::Link* retLink, Hermes::Functor* retFunc ) :
        SMEnterEvent( type, retLink, retFunc )
    { }
};

class RankEnterEvent : public SMEnterEvent {
  public:
    RankEnterEvent( int type, SST::Link* retLink, Hermes::Functor* retFunc,
        Hermes::Communicator _group, int* _rank ) :
        SMEnterEvent( type, retLink, retFunc ),
        group( _group ),
        rank( _rank )
    { }

    Hermes::Communicator group;
    int* rank;
};

class SizeEnterEvent : public SMEnterEvent {
  public:
    SizeEnterEvent( int type, SST::Link* retLink, Hermes::Functor* retFunc,
        Hermes::Communicator _group, int* _size ) :
        SMEnterEvent( type, retLink, retFunc ),
        group( _group ),
        size( _size )
    { }

    Hermes::Communicator group;
    int* size;
};

class BarrierEnterEvent : public SMEnterEvent {
  public:
    BarrierEnterEvent( int type, SST::Link* retLink, Hermes::Functor* retFunc,
        Hermes::Communicator _group ) :
        SMEnterEvent( type, retLink, retFunc ),
        group( _group )
    { }

    Hermes::Communicator group;
};

class RecvEnterEvent : public SMEnterEvent {

  public:
    RecvEnterEvent( int type, SST::Link* retLink, Hermes::Functor* retFunc,
            Hermes::Addr buf, uint32_t count,
            Hermes::PayloadDataType dtype, Hermes::RankID src,
            uint32_t tag, Hermes::Communicator group, 
            Hermes::MessageRequest* req, Hermes::MessageResponse* resp ) :
        SMEnterEvent( type, retLink, retFunc ),
        entry( buf, count, dtype, src, tag, group, resp, req )  
    {}

    RecvEntry   entry;
};


class SendEnterEvent : public SMEnterEvent {

  public:
    SendEnterEvent( int type, SST::Link* retLink, Hermes::Functor* retFunc,
                Hermes::Addr buf, uint32_t count,
                Hermes::PayloadDataType dtype, Hermes::RankID dest,
                uint32_t tag, Hermes::Communicator group, 
                Hermes::MessageRequest* req ) :
        SMEnterEvent( type, retLink, retFunc ),
        entry( buf, count, dtype, dest, tag, group, req )  
    {}

    SendEntry   entry;
};

class CollectiveEnterEvent : public SMEnterEvent {

  public:
    CollectiveEnterEvent(int type, SST::Link* retLink, Hermes::Functor* retFunc,
                Hermes::Addr _mydata, Hermes::Addr _result, uint32_t _count,
                Hermes::PayloadDataType _dtype, Hermes::ReductionOperation _op,
                Hermes::RankID _root, Hermes::Communicator _group,
                bool _all ) :
        SMEnterEvent( type, retLink, retFunc ),
        mydata(_mydata),
        result(_result),
        count(_count),
        dtype(_dtype),
        op(_op),
        root(_root),
        group(_group),
        all( _all ) 
    {}
    
    Hermes::Addr mydata;
    Hermes::Addr result;
    uint32_t count;
    Hermes::PayloadDataType dtype;
    Hermes::ReductionOperation op;
    Hermes::RankID  root;
    Hermes::Communicator group;
    bool  all;
};

class WaitEnterEvent : public SMEnterEvent {
  public:
    WaitEnterEvent( int type, SST::Link* retLink, Hermes::Functor* retFunc,
        Hermes::MessageRequest* _req, Hermes::MessageResponse* _resp ) :
        SMEnterEvent( type, retLink, retFunc ),
        req(_req),
        resp(_resp)
    { }

    Hermes::MessageRequest* req;
    Hermes::MessageResponse* resp;
};

}
}
#endif
