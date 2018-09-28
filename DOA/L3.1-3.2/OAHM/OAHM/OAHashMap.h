#pragma once
class OAHashMapException
{
};


template<typename KeyType, typename ValueType>
class OAHashMap
{
public:
	OAHashMap(const size_t s, int(*h)(KeyType)) 
	: hash(h), MAP_SIZE(s), nEntriesUsed(0)
	{
		map = new MapEntry[MAP_SIZE];
	}

	// ==========================================================================================
	// NAME:	search(key)
	// POST:	If entry with Key = key is found in the map, value is set to the corresponding value and
	//			true is returned. Otherwise, false is returned.
	// ==========================================================================================
	bool search(const KeyType& key, ValueType& value)
	{
		int index = findIndex(key);

		if (index == KEY_NOT_FOUND) return false;
		
		value = map[index].value;
		return true;
	}

	// ==========================================================================================
	// NAME:	insert
	// POST:	If the map is not-full, (key, value) is in map. Otherwise, an exception is thrown
	// ==========================================================================================
	void insert(const KeyType& key, const ValueType& val)
	{
		int hashIndex;
		int index;

		if (nEntriesUsed == MAP_SIZE) throw OAHashMapException();	// Map is full - no room for key
		
		index = hashIndex = hash(key);

		int nProbes = 0;
		while (map[index].state == MapEntry::AddressState::OCCUPIED)
		{
			if (map[index].key == key)
			{
				map[index].value = val;
				return;
			}
			index = (hashIndex + probe(++nProbes)) % MAP_SIZE;	// probing
		}
		// Open address found - insert key
		map[index].key = key;
		map[index].value = val;
		map[index].state = MapEntry::AddressState::OCCUPIED;

		++nEntriesUsed;
	}


	// ==========================================================================================
	// NAME:	remove()
	// POST:	Entry with key = key is not in map
	// ==========================================================================================
	void remove(const KeyType& key)
	{
		int index;

		if ((index = findIndex(key)) == KEY_NOT_FOUND) return;

		map[index].state = MapEntry::AddressState::PREV_USED;
		--nEntriesUsed;

	}

	// ==========================================================================================
	// NAME:	getLoadFactor()
	// POST:	The load factor is returned
	// ==========================================================================================
	double getLoadFactor() const
	{
		return static_cast<double>(nEntriesUsed) / MAP_SIZE;
	}

private:
	const int KEY_NOT_FOUND = -1;

	// Function pointer to the hash function
	int (*hash)(KeyType);

	// Internal class to hold map entries
	class MapEntry
	{
	public:
		enum AddressState
		{
			OCCUPIED,
			PREV_USED,
			NEVER_USED
		};

		MapEntry(const KeyType& k = KeyType(), const ValueType& v = ValueType()) 
		: key(k), value(v), state(NEVER_USED) {}
		
		KeyType key;
		ValueType value;
		AddressState state;
	};


	// ==========================================================================================
	// NAME:	findIndex()
	// POST:	index of the key is returned, or -1 if key is not found
	// ==========================================================================================
	int findIndex(const KeyType& key)
	{
		// YOUR CODE GOES HERE!!!
		int hashIndex;
		int index;

		index = hashIndex = hash(key);

		int nProbes = 0;
		while (map[index].state != MapEntry::AddressState::NEVER_USED && nProbes != MAP_SIZE)
		{
			if (map[index].key == key && map[index].state == MapEntry::AddressState::OCCUPIED)
			{
				return index;
			}
			else
				index = (hashIndex + probe(++nProbes)) % MAP_SIZE;	// probing
		}
		return KEY_NOT_FOUND;
	}

	// =========================================================================================
	// NAME: probe
	// PRE: i>0
	// POST: The probing offset for probe #i is returned
	// =========================================================================================
	int probe(int i)
	{
		return i;	// Linear probing
		// return pow(-1,i-1)*pow((i+1)/2, 2);	// Quadratic probing
	}


	MapEntry* map;
	const size_t MAP_SIZE;
	size_t nEntriesUsed;
};