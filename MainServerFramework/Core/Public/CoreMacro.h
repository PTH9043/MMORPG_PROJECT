#pragma once



#define SPACE_BEGIN(name) namespace name {

#define SPACE_END }


#define DECLARE_GET_TYPENAME(CLASS_NAME) \
    virtual String GetTypeName() const override { return #CLASS_NAME; }


#define DEBUG_MACRO_TO_METHOD __FILE__, __LINE__, __FUNCTION__

#define MAKESYSTEMERRORMSG(ex) CoreFunc::ConvertSystemError(ex, DEBUG_MACRO_TO_METHOD);

#define OUTSYSTEMERRORMSG(ex) CoreFunc::OutSystemErrorMsg(ex, DEBUG_MACRO_TO_METHOD);