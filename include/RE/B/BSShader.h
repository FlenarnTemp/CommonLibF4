#pragma once

#include "RE/B/BSGraphics.h"
#include "RE/B/BSReloadShaderI.h"
#include "RE/B/BSShaderTechniqueIDMap.h"
#include "RE/N/NiRefObject.h"

namespace RE
{
	class BSRenderPass;
	class BSShaderMaterial;

	class __declspec(novtable) BSShader :
		public NiRefObject,     // 000
		public BSReloadShaderI  // 010
	{
	public:
		static constexpr auto RTTI{ RTTI::BSShader };
		static constexpr auto VTABLE{ VTABLE::BSShader };

		// add
		virtual bool          SetupTechnique(std::uint32_t a_currentPass) = 0;                                            // 02
		virtual void          RestoreTechnique(std::uint32_t a_currentPass) = 0;                                          // 03
		virtual void          SetupMaterial([[maybe_unused]] const BSShaderMaterial* a_material) { return; }              // 04
		virtual void          RestoreMaterial([[maybe_unused]] const BSShaderMaterial* a_material) { return; }            // 05
		virtual void          SetupMaterialSecondary([[maybe_unused]] const BSShaderMaterial* a_material) { return; }     // 06
		virtual void          SetupGeometry(BSRenderPass* a_currentPass) = 0;                                             // 07
		virtual void          RestoreGeometry(BSRenderPass* a_currentPass) = 0;                                           // 08
		virtual void          GetTechniqueName(std::uint32_t a_techniqueID, char* a_buffer, std::uint32_t a_bufferSize);  // 09
		virtual void          RecreateRendererData() { return; }                                                          // 0A
		virtual void          ReloadShaders(bool a_clear);                                                                // 0B
		virtual std::uint32_t GetBonesVertexConstant() const { return 0; }                                                // 0C

		// members
		std::int32_t                                                shaderType;      // 018
		BSShaderTechniqueIDMap::MapType<BSGraphics::VertexShader*>  vertexShaders;   // 020
		BSShaderTechniqueIDMap::MapType<BSGraphics::HullShader*>    hullShaders;     // 050
		BSShaderTechniqueIDMap::MapType<BSGraphics::DomainShader*>  domainShaders;   // 080
		BSShaderTechniqueIDMap::MapType<BSGraphics::PixelShader*>   pixelShaders;    // 0B0
		BSShaderTechniqueIDMap::MapType<BSGraphics::ComputeShader*> computeShaders;  // 0E0
		const char*                                                 fxpFilename;     // 110
	};
	static_assert(sizeof(BSShader) == 0x118);
}
