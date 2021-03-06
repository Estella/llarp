#include <llarp/messages/path_latency.hpp>
#include <llarp/routing/handler.hpp>

namespace llarp
{
  namespace routing
  {
    PathLatencyMessage::PathLatencyMessage()
    {
    }

    bool
    PathLatencyMessage::DecodeKey(llarp_buffer_t key, llarp_buffer_t* val)
    {
      bool read = false;
      if(!BEncodeMaybeReadDictInt("L", L, read, key, val))
        return false;
      if(!BEncodeMaybeReadDictInt("S", S, read, key, val))
        return false;
      if(!BEncodeMaybeReadDictInt("T", T, read, key, val))
        return false;
      return read;
    }

    bool
    PathLatencyMessage::BEncode(llarp_buffer_t* buf) const
    {
      if(!bencode_start_dict(buf))
        return false;
      if(!BEncodeWriteDictMsgType(buf, "A", "L"))
        return false;
      if(L)
      {
        if(!BEncodeWriteDictInt("L", L, buf))
          return false;
      }
      if(T)
      {
        if(!BEncodeWriteDictInt("T", T, buf))
          return false;
      }
      if(!BEncodeWriteDictInt("S", S, buf))
        return false;
      return bencode_end(buf);
    }

    bool
    PathLatencyMessage::HandleMessage(IMessageHandler* h, llarp_router* r) const
    {
      return h && h->HandlePathLatencyMessage(this, r);
    }

  }  // namespace routing
}  // namespace llarp