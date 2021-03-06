﻿#ifndef _STRX_H_
#define _STRX_H_

// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  trancoding of XMLCh data to local code page for display.
// ---------------------------------------------------------------------------
class StrX
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    StrX(const XMLCh* const toTranscode)
{
        // Call the private transcoding method
        fLocalForm = XMLString::transcode(toTranscode);
}

~StrX()
{
    XMLString::release(&fLocalForm);
}


// -----------------------------------------------------------------------
//  Getter methods
// -----------------------------------------------------------------------
const char* localForm() const
{
    return fLocalForm;
}

private :
// -----------------------------------------------------------------------
//  Private data members
//
//  fLocalForm
//      This is the local code page form of the string.
// -----------------------------------------------------------------------
char*   fLocalForm;
};


inline XERCES_STD_QUALIFIER ostream& operator<<(XERCES_STD_QUALIFIER ostream& target, const StrX& toDump)
{
    target << toDump.localForm();
    return target;
}

#endif