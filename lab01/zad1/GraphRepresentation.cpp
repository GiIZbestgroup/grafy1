#include "GraphRepresentation.h"

using namespace std;

GraphRepresentation::GraphRepresentation()
{
	edgesNumber = 0;
	verticlesNumber = 0;
}

GraphRepresentation::~GraphRepresentation()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GraphRepresentation::SetEdgesNumber(int edgesNumber)
{
	this->edgesNumber = edgesNumber;
}

void GraphRepresentation::SetVerticlesNumber(int verticlesNumber)
{
	this->verticlesNumber = verticlesNumber;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int GraphRepresentation::GetEdgesNumber() const
{
	return edgesNumber;
}

int GraphRepresentation::GetVerticlesNumber() const
{
	return verticlesNumber;
}
