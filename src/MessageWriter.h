/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2015. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef NT_MESSAGEWRITER_H_
#define NT_MESSAGEWRITER_H_

#include "WireEncoder.h"

namespace ntimpl {

class MessageWriter : private WireEncoder {
 public:
  explicit MessageWriter(unsigned int proto_rev) : WireEncoder(proto_rev) {}
  ~MessageWriter();

  using WireEncoder::set_proto_rev;
  using WireEncoder::Reset;
  using WireEncoder::error;
  using WireEncoder::data;
  using WireEncoder::size;

  void WriteKeepAlive();
  void WriteClientHello(const NT_String& self_id);
  void WriteProtoUnsup();
  void WriteServerHelloDone();
  void WriteServerHello(unsigned int flags, const NT_String& self_id);
  void WriteClientHelloDone();
  void WriteEntryAssign(const NT_String& name, unsigned int id,
                        unsigned int seq_num, const NT_Value& value,
                        unsigned int flags);
  void WriteEntryUpdate(unsigned int id, unsigned int seq_num,
                        const NT_Value& value);
  void WriteFlagsUpdate(unsigned int id, unsigned int flags);
  void WriteEntryDelete(unsigned int id);
  void WriteClearEntries();
  void WriteExecuteRpc(unsigned int id, unsigned int uid,
                       const NT_Value* params_start,
                       const NT_Value* params_end);
  void WriteRpcResponse(unsigned int id, unsigned int uid,
                        const NT_Value* results_start,
                        const NT_Value* results_end);

  MessageWriter(const MessageWriter&) = delete;
  MessageWriter& operator=(const MessageWriter&) = delete;

 private:
  void WriteRpc(unsigned int msg_type, unsigned int id, unsigned int uid,
                const NT_Value* values_start, const NT_Value* values_end);
};

}  // namespace ntimpl

#endif  // NT_MESSAGEWRITER_H_
