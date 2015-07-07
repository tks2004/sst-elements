
// Copyright 2009-2015 Sandia Corporation. Under the terms
// of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
// Government retains certain rights in this software.
// 
// Copyright (c) 2009-2015, Sandia Corporation
// All rights reserved.
// 
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#ifndef COMPONENTS_FIREFLY_CTRLMSG_H
#define COMPONENTS_FIREFLY_CTRLMSG_H

#include <sst/core/component.h>
#include "protocolAPI.h"
#include "ctrlMsgFunctors.h"
#include "ioVec.h"
#include "sst/elements/hermes/msgapi.h"

using namespace Hermes;

namespace SST {
namespace Firefly {
namespace CtrlMsg {

typedef int  nid_t;

static const uint64_t AllgatherTag  = 0x10000000;
static const uint64_t AlltoallvTag  = 0x20000000;
static const uint64_t CollectiveTag = 0x30000000;
static const uint64_t GathervTag    = 0x40000000;
static const uint64_t LongProtoTag  = 0x50000000;
static const uint64_t TagMask       = 0xf0000000;

class XXX;

class _CommReq;

struct CommReq {
    _CommReq* req;
};

static const nid_t  AnyNid = -1;
static const uint64_t  AnyTag = -1; 
typedef int region_t;

typedef int RegionEvent;

class API : public ProtocolAPI {

  public:
    API( Component* owner, Params& );
    ~API();

    virtual void init( Info* info, VirtNic* );
    virtual void setup();
    virtual Info* info();
    virtual void finish();

    virtual std::string name() { return "CtrlMsgProtocol"; }
    virtual void setRetLink( Link* link );

    void send( void* buf, size_t len, nid_t dest, uint64_t tag, 
                                        FunctorBase_0<bool>* = NULL );
    void send( void* buf, size_t len, MP::RankID dest, MP::Communicator grp,
                            uint64_t tag, FunctorBase_0<bool>* = NULL );
    void isend( void* buf, size_t len, nid_t dest, uint64_t tag, CommReq*, 
                                        FunctorBase_0<bool>* = NULL );
    void sendv( std::vector<IoVec>&, nid_t dest, uint64_t tag,
                                        FunctorBase_0<bool>* = NULL );
    void isendv( std::vector<IoVec>&, nid_t dest, uint64_t tag, CommReq*,
                                        FunctorBase_0<bool>* = NULL );
    void recv( void* buf, size_t len, nid_t src, uint64_t tag,
                                        FunctorBase_0<bool>* = NULL );
    void recvv( std::vector<IoVec>&, nid_t src, uint64_t tag,
                                        FunctorBase_0<bool>* = NULL );
    void irecv( void* buf, size_t len, nid_t src, uint64_t tag, CommReq*,
                                        FunctorBase_0<bool>* = NULL );
    void irecv( void* buf, size_t len, MP::RankID src, MP::Communicator grp,
                    uint64_t tag, CommReq*, FunctorBase_0<bool>* = NULL );
    void irecvv( std::vector<IoVec>&, nid_t src, uint64_t tag, CommReq*,
                                        FunctorBase_0<bool>* = NULL );

    void wait( CommReq*, FunctorBase_1<CommReq*,bool>* = NULL );
    void waitAll( std::vector<CommReq*>&, FunctorBase_1<CommReq*, bool>* = NULL );
    void waitAny( std::vector<CommReq*>&, FunctorBase_1<CommReq*, bool>* = NULL );

	void send(MP::Addr buf, uint32_t count, 
		MP::PayloadDataType dtype, MP::RankID dest, uint32_t tag,
        MP::Communicator group, FunctorBase_0<bool>* func );

	void isend(MP::Addr buf, uint32_t count,
        MP::PayloadDataType dtype, MP::RankID dest, uint32_t tag,
        MP::Communicator group, MP::MessageRequest* req,
		FunctorBase_0<bool>* func );

    void recv(MP::Addr buf, uint32_t count,
        MP::PayloadDataType dtype, MP::RankID src, uint32_t tag,
        MP::Communicator group, MP::MessageResponse* resp,
		FunctorBase_0<bool>* func );

    void irecv(MP::Addr _buf, uint32_t _count,
        MP::PayloadDataType dtype, MP::RankID src, uint32_t tag,
        MP::Communicator group, MP::MessageRequest* req,
        FunctorBase_0<bool>* func );

	void wait( MP::MessageRequest, MP::MessageResponse* resp,
				FunctorBase_0<bool>* func );
   	void waitAny( int count, MP::MessageRequest req[], int *index,
              	MP::MessageResponse* resp, FunctorBase_0<bool>* func );
    void waitAll( int count, MP::MessageRequest req[],
                MP::MessageResponse* resp[], FunctorBase_0<bool>* func );

    size_t shortMsgLength();

  private:
    XXX*    m_xxx;
};

}
}
}

#endif
