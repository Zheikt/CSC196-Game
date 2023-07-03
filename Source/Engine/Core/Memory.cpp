#include "Memory.h"
#include <iostream>
#include "Memory.h"

using namespace std;

Enginuity::MemoryTracker Enginuity::g_memoryTracker; //has g_ to denote global variable

void* operator new (size_t size)
{
	void* address = malloc(size);
	
	Enginuity::g_memoryTracker.Add(address, size);

	return address;
}

void operator delete(void* address, size_t size)
{
	Enginuity::g_memoryTracker.Remove(address, size);

	free(address);
}

namespace Enginuity
{
	void MemoryTracker::Add(void* address, size_t size)
	{
		m_bytesAllocated += size;
		m_numAllocations++;
	}

	void MemoryTracker::Remove(void* address, size_t size)
	{
		m_bytesAllocated -= size;
		m_numAllocations--;
	}

	void MemoryTracker::DisplayInfo()
	{
		cout << "current bytes allocated: " << m_bytesAllocated << endl;
		cout << "current number allocations: " << m_numAllocations << endl;
	}
}