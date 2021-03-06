//----------------------------------------------------------------------------
//Yume Engine
//Copyright (C) 2015  arkenthera
//This program is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or
//(at your option) any later version.
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along
//with this program; if not, write to the Free Software Foundation, Inc.,
//51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/
//----------------------------------------------------------------------------
//
// File : YumeGraphics.h
// Date : 2.19.2016
// Comments :
//
//----------------------------------------------------------------------------
#ifndef __YumeD3D11ShaderVariation_h__
#define __YumeD3D11ShaderVariation_h__
//----------------------------------------------------------------------------
#include "YumeD3D11Required.h"

#include "Renderer/YumeRendererDefs.h"
#include "Renderer/YumeGpuResource.h"
#include "Renderer/YumeShaderVariation.h"
#include "YumeD3D11GpuResource.h"
//----------------------------------------------------------------------------
namespace YumeEngine
{
	
	class YumeConstantBuffer;
	class YumeShader;

	/// %Shader parameter definition.
	struct ShaderParameter
	{
		/// Construct with defaults.
		ShaderParameter():
			type_(VS),
			buffer_(0),
			offset_(0),
			size_(0),
			bufferPtr_(0)
		{
		}

		/// Construct with parameters.
		ShaderParameter(ShaderType type,const YumeString& name,unsigned buffer,unsigned offset,unsigned size,YumeConstantBuffer* ptr = 0):
			type_(type),
			name_(name),
			buffer_(buffer),
			offset_(offset),
			size_(size),
			bufferPtr_(ptr)
		{
		}

		/// %Shader type.
		ShaderType type_;
		/// Name of the parameter.
		YumeString name_;
		/// Constant buffer index.
		unsigned buffer_;
		/// Offset in constant buffer.
		unsigned offset_;
		/// Size of parameter in bytes.
		unsigned size_;
		/// Constant buffer pointer. Defined only in shader programs.
		YumeConstantBuffer* bufferPtr_;
	};

	/// Vertex or pixel shader on the GPU.
	class YumeD3DExport YumeD3D11ShaderVariation : public YumeShaderVariation,public YumeD3D11Resource
	{
	public:
		YumeD3D11ShaderVariation (YumeShader* owner,ShaderType type);
		virtual ~YumeD3D11ShaderVariation ();
		virtual void Release();

		virtual bool Create();

		ShaderType GetShaderType() const { return type_; }

		const YumeString& GetName() const { return name_; }

		YumeString GetFullName() const { return name_ + "(" + defines_ + ")"; }

		bool HasParameter(YumeHash param) const {
			return parameters_.find(param) != parameters_.end() ? true : false;
		}
		const YumeMap<YumeHash,ShaderParameter>::type& GetParameters() const { return parameters_; }
		const unsigned* GetConstantBufferSizes() const { return &constantBufferSizes_[0]; }

		void SetEntryPoint(const YumeString& entry) { shaderEntry = entry;}
	private:
		bool LoadByteCode(const YumeString& binaryShaderName);
		bool Compile();
		void ParseParameters(unsigned char* bufData,unsigned bufSize);
		void SaveByteCode(const YumeString& binaryShaderName);
		void CalculateConstantBufferSizes();

		YumeString shaderEntry;

		YumeMap<YumeHash,ShaderParameter>::type parameters_;
		unsigned constantBufferSizes_[MAX_SHADER_PARAMETER_GROUPS];

	};
}


//----------------------------------------------------------------------------
#endif
