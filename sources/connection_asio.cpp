#ifndef __CONNECTION_ASIO_CPP_GUARD
#define __CONNECTION_ASIO_CPP_GUARD

#include "headers/connection_asio.hpp"
#include "containers/dynamic_array.tpp"

#include <X11/Xproto.h>

#include <cstdio>
#include <span>

using namespace X11;

asio_connect::asio_connect()
    : socket(io_serv, asio::local::stream_protocol::endpoint(_SOCKET_FILE)) {

  /*setting asio connection*/

  socket.non_blocking(true);

  /// X protocol ///

  auto connect_client_prefix =
      xConnClientPrefix{.byteOrder = _ORDER,
                        .majorVersion = _PROT_MAJOR_VERSION,
                        .minorVersion = _PROT_MINOR_VERSION,
                        .nbytesAuthProto = 18,
                        .nbytesAuthString = 16};

  char xauth_cookie[1000] = {0};

  auto username = std::string(getlogin());

  auto *xauth_file =
      std::fopen(("/home/" + username + "/.Xauthority").c_str(), "rb");
  auto xauth_len =
      std::fread(xauth_cookie, 1, sizeof(xauth_cookie), xauth_file);

  fclose(xauth_file);

  char *str = xauth_cookie + xauth_len - 16;

  send<xConnClientPrefix *>(&connect_client_prefix, sz_xConnClientPrefix);
  send<char *>((char *)_AUTH_PROTOCOL, 20);
  send<char *>(str, std::strlen(str));

  auto reply = xConnSetupPrefix();

  receive<decltype(reply) *>(&reply, sz_xConnSetupPrefix);

  if (reply.success) {
    xConnSetup body;
    receive<xConnSetup *>(&body, sz_xConnSetup);
    auto vendor_string = std::span<char>(std::vector<char>(body.nbytesVendor).data(), body.nbytesVendor);

    receive<char *>(vendor_string.data(), body.nbytesVendor);
    VendorString = std::string(vendor_string.data());

    for (int x = 0; x < body.numFormats; x++) {
      xPixmapFormat f;
      receive<xPixmapFormat *>(&f, sz_xPixmapFormat);
      VecFormat.emplace_back(f);
    };
    for (int x = 0; x < body.numRoots; x++) {
      xWindowRoot screens;
      receive<xWindowRoot *>(&screens, sz_xWindowRoot);
      for (int y = 0; y < screens.nDepths; y++) {
        xDepth d;
        receive<xDepth *>(&d, sz_xDepth);
        for (int z = 0; z < d.nVisuals; z++) {
          xVisualType vis;
          receive<xVisualType *>(&vis, sz_xVisualType);
          VecVisualType.emplace_back(vis);
        }
        VecDepth.emplace_back(d);
      }
      VecScreen.emplace_back(screens);
    }
  } else {
    throw base_exception(__FILE__, __LINE__,
                         std::string("Failed Connection: \n Reason: "));
  }
};

asio_connect::~asio_connect() { socket.close(); }

#endif
