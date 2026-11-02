// -*- c++ -*-

// Several modules share the static feature arrays; destroying one module must
// leave them intact for the others

#include <iostream>

#include "colvar.h"
#include "colvarmodule.h"
#include "colvarproxy.h"
#include "colvarproxy_stub.h"

static std::string const config =
  "colvar {\n"
  "  name d\n"
  "  distance {\n"
  "    group1 { atomNumbers 1 }\n"
  "    group2 { atomNumbers 2 }\n"
  "  }\n"
  "}\n";

int main(int argc, char *argv[]) {

  colvarproxy_stub *first = new colvarproxy_stub();
  colvarproxy_stub *second = new colvarproxy_stub();

  if ((first->cvmodule->read_config_string(config) != COLVARS_OK) ||
      (second->cvmodule->read_config_string(config) != COLVARS_OK)) {
    std::cerr << "Error: could not read the configuration." << std::endl;
    return 1;
  }

  delete first;

  colvar *cv = second->cvmodule->colvar_by_name("d");
  if (cv->features().empty()) {
    std::cerr << "Error: the feature arrays were deleted with the first module."
              << std::endl;
    return 1;
  }

  delete second;

  return 0;
}
