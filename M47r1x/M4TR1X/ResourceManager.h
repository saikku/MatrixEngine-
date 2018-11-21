#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#define _CRT_SECURE_NO_DEPRECATE
#include <vector>
#include "Resource.h"
#include "Object.h"
#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include "SOIL.h"

namespace Resource{

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();
		std::map< std::string, int> resVector;



		int loadResource(const char * filename, int width, int height);

		resourceID addResource(const char * name, Resource *resource);
		resourceID getResourceID(const char * name);
		int getID(const char * name);

		void update();			 
		int texture;
	private:


	};

	
}
#endif