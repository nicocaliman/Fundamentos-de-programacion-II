#pragma once

#include <iostream>
#include <fstream>
#include "matrices.h"

using namespace std;

ostream& operator<<(ostream& out, const tMatriz& m);
ifstream& operator>>(ifstream& archivo, tMatriz& m);
