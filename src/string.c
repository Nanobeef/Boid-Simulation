#include <string.h>
#include "basic.h"
#include "alg.h"


b32 char_is_printable(char c)
{
	return (c >= ' ') && (c < 128);
}

u32 cstring_length(const char* cstring)
{
	return strlen(cstring);
}

b32 cstrings_are_equal(const char* a, const char* b)
{
	while((*a == *b) && (*a) && (*b)) {a++; b++;}
	return (b32)((*a) == (*b));
}

u64 hash_cstring(const char* c)
{
    u64 hash = 5381;
	while(c[0])
	{
        hash = ((hash << 5) + hash) + c[0];  
		hash = hash * 33 + c[0];
		c++;
	}
    return hash;
}


StringMap alloc_string_map(u64 capacity, Arena* arena)
{
	capacity = uint_next_power_of_two(capacity);
	StringMap map = {
		.map = allocate_array(const char*, capacity, arena),
		.pointers = allocate_array(const void*, capacity, arena),
		.mask = capacity - 1,
	};
	memzero(map.map, array_capacity_size(map.map));
	return map;
}

u64 string_map_insert(StringMap map, const char* cstring, const void* pointer)
{
	u64 index = hash_cstring(cstring) & map.mask;
	for(u64 i = index; i < array_capacity(map.map); i++)
	{
		if(map.map[i] == NULL)
		{
			map.map[i] = cstring;
			map.pointers[i] = pointer;
			return i;
		}
	}
	for(u64 i = 0; i < index; i++)
	{
		if(map.map[i] == NULL)
		{
			map.map[i] = cstring;
			map.pointers[i] = pointer;
			return i;
		}
	}
	return array_capacity(map.map);
}

u64 string_map_lookup(StringMap map, const char* cstring, const void** dst)
{
	u64 index = hash_cstring(cstring) & map.mask;
	for(u64 i = index; i < array_capacity(map.map); i++)
	{
		if(map.map[i] == 0){return false;}
		if(cstrings_are_equal(map.map[i], cstring))
		{
			dst[0] = map.pointers[i];
			return i;
		}
	}
	for(u64 i = 0; i < index; i++)
	{
		if(map.map[i] == 0){return false;}
		if(cstrings_are_equal(map.map[i], cstring))
		{
			dst[0] = map.pointers[i];
			return i;
		}
	}
	return array_capacity(map.map);
}

const void* string_map_lookup_raw(StringMap map, const char* cstring)
{
	const void* data = 0;
	if(string_map_lookup(map, cstring, &data) == 0)
	{
		return 0;	
	}
	return data;
}
