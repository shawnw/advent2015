/* MD5
 converted to C++ class by Frank Thilo (thilo@unix-ag.org)
 for bzflag (http://www.bzflag.org)
 
   based on:
 
   md5.h and md5.c
   reference implementation of RFC 1321
 
   Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.
 
License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.
 
License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.
 
RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.
 
These notices must be retained in any copies of any part of this
documentation and/or software.
 
*/
 
#ifndef BZF_MD5_H
#define BZF_MD5_H
 
#include <cstdint>
#include <iostream>
#include <string>
 
 
// a small class for calculating MD5 hashes of strings or byte arrays
// it is not meant to be fast or secure
//
// usage: 1) feed it blocks of uchars with update()
//      2) finalize()
//      3) get hexdigest() string
//      or
//      MD5(std::string).hexdigest()
//
// assumes that char is 8 bit and int is 32 bit
class MD5
{
public:
	using size_type = std::uint32_t;
 
  MD5();
  explicit MD5(const std::string& text);
  explicit MD5(const char *text) noexcept;
  void update(const std::uint8_t *buf, size_type length) noexcept;
  void update(const char *buf, size_type length) noexcept;
  void update(const std::string&) noexcept;
  MD5& finalize() noexcept;
  std::string hexdigest() const;
  const char *hexdigest_cstr() const noexcept;
  friend std::ostream& operator<<(std::ostream&, MD5 md5);
 
private:
  static const int blocksize = 64;
  
  void transform(const std::uint8_t block[blocksize]) noexcept;
  static void decode(std::uint32_t output[], const std::uint8_t input[], size_type len) noexcept;
  static void encode(std::uint8_t output[], const std::uint32_t input[], size_type len) noexcept;
 
  bool finalized;
  std::uint8_t buffer[blocksize]; // bytes that didn't fit in last 64 byte chunk
  std::uint32_t count[2];   // 64bit counter for number of bits (lo, hi)
  std::uint32_t state[4]; // digest so far
  std::uint8_t digest[16]; // the result
};
 
std::string md5(const std::string &str);
const char *md5_cstr(const std::string &str); 

#endif