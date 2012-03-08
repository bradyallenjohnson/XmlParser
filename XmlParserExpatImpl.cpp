
#include <stdio.h>
#include <expat.h>

#include "XmlParserExpatImpl.h"

const CString XmlParserExpatImpl::namespaceSeperatorChar_ = "@";
const CString XmlParserExpatImpl::encoding_ = "UTF-8";


XmlParserExpatImpl::XmlParserExpatImpl()
{
  parser_ = XML_ParserCreateNS(encoding_.str(), namespaceSeperatorChar_.str()[0]);

  XML_SetUserData(parser_, this);
  XML_SetStartElementHandler(parser_,   XmlParserExpatImpl::expatStartHandler);
  XML_SetEndElementHandler(parser_,     XmlParserExpatImpl::expatEndHandler);
  XML_SetCharacterDataHandler(parser_,  XmlParserExpatImpl::expatCharacterHandler);

  //XML_SetNamespaceDeclHandler();
}

XmlParserExpatImpl::~XmlParserExpatImpl()
{
  XML_ParserFree(parser_);
}


//pure virtual
void XmlParserExpatImpl::parse(const CString &xmlStr)
{
  if(XML_Parse(parser_, xmlStr.str(), xmlStr.size(), true) != 0)
  {
    // TODO error
  }
}

//pure virtual
void XmlParserExpatImpl::parseFile(const CString &xmlFile)
{
  FILE *file = fopen(xmlFile.str(), "r");
  if(file == NULL)
  {
    // TODO error opening file
    return;
  }

  CString fileData(5000); // set the initial capacity to 5000 chars
  char tmpData[1000];

  while(!feof(file) && !ferror(file))
  {
    fgets(tmpData, 1000, file);
    fileData.append(tmpData);
  }

  fclose(file);

  parse(fileData);
}

// virtual
int XmlParserExpatImpl::getLineNumber()
{
  return XML_GetCurrentLineNumber(parser_);
}

// virtual
int XmlParserExpatImpl::getColumnNumber()
{
  return XML_GetCurrentColumnNumber(parser_);
}

void XmlParserExpatImpl::expatStartHandler(void *userData, const XML_Char *name, const XML_Char **atts)
{
  XmlParserExpatImpl *parser = (XmlParserExpatImpl *) userData;

  if(parser->startHandler_ == NULL)
  {
    return;
  }

  // split the name and make an XmlName
  CStringTokenizer tokenizer(name, namespaceSeperatorChar_);
  XmlName xmlName(tokenizer.next(), tokenizer.next());

  parser->startHandler_->start(xmlName, atts);
}

void XmlParserExpatImpl::expatEndHandler(void *userData, const XML_Char *name)
{
  XmlParserExpatImpl *parser = (XmlParserExpatImpl *) userData;

  if(parser->endHandler_ == NULL)
  {
    return;
  }

  // split the name and make an XmlName
  CStringTokenizer tokenizer(name, namespaceSeperatorChar_);
  XmlName xmlName(tokenizer.next(), tokenizer.next());

  parser->endHandler_->end(xmlName);
}

void XmlParserExpatImpl::expatCharacterHandler(void *userData, const XML_Char *name, int len)
{
  XmlParserExpatImpl *parser = (XmlParserExpatImpl *) userData;

  if(parser->characterHandler_ == NULL)
  {
    return;
  }

  CString data(name, len, CString::DEFAULT_CAPACITY);
  parser->characterHandler_->character(data);
}
