/*
    Copyright (C) 2004, 2005 Nikolas Zimmermann <wildfox@kde.org>
                  2004, 2005, 2006 Rob Buis <buis@kde.org>

    This file is part of the KDE project

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

#include "config.h"
#ifdef SVG_SUPPORT
#include "SVGURIReference.h"

#include "SVGNames.h"
#include "SVGStyledElement.h"
#include "XLinkNames.h"

namespace WebCore {

SVGURIReference::SVGURIReference()
{
}

SVGURIReference::~SVGURIReference()
{
}

ANIMATED_PROPERTY_DEFINITIONS_WITH_CONTEXT(SVGURIReference, String, String, string, Href, href, XLinkNames::hrefAttr.localName(), m_href)

bool SVGURIReference::parseMappedAttribute(MappedAttribute* attr)
{
    if (attr->name().matches(XLinkNames::hrefAttr)) {
        setHrefBaseValue(attr->value());
        return true;
    }

    return false;
}

String SVGURIReference::getTarget(const String& url)
{
    DeprecatedString urlDeprecated = url.deprecatedString(); // FIXME: Needed until findRev exists for String
    if (url.startsWith("url(")) { // URI References, ie. fill:url(#target)
        unsigned int start = url.find('#') + 1;
        unsigned int end = url.reverseFind(')');

        return url.substring(start, end - start);
    } else if (url.find('#') > -1) { // format is #target
        unsigned int start = url.find('#') + 1;
        return url.substring(start, url.length() - start);
    } else // Normal Reference, ie. style="color-profile:changeColor"
        return url;
}

}

// vim:ts=4:noet
#endif // SVG_SUPPORT

