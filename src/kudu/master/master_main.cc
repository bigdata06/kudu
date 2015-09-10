// Copyright (c) 2013, Cloudera, inc.
// Confidential Cloudera Information: Covered by NDA.

#include <glog/logging.h>
#include <iostream>

#include "kudu/gutil/strings/substitute.h"
#include "kudu/master/master.h"
#include "kudu/util/flags.h"
#include "kudu/util/logging.h"

using kudu::master::Master;

DECLARE_string(rpc_bind_addresses);
DECLARE_int32(webserver_port);

namespace kudu {
namespace master {

static int MasterMain(int argc, char** argv) {
  // Reset some default values before parsing gflags.
  FLAGS_rpc_bind_addresses = strings::Substitute("0.0.0.0:$0",
                                                 Master::kDefaultPort);
  FLAGS_webserver_port = Master::kDefaultWebPort;

  ParseCommandLineFlags(&argc, &argv, true);
  if (argc != 1) {
    std::cerr << "usage: " << argv[0] << std::endl;
    return 1;
  }
  InitGoogleLoggingSafe(argv[0]);

  MasterOptions opts;
  Master server(opts);
  LOG(INFO) << "Initializing master server...";
  CHECK_OK(server.Init());

  LOG(INFO) << "Starting Master server...";
  CHECK_OK(server.Start());

  LOG(INFO) << "Master server successfully started.";
  while (true) {
    SleepFor(MonoDelta::FromSeconds(60));
  }

  return 0;
}

} // namespace master
} // namespace kudu

int main(int argc, char** argv) {
  return kudu::master::MasterMain(argc, argv);
}