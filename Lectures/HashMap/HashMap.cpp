#include "HashMap.h"
template<class Keys, class Values>
HashMap<Keys, Values>::HashMap(size_t _size, std::function<size_t(const Keys& key)> _h) :size(_size), h(_h)
{
	table = new HashMap<Keys, Values>::Entry * [size];
	for (size_t i = 0; i < size; i++)
	{
		table[i] = nullptr;
	}
}

template<class Keys, class Values>
Values HashMap<Keys, Values>::operator [](const Keys& key) const
{
	size_t index = h(key) % size;
	HashMap<Keys, Values>::Entry* kvpair = locate(index, key);
	assert(kvpair != nullptr);

	return kvpair->value;
}

template<class Keys, class Values>
Values& HashMap<Keys, Values>::operator [](const Keys& key)
{
	size_t index = h(key) % size;
	typename HashMap<Keys, Values>::Entry* kvpair = locate(index, key);
	if (kvpair != nullptr)
	{
		return kvpair->value;
	}
	else {
		table[index] = new HashMap<Keys, Values>::Entry{ key,Value(),table[index] };
		return table[index]->value;
	}
}

template<class Keys, class Values>
bool HashMap<Keys, Values>::hasKey(const Keys& key) const
{
	size_t index = h(index) % size;
	HashMap<Keys, Values>::Entry* kvpair = locate(index, key);

	return kvpair != nullptr;
}

template<class Keys, class Values>
typename HashMap<Keys, Values>::Entry* HashMap<Keys, Values>::locate(size_t index, const Keys& key) const
{
	typename HashMap<Keys, Values>::Entry* current = table[index];
	while (current != nullptr && current->key != key)
	{
		current = current->next;
	}
	return current;
}