#include "GeographicalObject.h"


GeographicalObject::GeographicalObject()
{

}

GeographicalObject::GeographicalObject(string name, long additionalInformation) : name(name), additionalInformation(additionalInformation)
{

}

GeographicalObject::GeographicalObject(string name, long additionalInformation, vector<shared_ptr<GeographicalObject> > &ownedObjects) : name(name), additionalInformation(additionalInformation)
{
	setOwnedObjects(ownedObjects);
}

GeographicalObject::GeographicalObject(string name, long additionalInformation, float probability) : name(name), additionalInformation(additionalInformation), probability(probability)
{

}

GeographicalObject::GeographicalObject(string name, long additionalInformation, float probability, vector<shared_ptr<GeographicalObject> > &ownedObjects) : name(name), additionalInformation(additionalInformation), probability(probability)
{
	setOwnedObjects(ownedObjects);
}


void GeographicalObject::setName(string name)
{
	this->name = name;
}

void GeographicalObject::setName(string &name)
{
	this->name = name;
}

string GeographicalObject::getName()
{
	return name;
}


void GeographicalObject::setAdditionalInformation(long additionalInformation)
{
	this->additionalInformation = additionalInformation;
}

void GeographicalObject::setAdditionalInformation(long &additionalInformation)
{
	this->additionalInformation = additionalInformation;
}

long GeographicalObject::getAdditionalInformation()
{
	return additionalInformation;
}


void GeographicalObject::setOwnedObjects(vector<shared_ptr<GeographicalObject> > &ownedObjects)
{
	for (int i = 0; i < int(ownedObjects.size()); ++i)
	{
		this->ownedObjects.addVertex(ownedObjects[i]);
	}
}


shared_ptr<GeographicalObject> GeographicalObject::getOwnedObject(long additionalInformation)
{
	return ownedObjects.getVertex(additionalInformation);
}