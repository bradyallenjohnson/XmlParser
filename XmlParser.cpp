
#include "XmlUtils.h"
#include "XmlParser.h"

XmlParser::XmlParser() :
  startHandler_(NULL),
  endHandler_(NULL),
  characterHandler_(NULL)
{
  //ctor
}

XmlParser::~XmlParser()
{
  //dtor
}

void XmlParser::setStartHandler(XmlParserStartHandler *handler)
{
  startHandler_ = handler;
}

void XmlParser::setEndHandler(XmlParserEndHandler *handler)
{
  endHandler_ = handler;
}

void XmlParser::setCharacterHandler(XmlParserCharacterHandler *handler)
{
  characterHandler_ = handler;
}

