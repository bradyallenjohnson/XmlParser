#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <CString.h>

#include "XmlUtils.h"

/**
 * XML Handler Interface used when start element encountered
 */
class XmlParserStartHandler
{
public:
  virtual void start(const XmlName &element, const char **attrs) = 0;
};

/**
 * XML Handler Interface used when end element encountered
 */
class XmlParserEndHandler
{
public:
  virtual void end(const XmlName &element) = 0;
};

/**
 * XML Handler Interface used when characters encountered
 * Ex: <element> characters </element>
 */
class XmlParserCharacterHandler
{
public:
  virtual void character(const CString &data) = 0;
};


/**
 * XmlParser interface
 * Basically a simple SAX parser
 */
class XmlParser
{
public:
  XmlParser();
  virtual ~XmlParser();

  void setStartHandler(XmlParserStartHandler *handler);
  void setEndHandler(XmlParserEndHandler *handler);
  void setCharacterHandler(XmlParserCharacterHandler *handler);

  virtual void parse(const CString &xmlStr) = 0;
  virtual void parseFile(const CString &xmlFile) = 0;
  virtual int getLineNumber() = 0;
  virtual int getColumnNumber() = 0;

protected:
  XmlParserStartHandler      *startHandler_;
  XmlParserEndHandler        *endHandler_;
  XmlParserCharacterHandler  *characterHandler_;
};

class XmlParserException
{
	public:
		XmlParserException(const CString &msg) : msg_(msg) {};
		inline const CString what() const {return msg_; };

	private:
    CString msg_;
};

// This is just a marker exception to help distinguish
class XmlParserInvalidStateException : public XmlParserException
{
	public:
		XmlParserInvalidStateException(const CString &msg) : XmlParserException(msg) {};
};

// This is just a marker exception to help distinguish
class XmlParserUnknownElementException : public XmlParserException
{
	public:
		XmlParserUnknownElementException(const CString &msg) : XmlParserException(msg) {};
};

// This is just a marker exception to help distinguish
class XmlParserMissingAttributeException : public XmlParserException
{
	public:
		XmlParserMissingAttributeException(const CString &msg) : XmlParserException(msg) {};
};

// This is just a marker exception to help distinguish
class XmlParserInvalidAttributeException : public XmlParserException
{
	public:
		XmlParserInvalidAttributeException(const CString &msg) : XmlParserException(msg) {};
};

#endif // XMLPARSER_H
