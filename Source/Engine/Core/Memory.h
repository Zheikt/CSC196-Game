#pragma once

namespace Enginuity
{
	struct MemoryAllocation
	{
		void* address;
		size_t size;
		MemoryAllocation* next;
	};

	class MemoryTracker
	{
	public:
		void Add(void* address, size_t size);
		void Remove(void* address, size_t size);

		void DisplayInfo();

	private:
		size_t m_bytesAllocated = 0; //Has m_ do denote member variable
		size_t m_numAllocations = 0;
	};
	extern MemoryTracker g_memoryTracker; //has g_ to denote global variable
}