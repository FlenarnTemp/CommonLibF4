#pragma once

#include "RE/I/ImageSpaceData.h"
#include "RE/I/ImageSpaceLUTData.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiPointer.h"
#include "RE/N/NiRect.h"
#include "RE/N/NiTArray.h"

namespace RE
{
	class BSTriShape;
	class ImageSpaceEffect;

	class ImageSpaceManager
	{
	public:
		enum class ImageSpaceEffectEnum
		{
			EFFECT_WORLD_CAMERA = 0,
			EFFECT_TEMPORAL_AA_PRE_HDR = 1,
			EFFECT_SUNBEAMS = 2,
			EFFECT_HDR = 3,
			EFFECT_HDR_CS = 4,
			EFFECT_REFRACTION = 5,
			EFFECT_DEPTH_OF_FIELD = 6,
			EFFECT_DEPTH_OF_FIELD_SPLIT_SCREEN = 7,
			EFFECT_RADIAL_BLUR = 8,
			EFFECT_FULLSCREEN_BLUR = 9,
			EFFECT_MOTIONBLUR = 10,
			EFFECT_GETHIT = 11,
			EFFECT_VATS_TARGET = 12,
			EFFECT_FULLSCREEN_COLOR = 13,
			EFFECT_SHADER_GAMMA_CORRECT = 14,
			EFFECT_SHADER_GAMMA_CORRECT_LUT = 15,
			EFFECT_SHADER_GAMMA_CORRECT_RESIZE = 16,
			EFFECT_SHADER_FXAA = 17,
			EFFECT_TEMPORAL_AA = 18,
			EFFECT_TEMPORAL_OLD_AA = 19,
			EFFECT_BOKEH_DEPTH_OF_FIELD = 20,
			EFFECT_UPSAMPLE_DYNAMIC_RESOLUTION = 21,
			EFFECT_ENDOFFRAME_END = 22,
			EFFECT_MAP = EFFECT_ENDOFFRAME_END,
			EFFECT_BLUR_START = 23,
			EFFECT_BLUR3 = EFFECT_BLUR_START,
			EFFECT_BLUR5 = 24,
			EFFECT_BLUR7 = 25,
			EFFECT_BLUR9 = 26,
			EFFECT_BLUR11 = 27,
			EFFECT_BLUR13 = 28,
			EFFECT_BLUR15 = 29,
			EFFECT_BLUR_END = EFFECT_BLUR15,
			EFFECT_NONHDR_BLUR3 = 30,
			EFFECT_NONHDR_BLUR5 = 31,
			EFFECT_NONHDR_BLUR7 = 32,
			EFFECT_NONHDR_BLUR9 = 33,
			EFFECT_NONHDR_BLUR11 = 34,
			EFFECT_NONHDR_BLUR13 = 35,
			EFFECT_NONHDR_BLUR15 = 36,
			EFFECT_BRIGHTPASS_BLUR3 = 37,
			EFFECT_BRIGHTPASS_BLUR5 = 38,
			EFFECT_BRIGHTPASS_BLUR7 = 39,
			EFFECT_BRIGHTPASS_BLUR9 = 40,
			EFFECT_BRIGHTPASS_BLUR11 = 41,
			EFFECT_BRIGHTPASS_BLUR13 = 42,
			EFFECT_BRIGHTPASS_BLUR15 = 43,
			EFFECT_BRIGHTPASS_HDR_BLUR15_320x180CS = 44,
			EFFECT_BRIGHTPASS_HDR_BLUR15_480x270CS = 45,
			EFFECT_BRIGHTPASS_HDR_BLUR15_1024x1024CS = 46,
			EFFECT_BLUR_CS_START = 47,
			EFFECT_BLUR3_480x270CS = EFFECT_BLUR_CS_START,
			EFFECT_BLUR5_480x270CS = 48,
			EFFECT_BLUR7_480x270CS = 49,
			EFFECT_BLUR9_480x270CS = 50,
			EFFECT_BLUR11_480x270CS = 51,
			EFFECT_BLUR13_480x270CS = 52,
			EFFECT_BLUR15_480x270CS = 53,
			EFFECT_BLUR_CS_END = EFFECT_BLUR15_480x270CS,
			EFFECT_BRIGHTPASS_BLUR3_480x270CS = 54,
			EFFECT_BRIGHTPASS_BLUR5_480x270CS = 55,
			EFFECT_BRIGHTPASS_BLUR7_480x270CS = 56,
			EFFECT_BRIGHTPASS_BLUR9_480x270CS = 57,
			EFFECT_BRIGHTPASS_BLUR11_480x270CS = 58,
			EFFECT_BRIGHTPASS_BLUR13_480x270CS = 59,
			EFFECT_BRIGHTPASS_BLUR15_480x270CS = 60,
			EFFECT_WATER_DISPLACEMENT = 61,
			EFFECT_NOISE = 62,
			EFFECT_RAINSPLASH = 63,
			EFFECT_VLS_LIGHT = 64,
			EFFECT_VLS = 65,
			EFFECT_PIPBOY_SCREEN = 66,
			EFFECT_HUD_GLASS = 67,
			EFFECT_MOD_MENU = 68,
			EFFECT_AO = 69,
			EFFECT_SAO = 70,
			EFFECT_SAO_CS = 71,
			EFFECT_TOP_LEVEL_END = 72,
			EFFECT_NIGHTVISION = EFFECT_TOP_LEVEL_END,
			EFFECT_END = EFFECT_TOP_LEVEL_END,
			EFFECT_SHADER_START = 72,
			EFFECT_SHADER_COPY = EFFECT_SHADER_START,
			EFFECT_SHADER_COPY_SCALE_BIAS = 73,
			EFFECT_SHADER_COPY_VIS_ALPHA = 74,
			EFFECT_SHADER_GREYSCALE = 75,
			EFFECT_SHADER_DOWNSAMPLE_DEPTH = 76,
			EFFECT_SHADER_COPY_STENCIL = 77,
			EFFECT_SHADER_COPY_WATER_MASK = 78,
			EFFECT_SHADER_COPY_SHADOWMAPTOARRAY = 79,
			EFFECT_SHADER_REFRACTION = 80,
			EFFECT_SHADER_DOUBLEVIS = 81,
			EFFECT_SHADER_TEXTUREMASK = 82,
			EFFECT_SHADER_MAP = 83,
			EFFECT_SHADER_WORLD_CAMERA = 84,
			EFFECT_SHADER_WORLD_CAMERA_NO_SKY_BLUR = 85,
			EFFECT_SHADER_DEPTH_OF_FIELD = 86,
			EFFECT_SHADER_DEPTH_OF_FIELD_FOGGED = 87,
			EFFECT_SHADER_DEPTH_OF_FIELD_SPLIT_SCREEN = 88,
			EFFECT_SHADER_BOKEH_DEPTH_OF_FIELD_PASS1 = 89,
			EFFECT_SHADER_BOKEH_DEPTH_OF_FIELD_PASS2 = 90,
			EFFECT_SHADER_BOKEH_DEPTH_OF_FIELD_PASS3 = 91,
			EFFECT_SHADER_BOKEH_DEPTH_OF_FIELD_PASS4 = 92,
			EFFECT_SHADER_BOKEH_DEPTH_OF_FIELD_PASS4_FOGGED = 93,
			EFFECT_SHADER_DISTANT_BLUR = 94,
			EFFECT_SHADER_DISTANT_BLUR_FOGGED = 95,
			EFFECT_SHADER_RADIAL_BLUR = 96,
			EFFECT_SHADER_RADIAL_BLUR_MED = 97,
			EFFECT_SHADER_RADIAL_BLUR_HIGH = 98,
			EFFECT_SHADER_HDR_BLENDINSHADER_CINEMATIC = 99,
			EFFECT_SHADER_HDR_BLENDINSHADER_CINEMATIC_FADE = 100,
			EFFECT_SHADER_HDR_DOWNSAMPLE16 = 101,
			EFFECT_SHADER_HDR_DOWNSAMPLE4 = 102,
			EFFECT_SHADER_HDR_DOWNSAMPLE16LUM = 103,
			EFFECT_SHADER_HDR_DOWNSAMPLE4RGB2LUM = 104,
			EFFECT_SHADER_HDR_DOWNSAMPLE4_LUMCLAMP = 105,
			EFFECT_SHADER_HDR_DOWNSAMPLE4_LIGHTADAPT = 106,
			EFFECT_SHADER_HDR_DOWNSAMPLE16_LUMCLAMP = 107,
			EFFECT_SHADER_HDR_DOWNSAMPLE16_LIGHTADAPT = 108,
			EFFECT_SHADER_HDR_DOWNSAMPLE4CS = 109,
			EFFECT_SHADER_HDR_DOWNSAMPLE64RGB2LUMCS = 110,
			EFFECT_SHADER_HDR_DOWNSAMPLE4LUMCS = 111,
			EFFECT_SHADER_HDR_DOWNSAMPLE16LUMCS = 112,
			EFFECT_SHADER_HDR_DOWNSAMPLE2_LIGHTADAPTCS = 113,
			EFFECT_SHADER_BLUR_START = 114,
			EFFECT_SHADER_BLUR3 = EFFECT_SHADER_BLUR_START,
			EFFECT_SHADER_BLUR5 = 115,
			EFFECT_SHADER_BLUR7 = 116,
			EFFECT_SHADER_BLUR9 = 117,
			EFFECT_SHADER_BLUR11 = 118,
			EFFECT_SHADER_BLUR13 = 119,
			EFFECT_SHADER_BLUR15 = 120,
			EFFECT_SHADER_BLUR_END = 120,
			EFFECT_SHADER_HDR_BLURX15_320CS = 121,
			EFFECT_SHADER_HDR_BLURX15_480CS = 122,
			EFFECT_SHADER_HDR_BLURX15_1024CS = 123,
			EFFECT_SHADER_NONHDR_BLUR_START = 124,
			EFFECT_SHADER_NONHDR_BLUR3 = 124,
			EFFECT_SHADER_NONHDR_BLUR5 = 125,
			EFFECT_SHADER_NONHDR_BLUR7 = 126,
			EFFECT_SHADER_NONHDR_BLUR9 = 127,
			EFFECT_SHADER_NONHDR_BLUR11 = 128,
			EFFECT_SHADER_NONHDR_BLUR13 = 129,
			EFFECT_SHADER_NONHDR_BLUR15 = 130,
			EFFECT_SHADER_NONHDR_BLUR_END = EFFECT_SHADER_NONHDR_BLUR15,
			EFFECT_SHADER_BRIGHTPASS_BLUR_START = 131,
			EFFECT_SHADER_BRIGHTPASS_BLUR3 = EFFECT_SHADER_BRIGHTPASS_BLUR_START,
			EFFECT_SHADER_BRIGHTPASS_BLUR5 = 132,
			EFFECT_SHADER_BRIGHTPASS_BLUR7 = 133,
			EFFECT_SHADER_BRIGHTPASS_BLUR9 = 134,
			EFFECT_SHADER_BRIGHTPASS_BLUR11 = 135,
			EFFECT_SHADER_BRIGHTPASS_BLUR13 = 136,
			EFFECT_SHADER_BRIGHTPASS_BLUR15 = 137,
			EFFECT_SHADER_BRIGHTPASS_BLUR_END = EFFECT_SHADER_BRIGHTPASS_BLUR15,
			EFFECT_SHADER_BRIGHTPASS_HDR_BLURY15_180CS = 138,
			EFFECT_SHADER_BRIGHTPASS_HDR_BLURY15_270CS = 139,
			EFFECT_SHADER_BRIGHTPASS_HDR_BLURY15_1024CS = 140,
			EFFECT_SHADER_WATER_DISPLACEMENT_START = 141,
			EFFECT_SHADER_WATER_DISPLACEMENT_CLEAR_SIMULATION = EFFECT_SHADER_WATER_DISPLACEMENT_START,
			EFFECT_SHADER_WATER_DISPLACEMENT_TEX_OFFSET = 142,
			EFFECT_SHADER_WATER_DISPLACEMENT_WADING_RIPPLE = 143,
			EFFECT_SHADER_WATER_DISPLACEMENT_RAIN_RIPPLE = 144,
			EFFECT_SHADER_WATER_DISPLACEMENT_WADING_HEIGHTMAP = 145,
			EFFECT_SHADER_WATER_DISPLACEMENT_RAIN_HEIGHTMAP = 146,
			EFFECT_SHADER_WATER_DISPLACEMENT_BLEND_HEIGHTMAPS = 147,
			EFFECT_SHADER_WATER_DISPLACEMENT_SMOOTH_HEIGHTMAP = 148,
			EFFECT_SHADER_WATER_DISPLACEMENT_NORMALS = 149,
			EFFECT_SHADER_WATER_DISPLACEMENT_END = 149,
			EFFECT_SHADER_NOISE_SCROLL_AND_BLEND = 150,
			EFFECT_SHADER_NOISE_NORMALMAP = 151,
			EFFECT_SHADER_LOCAL_MAP = 152,
			EFFECT_SHADER_LOCAL_MAP_COMPANION = 153,
			EFFECT_SHADER_ALPHA_BLEND = 154,
			EFFECT_SHADER_PIPBOY_SCREEN = 155,
			EFFECT_SHADER_HUD_GLASS = 156,
			EFFECT_SHADER_HUD_GLASS_DROPSHADOW = 157,
			EFFECT_SHADER_HUD_GLASS_BLURY = 158,
			EFFECT_SHADER_HUD_GLASS_BLURX = 159,
			EFFECT_SHADER_HUD_GLASS_MARKERS = 160,
			EFFECT_SHADER_VATS_TARGET_DEBUG = 161,
			EFFECT_SHADER_VATS_TARGET = 162,
			EFFECT_SHADER_MOD_MENU_EFFECT = 163,
			EFFECT_SHADER_MOD_MENU_GLOW_COMPOSITE = 164,
			EFFECT_SHADER_AO = 165,
			EFFECT_SHADER_AO_BLUR = 166,
			EFFECT_SHADER_VLS_SPOTLIGHT = 167,
			EFFECT_SHADER_VLS_APPLICATION = 168,
			EFFECT_SHADER_VLS_COMPOSITE = 169,
			EFFECT_SHADER_VLS_SLICE_COORD = 170,
			EFFECT_SHADER_VLS_SLICE_INTERP = 171,
			EFFECT_SHADER_VLS_SLICE_STENCIL = 172,
			EFFECT_SHADER_VLS_SLICE_SCATTER_RAY = 173,
			EFFECT_SHADER_VLS_SLICE_SCATTER_INTERP = 174,
			EFFECT_SHADER_VLS_SCATTER_ACCUM = 175,
			EFFECT_SHADER_SAO_CAMERAZ = 176,
			EFFECT_SHADER_SAO_MINIFY = 177,
			EFFECT_SHADER_SAO_RAWAO = 178,
			EFFECT_SHADER_SAO_BLUR_H = 179,
			EFFECT_SHADER_SAO_BLUR_V = 180,
			EFFECT_SHADER_SAO_RAWAO_EDITOR = 181,
			EFFECT_SHADER_SAO_CAMERAZ_CS = 182,
			EFFECT_SHADER_SAO_MINIFY_CS = 183,
			EFFECT_SHADER_SAO_CAMERAZ_AND_MIPS_CS = 184,
			EFFECT_SHADER_SAO_MIPS_CS = 185,
			EFFECT_SHADER_SAO_RAWAO_CS = 186,
			EFFECT_SHADER_SAO_BLUR_H_CS = 187,
			EFFECT_SHADER_SAO_BLUR_V_CS = 188,
			EFFECT_SHADER_MOTIONBLUR = 189,
			EFFECT_SHADER_TEMPORAL_AA = 190,
			EFFECT_SHADER_TEMPORAL_AA_MASKED = 191,
			EFFECT_SHADER_TEMPORAL_AA_POWERARMOR = 192,
			EFFECT_SHADER_GAMMA_LINEARIZE = 193,
			EFFECT_SHADER_SUNBEAMS = 194,
			EFFECT_SHADER_SSR_PREPASS = 195,
			EFFECT_SHADER_SSR_RAYTRACING = 196,
			EFFECT_SHADER_SSR_BLURH = 197,
			EFFECT_SHADER_SSR_BLURV = 198,
			EFFECT_SHADER_LENSFLARE = 199,
			EFFECT_SHADER_RAINSPLASH_SPAWN = 200,
			EFFECT_SHADER_RAINSPLASH_UPDATE = 201,
			EFFECT_SHADER_RAINSPLASH_DRAW = 202,
			EFFECT_SHADER_LENSFLAREVISIBILITY = 203,
			EFFECT_SHADER_UPSAMPLE_DYNAMIC_RESOLUTION = 204,
			EFFECT_SHADER_FULLSCREEN_COLOR = 205,
			EFFECT_SHADER_HUDGLASS_CLEAR = 206,
			EFFECT_SHADER_HUDGLASS_COPY = 207,
			EFFECT_SHADER_CS_V_START = 208,
			EFFECT_SHADER_ISBlur3_V_270_CS = 208,
			EFFECT_SHADER_ISBlur5_V_270_CS = 209,
			EFFECT_SHADER_ISBlur7_V_270_CS = 210,
			EFFECT_SHADER_ISBlur9_V_270_CS = 211,
			EFFECT_SHADER_ISBlur11_V_270_CS = 212,
			EFFECT_SHADER_ISBlur13_V_270_CS = 213,
			EFFECT_SHADER_ISBlur15_V_270_CS = 214,
			EFFECT_SHADER_CS_V_END = 215,
			EFFECT_SHADER_CS_H_START = 216,
			EFFECT_SHADER_ISBlur3_H_480_CS = EFFECT_SHADER_CS_H_START,
			EFFECT_SHADER_ISBlur5_H_480_CS = 217,
			EFFECT_SHADER_ISBlur7_H_480_CS = 218,
			EFFECT_SHADER_ISBlur9_H_480_CS = 219,
			EFFECT_SHADER_ISBlur11_H_480_CS = 220,
			EFFECT_SHADER_ISBlur13_H_480_CS = 221,
			EFFECT_SHADER_ISBlur15_H_480_CS = 222,
			EFFECT_SHADER_CS_H_END = 223,
			EFFECT_SHADER_BRIGHTPASS_CS_V_START = 224,
			EFFECT_SHADER_ISBrightPassBlur3_V_270_CS = 224,
			EFFECT_SHADER_ISBrightPassBlur5_V_270_CS = 225,
			EFFECT_SHADER_ISBrightPassBlur7_V_270_CS = 226,
			EFFECT_SHADER_ISBrightPassBlur9_V_270_CS = 227,
			EFFECT_SHADER_ISBrightPassBlur11_V_270_CS = 228,
			EFFECT_SHADER_ISBrightPassBlur13_V_270_CS = 229,
			EFFECT_SHADER_ISBrightPassBlur15_V_270_CS = 230,
			EFFECT_SHADER_BRIGHTPASS_CS_V_END = 231
		};

