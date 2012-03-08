#ifndef XMLUTILS_H
#define XMLUTILS_H

#include <list>

#include <CString.h>

/**
 * An XML Namespace
 * Composed of a namespace URL and/or namespace prefix
 * Ex: <prefix:tag/>
 */
class XmlNamespace
{
public:
  XmlNamespace();
  XmlNamespace(const char *namespacE);
  XmlNamespace(const CString &namespacE);
  XmlNamespace(const char *prefix, const char *namespacE);
  XmlNamespace(const CString &prefix, const CString &namespacE);
  XmlNamespace(const XmlNamespace &copy);

  inline CString getPrefix()     const {return prefix_;};
  inline CString getNamespace()  const {return namespace_;};

  inline void setPrefix(const char *prefix)        {prefix_ = prefix;}
  inline void setNamespace(const char *namespacE)  {namespace_= namespacE;}

  // bool operator==(const XmlNamespace &ns);
  bool equals(const XmlNamespace &ns) const;

private:
  CString prefix_;
  CString namespace_;
};

/**
 * An XML Name
 * composed of localname and an optional namespace
 */
class XmlName
{
public:
  XmlName();
  XmlName(const char *local);
  XmlName(const char *local, const char *nsName);
  XmlName(const CString &local, const CString &nsName);
  XmlName(const char *local, const char *nsPrefix, const char *nsName);
  XmlName(const XmlNamespace &ns, const char *local);
  XmlName(const XmlNamespace &ns, const CString &local);
  XmlName(const XmlName &copy);

  inline CString getLocalName()       const {return localName_;};
  inline XmlNamespace getNamespace()  const {return namespace_;};

  inline void setLocalName(const char *localName) {localName_ = localName;};
  inline void setNamespace(const char *namespacE) {namespace_ = namespacE;};

#ifndef NO_OPERATORS
  inline bool operator==(const XmlName &name) const {return equals(name);};
#endif
  bool equals(const XmlName &name) const;

private:
  CString localName_;
  XmlNamespace namespace_;
};

/**
 * An interface for an XML Sax Parsing state
 * There should be one XmlSaxParserElementHandler instance for each possible XML
 * tag. The instance should have all possible transitions for start end end tags.
 * EX: if a particular element is <value> which can only be in <valueChoice/>
 *     and <valueList/>, then the startTransitions should contain both
 *     valueList and valueChoice, thus obviating huge if/else blocks in
 *     the processing code.
 */
class XmlSaxParserElementHandler
{
public:
  XmlSaxParserElementHandler(const XmlName &element) : element_(element) {};

  virtual void start(const XmlName &element, const char **attrs) = 0;
  virtual void end(const XmlName &element) = 0;

  inline void setName(const XmlName &element) {element_ = element;};
  inline XmlName getName() const {return element_;};

  void addStartTransition(const XmlName &element);
  bool hasStartTransition(const XmlName &fromElement) const;

  void addEndTransition(const XmlName &element);
  bool hasEndTransition(const XmlName &fromElement) const;

private:
  XmlName element_;
  std::list<XmlName> startTransitions_;
  std::list<XmlName> endTransitions_;
};

#endif // XMLUTILS_H
