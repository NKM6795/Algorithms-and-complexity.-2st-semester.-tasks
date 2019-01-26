#include "GeographicalObject.h"


GeographicalObject::GeographicalObject()
{

}

GeographicalObject::GeographicalObject(string name, string additionalInformation) : name(name), additionalInformation(additionalInformation)
{

}

GeographicalObject::GeographicalObject(string name, string additionalInformation, vector<shared_ptr<GeographicalObject> > &ownedObjects) : name(name), additionalInformation(additionalInformation), ownedObjects(ownedObjects)
{

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


void GeographicalObject::setAdditionalInformation(string additionalInformation)
{
	this->additionalInformation = additionalInformation;
}

void GeographicalObject::setAdditionalInformation(string &additionalInformation)
{
	this->additionalInformation = additionalInformation;
}

string GeographicalObject::getAdditionalInformation()
{
	return additionalInformation;
}


void GeographicalObject::setOwnedObjects(vector<shared_ptr<GeographicalObject> > &ownedObjects)
{
	this->ownedObjects = ownedObjects;
}

vector<shared_ptr<GeographicalObject> > &GeographicalObject::getOwnedObjects()
{	
	return ownedObjects;
}