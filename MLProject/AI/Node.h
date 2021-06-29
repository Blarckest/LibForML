#pragma once
#include <vector>
#include "Matrix.h"
class Node
{
public:
    __declspec(dllexport) Node(int value, std::vector<Node*>* parents = nullptr);
    __declspec(dllexport) ~Node();
    __declspec(dllexport) int getValue();
    __declspec(dllexport) void setValue(int value);
    __declspec(dllexport) std::vector<Node*>* getParents();
    __declspec(dllexport) void setParents(std::vector<Node*>* parents);
private:
	int _value = 1;
    int _bias = 10;
	std::vector<Node*>* _parents;
};
namespace std
{
    template <>
    struct hash<Node>
    {
        size_t operator()(const Node& key)const
        {
            return hash<int>()((int)&key)*7;
        }
    };
}