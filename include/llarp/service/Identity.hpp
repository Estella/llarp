#ifndef LLARP_SERVICE_IDENTITY_HPP
#define LLARP_SERVICE_IDENTITY_HPP
#include <llarp/bencode.hpp>
#include <llarp/crypto.hpp>
#include <llarp/service/Info.hpp>
#include <llarp/service/IntroSet.hpp>
#include <llarp/service/types.hpp>

namespace llarp
{
  namespace service
  {
    // private keys
    struct Identity : public llarp::IBEncodeMessage
    {
      llarp::SecretKey enckey;
      llarp::SecretKey signkey;
      llarp::PQKeyPair pq;
      uint64_t version = 0;
      VanityNonce vanity;

      // public service info
      ServiceInfo pub;

      ~Identity();

      // regenerate secret keys
      void
      RegenerateKeys(llarp_crypto* c);

      // load from file
      bool
      LoadFromFile(const std::string& fpath);

      bool
      BEncode(llarp_buffer_t* buf) const;

      bool
      EnsureKeys(const std::string& fpath, llarp_crypto* c);

      bool
      KeyExchange(llarp_path_dh_func dh, byte_t* sharedkey,
                  const ServiceInfo& other, const byte_t* N) const;

      bool
      DecodeKey(llarp_buffer_t key, llarp_buffer_t* buf);

      bool
      SignIntroSet(IntroSet& i, llarp_crypto* c) const;

      bool
      Sign(llarp_crypto*, byte_t* sig, llarp_buffer_t buf) const;
    };
  }  // namespace service
}  // namespace llarp

#endif