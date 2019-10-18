#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "stack.h"
#include "header.h"

// recursive descent parser
#include "rdp.h"
// table driven parser
#include "tdp.h"



int main() {

  input = "a|(c.d)*";

  // parse_RDP();

  parse_TDP();


}
