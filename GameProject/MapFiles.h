#pragma once
#include <iostream>
using namespace std;

struct MapFiles
{
	string mapfile;
	struct Node* nextlevel;
	struct Node* prevlevel;
};

