/*=============================================================================

  CMAKECATCHMPI: A software package to demo MPI with CMake, CTest and Catch.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "ccmpiException.h"

namespace ccmpi
{

//-----------------------------------------------------------------------------
Exception::Exception(const std::string& fileName,
                     int lineNumber)
: std::exception()
, m_Description("")
, m_FileName(fileName)
, m_LineNumber(lineNumber)
{
}


//-----------------------------------------------------------------------------
Exception::~Exception()
{

}


//-----------------------------------------------------------------------------
std::string Exception::GetFileName() const
{
  return m_FileName;
}


//-----------------------------------------------------------------------------
int Exception::GetLineNumber() const
{
  return m_LineNumber;
}


//-----------------------------------------------------------------------------
std::string Exception::GetDescription() const
{
  return m_Description;
}


//-----------------------------------------------------------------------------
void Exception::SetDescription(const std::string& desc)
{
  m_Description = desc;
}


//-----------------------------------------------------------------------------
const char* Exception::What()
{
  return m_Description.c_str();
}

} // end namespace
