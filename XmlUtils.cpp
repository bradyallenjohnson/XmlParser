
#include <algorithm>
#include <list>

#include <CString.h>

#include "XmlUtils.h"

//-------------------------------------
//
//    XmlNamespace implementation
//
//-------------------------------------

XmlNamespace::XmlNamespace()
{
}

XmlNamespace::XmlNamespace(const char *namespacE) : namespace_(namespacE)
{
}

XmlNamespace::XmlNamespace(const CString &namespacE) : namespace_(namespacE)
{
}

XmlNamespace::XmlNamespace(const char *prefix, const char *namespacE) :
  prefix_(prefix),
  namespace_(namespacE)
{
}

XmlNamespace::XmlNamespace(const CString &prefix, const CString &namespacE) :
  prefix_(prefix),
  namespace_(namespacE)
{
}

XmlNamespace::XmlNamespace(const XmlNamespace &copy) :
  prefix_(copy.prefix_),
  namespace_(copy.namespace_)
{
}

bool XmlNamespace::equals(const XmlNamespace &ns) const
{
  // TODO, is it important to check the prefix?

  return namespace_.equals(ns.namespace_);
}

//-------------------------------------
//
//    XmlName implementation
//
//-------------------------------------

XmlName::XmlName()
{
}

XmlName::XmlName(const char *local) :
  localName_(local)
{
}

XmlName::XmlName(const char *local, const char *nsName) :
  localName_(local),
  namespace_(nsName)
{
}

XmlName::XmlName(const CString &local, const CString &nsName) :
  localName_(local),
  namespace_(nsName)
{
}

XmlName::XmlName(const char *local, const char *nsPrefix, const char *nsName) :
  localName_(local),
  namespace_(nsPrefix, nsName)
{
}

XmlName::XmlName(const XmlNamespace &ns, const char *local) :
  localName_(local),
  namespace_(ns)
{
}

XmlName::XmlName(const XmlNamespace &ns, const CString &local) :
  localName_(local),
  namespace_(ns)
{
}

XmlName::XmlName(const XmlName &copy) :
  localName_(copy.localName_),
  namespace_(copy.namespace_)
{
}

bool XmlName::equals(const XmlName &name) const
{
  if(!name.namespace_.equals(namespace_))
  {
    return false;
  }

  return localName_.equals(name.localName_);
}


//----------------------------------------------------
//
//    XmlSaxParseElementHandler implementation
//
//----------------------------------------------------

void XmlSaxParserElementHandler::addStartTransition(const XmlName &element)
{
  startTransitions_.push_back(element);
}

bool XmlSaxParserElementHandler::hasStartTransition(const XmlName &fromElement) const
{
  if(find(startTransitions_.begin(), startTransitions_.end(), fromElement) == startTransitions_.end())
  {
    return false;
  }

  return true;
}

void XmlSaxParserElementHandler::addEndTransition(const XmlName &element)
{
    endTransitions_.push_back(element);
}

bool XmlSaxParserElementHandler::hasEndTransition(const XmlName &fromElement) const
{
  if(find(endTransitions_.begin(), endTransitions_.end(), fromElement) == endTransitions_.end())
  {
    return false;
  }

  return true;
}
