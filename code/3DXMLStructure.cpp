/*
Open Asset Import Library (assimp)
----------------------------------------------------------------------

Copyright (c) 2006-2013, assimp team
All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the
following conditions are met:

* Redistributions of source code must retain the above
copyright notice, this list of conditions and the
following disclaimer.

* Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the
following disclaimer in the documentation and/or other
materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
contributors may be used to endorse or promote products
derived from this software without specific prior
written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------
*/

/** @file 3DXMLParser.cpp
 *  @brief Implementation of the 3DXML parser helper
 */

#include "AssimpPCH.h"

#ifndef ASSIMP_BUILD_NO_3DXML_IMPORTER
#ifndef ASSIMP_BUILD_NO_Q3BSP_IMPORTER

#include "3DXMLStructure.h"

#include <algorithm>

namespace Assimp {

	// ------------------------------------------------------------------------------------------------
	_3DXMLStructure::URI::URI() : uri(""), external(false), has_id(false), filename(""), extension(""), id(0) {
	
	}

	// ------------------------------------------------------------------------------------------------
	_3DXMLStructure::ID::ID(std::string _filename, unsigned int _id) : filename(_filename), id(_id) {
	
	}
	
	// ------------------------------------------------------------------------------------------------
	bool _3DXMLStructure::ID::operator==(const ID& other) const {
		return id == other.id && filename.compare(other.filename) == 0;
	}

	// ------------------------------------------------------------------------------------------------
	bool _3DXMLStructure::ID::operator<(const ID& other) const {
		int comp = filename.compare(other.filename);
		return comp < 0 || (comp == 0 && id < other.id);
	}

	// ------------------------------------------------------------------------------------------------
	_3DXMLStructure::Reference3D::Reference3D() : id(0), has_name(false), name(""), nb_references(0) {
	
	}

	// ------------------------------------------------------------------------------------------------
	_3DXMLStructure::ReferenceRep::ReferenceRep() : id(0), has_name(false), name(""), meshes(), index_begin(0), index_end(0) {
	
	}

	// ------------------------------------------------------------------------------------------------
	_3DXMLStructure::Instance3D::Instance3D() : id(0), has_name(false), node(new aiNode()), instance_of(NULL) {
	
	}

	// ------------------------------------------------------------------------------------------------
	_3DXMLStructure::InstanceRep::InstanceRep() : id(0), has_name(false), name(""), instance_of(NULL) {
	
	}

	// ------------------------------------------------------------------------------------------------
	_3DXMLStructure::MaterialApplication::MaterialApplication() : channel(0), two_sided(false), operation(REPLACE), materials() {

	}

	// ------------------------------------------------------------------------------------------------
	bool _3DXMLStructure::MaterialApplication::operator==(const MaterialApplication& other) const {
		return channel == other.channel && two_sided == other.two_sided && operation == other.operation && std::equal(materials.begin(), materials.end(), other.materials.begin());
	}

	// ------------------------------------------------------------------------------------------------
	bool _3DXMLStructure::MaterialApplication::operator<(const MaterialApplication& other) const {
		return channel < other.channel || (
			channel == other.channel && two_sided < other.two_sided || (
				two_sided == other.two_sided && operation < other.operation || (
					operation == other.operation && less(materials, other.materials)
				)
			)
		);
	}

	// ------------------------------------------------------------------------------------------------
	_3DXMLStructure::SurfaceAttributes::SurfaceAttributes() : color(), materials() {
	
	}

	// ------------------------------------------------------------------------------------------------
	bool _3DXMLStructure::SurfaceAttributes::operator<(const SurfaceAttributes& other) const {
		return color < other.color || (
			color == other.color && less(materials, other.materials)
		);
	}

	// ------------------------------------------------------------------------------------------------
	_3DXMLStructure::_3DXMLStructure(aiScene* _scene) : scene(_scene), references(), root_index(0), has_root_index(false) {
	
	}

} // Namespace Assimp

#endif // ASSIMP_BUILD_NO_Q3BSP_IMPORTER
#endif // ASSIMP_BUILD_NO_3DXML_IMPORTER