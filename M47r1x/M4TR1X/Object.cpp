
#include "Object.h"

#include <stdio.h>
#include <typeinfo>
//#include <es_util.h>
//
//#include <config.h>
#define SHOW_LEAKS


namespace Engine
{
	namespace
	{
		class RefCounter
		{
		public:
			RefCounter()
				: refs(0)
			{
			}


			~RefCounter()
			{
#if defined(SHOW_LEAKS)
				if (refs != 0)
				{
					printf("[%s] %d Memory leaks detected!\n", __FUNCTION__, refs);
#if defined(MEMORY_LEAK_DEBUGGING)
					for (size_t i = 0; i<m_objects.size(); ++i)
					{
						esLogMessage(m_objectNames[i].c_str());
					}
#endif
				}
				else
				{
					printf("No memory leaks detected!\n");
				}
#if defined(ASSERT_ON_LEAKS)
				assert(refs == 0);
#endif
#endif
			}

			void add(Object* o, const char* const name)
			{
#if defined(MEMORY_LEAK_DEBUGGING)
				m_objects.push_back(o);
				m_objectNames.push_back(name);
#else
				(void)name;
				(void)o;
#endif
				++refs;
			}

			void release(Object* o)
			{
#if defined(MEMORY_LEAK_DEBUGGING)
				size_t index = 0;

				for (; index<m_objects.size(); ++index)
				{
					if (m_objects[index] == o)
					{
						break;
					}
				}

				m_objects.erase(m_objects.begin() + index);
				m_objectNames.erase(m_objectNames.begin() + index);
#else
				(void)o;
#endif
				--refs;
			}

		private:
#if defined(MEMORY_LEAK_DEBUGGING)
			std::vector<Object*> m_objects;
			std::vector<std::string> m_objectNames;
#endif
			int refs;
		};

		static RefCounter refs;
	}

	Object::Object(/*const char* const name*/)
		: m_numOfRefs(0)
	{
		refs.add(this, "");
	}

	Object::~Object()
	{
		refs.release(this);
		if (this->m_numOfRefs != 0)
		{

		}
	}



}



