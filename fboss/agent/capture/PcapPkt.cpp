/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#include "fboss/agent/capture/PcapPkt.h"

#include "fboss/agent/RxPacket.h"
#include "fboss/agent/TxPacket.h"

namespace facebook { namespace fboss {

PcapPkt::PcapPkt() {
}

PcapPkt::PcapPkt(const RxPacket* pkt)
  : PcapPkt(pkt, std::chrono::system_clock::now()) {
}

PcapPkt::PcapPkt(const RxPacket* pkt, TimePoint timestamp)
  : initialized_(true),
    rx_(true),
    port_(pkt->getSrcPort()),
    vlan_(pkt->getSrcVlan()),
    timestamp_(timestamp),
    buf_() {
  pkt->buf()->cloneInto(buf_);
}

PcapPkt::PcapPkt(const TxPacket* pkt)
  : PcapPkt(pkt, std::chrono::system_clock::now()) {
}

PcapPkt::PcapPkt(const TxPacket* pkt, TimePoint timestamp)
  : initialized_(true),
    rx_(false),
    port_(0),
    vlan_(0),
    timestamp_(timestamp),
    buf_() {
  pkt->buf()->cloneInto(buf_);
}

}} // facebook::fboss