		[[nodiscard]] static ImageSpaceManager* GetSingleton()
		{
			static REL::Relocation<ImageSpaceManager**> singleton{ ID::ImageSpaceManager::Singleton };
			return *singleton;
		}

		// members
		NiRect<std::int32_t>                 scissorRect;               // 000
		NiTPrimitiveArray<ImageSpaceEffect*> effectList;                // 010
		NiPointer<BSTriShape>                screenTriShape;            // 028
		NiPointer<BSTriShape>                screenTriShapeColors;      // 030
		NiPointer<BSTriShape>                dynamicScreenTriShape;     // 038
		NiPointer<BSTriShape>                partialScreenTriShape;     // 040
		bool                                 enablePartialRender;       // 048
		std::int32_t                         mainTarget;                // 04C
		NiColorA                             refractionTint;            // 050
		const ImageSpaceBaseData*            baseData;                  // 060
		const ImageSpaceBaseData*            overRideBaseData;          // 068
		const ImageSpaceBaseData*            underwaterBaseData;        // 070
		ImageSpaceBaseData*                  consoleBaseData;           // 078
		ImageSpaceData                       currentEOFData;            // 080
		ImageSpaceLUTData                    lutData;                   // 130
		ImageSpaceLUTData*                   overrideLUTData;           // 1A0
		float                                motionBlurIntensity;       // 1A8
		float                                motionBlurMaxBlur;         // 1AC
		std::uint32_t                        forceNoBokehDepthOfField;  // 1B0
		bool                                 isReady;                   // 1B4
		bool                                 saveTarget;                // 1B5
		bool                                 useBokehDepthOfField;      // 1B6
	};
	static_assert(sizeof(ImageSpaceManager) == 0x1B8);
}
