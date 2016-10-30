/**
 * @file libobjgen/src/MetaVariableList.cpp
 * @ingroup libobjgen
 *
 * @author COMP Omega <compomega@tutanota.com>
 *
 * @brief Meta data for a member variable that is a list of variables.
 *
 * This file is part of the COMP_hack Object Generator Library (libobjgen).
 *
 * Copyright (C) 2012-2016 COMP_hack Team <compomega@tutanota.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MetaVariableList.h"

// libobjgen Includes
#include "Generator.h"
#include "MetaObject.h"

// Standard C++11 Libraries
#include <sstream>

using namespace libobjgen;

MetaVariableList::MetaVariableList(
    const std::shared_ptr<MetaVariable>& elementType) : MetaVariable(),
    mElementType(elementType)
{
}

MetaVariableList::~MetaVariableList()
{
}

size_t MetaVariableList::GetSize() const
{
    return 0;
}

std::shared_ptr<MetaVariable> MetaVariableList::GetElementType() const
{
    return mElementType;
}

MetaVariable::MetaVariableType_t MetaVariableList::GetMetaType() const
{
    return MetaVariable::MetaVariableType_t::TYPE_LIST;
}

std::string MetaVariableList::GetType() const
{
    return "list";
}

bool MetaVariableList::IsCoreType() const
{
    return false;
}

bool MetaVariableList::IsValid() const
{
    return MetaObject::IsValidIdentifier(GetName()) &&
        mElementType && mElementType->IsValid();
}

bool MetaVariableList::IsValid(const void *pData, size_t dataSize) const
{
    (void)pData;
    (void)dataSize;

    /// @todo Fix
    return true;
}

bool MetaVariableList::Load(std::istream& stream)
{
    (void)stream;

    /// @todo Fix
    return true;
}

bool MetaVariableList::Save(std::ostream& stream) const
{
    (void)stream;

    /// @todo Fix
    return true;
}

bool MetaVariableList::Load(const tinyxml2::XMLDocument& doc,
    const tinyxml2::XMLElement& root)
{
    (void)doc;

    return BaseLoad(root) && IsValid();
}

bool MetaVariableList::Save(tinyxml2::XMLDocument& doc,
    tinyxml2::XMLElement& root) const
{
    (void)doc;
    (void)root;

    /// @todo Fix
    return true;
}

uint16_t MetaVariableList::GetDynamicSizeCount() const
{
    return 1;
}

std::string MetaVariableList::GetCodeType() const
{
    if(mElementType)
    {
        std::stringstream ss;
        ss << "std::list<" << mElementType->GetCodeType() << ">";

        return ss.str();
    }
    else
    {
        return std::string();
    }
}

std::string MetaVariableList::GetConstructValue() const
{
    return std::string();
}

std::string MetaVariableList::GetValidCondition(const Generator& generator,
    const std::string& name, bool recursive) const
{
    (void)generator;

    std::string code;

    if(mElementType)
    {
        code = mElementType->GetValidCondition(generator, "value", recursive);

        if(!code.empty())
        {
            std::map<std::string, std::string> replacements;
            replacements["@VAR_NAME@"] = name;
            replacements["@VAR_VALID_CODE@"] = code;

            code = generator.ParseTemplate(0, "VariableArrayValidCondition",
                replacements);
        }
    }

    return code;
}

std::string MetaVariableList::GetLoadCode(const Generator& generator,
    const std::string& name, const std::string& stream) const
{
    (void)generator;

    std::string code;

    if(mElementType && MetaObject::IsValidIdentifier(name) &&
        MetaObject::IsValidIdentifier(stream))
    {
        code = mElementType->GetLoadCode(generator, "element", stream);

        if(!code.empty())
        {
            std::map<std::string, std::string> replacements;
            replacements["@VAR_NAME@"] = name;
            replacements["@VAR_TYPE@"] = mElementType->GetCodeType();
            replacements["@VAR_LOAD_CODE@"] = code;
            replacements["@STREAM@"] = stream;

            code = generator.ParseTemplate(0, "VariableListLoad",
                replacements);
        }
    }

    return code;
}

std::string MetaVariableList::GetSaveCode(const Generator& generator,
    const std::string& name, const std::string& stream) const
{
    (void)generator;

    std::string code;

    if(mElementType && MetaObject::IsValidIdentifier(name) &&
        MetaObject::IsValidIdentifier(stream))
    {
        code = mElementType->GetSaveCode(generator, "element", stream);

        if(!code.empty())
        {
            std::map<std::string, std::string> replacements;
            replacements["@VAR_NAME@"] = name;
            replacements["@VAR_SAVE_CODE@"] = code;
            replacements["@STREAM@"] = stream;

            code = generator.ParseTemplate(0, "VariableListSave",
                replacements);
        }
    }

    return code;
}

std::string MetaVariableList::GetXmlLoadCode(const Generator& generator,
    const std::string& name, const std::string& doc,
    const std::string& root, const std::string& members,
    size_t tabLevel) const
{
    (void)generator;
    (void)name;
    (void)doc;
    (void)root;
    (void)members;
    (void)tabLevel;

    /// @todo Fix
    return std::string();
}

std::string MetaVariableList::GetXmlSaveCode(const Generator& generator,
    const std::string& name, const std::string& doc,
    const std::string& root, size_t tabLevel) const
{
    std::string code;

    if(mElementType)
    {
        std::map<std::string, std::string> replacements;
        replacements["@VAR_NAME@"] = name;
        replacements["@VAR_XML_SAVE_CODE@"] = mElementType->GetXmlSaveCode(
            generator, "element", doc, root, tabLevel + 1);

        code = generator.ParseTemplate(0, "VariableListXmlSave",
            replacements);
    }

    return code;
}

std::string MetaVariableList::GetAccessDeclarations(const Generator& generator,
    const MetaObject& object, const std::string& name, size_t tabLevel) const
{
    std::stringstream ss;
    ss << MetaVariable::GetAccessDeclarations(generator,
        object, name, tabLevel);

    if(mElementType)
    {
        /// @todo Fix (add append, prepend, insert, remove, clear, iterator)
    }

    return ss.str();
}

std::string MetaVariableList::GetAccessFunctions(const Generator& generator,
    const MetaObject& object, const std::string& name) const
{
    std::stringstream ss;
    ss << MetaVariable::GetAccessFunctions(generator, object, name);

    if(mElementType)
    {
        /// @todo Fix (add append, prepend, insert, remove, clear, iterator)
    }

    return ss.str();
}
