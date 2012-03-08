#ifndef XMLPARSEREXPATIMPL_H
#define XMLPARSEREXPATIMPL_H

#include <expat.h>
#include <XmlParser.h>
#include <CString.h>

/**
 * An implementation of the XmlParser that wraps the expat parser
 */
class XmlParserExpatImpl : public XmlParser
{
public:
  XmlParserExpatImpl();
  virtual ~XmlParserExpatImpl();

  virtual void parse(const CString &xmlStr);
  virtual void parseFile(const CString &xmlFile);
  virtual int getLineNumber();
  virtual int getColumnNumber();

  const static CString namespaceSeperatorChar_;
  const static CString encoding_;

private:
  /**
   * Expat handlers
   */
  static void expatStartHandler(void *userData, const XML_Char *name, const XML_Char **atts);
  static void expatEndHandler(void *userData, const XML_Char *name);
  static void expatCharacterHandler(void *userData, const XML_Char *name, int len);

  XML_Parser parser_;
};

#endif // XMLPARSEREXPATIMPL_H
