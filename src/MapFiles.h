#pragma once
#include <SDL.h>
#include <iostream>
using namespace std;

class MapFiles
{
public:
	string mapfile;
	MapFiles* nextlevel;


	MapFiles(string map, MapFiles* next) {
		mapfile = map;
		nextlevel = next;
	}

};

class Map_LinkedList
{
	MapFiles* head;

public:
	Map_LinkedList()
	{
		this->head = NULL;
	}

	MapFiles* getHead()
	{
		return head;
	}
	Map_LinkedList* insertAtTail(string data) {
		MapFiles* tmp;
		tmp = new MapFiles(data, NULL);
		if (head == NULL) {
			head = tmp;
		}
		else {
			MapFiles* p = head;
			while (p->nextlevel != NULL) {
				p = p->nextlevel;

			}
			p->nextlevel = tmp;
		}
		return this;
	}
	void nextNode()
	{
		if(head->nextlevel!=NULL)
		head = head->nextlevel;
	}
};
