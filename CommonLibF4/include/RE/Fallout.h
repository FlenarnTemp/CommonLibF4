#pragma once

#include "F4SE/Impl/PCH.h"

#include "RE/Bethesda/AITimeStamp.h"
#include "RE/Bethesda/Actor.h"
#include "RE/Bethesda/ActorValueInfo.h"
#include "RE/Bethesda/Atomic.h"
#include "RE/Bethesda/BGSBaseAliases.h"
#include "RE/Bethesda/BGSBodyPartDefs.h"
#include "RE/Bethesda/BGSCharacterMorph.h"
#include "RE/Bethesda/BGSCharacterTint.h"
#include "RE/Bethesda/BGSCreatedObjectManager.h"
#include "RE/Bethesda/BGSDefaultObjectManager.h"
#include "RE/Bethesda/BGSHeadPart.h"
#include "RE/Bethesda/BGSInventoryInterface.h"
#include "RE/Bethesda/BGSInventoryItem.h"
#include "RE/Bethesda/BGSMod.h"
#include "RE/Bethesda/BGSPrimitive.h"
#include "RE/Bethesda/BGSStoryManagerTreeForm.h"
#include "RE/Bethesda/BGSTextureSet.h"
#include "RE/Bethesda/BSBound.h"
#include "RE/Bethesda/BSContainer.h"
#include "RE/Bethesda/BSExtraData.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSGraphics.h"
#include "RE/Bethesda/BSHavok.h"
#include "RE/Bethesda/BSInputDeviceManager.h"
#include "RE/Bethesda/BSInputEventReceiver.h"
#include "RE/Bethesda/BSInputEventUser.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSMTAManager.h"
#include "RE/Bethesda/BSPointerHandle.h"
#include "RE/Bethesda/BSPreCulledObjects.h"
#include "RE/Bethesda/BSResource.h"
#include "RE/Bethesda/BSScaleformManager.h"
#include "RE/Bethesda/BSScript.h"
#include "RE/Bethesda/BSScriptUtil.h"
#include "RE/Bethesda/BSShader.h"
#include "RE/Bethesda/BSSoundHandle.h"
#include "RE/Bethesda/BSSpring.h"
#include "RE/Bethesda/BSStringPool.h"
#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/BSSystemFile.h"
#include "RE/Bethesda/BSSystemFileStreamer.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTBTree.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTFreeList.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTInterpolator.h"
#include "RE/Bethesda/BSTList.h"
#include "RE/Bethesda/BSTMessageQueue.h"
#include "RE/Bethesda/BSTObjectArena.h"
#include "RE/Bethesda/BSTOptional.h"
#include "RE/Bethesda/BSTPoint.h"
#include "RE/Bethesda/BSTSingleton.h"
#include "RE/Bethesda/BSTSmallIndexScatterTable.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTTuple.h"
#include "RE/Bethesda/BSTextureSet.h"
#include "RE/Bethesda/BSTextureStreamer.h"
#include "RE/Bethesda/BSTimer.h"
#include "RE/Bethesda/CELLJobs.h"
#include "RE/Bethesda/CRC.h"
#include "RE/Bethesda/Calendar.h"
#include "RE/Bethesda/Console.h"
#include "RE/Bethesda/ControlMap.h"
#include "RE/Bethesda/Events.h"
#include "RE/Bethesda/FavoritesManager.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/FormFactory.h"
#include "RE/Bethesda/FormUtil.h"
#include "RE/Bethesda/GameScript.h"
#include "RE/Bethesda/IMenu.h"
#include "RE/Bethesda/IMovementInterface.h"
#include "RE/Bethesda/InputDevice.h"
#include "RE/Bethesda/InputEvent.h"
#include "RE/Bethesda/MagicItems.h"
#include "RE/Bethesda/MemoryManager.h"
#include "RE/Bethesda/Movement.h"
#include "RE/Bethesda/NavMesh.h"
#include "RE/Bethesda/NavMeshInfoMap.h"
#include "RE/Bethesda/PlayerCharacter.h"
#include "RE/Bethesda/PlayerControls.h"
#include "RE/Bethesda/PowerUtils.h"
#include "RE/Bethesda/Projectiles.h"
#include "RE/Bethesda/SWFToCodeFunctionHandler.h"
#include "RE/Bethesda/Script.h"
#include "RE/Bethesda/SendHUDMessage.h"
#include "RE/Bethesda/Settings.h"
#include "RE/Bethesda/SplineUtils.h"
#include "RE/Bethesda/TESBoundAnimObjects.h"
#include "RE/Bethesda/TESBoundObjects.h"
#include "RE/Bethesda/TESCamera.h"
#include "RE/Bethesda/TESCombatStyle.h"
#include "RE/Bethesda/TESCondition.h"
#include "RE/Bethesda/TESDataHandler.h"
#include "RE/Bethesda/TESFaction.h"
#include "RE/Bethesda/TESFile.h"
#include "RE/Bethesda/TESForms.h"
#include "RE/Bethesda/TESObjectREFRs.h"
#include "RE/Bethesda/TESPackages.h"
#include "RE/Bethesda/TESRace.h"
#include "RE/Bethesda/TESWaterForm.h"
#include "RE/Bethesda/TESWorldSpace.h"
#include "RE/Bethesda/UI.h"
#include "RE/Bethesda/UIMessage.h"
#include "RE/Bethesda/UIMessageQueue.h"
#include "RE/Bethesda/UserEvents.h"
#include "RE/Bethesda/Workshop.h"
#include "RE/Bethesda/bhkCharacterController.h"
#include "RE/Havok/hkArray.h"
#include "RE/Havok/hkBaseObject.h"
#include "RE/Havok/hkBaseTypes.h"
#include "RE/Havok/hkBlockStream.h"
#include "RE/Havok/hkHandle.h"
#include "RE/Havok/hkLifoAllocator.h"
#include "RE/Havok/hkMemoryAllocator.h"
#include "RE/Havok/hkMemoryRouter.h"
#include "RE/Havok/hkMemorySystem.h"
#include "RE/Havok/hkRefPtr.h"
#include "RE/Havok/hkReferencedObject.h"
#include "RE/Havok/hkSimdFloat.h"
#include "RE/Havok/hkVector4.h"
#include "RE/Havok/hknpAllHitsCollector.h"
#include "RE/Havok/hknpBodyId.h"
#include "RE/Havok/hknpCharacterContext.h"
#include "RE/Havok/hknpCharacterState.h"
#include "RE/Havok/hknpCharacterSurfaceInfo.h"
#include "RE/Havok/hknpClosestUniqueBodyIdHitCollector.h"
#include "RE/Havok/hknpCollisionQueryCollector.h"
#include "RE/Havok/hknpCollisionResult.h"
#include "RE/Havok/hknpMaterialId.h"
#include "RE/Havok/hknpShape.h"
#include "RE/Havok/hknpUniqueBodyIdHitCollector.h"
#include "RE/NetImmerse/NiAVObject.h"
#include "RE/NetImmerse/NiAlphaProperty.h"
#include "RE/NetImmerse/NiBinaryStream.h"
#include "RE/NetImmerse/NiBound.h"
#include "RE/NetImmerse/NiCollisionObject.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiExtraData.h"
#include "RE/NetImmerse/NiFile.h"
#include "RE/NetImmerse/NiFlags.h"
#include "RE/NetImmerse/NiMatrix3.h"
#include "RE/NetImmerse/NiNode.h"
#include "RE/NetImmerse/NiObject.h"
#include "RE/NetImmerse/NiObjectNET.h"
#include "RE/NetImmerse/NiPoint2.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiPoint4.h"
#include "RE/NetImmerse/NiProperty.h"
#include "RE/NetImmerse/NiQuaternion.h"
#include "RE/NetImmerse/NiRTTI.h"
#include "RE/NetImmerse/NiRect.h"
#include "RE/NetImmerse/NiRefObject.h"
#include "RE/NetImmerse/NiShadeProperty.h"
#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/NetImmerse/NiStream.h"
#include "RE/NetImmerse/NiTArray.h"
#include "RE/NetImmerse/NiTCollection.h"
#include "RE/NetImmerse/NiTDefaultAllocator.h"
#include "RE/NetImmerse/NiTLargeArray.h"
#include "RE/NetImmerse/NiTList.h"
#include "RE/NetImmerse/NiTListBase.h"
#include "RE/NetImmerse/NiTMap.h"
#include "RE/NetImmerse/NiTMapBase.h"
#include "RE/NetImmerse/NiTPointerAllocator.h"
#include "RE/NetImmerse/NiTPointerListBase.h"
#include "RE/NetImmerse/NiTPointerMap.h"
#include "RE/NetImmerse/NiTexture.h"
#include "RE/NetImmerse/NiTimeController.h"
#include "RE/NetImmerse/NiTransform.h"
#include "RE/RTTI.h"
#include "RE/Scaleform/GFx/GFx_ASMovieRootBase.h"
#include "RE/Scaleform/GFx/GFx_Loader.h"
#include "RE/Scaleform/GFx/GFx_Log.h"
#include "RE/Scaleform/GFx/GFx_Player.h"
#include "RE/Scaleform/GFx/GFx_Resource.h"
#include "RE/Scaleform/GFx/GFx_Types.h"
#include "RE/Scaleform/Kernel/SF_AllocInfo.h"
#include "RE/Scaleform/Kernel/SF_Allocator.h"
#include "RE/Scaleform/Kernel/SF_Array.h"
#include "RE/Scaleform/Kernel/SF_Atomic.h"
#include "RE/Scaleform/Kernel/SF_List.h"
#include "RE/Scaleform/Kernel/SF_Log.h"
#include "RE/Scaleform/Kernel/SF_Memory.h"
#include "RE/Scaleform/Kernel/SF_MemoryHeap.h"
#include "RE/Scaleform/Kernel/SF_RefCount.h"
#include "RE/Scaleform/Kernel/SF_Stats.h"
#include "RE/Scaleform/Kernel/SF_SysAlloc.h"
#include "RE/Scaleform/Kernel/SF_System.h"
#include "RE/Scaleform/Kernel/SF_Threads.h"
#include "RE/Scaleform/Render/Render_Color.h"
#include "RE/Scaleform/Render/Render_Constants.h"
#include "RE/Scaleform/Render/Render_Containers.h"
#include "RE/Scaleform/Render/Render_Context.h"
#include "RE/Scaleform/Render/Render_Matrix2x4.h"
#include "RE/Scaleform/Render/Render_Matrix3x4.h"
#include "RE/Scaleform/Render/Render_Matrix4x4.h"
#include "RE/Scaleform/Render/Render_ThreadCommandQueue.h"
#include "RE/Scaleform/Render/Render_TreeNode.h"
#include "RE/Scaleform/Render/Render_Types2D.h"
#include "RE/Scaleform/Render/Render_Viewport.h"
